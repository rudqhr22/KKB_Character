#include "AMapObj.h"
#include "ObjectManager.h"
#include "ATexture.h"


bool AMapObj::Load(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const TCHAR* szLoadName, const TCHAR* pLoadShaderFile, bool bThread)
{
	TCHAR szFileName[MAX_PATH];
	TCHAR Drive[MAX_PATH];
	TCHAR Dir[MAX_PATH];
	TCHAR FName[MAX_PATH];
	TCHAR Ext[MAX_PATH];

	if (szLoadName)
	{
		_tsplitpath(szLoadName, Drive, Dir, FName, Ext);
		Ext[4] = 0;
	}
	memset(szFileName, 0, sizeof(TCHAR) * MAX_PATH);
	_stprintf_s(szFileName, _T("%s%s"), Drive, Dir);

	FILE	*fp;
	_tfopen_s(&fp, szLoadName, _T("rb"));
	_ASSERT(fp != NULL);
	fread(&m_Scene, sizeof(AScene), 1, fp);

	TCHAR szBuffer[128] = { 0, };
	UINT convertedChars = 0;

	for (int iter = 0; iter < m_Scene.iNumMesh; iter++)
	{
		AMesh* pMesh = new AMesh();
		SkinMesh* pData = new SkinMesh();

		TCHAR szName[256] = { 0,0 };
		TCHAR szParentName[256] = { 0,0 };

		// 노드 이름
		int iLength = 0;
		fread(&iLength, sizeof(int), 1, fp);
		fread(szName, sizeof(TCHAR)*iLength, 1, fp);

		pMesh->m_strNodeName = szName;
		// 노드 부모 이름
		fread(&iLength, sizeof(int), 1, fp);
		if (iLength > 0)
		{
			fread(szParentName, sizeof(TCHAR)*iLength, 1, fp);
			pMesh->m_strParentName = szParentName;
		}
		// 월드 행렬
		fread(&pMesh->m_matLocalMesh, sizeof(D3DXMATRIX), 1, fp);
		//m_matLocal = pMesh->m_matLocal;

		fread(&pMesh->m_iNumMtrl, sizeof(int), 1, fp);
		if (pMesh->m_iNumMtrl <= 0)
		{
			LoadMesh(fp, pDevice, pMesh, pData, szFileName);
			//SAFE_NEW_ARRAY(pMesh->m_pDrawVertex, PNCT5_VERTEX, pMesh->m_iNumVertexs );
		}
		else
		{
			for (int iter = 0; iter < pMesh->m_iNumMtrl; iter++)
			{
				AMesh*  pSubMesh = new AMesh();
				SkinMesh*  pSubData = new SkinMesh();
				if (LoadMesh(fp, pDevice, pSubMesh, pSubData, szFileName))
				{
					SAFE_NEW_ARRAY(pSubData->m_pDrawVertex, PNCT5_VERTEX, pSubMesh->m_iNumVertexs);
					pMesh->m_pSubMesh.push_back(pSubMesh);
					pData->m_pSubMesh.push_back(pSubData);
				}
			}
		}
		m_pMesh.push_back(pMesh);
		m_pSkinMeshList.push_back(pData);
	}

	// 드레스 포즈의 각 바이패드 행렬 로드
	int iNumMatrix;
	fread(&iNumMatrix, sizeof(int), 1, fp);
	m_matBipedList.resize(iNumMatrix);
	for (int iMat = 0; iMat < iNumMatrix; iMat++)
	{
		fread(&m_matBipedList[iMat], sizeof(D3DXMATRIX), 1, fp);
	}

	fclose(fp);
#if 0
	for (int i = 0; i < m_pData[0]->m_VertexArray.size(); i++)
	{
		D3DXVec3TransformCoord(&m_pData[0]->m_VertexArray[i].p, &m_pData[0]->m_VertexArray[i].p,
			&m_matBipedList[m_pData[0]->m_VertexArray[i].i0.x]);
	}
#endif

	m_dxObj.m_iNumVertex = m_iMaxVertex;
	m_dxObj.m_iNumIndex = m_iMaxIndex;
	m_dxObj.m_iVertexSize = sizeof(PNCT5_VERTEX);

	if (!bThread && !Set(pDevice, pContext, pLoadShaderFile))
	{
		return false;
	}

	return true;
}




bool AMapObj::LoadMesh(FILE	*fp, ID3D11Device* pDevice, AMesh* pMesh, SkinMesh* pData, const TCHAR* szLoadFileName)
{
	char szBuffer[128] = { 0, };
	UINT convertedChars = 0;

	fread(&pMesh->m_iNumVertexs, sizeof(int), 1, fp);
	fread(&pMesh->m_iNumFace, sizeof(int), 1, fp);
	fread(&pMesh->m_iNumTex, sizeof(int), 1, fp);

	pData->m_VertexArray.resize(pMesh->m_iNumVertexs);
	pData->m_IndexArray.resize(pMesh->m_iNumFace * 3);

	fread(&pData->m_VertexArray.at(0), sizeof(PNCT5_VERTEX) * pMesh->m_iNumVertexs, 1, fp);
	fread(&pData->m_IndexArray.at(0), sizeof(unsigned int) * pMesh->m_iNumFace * 3, 1, fp);

	m_iMaxVertex += pData->m_VertexArray.size();
	m_iMaxIndex += pData->m_IndexArray.size();

	for (int itex = 0; itex < pMesh->m_iNumTex; itex++)
	{
		int iLen = _tcslen(pMesh->m_szTexName[itex]);
		fread(&iLen, sizeof(int), 1, fp);
		fread(&pMesh->m_iTexType[itex], sizeof(int), 1, fp);
		ZeroMemory(pMesh->m_szTexName[itex], sizeof(TCHAR) * 30);
		fread(pMesh->m_szTexName[itex], sizeof(TCHAR) * iLen, 1, fp);

		TCHAR szFileName[MAX_PATH];
		TCHAR Drive[MAX_PATH];
		TCHAR Dir[MAX_PATH];
		TCHAR FName[MAX_PATH];
		TCHAR Ext[MAX_PATH];
		if (szLoadFileName)
		{
			_tsplitpath(szLoadFileName, Drive, Dir, FName, Ext);
			Ext[4] = 0;
			memset(szFileName, 0, sizeof(TCHAR) * MAX_PATH);
		}
		T_STR loadFile = Drive;
		loadFile += Dir;
		loadFile += pMesh->m_szTexName[itex];
		// 디퓨즈 텍스쳐
		if (pMesh->m_iTexType[itex] == ID_BASIS_DI)
		{
			pMesh->m_iDiffuseTex = I_TEXTURE.Add(pDevice, loadFile.c_str());
		}
	}
	return true;
}


bool AMapObj::SetInputLayout(ID3D11Device* pDevice)
{
	HRESULT hr = S_OK;
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,		0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 },

		{ "TEXCOORD", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 64, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 80, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 4, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 96, D3D11_INPUT_PER_VERTEX_DATA, 0 },


	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);
	m_dxObj.g_pInputlayout.Attach(DX::CreateInputlayout(pDevice,
		m_dxObj.g_pVSBlob.Get()->GetBufferSize(),
		m_dxObj.g_pVSBlob.Get()->GetBufferPointer(), layout, numElements));
	return true;
}

bool AMapObj::Render(ID3D11DeviceContext*    pContext) noexcept
{

	PreRender(pContext);
	Draw(pContext, this);
	return true;
}

bool AMapObj::Draw(ID3D11DeviceContext*    pContext, AModel* pParent)
{
	GameObject::Render(pContext);
	for (DWORD dwObject = 0; dwObject < m_pMesh.size(); dwObject++)
	{
		auto pMesh = m_pMesh[dwObject];
		D3DXMATRIX matWorld = pMesh->m_matCalculation * pParent->GetWorldMatrix(); //pParent->m_matLocal;
		D3DXMatrixTranspose(&cbData.matWorld, &matWorld);
		SetMatrix(&m_matLocal, m_matView, m_matProj);
		UpdateConstantBuffer(pContext, pParent);
		if (pMesh->m_pSubMesh.size() > 0)
		{

			for (DWORD dwSub = 0; dwSub < pMesh->m_pSubMesh.size(); dwSub++)
			{
				auto pSubMesh = pMesh->m_pSubMesh[dwSub];
				if (pSubMesh->m_iNumFace < 1) continue;
				pContext->PSSetShaderResources(0, 1, pSubMesh->m_dxObj.g_pTextureSRV.GetAddressOf());
				pContext->DrawIndexed(pSubMesh->m_dxObj.m_iNumIndex,
					pSubMesh->m_dxObj.m_iBeginIB, pSubMesh->m_dxObj.m_iBeginVB);
			}
		}
		else
		{
			
			if (pMesh->m_iNumFace < 1) continue;
			pContext->PSSetShaderResources(0, 1, pMesh->m_dxObj.g_pTextureSRV.GetAddressOf());
			pContext->DrawIndexed(pMesh->m_dxObj.m_iNumIndex,
				pMesh->m_dxObj.m_iBeginIB,
				pMesh->m_dxObj.m_iBeginVB);
		}
	}

	return true;
}


bool		AMapObj::LoadTexture(ID3D11Device* device, const TCHAR* fileName)
{

	for (DWORD dwObject = 0; dwObject < m_pMesh.size(); dwObject++)
	{
		AMesh* pMesh = m_pMesh[dwObject];

		if (pMesh->m_pSubMesh.size() > 0)
		{
			for (DWORD dwSub = 0; dwSub < pMesh->m_pSubMesh.size(); dwSub++)
			{
				if (pMesh->m_pSubMesh[dwSub]->m_iDiffuseTex < 0) continue;
				pMesh->m_pSubMesh[dwSub]->m_pTextureSRV = I_TEXTURE.GetPtr(pMesh->m_pSubMesh[dwSub]->m_iDiffuseTex)->m_TextureSRV;
			}
		}
		else
		{
			if (pMesh->m_iDiffuseTex < 0) continue;
			pMesh->m_pTextureSRV = I_TEXTURE.GetPtr(pMesh->m_iDiffuseTex)->m_TextureSRV;
		}
	}

	////m_GeomObjList[asd]->m_iMtrlRef;
	//m_MtrlList;
	//m_MtrlList[0].m_TexMaps[0].m_strTextureName;
	//m_dxObj.g_pTextureSRV = I_TEXTURE.GetPtr(m_MtrlList[0].m_TexMaps[0].m_dwIndex)->m_TextureSRV;

	return true;
}

bool AMapObj::Frame(const float& spf, const float& accTime)  noexcept
{
	GameObject::Frame(spf, accTime);


	return true;
}
bool AMapObj::UpdateBuffer(ID3D11DeviceContext* pContext)
{
	if (!CombineBuffer(pContext, m_dxObj.g_pVertexBuffer.Get(), m_dxObj.g_pIndexBuffer.Get()))
	{
		return false;
	}
	return true;
}


bool		AMapObj::CombineBuffer(ID3D11DeviceContext* pContext, ID3D11Buffer* pVB, ID3D11Buffer* pIB)
{
	UINT dstOffset = 0;
	UINT vbOffset = 0;
	UINT dstibOffset = 0;
	UINT ibOffset = 0;
	{
		for (DWORD dwObject = 0; dwObject < m_pMesh.size(); dwObject++)
		{
			auto pMesh = m_pMesh[dwObject];
			auto pData = m_pSkinMeshList[dwObject];
			if (pMesh->m_pSubMesh.size() > 0)
			{
				for (DWORD dwSub = 0; dwSub < pMesh->m_pSubMesh.size(); dwSub++)
				{
					auto pSubMesh = pMesh->m_pSubMesh[dwSub];
					auto pSubData = pData->m_pSubMesh[dwSub];
					if (pData->m_VertexArray.size() < 3) continue;

					pSubMesh->m_dxObj.m_iNumVertex = pData->m_VertexArray.size();
					pSubMesh->m_dxObj.m_iVertexSize = m_dxObj.m_iVertexSize;

					pSubMesh->m_dxObj.m_BoxVB.left = dstOffset;
					pSubMesh->m_dxObj.m_BoxVB.right = dstOffset + pSubMesh->m_dxObj.m_iNumVertex*m_dxObj.m_iVertexSize;
					pSubMesh->m_dxObj.m_BoxVB.top = 0; pSubMesh->m_dxObj.m_BoxVB.bottom = 1;
					pSubMesh->m_dxObj.m_BoxVB.front = 0; pSubMesh->m_dxObj.m_BoxVB.back = 1;

					pContext->UpdateSubresource(
						pVB, 0,
						&pSubMesh->m_dxObj.m_BoxVB,
						(uint8_t*)&pSubData->m_VertexArray.at(0),
						0, 0);


					/*m_pImmediateContext->CopySubresourceRegion(
					m_dxObj.g_pVertexBuffer.Get(), 0, iBeginPos, 0, 0,
					(void*)&pSubMesh->m_VertexArray.at(0),
					0, &pSubMesh->m_dxObj.m_BoxVB);*/

					pSubMesh->m_dxObj.m_iBeginVB = vbOffset;
					vbOffset += pSubMesh->m_dxObj.m_iNumVertex;
					dstOffset = pSubMesh->m_dxObj.m_BoxVB.right;

					pSubMesh->m_dxObj.m_iNumIndex = pSubData->m_IndexArray.size();
					pSubMesh->m_dxObj.m_BoxIB.left = dstibOffset;
					pSubMesh->m_dxObj.m_BoxIB.right = dstibOffset + pSubMesh->m_dxObj.m_iNumIndex * sizeof(DWORD);
					pSubMesh->m_dxObj.m_BoxIB.top = 0;		pSubMesh->m_dxObj.m_BoxIB.bottom = 1;
					pSubMesh->m_dxObj.m_BoxIB.front = 0;	pSubMesh->m_dxObj.m_BoxIB.back = 1;

					pContext->UpdateSubresource(pIB, 0,
						&pSubMesh->m_dxObj.m_BoxIB, (void*)&pSubData->m_IndexArray.at(0), 0, 0);

					pSubMesh->m_dxObj.m_iBeginIB = ibOffset;
					ibOffset += pSubMesh->m_dxObj.m_iNumIndex;
					dstibOffset = pSubMesh->m_dxObj.m_BoxIB.right;

					//texture
					if (pSubMesh->m_iDiffuseTex < 0) continue;
					pSubMesh->m_dxObj.g_pTextureSRV = I_TEXTURE.GetPtr(pSubMesh->m_iDiffuseTex)->m_TextureSRV;
				}
			}
			else
			{
				if (pData->m_VertexArray.size() < 3) continue;

				pMesh->m_dxObj.m_iNumVertex = pData->m_VertexArray.size();
				pMesh->m_dxObj.m_iVertexSize = m_dxObj.m_iVertexSize;

				pMesh->m_dxObj.m_BoxVB.left = dstOffset;
				pMesh->m_dxObj.m_BoxVB.right = dstOffset + pMesh->m_dxObj.m_iNumVertex*m_dxObj.m_iVertexSize;
				pMesh->m_dxObj.m_BoxVB.top = 0; pMesh->m_dxObj.m_BoxVB.bottom = 1;
				pMesh->m_dxObj.m_BoxVB.front = 0; pMesh->m_dxObj.m_BoxVB.back = 1;

				pContext->UpdateSubresource(pVB, 0, &pMesh->m_dxObj.m_BoxVB, (void*)&pData->m_VertexArray.at(0), 0, 0);

				pMesh->m_dxObj.m_iBeginVB = vbOffset;
				vbOffset += pMesh->m_dxObj.m_iNumVertex;
				dstOffset = pMesh->m_dxObj.m_BoxVB.right;

				pMesh->m_dxObj.m_iNumIndex = pData->m_IndexArray.size();
				pMesh->m_dxObj.m_BoxIB.left = dstibOffset;
				pMesh->m_dxObj.m_BoxIB.right = dstibOffset + pMesh->m_dxObj.m_iNumIndex * sizeof(DWORD);
				pMesh->m_dxObj.m_BoxIB.top = 0; pMesh->m_dxObj.m_BoxIB.bottom = 1;
				pMesh->m_dxObj.m_BoxIB.front = 0; pMesh->m_dxObj.m_BoxIB.back = 1;

				pContext->UpdateSubresource(pIB, 0, &pMesh->m_dxObj.m_BoxIB, (void*)&pData->m_IndexArray.at(0), 0, 0);
				pMesh->m_dxObj.m_iBeginIB = ibOffset;
				ibOffset += pMesh->m_dxObj.m_iNumIndex;
				dstibOffset = pMesh->m_dxObj.m_BoxIB.right;

				//texture
				if (pMesh->m_iDiffuseTex <= 0) continue;
				pMesh->m_dxObj.g_pTextureSRV = I_TEXTURE.GetPtr(pMesh->m_iDiffuseTex)->m_TextureSRV;
			}
		}
	}
	return true;

}



bool AMapObj::Release() noexcept
{
	m_pSkinMeshList.clear();
	m_matBipedList.clear();
	return true;
}


GameObject* AMapObj::clone() noexcept
{
	return cloneChild(new AMapObj(*this));
}



AMapObj::AMapObj()
{
}


AMapObj::~AMapObj()
{
	ObjectManager::KeyObjects.erase(m_keyValue);
}

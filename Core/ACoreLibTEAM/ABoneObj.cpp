#include "ABoneObj.h"
#include "ATexture.h"
#include "ObjectManager.h"

#define MAX_BONE_MATRICES 255

//멤버 변수인 m_pMatrix를 사용하여 상수버퍼를 갱신
void		ABoneObj::SetBoneMatrices(ID3D11DeviceContext*    pContext)
{
	D3DXMATRIX* pMatrices;
	HRESULT hr = S_OK;
	D3D11_MAPPED_SUBRESOURCE MappedFaceDest;


	if (SUCCEEDED(pContext->Map((ID3D11Resource*)m_pBoneBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedFaceDest)))
	{
		pMatrices = (D3DXMATRIX*)MappedFaceDest.pData;
		for (DWORD dwObject = 0; dwObject < m_Scene.iNumMesh; dwObject++)
		{
			pMatrices[dwObject] = m_pMatrix[dwObject];
		}
		pContext->Unmap(m_pBoneBuffer, 0);
	}
}
//pMatrix  를 사용하여 상수버퍼를 갱신한다.
void		ABoneObj::SetBoneMatrices(ID3D11DeviceContext*    pContext, D3DXMATRIX* pMatrix)
{
	D3DXMATRIX* pMatrices;
	HRESULT hr = S_OK;
	D3D11_MAPPED_SUBRESOURCE MappedFaceDest;
	if (SUCCEEDED(pContext->Map((ID3D11Resource*)m_pBoneBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedFaceDest)))
	{
		pMatrices = (D3DXMATRIX*)MappedFaceDest.pData;
		for (DWORD dwObject = 0; dwObject < m_Scene.iNumMesh; dwObject++)
		{
			pMatrices[dwObject] = pMatrix[dwObject];
		}
		pContext->Unmap(m_pBoneBuffer, 0);
	}
}

//pMatrix 를 사용하여 상수버퍼를 갱신한다.-> 바이패드에 해당하는 행렬에 곱하여 갱신한다*(바이드 포즈에 사용)
void		ABoneObj::SetBoneMatrices(ID3D11DeviceContext*    pContext, D3DXMATRIX* pMatrix, vector<D3DXMATRIX>* pList)
{
	D3DXMATRIX* pMatrices;
	HRESULT hr = S_OK;
	D3D11_MAPPED_SUBRESOURCE MappedFaceDest;
	if (SUCCEEDED(pContext->Map((ID3D11Resource*)m_pBoneBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedFaceDest)))
	{
		pMatrices = (D3DXMATRIX*)MappedFaceDest.pData;
		for (DWORD dwObject = 0; dwObject < m_Scene.iNumMesh; dwObject++)
		{
			pMatrices[dwObject] = (*pList)[dwObject] * pMatrix[dwObject];
		}
		pContext->Unmap(m_pBoneBuffer, 0);
	}
}
bool		ABoneObj::AniFrame(FLOAT fCurFrame, FLOAT fElapsedTime,	int iFirstFrame, int iLastFrame,	D3DXMATRIX* pMatrix, D3DXMATRIX* pParent)
{
	if (pMatrix == NULL)
	{
		pMatrix = m_pMatrix;
	}
	
	D3DXMatrixIdentity(m_pMatrix);
	bool bResult = false;
	D3DXQUATERNION TmpQuat;
	int iCurFrame = (int)fCurFrame;
	int iNextFrame = iCurFrame + 1;

	D3DXVECTOR3 vScale, vTrans;
	D3DXMATRIX matRotate, matScale, matTrans;
	D3DXMatrixIdentity(&matScale);


	if (m_bOneTime==true)
	{
		for (int i = 0; i < m_Scene.iNumMesh; i++)
		{
			if (iNextFrame >= iLastFrame)
			{
				m_bAnimPlay = false;
				m_NoneANIM = true;
			}
			else
			{
				m_bAnimPlay = true;
				D3DXQUATERNION	CurQuat = m_ppAniQuater[i][iCurFrame];
				D3DXQUATERNION	NextQuat = m_ppAniQuater[i][iNextFrame];
				D3DXQuaternionSlerp(&TmpQuat, &CurQuat, &NextQuat, fElapsedTime);
				D3DXMatrixRotationQuaternion(&matRotate, &TmpQuat);

				D3DXVec3Lerp(&vScale, &m_ppScaleVector[i][iCurFrame], &m_ppScaleVector[i][iNextFrame], fElapsedTime);
				D3DXMatrixScaling(&matScale, vScale.x, vScale.y, vScale.z);
				D3DXVec3Lerp(&vTrans, &m_ppTransVector[i][iCurFrame], &m_ppTransVector[i][iNextFrame], fElapsedTime);

				pMatrix[i] = matScale * matRotate;

				pMatrix[i]._41 = vTrans.x;
				pMatrix[i]._42 = vTrans.y;
				pMatrix[i]._43 = vTrans.z;
			}
		}
		return false;
	}

	for (int i = 0; i < m_Scene.iNumMesh; i++)
	{
		if (iNextFrame >= iLastFrame)
		{
			iCurFrame = iFirstFrame;
			D3DXQUATERNION	CurQuat = m_ppAniQuater[i][iCurFrame];
			D3DXQUATERNION	NextQuat = m_ppAniQuater[i][iCurFrame + 1];
			D3DXQuaternionSlerp(&TmpQuat, &CurQuat, &NextQuat, fElapsedTime);
			D3DXMatrixRotationQuaternion(&matRotate, &TmpQuat);

			D3DXMatrixScaling(&matScale, m_ppScaleVector[i][iCurFrame].x, m_ppScaleVector[i][iCurFrame].y, m_ppScaleVector[i][iCurFrame].z);
			vTrans = m_ppTransVector[i][iCurFrame];

/*			if (pParent != nullptr)
			{
			pMatrix[i] = matScale * matRotate;
				D3DXMatrixMultiply(&pMatrix[i], &pMatrix[i],&pParent[i]);
			}
			else*/
			//{
				pMatrix[i] = matScale * matRotate;
			//}
	
			pMatrix[i]._41 = vTrans.x;
			pMatrix[i]._42 = vTrans.y;
			pMatrix[i]._43 = vTrans.z;
			bResult = true;

		}
		else
		{
			//m_bAnimPlay = true;
			D3DXQUATERNION	CurQuat = m_ppAniQuater[i][iCurFrame];
			D3DXQUATERNION	NextQuat = m_ppAniQuater[i][iNextFrame];
			D3DXQuaternionSlerp(&TmpQuat, &CurQuat, &NextQuat, fElapsedTime);
			D3DXMatrixRotationQuaternion(&matRotate, &TmpQuat);

			D3DXVec3Lerp(&vScale, &m_ppScaleVector[i][iCurFrame], &m_ppScaleVector[i][iNextFrame], fElapsedTime);
			D3DXMatrixScaling(&matScale, vScale.x, vScale.y, vScale.z);
			D3DXVec3Lerp(&vTrans, &m_ppTransVector[i][iCurFrame], &m_ppTransVector[i][iNextFrame], fElapsedTime);

			//if (pParent != nullptr)
			//{
			//	//D3DXMatrixMultiply(, , matRotate);
			//	pMatrix[i] = matScale * matRotate;
			//	D3DXMatrixMultiply(&pMatrix[i], &pMatrix[i], &pParent[i]);
			//}
			//else
			//{
				pMatrix[i] = matScale * matRotate;
//			}
					
			pMatrix[i]._41 = vTrans.x;
			pMatrix[i]._42 = vTrans.y;
			pMatrix[i]._43 = vTrans.z;
		}
	}
	return bResult;//( iCurFrame > m_iLastFrame ) ? TRUE : FALSE;	
}


bool		ABoneObj::Init() noexcept
{
	return true;
}

bool		ABoneObj::Frame(const float& spf, const float& accTime)	noexcept
{
	m_fElapseTime += (spf * m_fSpeed *  m_Scene.iFrameSpeed);
	m_iCurrentFrame = (int)m_fElapseTime;
	m_fLerpTime = m_fElapseTime - m_iCurrentFrame;// 1프레임 사이 간격


	if (AniFrame(m_iCurrentFrame, m_fLerpTime, m_iStartFrame, m_iLastFrame, m_pMatrix))
	{
		m_iCurrentFrame = m_iStartFrame;
		m_fElapseTime = (float)m_iStartFrame;// + fElapsedTime;		
	}

	//SetBoneMatrices(DxManager::GetDContext());
	
	return true;
}




	
bool		ABoneObj::Render(ID3D11DeviceContext*    pContext) noexcept
{
	PreRender(pContext);
	Draw(pContext, this);
	return true;
}

bool		ABoneObj::Release() noexcept
{
	if (!m_pMatrix) return true;
	SAFE_DELETE_ARRAY(m_pMatrix);
	m_pMatrix = 0;

	for (int i = 0; i < m_Scene.iNumMesh; i++)
	{
		if (m_ppAniMatrix)	SAFE_DELETE_ARRAY(m_ppAniMatrix[i]);
		if (m_ppAniQuater)	SAFE_DELETE_ARRAY(m_ppAniQuater[i]);
		if (m_ppScaleVector)	SAFE_DELETE_ARRAY(m_ppScaleVector[i]);
		if (m_ppTransVector)	SAFE_DELETE_ARRAY(m_ppTransVector[i]);
	}
	if (m_ppAniMatrix)		SAFE_DELETE_ARRAY(m_ppAniMatrix);
	if (m_ppAniQuater)		SAFE_DELETE_ARRAY(m_ppAniQuater);
	if (m_ppScaleVector)	SAFE_DELETE_ARRAY(m_ppScaleVector);
	if (m_ppTransVector)	SAFE_DELETE_ARRAY(m_ppTransVector);

	SAFE_RELEASE(m_pBoneBuffer);
	SAFE_RELEASE(m_pBoneBufferRV);

	m_pBonehList.clear();

	return true;
}



bool		ABoneObj::Load(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const TCHAR* szLoadName, const TCHAR* pLoadShaderFile, bool bThread)
{
	FILE	*fp;
	fp = _tfopen(szLoadName, _T("rb"));
	if (!fp) return false;

	char szBuffer[MAX_PATH] = { 0, };
	UINT convertedChars = 0;

	//tm newtime;
	//fread(&newtime, sizeof(tm), 1, fp);
	//T_STR today = _tasctime(&newtime);	// The date string has a \n appended.
	//today[today.size() - 1] = 0;
	fread(&m_Scene, sizeof(AScene), 1, fp);

	// 시작 프레임이 0일 아닐 경우가 있기 때문에 무조건 
	// 시작 프레임을 0으로 맞춘다.( 해당 프레임 만큼만 배열 할당 된다.)
	m_iStartFrame = 0;//m_Scene.iFirstFrame;
	m_iLastFrame = m_Scene.iLastFrame - m_Scene.iFirstFrame;
	m_fElapseTime = (float)m_iStartFrame;
	m_Scene.iFirstFrame = 0;
	m_Scene.iLastFrame = m_iLastFrame;

	SAFE_NEW_ARRAY_CLEAR(m_pMatrix, D3DXMATRIX, m_Scene.iNumMesh);
	SAFE_NEW_ARRAY_CLEAR(m_ppAniMatrix, LPD3DXMATRIX, m_Scene.iNumMesh);
	SAFE_NEW_ARRAY_CLEAR(m_ppAniQuater, LPD3DXQUATERNION, m_Scene.iNumMesh);
	SAFE_NEW_ARRAY_CLEAR(m_ppScaleVector, LPD3DXVECTOR3, m_Scene.iNumMesh);
	SAFE_NEW_ARRAY_CLEAR(m_ppTransVector, LPD3DXVECTOR3, m_Scene.iNumMesh);

	int iNumFrame = m_iLastFrame - m_iStartFrame;
	for (int i = 0; i < m_Scene.iNumMesh; i++)
	{
		SAFE_NEW_ARRAY(m_ppAniMatrix[i], D3DXMATRIX, iNumFrame);
		SAFE_NEW_ARRAY(m_ppAniQuater[i], D3DXQUATERNION, iNumFrame);
		SAFE_NEW_ARRAY(m_ppScaleVector[i], D3DXVECTOR3, iNumFrame);
		SAFE_NEW_ARRAY(m_ppTransVector[i], D3DXVECTOR3, iNumFrame);
	}

	D3DXQUATERNION qRotate;
	D3DXVECTOR3 vScale, vTrans;
	D3DXMATRIX matFrameWorld;

	for (int ibip = 0; ibip < m_Scene.iNumMesh; ibip++)
	{
		for (int iFrame = 0; iFrame < iNumFrame; iFrame++)
		{
			fread(&m_ppAniMatrix[ibip][iFrame], sizeof(D3DXMATRIX), 1, fp);
		}
	}

	for (int ibip = 0; ibip < m_Scene.iNumMesh; ibip++)
	{
		BoneMesh* pData = new BoneMesh();
		AMesh* pMesh = new AMesh;
		int iCount;
		pMesh->m_iDiffuseTex = -1;
		TCHAR szBuffer[256] = { 0, };
		TCHAR szName[256] = { 0, };
		fread(&pMesh->m_ClassType, sizeof(int), 1, fp);
		fread(&iCount, sizeof(int), 1, fp);
		fread(szName, sizeof(TCHAR) * iCount, 1, fp);

		pMesh->m_strNodeName = szName;
		fread(&pMesh->m_matLocalMesh, sizeof(D3DXMATRIX), 1, fp);
		//SetWorldMatrix(pMesh->m_matLocalMesh);
		D3DXMatrixInverse(&pData->m_matInverse, 0, &pMesh->m_matLocalMesh);

		fread(&iCount, sizeof(int), 1, fp);
		// 메쉬 버텍스 리스트
		if (iCount == 2)
		{
			pData->m_VertexArray.resize(36);
			m_iMaxVertex += 36;
		}
		else
		{
			pData->m_VertexArray.resize(iCount);
			m_iMaxVertex += iCount;
		}

		for (int iVertex = 0; iVertex < iCount; iVertex++)
		{
			fread(&pData->m_VertexArray[iVertex], sizeof(PNC_VERTEX), 1, fp);
			if (m_Scene.iBindPose)
			{
				D3DXVec3TransformCoord(&pData->m_VertexArray[iVertex].p,
					&pData->m_VertexArray[iVertex].p,
					&pData->m_matInverse);
			}
		}

		// 본과 더미 오브젝트( 최대 및 최소값 2개 출력되어 있음 )
		if (iCount == 2)
		{
			D3DXVECTOR3 Quad[8];
			D3DXVECTOR3 vMax = pData->m_VertexArray[0].p;
			D3DXVECTOR3 vMin = pData->m_VertexArray[1].p;

			Quad[0] = D3DXVECTOR3(vMin.x, vMin.y, vMin.z);
			Quad[1] = D3DXVECTOR3(vMin.x, vMax.y, vMin.z);
			Quad[2] = D3DXVECTOR3(vMax.x, vMax.y, vMin.z);
			Quad[3] = D3DXVECTOR3(vMax.x, vMin.y, vMin.z);

			Quad[4] = D3DXVECTOR3(vMin.x, vMin.y, vMax.z);
			Quad[5] = D3DXVECTOR3(vMin.x, vMax.y, vMax.z);
			Quad[6] = D3DXVECTOR3(vMax.x, vMax.y, vMax.z);
			Quad[7] = D3DXVECTOR3(vMax.x, vMin.y, vMax.z);
			SetBoundBox(Quad, pData);
		}
		pMesh->m_iNumFace = pData->m_VertexArray.size() / 3;
		m_pMesh.push_back(pMesh);
		m_pBonehList.push_back(pData);
	}

	for (int ibip = 0; ibip < m_Scene.iNumMesh; ibip++)
	{
		for (int jFrame = 0; jFrame < m_iLastFrame - m_iStartFrame; jFrame++)
		{
			if (m_Scene.iBindPose)
			{
				//m_ppAniMatrix[ibip][jFrame] = m_pData[ibip]->m_matLocal * m_ppAniMatrix[ibip][jFrame];
			}
			if (SUCCEEDED(D3DXMatrixDecompose(&vScale, &qRotate, &vTrans, &m_ppAniMatrix[ibip][jFrame])))
			{
				m_ppAniQuater[ibip][jFrame] = qRotate;
				m_ppScaleVector[ibip][jFrame] = vScale;
				m_ppTransVector[ibip][jFrame] = vTrans;
			}
			else
			{
				D3DXQuaternionRotationMatrix(&m_ppAniQuater[ibip][jFrame], &m_ppAniMatrix[ibip][jFrame]);
			}
		}
	}

	fclose(fp);

	m_dxObj.m_iNumVertex = m_iMaxVertex;
	m_dxObj.m_iNumIndex = m_iMaxIndex;
	m_dxObj.m_iVertexSize = sizeof(PNC_VERTEX);



	if (!Set(pDevice, pContext,pLoadShaderFile, 0, true))
	{
		return false;
	}
	return true;



	return true;
}




bool		ABoneObj::Convert(const TCHAR* strPathName) 
{



	return true;
}

//void		ABoneObj::SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj)
//{
//	if (pWorld != NULL)
//	{
//		m_matLocal = *pWorld;
//		/*m_position.x = pWorld->_41;
//		m_position.y = pWorld->_42;
//		m_position.z = pWorld->_43;*/
//
//		m_matLocal = m_matLocal;
//	}
//	if (pView != NULL)
//	{
//		m_matView = *pView;
//	}
//	if (pProj != NULL)
//	{
//		m_matProj = *pProj;
//	}
//	//D3DXMatrixTranspose(&cbData.matWorld, &m_matLocal);
//	//D3DXMatrixTranspose(&cbData.matWorld, &m_matLocal);
//	D3DXMatrixTranspose(&cbData.matView, &m_matView);
//	D3DXMatrixTranspose(&cbData.matProj, &m_matProj);
//}

bool		ABoneObj::SetInputLayout(ID3D11Device* pdevice)
{
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);
	m_dxObj.g_pInputlayout.Attach(DX::CreateInputlayout(pdevice,
		m_dxObj.g_pVSBlob.Get()->GetBufferSize(),
		m_dxObj.g_pVSBlob.Get()->GetBufferPointer(), layout, numElements));

	SetBuffer(pdevice);

	return true;
}

//typedef struct D3D11_BUFFER_DESC
//{
//	UINT ByteWidth;
//	D3D11_USAGE Usage;
//	UINT BindFlags;
//	UINT CPUAccessFlags;
//	UINT MiscFlags;
//	UINT StructureByteStride;
//} 	D3D11_BUFFER_DESC;

bool		ABoneObj::SetBuffer(ID3D11Device* pd3dDevice)
{
	D3D11_BUFFER_DESC vbdesc =
	{
		MAX_BONE_MATRICES * sizeof(D3DXMATRIX),
		D3D11_USAGE_DYNAMIC,
		D3D11_BIND_SHADER_RESOURCE,
		D3D11_CPU_ACCESS_WRITE,
		0
	};
	pd3dDevice->CreateBuffer(&vbdesc, NULL, &m_pBoneBuffer);

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
	// Again, we need a resource view to use it in the shader
	ZeroMemory(&SRVDesc, sizeof(SRVDesc));
	SRVDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
	SRVDesc.Buffer.ElementOffset = 0;
	SRVDesc.Buffer.ElementWidth = MAX_BONE_MATRICES * 4;
	pd3dDevice->CreateShaderResourceView(m_pBoneBuffer, &SRVDesc, &m_pBoneBufferRV);
	return true;
}

void		ABoneObj::SetBoundBox(D3DXVECTOR3* Quad, BoneMesh* pMesh)
{
	pMesh->m_VertexArray[0].p.x = Quad[0].x; pMesh->m_VertexArray[0].p.y = Quad[0].y;
	pMesh->m_VertexArray[0].p.z = Quad[0].z; pMesh->m_VertexArray[0].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	pMesh->m_VertexArray[1].p.x = Quad[1].x; pMesh->m_VertexArray[1].p.y = Quad[1].y;
	pMesh->m_VertexArray[1].p.z = Quad[1].z; pMesh->m_VertexArray[1].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	pMesh->m_VertexArray[2].p.x = Quad[2].x; pMesh->m_VertexArray[2].p.y = Quad[2].y;
	pMesh->m_VertexArray[2].p.z = Quad[2].z; pMesh->m_VertexArray[2].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

	pMesh->m_VertexArray[3].p.x = Quad[0].x; pMesh->m_VertexArray[3].p.y = Quad[0].y;
	pMesh->m_VertexArray[3].p.z = Quad[0].z; pMesh->m_VertexArray[3].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	pMesh->m_VertexArray[4].p.x = Quad[2].x; pMesh->m_VertexArray[4].p.y = Quad[2].y;
	pMesh->m_VertexArray[4].p.z = Quad[2].z; pMesh->m_VertexArray[4].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	pMesh->m_VertexArray[5].p.x = Quad[3].x; pMesh->m_VertexArray[5].p.y = Quad[3].y;
	pMesh->m_VertexArray[5].p.z = Quad[3].z; pMesh->m_VertexArray[5].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);



	pMesh->m_VertexArray[6].p.x = Quad[3].x; pMesh->m_VertexArray[6].p.y = Quad[3].y;
	pMesh->m_VertexArray[6].p.z = Quad[3].z; pMesh->m_VertexArray[6].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	pMesh->m_VertexArray[7].p.x = Quad[2].x; pMesh->m_VertexArray[7].p.y = Quad[2].y;
	pMesh->m_VertexArray[7].p.z = Quad[2].z; pMesh->m_VertexArray[7].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	pMesh->m_VertexArray[8].p.x = Quad[6].x; pMesh->m_VertexArray[8].p.y = Quad[6].y;
	pMesh->m_VertexArray[8].p.z = Quad[6].z; pMesh->m_VertexArray[8].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);


	pMesh->m_VertexArray[9].p.x = Quad[3].x; pMesh->m_VertexArray[9].p.y = Quad[3].y;
	pMesh->m_VertexArray[9].p.z = Quad[3].z; pMesh->m_VertexArray[9].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	pMesh->m_VertexArray[10].p.x = Quad[6].x; pMesh->m_VertexArray[10].p.y = Quad[6].y;
	pMesh->m_VertexArray[10].p.z = Quad[6].z; pMesh->m_VertexArray[10].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	pMesh->m_VertexArray[11].p.x = Quad[7].x; pMesh->m_VertexArray[11].p.y = Quad[7].y;
	pMesh->m_VertexArray[11].p.z = Quad[7].z; pMesh->m_VertexArray[11].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

	// Back
	pMesh->m_VertexArray[12].p.x = Quad[7].x; pMesh->m_VertexArray[12].p.y = Quad[7].y;
	pMesh->m_VertexArray[12].p.z = Quad[7].z; pMesh->m_VertexArray[12].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	pMesh->m_VertexArray[13].p.x = Quad[6].x; pMesh->m_VertexArray[13].p.y = Quad[6].y;
	pMesh->m_VertexArray[13].p.z = Quad[6].z; pMesh->m_VertexArray[13].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	pMesh->m_VertexArray[14].p.x = Quad[5].x; pMesh->m_VertexArray[14].p.y = Quad[5].y;
	pMesh->m_VertexArray[14].p.z = Quad[5].z; pMesh->m_VertexArray[14].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

	pMesh->m_VertexArray[15].p.x = Quad[7].x; pMesh->m_VertexArray[15].p.y = Quad[7].y;
	pMesh->m_VertexArray[15].p.z = Quad[7].z; pMesh->m_VertexArray[15].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	pMesh->m_VertexArray[16].p.x = Quad[5].x; pMesh->m_VertexArray[16].p.y = Quad[5].y;
	pMesh->m_VertexArray[16].p.z = Quad[5].z; pMesh->m_VertexArray[16].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	pMesh->m_VertexArray[17].p.x = Quad[4].x; pMesh->m_VertexArray[17].p.y = Quad[4].y;
	pMesh->m_VertexArray[17].p.z = Quad[4].z; pMesh->m_VertexArray[17].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

	pMesh->m_VertexArray[18].p.x = Quad[4].x; pMesh->m_VertexArray[18].p.y = Quad[4].y;
	pMesh->m_VertexArray[18].p.z = Quad[4].z; pMesh->m_VertexArray[18].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	pMesh->m_VertexArray[19].p.x = Quad[5].x; pMesh->m_VertexArray[19].p.y = Quad[5].y;
	pMesh->m_VertexArray[19].p.z = Quad[5].z; pMesh->m_VertexArray[19].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	pMesh->m_VertexArray[20].p.x = Quad[1].x; pMesh->m_VertexArray[20].p.y = Quad[1].y;
	pMesh->m_VertexArray[20].p.z = Quad[1].z; pMesh->m_VertexArray[20].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

	pMesh->m_VertexArray[21].p.x = Quad[4].x; pMesh->m_VertexArray[21].p.y = Quad[4].y;
	pMesh->m_VertexArray[21].p.z = Quad[4].z; pMesh->m_VertexArray[21].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	pMesh->m_VertexArray[22].p.x = Quad[1].x; pMesh->m_VertexArray[22].p.y = Quad[1].y;
	pMesh->m_VertexArray[22].p.z = Quad[1].z; pMesh->m_VertexArray[22].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	pMesh->m_VertexArray[23].p.x = Quad[0].x; pMesh->m_VertexArray[23].p.y = Quad[0].y;
	pMesh->m_VertexArray[23].p.z = Quad[0].z; pMesh->m_VertexArray[23].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

	// Side
	pMesh->m_VertexArray[24].p.x = Quad[6].x; pMesh->m_VertexArray[24].p.y = Quad[6].y;
	pMesh->m_VertexArray[24].p.z = Quad[6].z; pMesh->m_VertexArray[24].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	pMesh->m_VertexArray[25].p.x = Quad[2].x; pMesh->m_VertexArray[25].p.y = Quad[2].y;
	pMesh->m_VertexArray[25].p.z = Quad[2].z; pMesh->m_VertexArray[25].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	pMesh->m_VertexArray[26].p.x = Quad[1].x; pMesh->m_VertexArray[26].p.y = Quad[1].y;
	pMesh->m_VertexArray[26].p.z = Quad[1].z; pMesh->m_VertexArray[26].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

	pMesh->m_VertexArray[27].p.x = Quad[6].x; pMesh->m_VertexArray[27].p.y = Quad[6].y;
	pMesh->m_VertexArray[27].p.z = Quad[6].z; pMesh->m_VertexArray[27].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	pMesh->m_VertexArray[28].p.x = Quad[1].x; pMesh->m_VertexArray[28].p.y = Quad[1].y;
	pMesh->m_VertexArray[28].p.z = Quad[1].z; pMesh->m_VertexArray[28].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	pMesh->m_VertexArray[29].p.x = Quad[5].x; pMesh->m_VertexArray[29].p.y = Quad[5].y;
	pMesh->m_VertexArray[29].p.z = Quad[5].z; pMesh->m_VertexArray[29].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

	pMesh->m_VertexArray[30].p.x = Quad[3].x; pMesh->m_VertexArray[30].p.y = Quad[3].y;
	pMesh->m_VertexArray[30].p.z = Quad[3].z; pMesh->m_VertexArray[30].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	pMesh->m_VertexArray[31].p.x = Quad[7].x; pMesh->m_VertexArray[31].p.y = Quad[7].y;
	pMesh->m_VertexArray[31].p.z = Quad[7].z; pMesh->m_VertexArray[31].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	pMesh->m_VertexArray[32].p.x = Quad[4].x; pMesh->m_VertexArray[32].p.y = Quad[4].y;
	pMesh->m_VertexArray[32].p.z = Quad[4].z; pMesh->m_VertexArray[32].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

	pMesh->m_VertexArray[33].p.x = Quad[3].x; pMesh->m_VertexArray[33].p.y = Quad[3].y;
	pMesh->m_VertexArray[33].p.z = Quad[3].z; pMesh->m_VertexArray[33].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	pMesh->m_VertexArray[34].p.x = Quad[4].x; pMesh->m_VertexArray[34].p.y = Quad[4].y;
	pMesh->m_VertexArray[34].p.z = Quad[4].z; pMesh->m_VertexArray[34].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	pMesh->m_VertexArray[35].p.x = Quad[0].x; pMesh->m_VertexArray[35].p.y = Quad[0].y;
	pMesh->m_VertexArray[35].p.z = Quad[0].z; pMesh->m_VertexArray[35].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
}


int a = 0;
bool		ABoneObj::Draw(ID3D11DeviceContext*    pContext, AModel* pParent)
{

	for (DWORD dwObject = 0; dwObject < m_pMesh.size(); dwObject++)
	{
		AMesh* pMesh = m_pMesh[dwObject];
		if (pMesh->m_ClassType == CLASS_GEOM) continue;
		D3DXMATRIX matWorld = m_pMatrix[dwObject] * m_matLocal;
		D3DXMatrixTranspose(&cbData.matWorld, &matWorld);
		//UpdateConstantBuffer(pContext, pParent);
		pContext->UpdateSubresource(pParent->m_dxObj.g_pConstantBuffer.Get(), 0, NULL, &pParent->cbData, 0, 0);

		if (pMesh->m_iNumFace < 1) continue;
		pContext->PSSetShaderResources(0, 1, pMesh->m_dxObj.g_pTextureSRV.GetAddressOf());
	pContext->Draw(pMesh->m_dxObj.m_iNumVertex, pMesh->m_dxObj.m_iBeginVB);
	}

	//for (DWORD dwObject = 0; dwObject < m_pMesh.size(); dwObject++)
	//{
	//	AMesh* pMesh = m_pMesh[dwObject];
	//	if (pMesh->m_ClassType == CLASS_GEOM) continue;
	//	UINT stride = sizeof(PNC_VERTEX);
	//	UINT offset = 0;
	//	D3DXMATRIX matWorld = pMesh->m_matCalculation * pParent->m_matLocal;
	//	D3DXMatrixTranspose(&cbData.matWorld, &matWorld);
	//	UpdateConstantBuffer(pContext, pParent);
	//	if (pMesh->m_iNumFace < 1) continue;
	//	pContext->IASetVertexBuffers(0, 1, pMesh->m_pVertexBuffer.GetAddressOf(), &stride, &offset);
	//	pContext->PSSetShaderResources(0, 1, pMesh->m_pTextureSRV.GetAddressOf());
	//	//pContext->DrawIndexed(m_pBonehList[dwObject]->m_IndexArray.size(), 0, 0);
	//	pContext->Draw(m_pBonehList[dwObject]->m_VertexArray.size(), 0);
	//}


	return true;
}



bool ABoneObj::UpdateBuffer(ID3D11DeviceContext* pContext)
{
	UINT dstOffset = 0;
	UINT vbOffset = 0;
	UINT dstibOffset = 0;
	UINT ibOffset = 0;
	{
		for (DWORD dwObject = 0; dwObject < m_pMesh.size(); dwObject++)
		{
			auto pMesh = m_pMesh[dwObject];
			auto pData = m_pBonehList[dwObject];
			if (pData->m_VertexArray.size() < 3) continue;
			pMesh->m_dxObj.m_iNumVertex = pData->m_VertexArray.size();
			pMesh->m_dxObj.m_iVertexSize = m_dxObj.m_iVertexSize;
			pMesh->m_dxObj.m_BoxVB.left = dstOffset;
			pMesh->m_dxObj.m_BoxVB.right = dstOffset + pMesh->m_dxObj.m_iNumVertex*m_dxObj.m_iVertexSize;
			pMesh->m_dxObj.m_BoxVB.top = 0; pMesh->m_dxObj.m_BoxVB.bottom = 1;
			pMesh->m_dxObj.m_BoxVB.front = 0; pMesh->m_dxObj.m_BoxVB.back = 1;
		
			pContext->UpdateSubresource(m_dxObj.g_pVertexBuffer.Get(), 0, &pMesh->m_dxObj.m_BoxVB, (void*)&pData->m_VertexArray.at(0), 0, 0);
			pMesh->m_dxObj.m_iBeginVB = vbOffset;
			vbOffset += pMesh->m_dxObj.m_iNumVertex;
			dstOffset = pMesh->m_dxObj.m_BoxVB.right;
			//texture
			if (pMesh->m_iDiffuseTex < 0) continue;
			{
				pMesh->m_dxObj.g_pTextureSRV = I_TEXTURE.GetPtr(pMesh->m_iDiffuseTex)->m_TextureSRV;
			}
		}
	}

	return true;
}

//bool ABoneObj::CreateVertexBuffer()
//{
//
//	for (DWORD dwObject = 0; dwObject < m_pMesh.size(); dwObject++)
//	{
//		AMesh* pMesh = m_pMesh[dwObject];
//		if (m_pBonehList[dwObject]->m_VertexArray.size() < 3) continue;
//
//		pMesh->m_pVertexBuffer.Attach(DX::CreateVertexBuffer(m_pd3dDevice.Get(),
//			&m_pBonehList[dwObject]->m_VertexArray.at(0),
//			m_pBonehList[dwObject]->m_VertexArray.size(),
//				sizeof(PNC_VERTEX)));
//
//		
//	}
//	return true;
//}

//bool ABoneObj::CreateIndexBuffer()
//{
//
//
//	return true;
//}
//


ABoneObj::ABoneObj()
{
	m_fSpeed = 1.0f;
	m_pMatrix = NULL;
	m_ppAniMatrix = NULL;
	m_ppAniQuater = NULL;
	m_ppScaleVector = NULL;
	m_ppTransVector = NULL;
	m_fLerpTime = 0.0f;
	m_pBoneBuffer = NULL;
	m_pBoneBufferRV = NULL;
	
	m_bOneTime = false;
	m_bAnimPlay = false;
	m_NoneANIM = false;

}


ABoneObj::~ABoneObj()
{
	ObjectManager::KeyObjects.erase(m_keyValue);

}

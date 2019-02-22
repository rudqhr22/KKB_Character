#include "AHeroObj.h"
#include "ObjectManager.h"


bool AHeroObj::SetPlayerCharacter(const TCHAR* fileName, float x , float y, float z)
{
	m_pChar = I_CHARMGR.GetPtr(fileName);
	if (m_pChar == nullptr) {
		return false;
	}


	m_pBoneObject = m_pChar->m_pBoneObject;
	SetActionFrame(
		m_pBoneObject->m_Scene.iFirstFrame,
		m_pBoneObject->m_Scene.iLastFrame);

	m_PlayerSelect = KKB::PLAYER_SELECT::DEFAULT;
	//SetCollisionData(
	//D3DXVECTOR3(-15.0f, 0.0f, -15.0f),
	//D3DXVECTOR3(15.0f, 75.0f, 15.0f));

	//m_InitBox.vMin = D3DXVECTOR3(-15.0f, 0.0f, -15.0f);
	//m_InitBox.vMax = D3DXVECTOR3(15.0f, 75.0f, 15.0f);
	
	if (fileName == Paladin)
	{
		m_PlayerSelect = KKB::PLAYER_SELECT::PALADIN;
		m_IdleName = Paladin_IDLE;
	}
	else if (fileName == Archer)
	{
		m_PlayerSelect = KKB::PLAYER_SELECT::ARCHER;
		m_IdleName = Archer_IDLE;
	}
	else if (fileName == Mage)
	{
		m_PlayerSelect = KKB::PLAYER_SELECT::MAGE;
		m_IdleName = Mage_IDLE;
	}
	else if (fileName == Zombie)
	{
		m_PlayerSelect = KKB::PLAYER_SELECT::ZOMBIE;
		m_IdleName = Zombie_IDLE;
	}
	else if (fileName == ZombieR)
	{  
		m_PlayerSelect = KKB::PLAYER_SELECT::ZOMBIE;
		m_IdleName = ZombieR_IDLE;
	}
	else if (fileName == ZombieEX)
	{
		m_PlayerSelect = KKB::PLAYER_SELECT::ZOMBIE_EX;
		m_IdleName = ZombieEX_IDLE;
	}
	else if (fileName == Zombie_KING)
	{
		m_PlayerSelect = KKB::PLAYER_SELECT::ZOMBIE_KING;
		m_IdleName = Zombie_KING_IDLE;
	}
	else
	{
		m_PlayerSelect = KKB::PLAYER_SELECT::DEFAULT;
	}



	m_position.x = x;
	m_position.y = y;
	m_position.z = z;

	return true;
}



bool AHeroObj::CreateConstantBuffer(ID3D11Device* pDevice)
{
	HRESULT hr = S_OK;
	D3D11_BUFFER_DESC Desc;
	Desc.Usage = D3D11_USAGE_DYNAMIC;
	Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	Desc.MiscFlags = 0;
	Desc.ByteWidth = sizeof(CBConstBoneWorld);
	hr = pDevice->CreateBuffer(&Desc, NULL, m_pCBConstBoneWorld.GetAddressOf());


	return true;
}

void AHeroObj::SetActionFrame(int iStart, int iEnd, int iCharacterMatrixIndex, int iModelMatrixIndex)
{
	m_iStartFrame = iStart;
	m_iLastFrame = iEnd;
	m_iCurrentFrame = (float)iStart;
	m_fFrame = m_iStartFrame;

	if (iCharacterMatrixIndex >= 0)
	{
		m_iMatrixIndex = iCharacterMatrixIndex;
	}

}


bool		AHeroObj::SetANIM_Loop(const TCHAR* szName)
{
	if (m_pBoneObject->m_bAnimPlay == false)
	{
		SetActionFrame(0, 0);

		m_pBoneObject = (ABoneObj*)I_OBJMGR.GetPtr(szName);
		if (m_pBoneObject == nullptr) {
			return false;
		}

		m_pBoneObject->m_bOneTime = false;

		SetActionFrame(
			m_pBoneObject->m_Scene.iFirstFrame,
			m_pBoneObject->m_Scene.iLastFrame);
	}

	
	return true;
}

bool		AHeroObj::SetANIM_OneTime(const TCHAR* szName)
{
	SetActionFrame(0, 0);

	m_pBoneObject = (ABoneObj*)I_OBJMGR.GetPtr(szName);
	if (m_pBoneObject == nullptr) {
		return false;
	}
	m_pBoneObject->m_bOneTime = true;

	SetActionFrame(
		m_pBoneObject->m_Scene.iFirstFrame,
		m_pBoneObject->m_Scene.iLastFrame);


	return true;
}

void AHeroObj::SetBoneMatrices(vector<D3DXMATRIX>* pList)
{


	for (UINT i = 0; i < pList->size(); i++)
	{
		D3DXMatrixTranspose(&m_cbBoneData.g_mConstBoneWorld[i], &((*pList)[i] * m_pMatrix[i]));
	}
}


bool	AHeroObj::Frame(const float& spf, const float& accTime) noexcept 
{
	GameObject::Frame(spf, accTime);
	m_fFrame += (spf * m_fSpeed * m_pBoneObject->m_Scene.iFrameSpeed);
	m_iCurrentFrame = (int)m_fFrame;

	// 1프레임 사이 간격
	m_fLerpTime = m_fFrame - m_iCurrentFrame;

	if (m_Parent != nullptr) 
	{
		if (m_pBoneObject->AniFrame(m_fFrame, m_fLerpTime, m_iStartFrame, m_iLastFrame, m_pMatrix, m_Parent->m_pMatrix))
		{
			m_iCurrentFrame = m_iStartFrame;
			m_fFrame = (float)m_iStartFrame + m_fLerpTime;
		}
	}
	else
	{
		if (m_pBoneObject->AniFrame(m_fFrame, m_fLerpTime, m_iStartFrame, m_iLastFrame, m_pMatrix))
		{
			m_iCurrentFrame = m_iStartFrame;
			m_fFrame = (float)m_iStartFrame + m_fLerpTime;
		}
	}



	if (m_pBoneObject->m_NoneANIM == true)
	{
		SetANIM_Loop(m_IdleName);
	}


	return true;
}

bool	AHeroObj::Render(ID3D11DeviceContext*    pContext) noexcept
{
	GameObject::Render(pContext);

	//if (m_Parent != nullptr) 
	//{
	//	for (int iObj = 0; iObj < m_pChar->m_pModelList.size(); iObj++)
	//	{
	//		ASkinObj* pModel = (ASkinObj*)m_pChar->m_pModelList[iObj]->m_pModel;
	//		_ASSERT(pModel);
	//			m_Parent->m_pBoneObject->m_pMesh;
	//		
	//		//m_matLocal._41 = m_Parent->m_matLocal._41;
	//		//m_matLocal._42 = m_Parent->m_matLocal._42;
	//		//m_matLocal._43 = m_Parent->m_matLocal._43;
	//		//D3DXMatrixMultiply(&m_matLocal,  &m_Parent->m_pBoneObject->m_pMesh[26]->m_matLocalMesh, &m_matLocal);
	//		
	//		pModel->SetMatrix(&m_matLocal, m_matView, m_matProj);
	//		//{
	//			//for (int i = 0; i < 255; i++) 
	//			//{
	//			//		D3DXMatrixMultiply(&m_pMatrix[i], &m_pMatrix[i], &m_Parent->m_pMatrix[i] );
	//			//}
	//	
	//			ASkinObj* pModel2 = (ASkinObj*)m_Parent->m_pChar->m_pModelList[iObj]->m_pModel;
	//			//m_pBoneObject->SetBoneMatrices(pContext, m_pMatrix, pModel->GetMatrix());
	//			m_pBoneObject->SetBoneMatrices(pContext, m_Parent->m_pMatrix, pModel2->GetMatrix());
	//			ID3D11ShaderResourceView* aRViews[1] = { m_pBoneObject->m_pBoneBufferRV };
	//			pContext->VSSetShaderResources(1, 1, aRViews);
	//		//}
	//		pModel->Render(pContext);
	//		return true;
	//	}
	//}


	if (m_bHeroRender == true) {
		for (int iObj = 0; iObj < m_pChar->m_pModelList.size(); iObj++)
		{
			ASkinObj* pModel = (ASkinObj*)m_pChar->m_pModelList[iObj]->m_pModel;
			_ASSERT(pModel);
			pModel->SetMatrix(&m_matLocal, m_matView, m_matProj);
			
			if (m_bConstantBufferType)	//바인드포즈가 아닐경우?
			{
				SetBoneMatrices(pModel->GetMatrix());
				D3D11_MAPPED_SUBRESOURCE MappedResource;
				pContext->Map(m_pCBConstBoneWorld.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource);
				memcpy(MappedResource.pData, &m_cbBoneData, sizeof(CBConstBoneWorld));
				pContext->Unmap(m_pCBConstBoneWorld.Get(), 0);
				pContext->VSSetConstantBuffers(1, 1, m_pCBConstBoneWorld.GetAddressOf());
			}
			else
			{
				m_pBoneObject->SetBoneMatrices(pContext, m_pMatrix, pModel->GetMatrix());

				ID3D11ShaderResourceView* aRViews[1] = { m_pBoneObject->m_pBoneBufferRV };
				pContext->VSSetShaderResources(1, 1, aRViews);
			}
			pModel->Render(pContext);
		}
	}

	//// 본 오브젝트 랜더링
	//if (m_bBoneRender)
	//{
	//	memcpy(m_pBoneObject->m_pMatrix, m_pMatrix, m_pBoneObject->m_Scene.iNumMesh * sizeof(D3DXMATRIX));
	//	m_pBoneObject->SetMatrix(&m_matLocal, m_matView, m_matProj);
	//	m_pBoneObject->Render(pContext);
	//}
	return true;
}


//bool	AHeroObj::Render(ID3D11DeviceContext*    pContext) noexcept
//{
//	GameObject::Render(pContext);
//	// 메쉬 랜더링
//	for (int iObj = 0; iObj < m_pChar->m_pModelList.size(); iObj++)
//	{
//		ASkinObj* pModel = (ASkinObj*)m_pChar->m_pModelList[iObj]->m_pModel;
//		ASkinObj* pParentModel = (ASkinObj*)m_pChar->m_pModelList[0]->m_pModel;
//		_ASSERT(pModel);
//
//		//m_matLocal = m_pChar->m_pBoneObject->m_pMesh[26]->GetWorldMatrix();
//		if (iObj > 0)
//		{
//			//m_matLocal = m_pChar->m_pBoneObject->m_pMesh[26]->m_matLocalMesh;
//			//m_matLocal = m_pChar->m_pBoneObject->m_pMesh[26]->m_matWorldRotate * m_pChar->m_pBoneObject->m_pMesh[26]->m_matWorldTrans;
//			//D3DXMatrixMultiply(&m_matLocal,&m_pChar->m_pBoneObject->m_pMesh[26]->m_matWorldRotate,& m_pChar->m_pBoneObject->m_pMesh[26]->m_matWorldTrans);
//
//			m_matLocal._12 = m_pChar->m_pBoneObject->m_pMesh[26]->m_matLocalMesh._12;
//			m_matLocal._13 = m_pChar->m_pBoneObject->m_pMesh[26]->m_matLocalMesh._13;
//			m_matLocal._14 = m_pChar->m_pBoneObject->m_pMesh[26]->m_matLocalMesh._14;
//
//			m_matLocal._21 = m_pChar->m_pBoneObject->m_pMesh[26]->m_matLocalMesh._21;
//			m_matLocal._23 = m_pChar->m_pBoneObject->m_pMesh[26]->m_matLocalMesh._23;
//			m_matLocal._24 = m_pChar->m_pBoneObject->m_pMesh[26]->m_matLocalMesh._24;
//
//			m_matLocal._31 = m_pChar->m_pBoneObject->m_pMesh[26]->m_matLocalMesh._31;
//			m_matLocal._32 = m_pChar->m_pBoneObject->m_pMesh[26]->m_matLocalMesh._32;
//			m_matLocal._34 = m_pChar->m_pBoneObject->m_pMesh[26]->m_matLocalMesh._24;
//
//			m_matLocal._41 = m_pChar->m_pBoneObject->m_pMesh[26]->m_matLocalMesh._41;
//			m_matLocal._42 = m_pChar->m_pBoneObject->m_pMesh[26]->m_matLocalMesh._42;
//			m_matLocal._43 = m_pChar->m_pBoneObject->m_pMesh[26]->m_matLocalMesh._43;
//
//			//	m_matLocal._41 += 10; m_pChar->m_pBoneObject->m_pMesh[26]->m_matLocalMesh._41;
//			//	m_matLocal._42 += 10;  m_pChar->m_pBoneObject->m_pMesh[26]->m_matLocalMesh._42;
//			//	m_matLocal._43 += 10;
//
//			pModel->SetMatrix(&m_matLocal, m_matView, m_matProj);
//		}
//		else
//		{
//			pModel->SetMatrix(&m_matLocal, m_matView, m_matProj);
//		}
//		if (m_bConstantBufferType)	//바인드포즈가 아닐경우?
//		{
//			SetBoneMatrices(pModel->GetMatrix());
//			D3D11_MAPPED_SUBRESOURCE MappedResource;
//			pContext->Map(m_pCBConstBoneWorld.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource);
//			memcpy(MappedResource.pData, &m_cbBoneData, sizeof(CBConstBoneWorld));
//			pContext->Unmap(m_pCBConstBoneWorld.Get(), 0);
//			pContext->VSSetConstantBuffers(1, 1, m_pCBConstBoneWorld.GetAddressOf());
//		}
//		else
//		{
//			if (iObj > 0)
//			{
//				m_pBoneObject->SetBoneMatrices(pContext, m_pMatrix, pParentModel->GetMatrix());
//			}
//			else
//			{
//				m_pBoneObject->SetBoneMatrices(pContext, m_pMatrix, pModel->GetMatrix());
//			}
//			ID3D11ShaderResourceView* aRViews[1] = { m_pBoneObject->m_pBoneBufferRV };
//			pContext->VSSetShaderResources(1, 1, aRViews);
//		}
//
//		pModel->Render(pContext);
//	}
//	//// 본 오브젝트 랜더링
//	//if (m_bBoneRender)
//	//{
//	//	memcpy(m_pBoneObject->m_pMatrix, m_pMatrix, m_pBoneObject->m_Scene.iNumMesh * sizeof(D3DXMATRIX));
//	//	m_pBoneObject->SetMatrix(&m_matLocal, m_matView, m_matProj);
//	//	m_pBoneObject->Render(pContext);
//	//}
//	return true;
//}





bool					AHeroObj::SetVSShader(ID3D11VertexShader* pVs)
{
	if (pVs == NULL) return false;
	m_dxObj.g_pVertexShader = pVs;
	m_HeroVS = m_dxObj.g_pVertexShader.Get();
	return true;
}

bool					AHeroObj::SetPSShader(ID3D11PixelShader* pPs)
{
	if (pPs == NULL) return false;
	m_dxObj.g_pPixelShader = pPs;
	m_HeroPS = m_dxObj.g_pPixelShader.Get();
	return true;
}

ID3D11VertexShader*		AHeroObj::GetVSShader()
{
	return	m_dxObj.g_pVertexShader.Get();
}

ID3D11PixelShader*		AHeroObj::GetPSShader()
{
	return m_dxObj.g_pPixelShader.Get();
}


bool		AHeroObj::ReturnVSShader()
{
	m_dxObj.g_pVertexShader = m_HeroVS;
	if (m_dxObj.g_pVertexShader == NULL)
	{
		return false;
	}
	return true;
}
bool		AHeroObj::ReturnPSShader()
{
	m_dxObj.g_pPixelShader = m_HeroPS;
	if (m_dxObj.g_pPixelShader == NULL)
	{
		return false;
	}
	return true;
}


void		AHeroObj::SetHeroAnimSpeed(float fSpeed)
{
	if (m_fSpeed != NULL) {
		m_fSpeed = fSpeed;
	}
}




bool	AHeroObj::Release() noexcept
{
	GameObject::Release();


	return true;
}

GameObject* AHeroObj::clone() noexcept
{
	return cloneChild(new AHeroObj(*this));
}


void		AHeroObj::SetHeroRender(bool i)
{
	m_bHeroRender = i;
}

AHeroObj::AHeroObj()
{
	m_bHeroRender = true;
	m_fSpeed = 1.0f;
	m_fFrame = 0.0f;
	m_fLerpTime = 0.0f;
	m_iStartFrame = 0;
	m_iLastFrame = 0;
	m_bConstantBufferType = false;
	m_bBoneRender = false;

	//m_keyValue = ++ObjectKeyCount;
	//ObjectManager::KeyObjects[m_keyValue] = this;
}


AHeroObj::~AHeroObj()
{
	ObjectManager::KeyObjects.erase(m_keyValue);


}



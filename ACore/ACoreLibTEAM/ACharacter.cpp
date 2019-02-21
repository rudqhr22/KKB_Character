#include "ACharacter.h"

void ACharacter::SetActionFrame(int iStart, int iEnd,
	int iCharacterMatrixIndex,
	int iModelMatrixIndex)
{
	m_iStartFrame = iStart;
	m_iLastFrame = iEnd;
	m_iCurrentFrame = (float)iStart;
	m_fFrame = m_iStartFrame;

	if (iCharacterMatrixIndex >= 0)
	{
		m_iMatrixIndex = iCharacterMatrixIndex;
	}
	if (iModelMatrixIndex >= 0)
	{
		SetModelMaterixID(iModelMatrixIndex);
	}
}

void ACharacter::SetModelMaterixID(int iMatrixIndex)
{
	for (int iObj = 0; iObj < m_pModelList.size(); iObj++)
	{
		m_pSubObjList[iObj]->SetMatrixIndex(iMatrixIndex);
	}
}

bool ACharacter::Add(ID3D11Device* pd3dDevice,
	ID3D11DeviceContext*    pImmediateContext,
	const TCHAR* strSkinFileName,
	const TCHAR* strSkinShaderName,
	int	iMatrixIndex,
	int iModelMatrixIndex)
{
	if (!_tcsicmp(strSkinFileName, _T("null")))
	{
		return false;
	}

	if (!Load(pd3dDevice, pImmediateContext, strSkinFileName, strSkinShaderName))
	{
		return false;
	}

	m_pBoneObject = (ABoneObj*)I_OBJMGR.GetPtr(iMatrixIndex);
	// �⺻�� = ��ü �������� ���ϸ��̼� �Ѵ�.
	SetActionFrame(m_pBoneObject->m_Scene.iFirstFrame,
		m_pBoneObject->m_Scene.iLastFrame,
		iMatrixIndex, iModelMatrixIndex);

	return true;
}
bool ACharacter::Init() noexcept
{
	AModelObj::Init();
	return true;
}
bool ACharacter::Render(ID3D11DeviceContext*    pContext) noexcept
{
	m_pBoneObject->m_pMatrix = m_pMatrix;
	// �޽� ������
	AModelObj::Render(pContext);
	// �� ������Ʈ ������
	m_pBoneObject->Render(pContext);
	return true;
}
void ACharacter::SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj)
{
	AModelObj::SetMatrix(pWorld, pView, pProj);
	m_pBoneObject->SetMatrix(pWorld, pView, pProj);
}
bool ACharacter::Release() noexcept
{
	AModelObj::Release();
	return true;
}

bool ACharacter::Frame(const float& spf, const float& accTime) noexcept
{
	_ASSERT(m_pBoneObject);
	//m_fLerpTime *= 0.1f;
	m_fFrame += (spf * m_pBoneObject->m_Scene.iFrameSpeed);
	m_iCurrentFrame = (int)m_fFrame;
	// 1������ ���� ����
	m_fLerpTime = m_fFrame - m_iCurrentFrame;
	if (m_pBoneObject->AniFrame(m_iCurrentFrame,
		m_fLerpTime,
		m_iStartFrame,
		m_iLastFrame,
		m_pMatrix))
	{
		m_iCurrentFrame = m_iStartFrame;
		m_fFrame = (float)m_iStartFrame;
	}

	AModelObj::Frame(spf, accTime);
	return true;
}

ACharacter::ACharacter(void)
{
	m_iMatrixIndex = -1;
}

ACharacter::~ACharacter(void)
{
}




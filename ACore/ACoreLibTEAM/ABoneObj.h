#pragma once
#include "AMesh.h"


struct BoneMesh : public PNC_VERTEX
{
public:
	int										m_iNumFace;
	vector<PNC_VERTEX>						m_VertexArray;
	vector<DWORD>							m_IndexArray;
	vector<ATri>							m_TriList;
	vector<BoneMesh*>						m_pSubMesh;
	vector<PNC_VERTEX*>						m_pChildMesh;
	PNC_VERTEX*								m_pDrawVertex;
	D3DXMATRIX								m_matInverse;
public:
//	int IsEqulVertexList(vector<PNC_VERTEX>&  VertexArray, PNC_VERTEX& Vertex);
//	int SetUniqueBuffer(vector <ATri_PNCT5>& TriList, int iMtrl, int iStartTri);
	BoneMesh(void)
	{
		m_pDrawVertex = NULL;
		m_iNumFace = 0;
	}
};

class ABoneObj : public AModel
{
public:
	vector<BoneMesh*>			m_pBonehList;
	FLOAT						m_fSpeed;
	FLOAT						m_fLerpTime;
	int							m_iCurrentFrame;
	D3DXMATRIX*					m_pMatrix;			//���ִϸ��̼� ������ ���� ������ ��Ʈ����?
	D3DXMATRIX**				m_ppAniMatrix;
	D3DXQUATERNION**			m_ppAniQuater;
	D3DXVECTOR3**				m_ppScaleVector;
	D3DXVECTOR3**				m_ppTransVector;
	ID3D11Buffer*               m_pBoneBuffer;
	ID3D11ShaderResourceView*	m_pBoneBufferRV;
	bool m_bOneTime;
	bool m_bAnimPlay;
	bool m_NoneANIM;


public:
	// ��� ���� �� ���ϸ��̼� ����
	void		SetBoneMatrices(ID3D11DeviceContext*    pContext);						//��� ������ m_pMatrix�� ����Ͽ� ������۸� ����
	void		SetBoneMatrices(ID3D11DeviceContext*    pContext, D3DXMATRIX* pMatrix);	//pMatrix  �� ����Ͽ� ������۸� �����Ѵ�.
	void		SetBoneMatrices(ID3D11DeviceContext*    pContext, D3DXMATRIX* pMatrix, vector<D3DXMATRIX>* pList);	//pMatrix �� ����Ͽ� ������۸� �����Ѵ�.-> �����е忡 �ش��ϴ� ��Ŀ� ���Ͽ� �����Ѵ�*(���̵� ��� ���)

	bool		AniFrame(FLOAT fCurFrame, FLOAT fElapsedTime,
		int iFirstFrame, int iLastFrame,
		D3DXMATRIX* pMatrix, D3DXMATRIX* pParent=0);


public:
	bool		Init()noexcept override;
	bool		Frame(const float& spf, const float& accTime)	noexcept override;

	bool		Render(ID3D11DeviceContext*    pContext) noexcept override;
	bool		Release()noexcept override;
	//bool		Load(ID3D11Device* pDevice,
	//	const TCHAR* szLoadName,
	//	const TCHAR* pLoadShaderFile,
	//	bool bThread = false);

	bool		Load(ID3D11Device* pDevice,
		ID3D11DeviceContext* pContext,
		const TCHAR* szLoadName,
		const TCHAR* pLoadShaderFile,
		bool bThread = false);



	bool		Convert(const TCHAR* strPathName = 0);
public:
	//void		SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj);
	bool		SetInputLayout(ID3D11Device* pdevice);
	bool		SetBuffer(ID3D11Device* pd3dDevice);
	void		SetBoundBox(D3DXVECTOR3* Quad, BoneMesh* pMesh);
	bool		UpdateBuffer(ID3D11DeviceContext* pContext);
//	bool		CombineBuffer(ID3D11Buffer* pVB, ID3D11Buffer* pIB);
	bool		Draw(ID3D11DeviceContext*    pContext, AModel* pParent);
//	bool	CreateVertexBuffer();
	//bool	CreateIndexBuffer();

public:
	ABoneObj();
	virtual ~ABoneObj();
};


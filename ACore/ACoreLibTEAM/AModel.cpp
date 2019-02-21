#include "AModel.h"
#include "ATexture.h"
#include "ObjectManager.h"

//bool AModel::Load(ID3D11Device* pDevice, const TCHAR* szLoadName, const TCHAR* pLoadShaderFile,
//	bool bThread)
//{
//	return true;
//}




bool AModel::Load(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const TCHAR* szLoadName, const TCHAR* pLoadShaderFile,
	bool bThread)
{
	return true;
}


void		AModel::UpdateMatrix() noexcept
{
	D3DXMatrixScaling(&m_matScale, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixRotationYawPitchRoll(&m_matRotation, m_rotation.y, m_rotation.x, m_rotation.z);
	m_matLocal = m_matScale * m_matRotation;
	m_matLocal._41 = m_position.x;
	m_matLocal._42 = m_position.y;
	m_matLocal._43 = m_position.z;


	D3DXMatrixTranspose(&m_matLocal, &m_matLocal);
	if (m_pParent != nullptr)
	{
		m_matLocal = m_pParent->GetWorldMatrix() * m_matLocal;
	}


	m_Side = { -m_matLocal._11, -m_matLocal._21, -m_matLocal._31 };
	m_Up = { m_matLocal._12, m_matLocal._22, m_matLocal._32 };
	m_Look = { -m_matLocal._13, -m_matLocal._23, -m_matLocal._33 };
	D3DXMatrixTranspose(&m_matLocal, &m_matLocal);

 }

void		 AModel::SetCollisionData(D3DXVECTOR3 min, D3DXVECTOR3 max)
{
	//m_InitBox.vMin = min;
	//m_InitBox.vMax = max;
}

void		AModel::UpdateCollisionData(D3DXVECTOR3 position)
{
	//m_CollsionBox.vCenter = m_position;
	////// w= 1
	//D3DXVECTOR3 vMax = m_InitBox.vMax;
	//D3DXVECTOR3 vMin = m_InitBox.vMin;
	//D3DXVec3TransformCoord(&m_CollsionBox.vMax, &vMax, &m_matLocal);
	//D3DXVec3TransformCoord(&m_CollsionBox.vMin, &vMin, &m_matLocal);
	////// w= 0 * _41
	//D3DXVec3TransformNormal(&m_CollsionBox.vAxis[0], &m_InitBox.vAxis[0], &m_matLocal);
	//D3DXVec3TransformNormal(&m_CollsionBox.vAxis[1], &m_InitBox.vAxis[1], &m_matLocal);
	//D3DXVec3TransformNormal(&m_CollsionBox.vAxis[2], &m_InitBox.vAxis[2], &m_matLocal);
	//D3DXVec3Normalize(&m_CollsionBox.vAxis[0], &m_CollsionBox.vAxis[0]);
	//D3DXVec3Normalize(&m_CollsionBox.vAxis[1], &m_CollsionBox.vAxis[1]);
	//D3DXVec3Normalize(&m_CollsionBox.vAxis[2], &m_CollsionBox.vAxis[2]);
	//m_CollsionBox.fExtent[0] = (m_CollsionBox.vMax.x - m_CollsionBox.vMin.x) * 0.5f;
	//m_CollsionBox.fExtent[1] = (m_CollsionBox.vMax.y - m_CollsionBox.vMin.y) * 0.5f;
	//m_CollsionBox.fExtent[2] = (m_CollsionBox.vMax.z - m_CollsionBox.vMin.z) * 0.5f;
	//m_position = D3DXVECTOR3(m_position.x, m_position.y, m_position.z);
	//m_Sphere.vCenter = m_position;
	//m_Sphere.fRadius = D3DXVec3Length(&(m_CollsionBox.vMax - m_CollsionBox.vCenter));
}




void		AModel::SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj)
{
	if (pWorld != NULL)
	{
		m_matLocal = *pWorld;
		m_position.x = pWorld->_41;
		m_position.y = pWorld->_42;
		m_position.z = pWorld->_43;

	}
	if (pView != NULL)
	{
		m_matView = pView;
	}
	if (pProj != NULL)
	{
		m_matProj = pProj;
	}


	D3DXMatrixTranspose(&cbData.matView, m_matView);		//전치시키는 함수
	D3DXMatrixTranspose(&cbData.matProj, m_matProj);		//전치시키는 함수
}



bool		AModel::SetInputLayout(ID3D11Device* pdevice)
{
	HRESULT hr = S_OK;
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);

	m_dxObj.g_pInputlayout.Attach(DX::CreateInputlayout(
		pdevice,
		m_dxObj.g_pVSBlob.Get()->GetBufferSize(),
		m_dxObj.g_pVSBlob.Get()->GetBufferPointer(),
		layout,
		numElements));

	return true;
}


bool		AModel::Set(ID3D11Device* device, ID3D11DeviceContext* pContext, const TCHAR* shaderName, const TCHAR* fileName, bool pass)
{
	if (!CompileShader(device, shaderName)) {
		MessageBox(0, _T("CompileShader 실패"), _T("Fatal error"), MB_OK);
		return false;
	}

	if (!SetInputLayout(device))
	{
		MessageBox(0, _T("SetInputLayout 실패"), _T("Fatal error"), MB_OK);
		return false;
	}

	if (!CreateVertexData()) {
		MessageBox(0, _T("CreateVertexData 실패"), _T("Fatal error"), MB_OK);
		return false;
	}
	if (!CreateIndexData()) {
		MessageBox(0, _T("CreateIndexData 실패"), _T("Fatal error"), MB_OK);
		return false;
	}
	if (!CreateVertexBuffer(device))
	{
		MessageBox(0, _T("CreateVertexBuffer 실패"), _T("Fatal error"), MB_OK);
		return false;
	}

	if (!CreateIndexBuffer(device)) {
		MessageBox(0, _T("CreateIndexBuffer 실패"), _T("Fatal error"), MB_OK);
		return false;
	}

	if (!CreateConstantBuffer(device)) {
		MessageBox(0, _T("CreateConstantBuffer 실패"), _T("Fatal error"), MB_OK);
		return false;
	}

	if (!UpdateBuffer(pContext))
	{
		MessageBox(0, _T("UpdateBuffer 실패"), _T("Fatal error"), MB_OK);
		return false;
	}


	if (!CreatePrimitiveType()) {
		return false;
	}

	if (pass == true) { return true; }

	if (!LoadTexture(device, fileName)) {
		MessageBox(0, _T("LoadTexture 실패"), _T("Fatal error"), MB_OK);
		return false;
	}


	return Init();


}



bool	AModel::UpdateBuffer(ID3D11DeviceContext* pContext)
{
	return true; 
};

bool		AModel::CreateVertexData() { return true; };

bool		AModel::CreateIndexData() { return true; };


bool		AModel::CreateVertexBuffer(ID3D11Device* pdevice)
{
	if (m_dxObj.m_iNumVertex <= 0) return true;
	void** pData = nullptr;

	if (m_PNCTList.size() > 0) pData = (void**)&m_PNCTList.at(0);

	m_dxObj.g_pVertexBuffer.Attach(
		DX::CreateVertexBuffer(pdevice,
			pData,
			m_dxObj.m_iNumVertex,
			m_dxObj.m_iVertexSize));
	return true;
};

bool		AModel::CreateIndexBuffer(ID3D11Device* pdevice)
{
	if (m_dxObj.m_iNumIndex <= 0) return true;

	void** pData = nullptr;

	if (m_IndexList.size() > 0) pData = (void**)&m_IndexList.at(0);

	m_dxObj.g_pIndexBuffer.Attach(DX::CreateIndexBuffer(pdevice,
		pData,
		m_dxObj.m_iNumIndex,
		m_dxObj.m_iIndexSize));

	return true;
};

bool		AModel::CreateConstantBuffer(ID3D11Device* pdevice)
{
	cbData.vColor = D3DXVECTOR4(1, 1, 1, 1);
	m_dxObj.g_pConstantBuffer.Attach(DX::CreateConstantBuffer(pdevice, &cbData, 1, sizeof(VS_CONSTANT_BUFFER)));
	return true;
};


//디바이스와 픽쉘 쉐이더
bool		AModel::CompileShader(ID3D11Device* device, const TCHAR* fileName)
{
	HRESULT hr;
	//DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

	m_dxObj.g_pVertexShader.Attach(DX::LoadVertexShaderFile(device, fileName, m_dxObj.g_pVSBlob.GetAddressOf()));
	if (m_dxObj.g_pVertexShader == NULL) return false;
	

	m_dxObj.g_pPixelShader.Attach(DX::LoadPixelShaderFile(device, fileName));
	if (m_dxObj.g_pPixelShader == NULL) return false;

	//m_dxObj.g_pGeometryShader.Attach(DX::LoadGeometryShaderFile(device, fileName, m_dxObj.g_pGSBlob.GetAddressOf()));
	//m_dxObj.g_pHullShader.Attach(DX::LoadHullShaderFile(device, fileName, m_dxObj.g_pHSBlob.GetAddressOf()));
	///m_dxObj.g_pDomainShader.Attach(DX::LoadDomainShaderFile(device, fileName, m_dxObj.g_pDSBlob.GetAddressOf()));
	//m_dxObj.g_pComputeShader.Attach(DX::LoadComputeShaderFile(device, fileName, m_dxObj.g_pCSBlob.GetAddressOf()));
	
	return true;
}


bool		AModel::LoadTexture(ID3D11Device* device, const TCHAR* fileName)
{

	HRESULT hr = S_OK;
	//m_dxObj.g_pTextureSRV.Attach(DX::CreateShaderResourceView(device, fileName));

	//I_TEXTURE.Add(device, fileName, m_dxObj.g_pTextureSRV);

	//if (FAILED(hr = D3DX11CreateShaderResourceViewFromFile(device, fileName, NULL, NULL, &m_dxObj.g_pTextureSRV, NULL))) {
	//	return false;
	//}

	m_dxObj.g_pTextureSRV.Attach(DX::CreateShaderResourceView(device, fileName));

	return true;
}


HRESULT		AModel::TextureInfo(const TCHAR* texture)
{
	HRESULT hr=S_OK;
	//D3DX11_IMAGE_INFO ImageInfo;
	//if (texture == NULL) return S_OK;

	//hr = D3DX11GetImageInfoFromFile(texture, NULL, &ImageInfo, &hr);

	//weidght =ImageInfo.Width;
	//height = ImageInfo.Height;

	//D3DX11_IMAGE_LOAD_INFO LInfo;
	//ZeroMemory(&LInfo, sizeof(LInfo));
	//LInfo.Format = DXGI_FORMAT_FROM_FILE; //DXGI_FORMAT_BC1_UNORM
	//LInfo.CpuAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
	//LInfo.pSrcInfo = &ImageInfo;
	//LInfo.Usage = D3D11_USAGE_STAGING;
	
	//ID3D11Resource *pTexture = NULL;
	//hr = D3DX11CreateTextureFromFile(m_pd3dDevice.Get(), texture, &LInfo, NULL, &pTexture, NULL);

	//ID3D11Texture2D *pTexture2D = NULL;
	//hr = pTexture->QueryInterface(__uuidof(ID3D11Texture2D), (LPVOID*)&pTexture2D);
	//SAFE_RELEASE(pTexture);

	//D3D11_TEXTURE2D_DESC td2d_Desc;
	//pTexture2D->GetDesc(&td2d_Desc);

	//weidght = td2d_Desc.Width;
	//height = td2d_Desc.Height;

	return hr;
}

bool AModel::Init() noexcept
{
	GameObject::Init();

	return true;
}
bool AModel::Frame(const float& spf, const float& accTime)  noexcept
{
	GameObject::Frame(spf, accTime);


	return true; 
}
bool AModel::Release() noexcept
{
	GameObject::Release();

	m_pMesh.clear();

	return true;
}

bool	AModel::Render(ID3D11DeviceContext* context) noexcept
{
	GameObject::Render(context);

	PreRender(context);
	PostRender(context);
	

	return true;
};

void AModel::UpdateConstantBuffer(ID3D11DeviceContext* pContext, AModel* pParent)
{
	//D3DXMatrixPerspectiveFovLH(&cbData.matProj, (float)D3DX_PI*0.5f, (g_iClientWidth / (float)g_iClientHeight), 1, 100.0f);
	//D3DXMatrixTranspose(&cbData.matProj, &cbData.matProj);

	if (pParent != NULL && pParent->m_dxObj.g_pConstantBuffer != nullptr)
	{
		pContext->UpdateSubresource(pParent->m_dxObj.g_pConstantBuffer.Get(), 0, NULL, &pParent->cbData, 0, 0);
	}
	else
	{
		if (m_dxObj.g_pConstantBuffer != nullptr)
			pContext->UpdateSubresource(m_dxObj.g_pConstantBuffer.Get(), 0, NULL, &cbData, 0, 0);
	}

	//if (m_dxObj.g_pConstantBuffer != nullptr) 
	//{
	//	pContext->UpdateSubresource(m_dxObj.g_pConstantBuffer.Get(), 0, NULL, &cbData, 0, 0);
	//}
	
}

bool	AModel::PreRender(ID3D11DeviceContext* context)
{
	context->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)m_dxObj.m_iPrimitiveType);


	m_dxObj.PreRender(context, m_dxObj.m_iVertexSize);

	return true;
};

bool	AModel::PostRender(ID3D11DeviceContext* context) 
{

	UpdateConstantBuffer(context);
	//context->DrawIndexed(m_dxObj.m_iNumIndex, 0, 0);
	m_dxObj.PostRender(context, m_dxObj.m_iNumIndex);
	return true;
};

bool		AModel::CreatePrimitiveType()
{
	m_dxObj.m_iPrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	return true;
}


//GameObject* AModel::clone() noexcept
//{
//	m_keyValue = ++ObjectKeyCount;
//	return ObjectManager::KeyObjects[m_keyValue] = cloneChild(new AModel(*this));
//}


bool					AModel::SetVSShader(ID3D11VertexShader* pVs)
{
	if (pVs == NULL) return false;
	m_dxObj.g_pVertexShader = pVs;
	m_HeroVS = m_dxObj.g_pVertexShader.Get();
	return true;
}

bool					AModel::SetPSShader(ID3D11PixelShader* pPs)
{
	if (pPs == NULL) return false;
	m_dxObj.g_pPixelShader = pPs;
	m_HeroPS = m_dxObj.g_pPixelShader.Get();
	return true;
}

ID3D11VertexShader*		AModel::GetVSShader()
{
	return	m_dxObj.g_pVertexShader.Get();
}

ID3D11PixelShader*		AModel::GetPSShader()
{
	return m_dxObj.g_pPixelShader.Get();
}


bool					AModel::ReturnVSShader()
{
	m_dxObj.g_pVertexShader = m_HeroVS;
	if (m_dxObj.g_pVertexShader == NULL)
	{
		return false;
	}
	return true;
}
bool					AModel::ReturnPSShader()
{
	m_dxObj.g_pPixelShader = m_HeroPS;
	if (m_dxObj.g_pPixelShader == NULL)
	{
		return false;
	}
	return true;
}



AModel::AModel()
{


	//m_InitBox.vMax = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	//m_InitBox.vMin = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);


	cbData.vColor = D3DXVECTOR4(1, 1, 1, 1);
	//D3DXMatrixIdentity(&m_matLocal);
	//D3DXMatrixIdentity(m_matView);
	//D3DXMatrixIdentity(m_matProj);
//	D3DXMatrixIdentity(&m_matControlWorld);




}


AModel::~AModel()
{

	

}

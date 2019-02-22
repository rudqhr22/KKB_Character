#include "AMapMgr.h"

int		AMapMgr::Create(ID3D11Device* pd3dDevice,	ID3D11DeviceContext*    pImmediateContext,
	const TCHAR* strFileName,	const TCHAR* strShaderName)
{
	TCHAR szFileName[256];
	TCHAR Drive[MAX_PATH];
	TCHAR Dir[MAX_PATH];
	TCHAR FName[MAX_PATH];
	TCHAR Ext[MAX_PATH];

	// 종복 방지 
	if (strFileName)
	{

		_tsplitpath_s(strFileName, Drive, Dir, FName, Ext);
		Ext[4] = 0;
		_stprintf_s(szFileName, _T("%s%s"), FName, Ext);

		for (auto itor = m_MapObjList.begin(); itor != m_MapObjList.end(); itor++)
		{
			AMapObj *pPoint = (AMapObj *)(*itor).second;
			if (!_tcsicmp(pPoint->m_szName.c_str(), szFileName))
			{
				return (*itor).first;
			}
		}
	}

	AMapObj* pChild = 0;
	SAFE_NEW(pChild, AMapObj);
	pChild->m_szName = szFileName;
	pChild->Load(pd3dDevice, pImmediateContext, strFileName, strShaderName);

	{
		m_MapObjList.insert(make_pair(m_iCurIndex++, pChild));
		return m_iCurIndex - 1;
	}

	return -1;
};

bool		AMapMgr::Load(ID3D11Device* pd3dDevice, ID3D11DeviceContext*    pImmediateContext, const TCHAR* strFileName)
{
	int		iNumObj = 0;
	TCHAR	strObjName[MAX_PATH] = { 0, };
	TCHAR	strMeshName[MAX_PATH] = { 0, };
	TCHAR	strShaderName[MAX_PATH] = { 0, };
	TCHAR	strMatrixName[MAX_PATH] = { 0, };
	int iObjIndex = -1;

	m_Parser.OpenStream(strFileName);
	if (m_Parser.GetDataFromFileLoop(_T("*NUMMAPOBJ"), &iNumObj, INT_DATA))
	{
		for (int iNum = 0; iNum < iNumObj; iNum++)
		{
			m_Parser.GetDataFromFileLoop(_T("*OBJNAME"), strObjName, STRING_DATA);
			m_Parser.GetDataFromFileLoop(_T("*SHADERFILENMAE"), strShaderName, STRING_DATA);
			m_Parser.GetDataFromFileLoop(_T("*OBJFILENMAE"), strMeshName, STRING_DATA);

			
			
			iObjIndex = Create(pd3dDevice, pImmediateContext, strMeshName, strShaderName);
			m_pModelObj = GetPtr(iObjIndex);
			m_pModelObj->m_szName = strObjName;
			//pNew->Load(pd3dDevice, pImmediateContext, strFileName, strShaderName);
			//pNew->Load(pd3dDevice, pImmediateContext, strFileName, L"../../Data/MODEL/SkinViewer.hlsl");
		}
	}


	return true;
}

bool		AMapMgr::Init()
{
	m_iCurIndex = 0;
	m_MapObjList.clear();
	return true;
}


AMapObj*	const	AMapMgr::GetPtr(int index)
{
	auto it = m_MapObjList.find(index);
	if (it == m_MapObjList.end()) return NULL;

	return (*it).second;
}


AMapObj*	const	AMapMgr::GetPtr(const TCHAR* szName)
{
	for (auto it = m_MapObjList.begin(); it != m_MapObjList.end(); it++)
	{
		AMapObj* pPoint = (AMapObj*)(*it).second;
		
		if (!_tcsicmp(pPoint->m_szName.c_str(), szName))
		{
			return pPoint;
		}
	}
	return NULL;
}


int			AMapMgr::GetID(AModel* pChild)
{
	for (auto it = m_MapObjList.begin(); it != m_MapObjList.end(); it++)
	{
		AModel *pPoint = (AModel *)(*it).second;
		if (pChild == pPoint)
		{
			return (int)(*it).first;;
		}
	}
	return -1;
}

int			AMapMgr::GetID(const TCHAR* szName)
{
	for (auto it = m_MapObjList.begin(); it != m_MapObjList.end(); it++)
	{
		AModel *pPoint = (AModel *)(*it).second;
		if (!_tcsicmp(pPoint->m_szName.c_str(),szName))
		{
			return (*it).first;
		}
	}
	return -1;
}


int			AMapMgr::Count()
{
	return (int)m_MapObjList.size();
}

bool		AMapMgr::Release()
{
	for (auto itor = m_MapObjList.begin(); itor != m_MapObjList.end(); itor++)
	{
		AModel *pPoint = (AModel *)(*itor).second;
		if (pPoint)
		{
			pPoint->Release();
		}
	}
	return true;
}


bool		AMapMgr::Delete(int iIndex)
{
	AModel* const pPoint = GetPtr(iIndex);
	if (pPoint)
	{
		pPoint->Release();
		m_MapObjList.erase(iIndex);
		return true;

	}
	return false;

}


bool		AMapMgr::Delete(AModel* pPoint)
{
	if (pPoint)
	{
		pPoint->Release();
		m_MapObjList.erase(GetID(pPoint));
		return true;

	}
	return false;
}





AMapMgr::AMapMgr()
{
}


AMapMgr::~AMapMgr()
{
}

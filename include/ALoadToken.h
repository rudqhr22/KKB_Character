#pragma once
//#include "ADxHelperEx.h"
#include "AStd.h"
class ALoadToken
{
public:
	T_STR		m_szDirName;
	T_STR		m_szName;

	HANDLE		m_hHandle;

	CHAR*		m_pmbStaticMeshData;		//��Ƽ����Ʈ �޽�������
	TCHAR*		m_pwcStaticMeshData;		//�����ڵ� �޽�������

	vector<T_STR>	m_ListTokens;			//�޽������͸� ���ٷ� ���� ����

	T_STR		m_pwcToken;					//�����ڵ� ��ū

	TCHAR		m_pString[256];
	
	TCHAR*		m_pwcSearchData;			//�����ڵ� �˻� ������
	T_STR		m_pwcTokenData;				//�����ڵ� ��ū ������
	
	
	INT			m_iData;
	DWORD		m_TokenIndex;			//��ū �̆�����
	DWORD		m_TokenMaxSize;			//�ƽ� ���̺�?

public:
	void			SetToken(T_STR szToken) { m_pwcToken = szToken; }
	bool			BeginToken();
	const TCHAR*	GetNextTokenString();
	const TCHAR*	GetCurrentTokenString();
	
	bool			LoadBuffer(const TCHAR* strFileName);
	bool			CutDirName(const TCHAR* strFileName);

	INT				SearchTokenArray(INT NumObjType,const TCHAR** pObjectType, DWORD dwNextObjectIndex = 0);
	const TCHAR*	GetSearchString(const TCHAR* szSearchData, bool bLoop = true);
	//bool			DeleteBuffer();


public:
	ALoadToken();
	~ALoadToken();
};


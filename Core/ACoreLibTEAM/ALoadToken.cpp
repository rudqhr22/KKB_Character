#include "ALoadToken.h"

bool	ALoadToken::CutDirName(const TCHAR* strFileName)
{
	TCHAR Drive[MAX_PATH];
	TCHAR Dir[MAX_PATH];
	TCHAR FName[MAX_PATH];
	TCHAR Ext[MAX_PATH];

	_tsplitpath_s(strFileName, Drive, Dir, FName, Ext);
	m_szDirName = Drive;
	m_szDirName += Dir;
	m_szName = FName;
	m_szName += Ext;

	return true;
}


bool ALoadToken::LoadBuffer(const TCHAR* strFileName)
{

	LARGE_INTEGER FileSize;


	CutDirName(strFileName);

	m_hHandle = CreateFile(strFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);

	if (m_hHandle == NULL) return false;

	GetFileSizeEx(m_hHandle, &FileSize);				//�� ���� ���� ����Ʈ Ȯ��

	m_pmbStaticMeshData = new char[FileSize.LowPart];	//������ ��ŭ ��Ƽ����Ʈ�� �Ҵ�

	DWORD dwBytesRead;
	if (ReadFile(m_hHandle, m_pmbStaticMeshData, FileSize.LowPart, &dwBytesRead, NULL) == FALSE)	//�������Ͽ� ���� �񵿱�� ��� �Ҽ� �ִ�.
	{
		delete[] m_pmbStaticMeshData;
		CloseHandle(m_hHandle);
		return false;
	}
	


	m_pwcStaticMeshData = new TCHAR[FileSize.LowPart];

	TCHAR* szMeshData = NULL;
	TCHAR* SearchString = NULL;
	size_t convertedChars = 0;

	//��Ƽ ����Ʈ �����͸� �����ڵ�� ī��
	mbstowcs_s(&convertedChars, m_pwcStaticMeshData, FileSize.LowPart, m_pmbStaticMeshData, _TRUNCATE);

	delete[] m_pmbStaticMeshData;	//��Ƽ����Ʈ �޽������ʹ� �ʿ� ������ �����ش�.
	m_pmbStaticMeshData = NULL;

	//�޽������͸� ��ū �����Ϳ� �־��ش�
	m_pwcTokenData = m_pwcStaticMeshData;	
	//m_pwcSearchData = m_pwcStaticMeshData;	


	CloseHandle(m_hHandle);


	BeginToken();		

	return true;
}



bool ALoadToken::BeginToken()
{
	m_TokenIndex = 0;
	m_TokenMaxSize = 0;
	
	T_STR		strTokenData;
	strTokenData = m_pwcTokenData;

	//m_pwcToken = "*"
	size_t start, stop;
	size_t end = strTokenData.length();
	//=================================================================================================
	for (start = strTokenData.find_first_not_of(m_pwcToken);			//��ū�� ���۵��� ���� ù����  
		0 <= start && start < end;								
		start = strTokenData.find_first_not_of(m_pwcToken, stop + 1))	
	{
		stop = strTokenData.find_first_of(m_pwcToken, start);			//���� ��ū�� ã�Ƽ� stop

		//���ܻ���
		if (stop < 0 || stop > end) {
			stop = end;
		}
		m_ListTokens.push_back(strTokenData.substr(start, stop - start));
	}
	//=================================================================================================
	
	m_TokenMaxSize = (DWORD)m_ListTokens.size();

	return true;
}


//���ڸ� ����
const TCHAR* ALoadToken::GetSearchString(const TCHAR* szSearchData, bool bLoop)
{
	//ã�� ��Ʈ�� �˻�
	const TCHAR* szSearchStr = NULL;
	GetNextTokenString();		//��������
	if (!bLoop)					//�ݺ����� �ʰٴٸ� ���� ã��, ����
	{
		szSearchStr = _tcsstr(m_pwcTokenData.c_str(), szSearchData);	//��Ʈ�� ���Լ�
		if (szSearchStr == NULL)
		{
			--m_TokenIndex;
		}
	}
	else
	{	//�⺻������ �ݺ�
		szSearchStr = _tcsstr(m_pwcTokenData.c_str(), szSearchData);	//��Ʈ�� ���Լ�
		while (szSearchStr == NULL)
		{
			GetNextTokenString();
			szSearchStr = _tcsstr(m_pwcTokenData.c_str(), szSearchData);
			if (_tcsstr(m_pwcTokenData.c_str(), szSearchData) != NULL)
			{
				break;
			}
		}
	}
	return szSearchStr;
}

const TCHAR* ALoadToken::GetNextTokenString()
{
	if (m_TokenIndex + 1 >= m_TokenMaxSize)			//�ִ�ġ �������� ���� ��ȯ
	{
		return NULL;
	}

	m_pwcTokenData = m_ListTokens[++m_TokenIndex].c_str();	//��ū ���� ����Ʈ[������] ������ �־��ش�.
	return m_pwcTokenData.c_str();
}

//��ū�� �ִ� ���ڸ� �ѱ�
const TCHAR* ALoadToken::GetCurrentTokenString()
{
	return m_pwcTokenData.c_str();
}


//���� �������� �Ѿ�鼭, �迭�� �ִ� ���ڿ��� ���ư��鼭 ��� �񱳸� �Ѵ�. �׷��� �Ѿ�� ������ ���� �߿���.
INT ALoadToken::SearchTokenArray(INT NumObjType, const TCHAR** pObjectType, DWORD dwNextObjectIndex)
{
	INT iIndex = -1;
	bool IsLineCheck = true;

	while (IsLineCheck)
	{
		//if (dwNextObjectIndex > 0 && dwNextObjectIndex - 1 <= m_TokenIndex)
		//{
		//	//�ƹ� �͵� ���� �� -1�� ���� �Ѵ�.?
		//	break;
		//}

		if (GetNextTokenString() == NULL) break;

		for (INT iType = 0; iType < NumObjType; iType++)
		{
			if (_tcsstr(m_pwcTokenData.c_str(), pObjectType[iType]) != NULL)
			{
				iIndex = iType;
				IsLineCheck = false;
				break;
			}
		}

	}
	return iIndex;
}

ALoadToken::ALoadToken()
{
	ZeroMemory(m_pString, sizeof(TCHAR) * 256);
	m_pmbStaticMeshData = 0;
	m_pwcStaticMeshData = 0;
	m_pwcToken = _T("*");
}


ALoadToken::~ALoadToken()
{
}

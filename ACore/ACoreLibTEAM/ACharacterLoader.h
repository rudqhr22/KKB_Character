#pragma once
#include "AAseObjStd.h"


class ACharacterLoader
{
public:
	FILE * m_pStream;
	TCHAR	m_pBuffer[256];
	TCHAR	m_pString[256];

public:
	BOOL			GetDataFromSkinMeshString(const TCHAR* pString, void* pData0, void* pData1);

public:
	BOOL	ComparisonData(TCHAR* pDestString, TCHAR* pSrcString = NULL);
	
	BOOL	OpenStream(const TCHAR* pFileName);
	BOOL    CloseStream() { fclose(m_pStream); return TRUE; };
	BOOL	GetData(VOID* pData, INT DataType);
	// ��ü���Ͽ��� �ش� ���ڿ��� ã���� ���� �˻��ϰ� ���������͸� ������������ �ű��.
	BOOL	GetDataFromFileLoop(const TCHAR* pString = NULL, VOID* pData = NULL, INT DataType = NULL_DATA);
	// ���������� ������� ���忭�� ã�� ������������ ���������͸� �ű��.
	BOOL	GetDataFromFileNext(TCHAR* pString = NULL, VOID* pData = NULL, INT DataType = NULL_DATA);
	// ���ϴ� ���ڿ��� ã�� ã�� ���ڿ� ������ġ�� �ű��
	BOOL	GetDataFromFileString(TCHAR* pString = NULL, VOID* pData = NULL, INT DataType = NULL_DATA);
	// ���������� ������� �ش繮�ڿ��� ã�� �˻��� �����ϸ� ���� �������� ���������͸� �ű��.
	BOOL	GetDataFromFile(TCHAR* pString = NULL, VOID* pData = NULL, INT DataType = NULL_DATA);
	BOOL    GetNodeName(TCHAR* pString = NULL, VOID* pData = NULL, INT DataType = NULL_DATA);

public:
	ACharacterLoader();
	virtual ~ACharacterLoader();
};


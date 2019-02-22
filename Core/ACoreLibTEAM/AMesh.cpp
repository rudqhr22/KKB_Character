#include "AMesh.h"
#include "ObjectManager.h"


int	AMesh::IsEqulVertex(vector<PNCT_VERTEX>&  VertexArray, PNCT_VERTEX& Vertex)
{
	for (int iVertex = 0; iVertex < VertexArray.size(); iVertex++)
	{
		if (VertexArray[iVertex]== Vertex)
		{
			return iVertex;
		}
	}
	return -1;
}

int AMesh::IsEqulVertexList(vector<PNCT_VERTEX>&  VertexArray, PNCT_VERTEX& Vertex)
{
	for (int iVertex = 0; iVertex < m_AseVertexList.size(); iVertex++)
	{
		if (m_AseVertexList[iVertex] == Vertex)
		{
			return iVertex;
		}
	}
	return -1;
}


//void		 AMesh::MakeBuffer()
//{
//	int iNumFaces = m_AseFaceList.size() / 3;
//	m_AseVertexList.reserve(iNumFaces * 3);
//	m_AseIndexList.reserve(iNumFaces * 3);
//
//
//	for (int iCnt = 0; iCnt < m_AseFaceList.size(); iCnt++)
//	{
//		int iPosReturn = IsEqulVertex(m_AseVertexList, m_AseFaceList[iCnt]);
//		if (iPosReturn < 0)
//		{
//			m_AseVertexList.push_back(m_AseFaceList[iCnt]);
//			iPosReturn = m_AseVertexList.size() - 1;
//		}
//		m_AseIndexList.push_back(iPosReturn);
//	}
//
//}
//
//int		 AMesh::MakeSubBuffer(vector<PNCT_VERTEX>& vVertex, int isub, int addcnt)
//{
//
//	int iNumFaces = vVertex.size()/3;
//	m_AseVertexList.reserve(iNumFaces);
//	m_AseIndexList.reserve(iNumFaces);
//
//	iNumFaces = 0;
//	PNCT_VERTEX  triSame;
//	triSame.iSubIndex = isub;
//
//	if (isub >= 0)
//	{
//		//IsTriangleSame(isub);
//
//		iNumFaces = count_if(vVertex.begin(), vVertex.end(), IsiSubSame(triSame));
//
//		/*	for (auto A = vVertex.begin(); A < vVertex.end(); A++)
//			{
//				if (A->iSubIndex == isub)
//				{
//					++iNumFaces;
//				}
//			}*/
//	}
//
//	if (addcnt > 0 && iNumFaces>0)
//	{
//		int a = 666;
//	}
//
//	for (int iCnt = 0; iCnt < iNumFaces; iCnt++)
//	{
//		int iPosReturn = IsEqulVertex(m_AseVertexList, vVertex[addcnt+iCnt]);
//		if (iPosReturn < 0)
//		{
//			m_AseVertexList.push_back(vVertex[addcnt+iCnt]);
//			iPosReturn = m_AseVertexList.size() - 1;
//		}
//		m_AseIndexList.push_back(iPosReturn);
//
//	}
//	return iNumFaces;
//}


int AMesh::SetUniqueBuffer(vector <ATri>& TriList, int iMtrl, int iStartTri)
{
	int iNumFaces = TriList.size();
	m_AseVertexList.reserve(iNumFaces * 3);
	m_AseIndexList.reserve(iNumFaces * 3);

	ATri  triSame(iMtrl);
	if (iMtrl >= 0)
	{
		iNumFaces = count_if(TriList.begin(), TriList.end(), IsTriangleSame(triSame));
	}

	for (int iFace = 0; iFace < iNumFaces; iFace++)
	{
		for (int iCnt = 0; iCnt < 3; iCnt++)
		{
			int iPosReturn = IsEqulVertexList(m_AseVertexList, TriList[iStartTri + iFace].vVertex[iCnt]);
			if (iPosReturn < 0)
			{
				m_AseVertexList.push_back(TriList[iStartTri + iFace].vVertex[iCnt]);
				iPosReturn = m_AseVertexList.size() - 1;
			}
			m_AseIndexList.push_back(iPosReturn);
		}
	}

	return iNumFaces;
}


AMesh::AMesh()
{
	m_pParent = NULL;
	D3DXMatrixIdentity(&m_matLocal);
	D3DXMatrixIdentity(&m_matWorldTrans);
	D3DXMatrixIdentity(&m_matWorldRotate);
	D3DXMatrixIdentity(&m_matWorldScale);
	D3DXMatrixIdentity(&m_matCalculation);
	m_bUnAnimObj = false;
	m_bSelect = false;
}


AMesh::~AMesh()
{
	SAFE_DEL(m_pParent);

	m_pSubMesh.clear();
	m_pChildMesh.clear();

	

}





bool AAnimation::GetAnimationTrack(float fFrame, vector<AAnimTrack*>& pTrackList, AAnimTrack** pStartTrack, AAnimTrack** pEndTrack)
{
	for (DWORD dwTrack = 0; dwTrack < pTrackList.size(); dwTrack++)
	{
		AAnimTrack *pTrack = pTrackList[dwTrack];
		_ASSERT(pTrack);
		// fFrame 보다 큰 Tick 트랙이 있다면 이전 트랙을 넘겨 주어야 하기 때문에 break한다.
		if (pTrack->iTick > fFrame)
		{
			*pEndTrack = pTrack;
			break;
		}
		// 현프레임보다 큰값이 없다면. 가장 시간경과가 오래된 것을 사용한다.
		*pStartTrack = pTrack;
	}
	return (*pStartTrack != NULL) ? true : false;
}

D3DXMATRIX AAnimation::Interpolate(AMesh* pMesh, D3DXMATRIX* matParents, float fFrameTick, AScene tScene)
{

	// TM		= AnimMat * ParentTM;
	// AaniMat	= TM * Inverse(ParentTM)
	D3DXQUATERNION qR, qS;
	D3DXMATRIX matAnim, matPos, matRotate, matScale, matCalculation;

	D3DXMatrixIdentity(&matCalculation);

	matRotate = pMesh->m_matWorldRotate;
	matPos = pMesh->m_matWorldTrans;
	matScale = pMesh->m_matWorldScale;

	D3DXQuaternionRotationMatrix(&qR, &matRotate);
	D3DXQuaternionRotationMatrix(&qS, &matScale);

	// fFrameTick = m_Scene.iFirstFrame * m_Scene.iTickPerFrame + CurFame;
	float fStartTick = tScene.iFirstFrame * tScene.iTickPerFrame;
	float fEndTick = 0.0f;

	AAnimTrack* pStartTrack = NULL;
	AAnimTrack* pEndTrack = NULL;
	if (pMesh->m_RotTrack.size())
	{
		// pStartTrack를 찾을수 있으면
		if (GetAnimationTrack(fFrameTick, pMesh->m_RotTrack, &pStartTrack, &pEndTrack))
		{
			qR = pStartTrack->qRotate;
			fStartTick = pStartTrack->iTick;
		}
		if (pEndTrack)
		{
			fEndTick = pEndTrack->iTick;
			D3DXQuaternionSlerp(&qR, &qR, &pEndTrack->qRotate, (fFrameTick - fStartTick) / (fEndTick - fStartTick));
		}
		D3DXMatrixRotationQuaternion(&matRotate, &qR);
	}

	pStartTrack = NULL;
	pEndTrack = NULL;

	D3DXVECTOR3 Trans(matPos._41, matPos._42, matPos._43);
	if (pMesh->m_PosTrack.size())
	{
		// pStartTrack를 찾을수 있으면
		if (GetAnimationTrack(fFrameTick, pMesh->m_PosTrack, &pStartTrack, &pEndTrack))
		{
			Trans = pStartTrack->vVector;
			fStartTick = pStartTrack->iTick;
		}
		if (pEndTrack)
		{
			fEndTick = pEndTrack->iTick;
			D3DXVec3Lerp(&Trans, &Trans, &pEndTrack->vVector, (fFrameTick - fStartTick) / (fEndTick - fStartTick));
		}

		D3DXMatrixTranslation(&matPos, Trans.x, Trans.y, Trans.z);
	}


	pStartTrack = NULL;
	pEndTrack = NULL;

	D3DXMATRIX matScaleRot, matInvScaleRot;
	D3DXVECTOR3 vScale(matScale._11, matScale._22, matScale._33);
	if (pMesh->m_SclTrack.size())
	{
		// pStartTrack를 찾을수 있으면
		if (GetAnimationTrack(fFrameTick, pMesh->m_SclTrack, &pStartTrack, &pEndTrack))
		{
			vScale = pStartTrack->vVector;
			qS = pStartTrack->qRotate;
			fStartTick = pStartTrack->iTick;
		}
		if (pEndTrack)
		{
			fEndTick = pEndTrack->iTick;
			D3DXVec3Lerp(&vScale, &vScale, &pEndTrack->vVector, (fFrameTick - fStartTick) / (fEndTick - fStartTick));
			D3DXQuaternionSlerp(&qS, &qS, &pEndTrack->qRotate, (fFrameTick - fStartTick) / (fEndTick - fStartTick));
		}
		D3DXMatrixScaling(&matScale, vScale.x, vScale.y, vScale.z);
		D3DXMatrixRotationQuaternion(&matScaleRot, &qS);
		D3DXMatrixInverse(&matInvScaleRot, NULL, &matScaleRot);
		matScale = matInvScaleRot * matScale * matScaleRot;
	}

	pStartTrack = NULL;
	pEndTrack = NULL;

	float fCurAlpha, fNextAlpha, fOffSet;
	fCurAlpha = 0.0f;
	fNextAlpha = 0.0f;
	//if (pMesh->m_VisTrack.size())
	//{
	//	// pStartTrack를 찾을수 있으면
	//	if (GetAnimationTrack(fFrameTick, pMesh->m_VisTrack, &pStartTrack, &pEndTrack))
	//	{
	//		fCurAlpha = pStartTrack->vVector.x;
	//		fStartTick = pStartTrack->iTick;
	//	}
	//	if (pEndTrack)
	//	{
	//		fNextAlpha = pEndTrack->vVector.x;
	//		fEndTick = pEndTrack->iTick;

	//		fOffSet = (fFrameTick - fStartTick) / (fEndTick - fStartTick);
	//		fNextAlpha = (fNextAlpha - fCurAlpha)*fOffSet;
	//	}
	//	pMesh->m_VisTrack = (fCurAlpha + fNextAlpha);
	//}
	//else
	//{
	//	pMesh->m_fVisibility = 1.0f;
	//}

	D3DXMatrixMultiply(&matAnim, &matScale, &matRotate);
	matAnim._41 = matPos._41;
	matAnim._42 = matPos._42;
	matAnim._43 = matPos._43;
	// 최종 에미메이션 행렬을 완성한다.	
	D3DXMatrixMultiply(&matCalculation, &matAnim, matParents);

	// 인버스 매트릭스 확인 코드.
	D3DXVECTOR3 v0, v1, v2, v3;
	v0 = pMesh->m_matCalculation.m[0];
	v1 = pMesh->m_matCalculation.m[1];
	v2 = pMesh->m_matCalculation.m[2];
	D3DXVec3Cross(&v3, &v1, &v2);
	if (D3DXVec3Dot(&v3, &v0) < 0.0f)
	{
		D3DXMATRIX matW;
		D3DXMatrixScaling(&matW, -1.0f, -1.0f, -1.0f);
		D3DXMatrixMultiply(&matCalculation, &pMesh->m_matCalculation, &matW);
	}
	return matCalculation;
}

D3DXMATRIX AAnimation::Update(float fElapseTime, AMesh* pMesh, D3DXMATRIX &matParent, AScene &tScene)
{
	D3DXMATRIX mat, matReturn;
	D3DXMatrixIdentity(&mat);
	D3DXMatrixIdentity(&matReturn);

	if (pMesh->m_bUnAnimObj != false)
	{
		if (pMesh->m_pParent)
			return Interpolate(pMesh, &matParent, fElapseTime, tScene);
		else
			return Interpolate(pMesh, &mat, fElapseTime, tScene);
	}

	return mat;
}

AAnimation::AAnimation(void)
{
}

AAnimation::~AAnimation(void)
{
}

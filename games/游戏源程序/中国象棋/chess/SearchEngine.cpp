// SearchEngine.cpp: implementation of the CSearchEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "chess.h"
#include "SearchEngine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSearchEngine::CSearchEngine()
{

}

CSearchEngine::~CSearchEngine()
{
	delete m_pMG;	//ɾ���������������ϵ��߷�������
	delete m_pEval;	//ɾ���������������ϵĹ�ֵ����
}

//���ݴ�����߷��ı�����
//move��Ҫ���е��߷�
BYTE CSearchEngine::MakeMove(CHESSMOVE* move)
{
	BYTE	nChessID;
	//ȡĿ��λ�õ�����
	nChessID = CurPosition[move->To.y][move->To.x];
	//�������ƶ���Ŀ��λ����
	CurPosition[move->To.y][move->To.x] = 
	CurPosition[move->From.y][move->From.x];
	//��ԭλ�����
	CurPosition[move->From.y][move->From.x] = NOCHESS;
	return nChessID;	//���ر��Ե�������
}

//����Ҫ������߷��ظ�����
//move��Ҫ�ָ����߷�
//nChessID��Ҫԭ������moveĿ��λ�õ���������
void CSearchEngine::UnMakeMove(CHESSMOVE *move,BYTE nChessID)
{
	//��Ŀ��λ�ú����ӿ���ԭλ
	CurPosition[move->From.y][move->From.x] = 
		CurPosition[move->To.y][move->To.x];
	//�ָ�Ŀ��λ�õ�����
	CurPosition[move->To.y][move->To.x] = nChessID;
}

//���Լ�����������Ϸ�Ƿ����
//���δ����,����0,���򷵻ؼ���/��Сֵ
int CSearchEngine::IsGameOver(BYTE position[10][9],int nDepth)
{
	int i,j;
	BOOL RedLive = FALSE,BlackLive = FALSE;
	//���췽�Ź��Ƿ��н�˧
	for(i = 7;i < 10; i++)
	{
		for(j = 3; j < 6; j++)
		{
			if(position[i][j] == B_KING)
				BlackLive = TRUE;
			if(position[i][j] == R_KING)
				RedLive = TRUE;
		}
	}
	//���ڷ��Ź��Ƿ��н�˧
	for(i = 0; i < 3; i++)
	{
		for(j = 3; j < 6; j++)
		{
			if(position[i][j] == B_KING)
				BlackLive = TRUE;
			if(position[i][j] == R_KING)
				RedLive = TRUE;
		}
	}
	i = (m_nMaxDepth - nDepth + 1) % 2; //ȡ��ǰ����ż��־

	if(!RedLive)	//�콫�Ƿ�����
	{
		if(i)
			return 19990 + nDepth;	//�����㷵�ؼ���ֵ
		else
			return - 19990 - nDepth;	//ż���㷵�ؼ�Сֵ
	}
	if(!BlackLive)
	{
		if(i)
			return - 19990 - nDepth;	//�����㷵�ؼ�Сֵ
		else
			return - 19990 + nDepth;	//ż���㷵�ؼ���ֵ
	}

	return 0;//����������,����0
}

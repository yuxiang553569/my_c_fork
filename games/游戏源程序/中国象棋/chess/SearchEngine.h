// SearchEngine.h: interface for the CSearchEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEARCHENGINE_H__A3277FA2_5470_4CA3_887F_CA5C55F5D2AB__INCLUDED_)
#define AFX_SEARCHENGINE_H__A3277FA2_5470_4CA3_887F_CA5C55F5D2AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MoveGenerator.h"
#include "Eveluation.h"

//��������Ļ��� .����ӿڼ���������.
class CSearchEngine  
{
public:
	CSearchEngine();
	virtual ~CSearchEngine();
	//���Ľӿ�,Ϊ��ǰ�����߳���һ����
	virtual SearchAGoodMove(BYTE position[10][9])=0;
	//�趨����������
	virtual SetSearchDepth(int nDepth){m_nSearchDepth = nDepth;};
	//��ƹ�ֵ����
	virtual SetEveluator(CEveluation *pEval){m_pEval = pEval;};
	//�趨�߷�������
	virtual SetMoveGenerator(CMoveGenerator *pMG){m_pMG = pMG;};

protected:
	//����ĳһ�߷����������Ժ������
	virtual BYTE MakeMove(CHESSMOVE* move);
	//�ָ�ĳһ�߷�����������Ϊ�߹�֮ǰ��
	virtual void UnMakeMove(CHESSMOVE* move,BYTE type);
	//�����жϵ�ǰ�����Ƿ��Ѿ��ֳ�ʤ��
	virtual int IsGameOver(BYTE position[10][9], int nDepth);
	//�������ڵ�ǰ�ڵ�����״̬������
	BYTE CurPosition[10][9];
	//��¼����߷��ı���
	CHESSMOVE m_cmBestMove;
	//�߷�������ָ��
	CMoveGenerator *m_pMG;
	//��ֵ����ָ��
	CEveluation *m_pEval;
	//����������	
	int m_nSearchDepth;
	//��ǰ����������������
	int m_nMaxDepth;

};

#endif // !defined(AFX_SEARCHENGINE_H__A3277FA2_5470_4CA3_887F_CA5C55F5D2AB__INCLUDED_)

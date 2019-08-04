// NegaMaxEngine.h: interface for the CNegaMaxEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEGAMAXENGINE_H__A34B36C1_E7A6_4353_86D4_199592A72698__INCLUDED_)
#define AFX_NEGAMAXENGINE_H__A34B36C1_E7A6_4353_86D4_199592A72698__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SearchEngine.h"

//��������. ʹ�ø�����ֵ���� ��CSearchEngine������
class CNegaMaxEngine : public CSearchEngine
{
public:
	CNegaMaxEngine();
	virtual ~CNegaMaxEngine();
	//�����ҳ������������һ���߷�
	virtual SearchAGoodMove(BYTE position[10][9]);

protected:
	int NegaMax(int depth);	//������ֵ��������

};

#endif // !defined(AFX_NEGAMAXENGINE_H__A34B36C1_E7A6_4353_86D4_199592A72698__INCLUDED_)

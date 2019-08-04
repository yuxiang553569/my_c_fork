// Logic.h: interface for the Logic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGIC_H__6EA3C45A_E5BF_4EEE_B2D3_A3A91475C32A__INCLUDED_)
#define AFX_LOGIC_H__6EA3C45A_E5BF_4EEE_B2D3_A3A91475C32A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define maxnum 20
#include <math.h>
#include "iostream.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <Winbase.h>

class Logic  
{
public:
	Logic();
	virtual ~Logic();
private:

public:


	void Deal();
	bool LogicCheck(int tablenum,int* CurrentCards,int CurrentLen,int PreType,int PrePoint,int PreLen);
	bool RuleCheck(int tablenum,int* CurrentCards,int CurrentLen);
	bool flowCheck(int tablenum,int* CurrentCards,int CurrentLen,int PreType,int PrePoint,int PreLen);
	void SortPok(int tablenum,int* CurrentCards,int CurrentLen);
	bool DoubleCheck(int tablenum,int* CurrentCards);
	bool Bombcheck(int tablenum,int* CurrentCards);
	bool ThreeOneCheck(int tablenum,int* CurrentCards);
	bool ThreeTowCheck(int tablenum,int *CurrentCards);
	bool ThreeCheck(int tablenum,int* CurrentCards);
	bool ListCheck(int tablenum,int* CurrentCards,int CurrentLen);
	bool SisterDoubleCheck(int tablenum,int* CurrentCards,int CurrentLen);
	bool PlaneOneCheck(int tablenum,int* CurrentCards,int CurrentLen);
	bool PlaneTwoCheck(int tablenum,int* CurrentCards,int CurrentLen);
//	void BombWarning(int tablenum);
	int  GetPoint(int tablenum);
	int  GetType(int tablenum);
	bool bombWarning(int tablenum);
	int  pointCheck(int tablenum,int pok);
};

#endif // !defined(AFX_LOGIC_H__6EA3C45A_E5BF_4EEE_B2D3_A3A91475C32A__INCLUDED_)

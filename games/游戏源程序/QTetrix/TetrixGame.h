// TetrixGame.h: interface for the CTetrixGame class.
//
//////////////////////////////////////////////////////////////////////

#ifndef TETRIXGAME_H
#define TETRIXGAME_H
#include "stdlib.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define		LINUXPLATFORM

#define		MAPWIDTH		240
#define		MAPHEIGHT		480
#define		LEFTSPAN		10
#define		TOPSPAN			20

#define		NOTEMAPWIDTH            144		//提示区域的底图宽度
#define		NOTEMAPHEIGHT           144		//提示区域的底图高度
#define		NOTELEFTSPAN            280		//提示区域左上角在对话框中的横坐标位置
#define		NOTETOPSPAN		50		//提示区域左上角在对话框中的纵坐标位置

#define		TETRIXLEN		24
/*****************************************************************************
*********描述游戏矩阵中每个小矩形的状态;如果是空白状态，屏幕不显示方块，******
*********只能看到底图；如果有正在下落的方块，则屏幕应显示彩色方块；如果 ******
*********处于静止状态，则屏幕应显示灰色方块；将这三个状态设置为三个宏， ******
*********分别为BLANK、RUNNING和STOPPING                                 ******
*****************************************************************************/
#define		BLANK			0
#define		RUNNING			1
#define		STOPPING		2
#define		CLEARING		3

#define		GAMERUNNING		0
#define		GAMEPAUSE		1
#define		GAMEOVER		2

#define		XLEN			10
#define		YLEN			20

//描述7种不同类型方块的类型编号
#define		TYPEI			1
#define		TYPEZ			2
#define		TYPES			3
#define		TYPEO			4
#define		TYPET			5
#define		TYPEL			6
#define		TYPEJ			7

#ifdef	WINPLATFORM
typedef		__int8			SINT;
#else
#define         TRUE        true
#define         FALSE       false
typedef		short			SINT;

typedef         int         INT;
typedef         bool        BOOL;

#endif

//描述每个不同类型的方块的基本信息，x、y分别表示横纵坐标
struct tetrix
{
	SINT		x;
	SINT		y;
};
typedef		struct tetrix	TETRIX;

class CTetrixGame  
{
public:
	SINT DoDirectDrop();
	SINT GenNew();
	void DoClear();
	void SetClearStatus(SINT status);
	SINT PrepareClear();
	SINT DoDrop();
	INT GetGameScore();
	INT GetGameLevel();
	void SetGameStatus(SINT status);
	SINT GetGameStatus();
	void GameOver();
	int GoRight();
	int GoLeft();
	BOOL JudgeMatrixStatus(SINT x, SINT y, SINT status);
	int DoRotate();
	int GameStart();
	SINT UpdateScoreAndLevel();
	SINT GetNoteTriXPos(SINT i){return m_arNextTri[i].x;};
	SINT GetNoteTriYPos(SINT i){return m_arNextTri[i].y;};
	CTetrixGame();
	virtual ~CTetrixGame();
protected:
	BOOL CopyTri(TETRIX *artridest, TETRIX *artrisrc);

	
	
	void SetRowStatus(SINT arMatrix[][YLEN], SINT row, SINT  status);
	//根据arTetrix方块最后的位置和arMatrix的状态，先通过GetTetrixYPos函数
	//来得到扫描行的起始位置，再调用GetCanBeClearedRow得到需要消行的行集合，
	//然后将可以消去的行消去，并将该行状态全部置为BLANK，将上面的行进行下移，
	//同时更新位置状态;
	//arClearedRow数组中的行位置是按坐标的从大到小排列的，也就是从底部到顶部，
	//这样的排列有利于消行后其上面的行的下移操作
	//函数返回消去的行数
	SINT DoClearRow(SINT arMatrix[][YLEN], 
						SINT* arClearedRow, SINT arsize );

	//该函数利用从GetTetrixYPos函数中返回的最小行坐标和最大行坐标，
	//将MinY传递给startY，将MaxY传递给endY，从而获得扫描行的范围从startY到endY，
	//将满足消行条件的行坐标存储在数组arClearedRow中，arsize返回这个数组的大小，
	//arsize为零表示没有可以消去的行
	void GetCanBeClearedRow(SINT arMatrix[][YLEN], SINT startY, 
					SINT endY, SINT *arClearedRow, SINT &arsize);

	//从方块arTetrix中取得方块所在的最小行坐标MinY和最大行坐标MaxY
	void GetTetrixYPos(TETRIX *arTetrix, SINT &MinY, SINT &MaxY);

	//判断方块artri是否出界或重叠
	INT OutOfMatrixOROverlap(SINT arMatrix[][YLEN], TETRIX* artri, INT arsize);

	//完成TETRIX数组的拷贝
	void CopyTetrixArray(TETRIX* ardest, TETRIX* arsrc, INT arsize);
	void DropTetrix(TETRIX *artri, INT arsize);
	void MoveRightTetrix(TETRIX *artri, INT arsize);
	void MoveLeftTetrix(TETRIX *artri, INT arsize);
	void SetStatus(SINT arMatrix[][YLEN], 
		TETRIX *arCurTri, INT status);
	BOOL RotateTetrix(TETRIX *artri, 
				INT arsize, INT rottimes );
	BOOL GenerateOneTetrix(SINT type, TETRIX* artri);
protected:
	SINT		m_arMatrix[XLEN][YLEN];
	//在备选7种类型的方块中选择一种类型的方块存储在一个TETRIX（前面定义的）数组中，
	//长度为5，第一个元素表示类型和旋转轴，后四个表示方块在6*6矩阵中的相对位置
	TETRIX		m_arCurrentTri[5];
	TETRIX		m_arNextTri[5];
	INT			m_rotTimes;
	SINT		m_GameStatus;

	INT			m_iScore;					//游戏计分
	SINT		m_iLevel;					//游戏当前等级
	INT			m_iGradeScore;				//当前等级提高的分数限制

	SINT		m_arclearRow[4];
	SINT		m_arclearsize;
	
};

#endif

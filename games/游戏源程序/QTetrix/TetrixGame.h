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

#define		NOTEMAPWIDTH            144		//��ʾ����ĵ�ͼ���
#define		NOTEMAPHEIGHT           144		//��ʾ����ĵ�ͼ�߶�
#define		NOTELEFTSPAN            280		//��ʾ�������Ͻ��ڶԻ����еĺ�����λ��
#define		NOTETOPSPAN		50		//��ʾ�������Ͻ��ڶԻ����е�������λ��

#define		TETRIXLEN		24
/*****************************************************************************
*********������Ϸ������ÿ��С���ε�״̬;����ǿհ�״̬����Ļ����ʾ���飬******
*********ֻ�ܿ�����ͼ���������������ķ��飬����ĻӦ��ʾ��ɫ���飻��� ******
*********���ھ�ֹ״̬������ĻӦ��ʾ��ɫ���飻��������״̬����Ϊ�����꣬ ******
*********�ֱ�ΪBLANK��RUNNING��STOPPING                                 ******
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

//����7�ֲ�ͬ���ͷ�������ͱ��
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

//����ÿ����ͬ���͵ķ���Ļ�����Ϣ��x��y�ֱ��ʾ��������
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
	//����arTetrix��������λ�ú�arMatrix��״̬����ͨ��GetTetrixYPos����
	//���õ�ɨ���е���ʼλ�ã��ٵ���GetCanBeClearedRow�õ���Ҫ���е��м��ϣ�
	//Ȼ�󽫿�����ȥ������ȥ����������״̬ȫ����ΪBLANK����������н������ƣ�
	//ͬʱ����λ��״̬;
	//arClearedRow�����е���λ���ǰ�����ĴӴ�С���еģ�Ҳ���Ǵӵײ���������
	//�������������������к���������е����Ʋ���
	//����������ȥ������
	SINT DoClearRow(SINT arMatrix[][YLEN], 
						SINT* arClearedRow, SINT arsize );

	//�ú������ô�GetTetrixYPos�����з��ص���С���������������꣬
	//��MinY���ݸ�startY����MaxY���ݸ�endY���Ӷ����ɨ���еķ�Χ��startY��endY��
	//����������������������洢������arClearedRow�У�arsize�����������Ĵ�С��
	//arsizeΪ���ʾû�п�����ȥ����
	void GetCanBeClearedRow(SINT arMatrix[][YLEN], SINT startY, 
					SINT endY, SINT *arClearedRow, SINT &arsize);

	//�ӷ���arTetrix��ȡ�÷������ڵ���С������MinY�����������MaxY
	void GetTetrixYPos(TETRIX *arTetrix, SINT &MinY, SINT &MaxY);

	//�жϷ���artri�Ƿ������ص�
	INT OutOfMatrixOROverlap(SINT arMatrix[][YLEN], TETRIX* artri, INT arsize);

	//���TETRIX����Ŀ���
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
	//�ڱ�ѡ7�����͵ķ�����ѡ��һ�����͵ķ���洢��һ��TETRIX��ǰ�涨��ģ������У�
	//����Ϊ5����һ��Ԫ�ر�ʾ���ͺ���ת�ᣬ���ĸ���ʾ������6*6�����е����λ��
	TETRIX		m_arCurrentTri[5];
	TETRIX		m_arNextTri[5];
	INT			m_rotTimes;
	SINT		m_GameStatus;

	INT			m_iScore;					//��Ϸ�Ʒ�
	SINT		m_iLevel;					//��Ϸ��ǰ�ȼ�
	INT			m_iGradeScore;				//��ǰ�ȼ���ߵķ�������

	SINT		m_arclearRow[4];
	SINT		m_arclearsize;
	
};

#endif

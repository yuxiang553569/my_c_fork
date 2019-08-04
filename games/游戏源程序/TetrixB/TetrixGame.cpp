// TetrixGame.cpp: implementation of the CTetrixGame class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "TetrixB.h"
#include "TetrixGame.h"
#include "assert.h"
#ifdef _DEBUG
#include "TIME.H"
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CTetrixGame::CTetrixGame()
{
	SINT i, j;
	//游戏屏幕矩阵10*20的初始化，初始状态都为空
	for( i = 0; i < XLEN; i++ )
		for(j = 0; j < YLEN; j++ )
			m_arMatrix[i][j] = BLANK;
}

CTetrixGame::~CTetrixGame()
{

}

/******************************************************************************
***生成一种类型的方块，type表示生成方块的类型，成功则返回TRUE，否则返回FALSE***
***每个方块使用m_arCurrentTri这个数组来描述，该数组有5个元素                ***
***第一个元素表示类型和旋转轴，后四个表示方块在6*6矩阵中的相对位置          ***
***该数组在游戏运行中，需要将6*6的矩阵匹配到游戏容器10*20的矩阵中           ***
******************************************************************************/
BOOL CTetrixGame::GenerateOneTetrix(SINT type, TETRIX* artri)
{
	assert((type > 7) || (type < 1));
	switch( type )
	{
	case	TYPEI:
		artri[1].x = 1;
		artri[1].y = 2;		
		artri[2].x = 2;
		artri[2].y = 2;		
		artri[3].x = 3;
		artri[3].y = 2;		
		artri[4].x = 4;
		artri[4].y = 2;		
		artri[0].x = TYPEI;
		artri[0].y = 3;
		break;
	case	TYPEZ:
		artri[1].x = 2;
		artri[1].y = 2;		
		artri[2].x = 3;
		artri[2].y = 2;		
		artri[3].x = 3;
		artri[3].y = 3;		
		artri[4].x = 4;
		artri[4].y = 3;		
		artri[0].x = TYPEZ;
		artri[0].y = 2;	
		break;
	case	TYPES:
		artri[1].x = 2;
		artri[1].y = 3;		
		artri[2].x = 3;
		artri[2].y = 3;		
		artri[3].x = 3;
		artri[3].y = 2;		
		artri[4].x = 4;
		artri[4].y = 2;		
		artri[0].x = TYPES;
		artri[0].y = 3;
		break;
	case	TYPEO:
		artri[1].x = 2;
		artri[1].y = 2;		
		artri[2].x = 3;
		artri[2].y = 2;		
		artri[3].x = 2;
		artri[3].y = 3;		
		artri[4].x = 3;
		artri[4].y = 3;		
		artri[0].x = TYPEO;
		artri[0].y = 0;
		break;
	case	TYPET:
		artri[1].x = 2;
		artri[1].y = 2;		
		artri[2].x = 3;
		artri[2].y = 2;		
		artri[3].x = 4;
		artri[3].y = 2;		
		artri[4].x = 3;
		artri[4].y = 3;		
		artri[0].x = TYPET;
		artri[0].y = 2;
		break;
	case	TYPEL:
		artri[1].x = 2;
		artri[1].y = 3;		
		artri[2].x = 2;
		artri[2].y = 2;		
		artri[3].x = 3;
		artri[3].y = 2;		
		artri[4].x = 4;
		artri[4].y = 2;		
		artri[0].x = TYPEL;
		artri[0].y = 3;
		break;
	case	TYPEJ:
		artri[1].x = 2;
		artri[1].y = 2;		
		artri[2].x = 3;
		artri[2].y = 2;		
		artri[3].x = 4;
		artri[3].y = 2;		
		artri[4].x = 4;
		artri[4].y = 3;		
		artri[0].x = TYPEJ;
		artri[0].y = 2;
		break;
	default:
		return FALSE;
		break;
	}
	return TRUE;
}

/*******************************************************************************
********************************************************************************
***将7个类别的方块分为三类：                                                 ***
***第一类只有一个类型的方块，即 O 类型，这种类型的方块没有旋转，因为旋转后还 ***
***是原来的样子，就像一个‘田’字，倒过来看还是同一个字                      ***
***第二类有三个类型的方块，即I、Z、S类型，这三种类型的方块只有两种旋转姿态， ***
***一种状态是默认的水平状态，另一种是在水平状态的基础上沿轴心顺时针旋转90度；***
***将每个方块从生成开始成功旋转的次数用一个变量（从0开始）记录下来，当这个变 ***
***量为偶数时，顺时针旋转90度；当这个变量为奇数时，将逆时针旋转90度（也就是顺***
***时针旋转-90度），这样就复原了                                             ***
***第三种类型的方块为 T、L、 J。不需要使用旋转变量了，每次顺时针旋转90度，   ***
***每次都使用同样的公式                                                      ***
********************************************************************************
********************************************************************************
***旋转公式：（顺时针）（图形按轴心顺时针旋转a度，x0，y0为轴心的坐标）**********
***		X’ – x0 = ( x – x0 )*cos(-a) + ( y – y0 )*sin(-a)		      **********
***		Y’ – y0 = -( x – x0 )*sin(-a) + ( y – y0 )*cos(-a)		      **********
***逆时针旋转的公式就是将上面的角度-a都换成a就可以了				  **********
********************************************************************************
*******************************************************************************/
//artri为传入的方块位置数组的头指针，arsize为该数组的长度，在本程序中应该为5
//rottimes为每个方块从生成开始记录的成功旋转的次数
BOOL CTetrixGame::RotateTetrix(TETRIX *artri, INT arsize, INT rottimes )
{
	if( arsize != 5 )
		return FALSE;
	SINT type = artri[0].x;
	SINT rotcenter = artri[0].y;
	if( rotcenter > 4 || rotcenter < 1 )
		return FALSE;
	if( rottimes < 0 )
		return FALSE;
	//记录旋转轴心的坐标
	SINT	centerx = artri[rotcenter].x;
	SINT	centery = artri[rotcenter].y;
	INT		i = 0;
	switch( type )
	{
	//第一类方块
	case	TYPEO:
		//不做任何处理
		break;
	//第二类方块
	case	TYPEI:
	case	TYPEZ:
	case	TYPES:
	//分成功旋转次数的奇偶来选择是如何旋转
		if( ( rottimes % 2 ) == 0 )
		{
			for( i = 1; i < arsize; i++ )
			{
				SINT tx = artri[i].x;
				SINT ty = artri[i].y;
				artri[i].x = centery - ty + centerx;
				artri[i].y = tx - centerx + centery;
			}
		}
		else
		{
			for( i = 1; i < arsize; i++ )
			{
				SINT tx = artri[i].x;
				SINT ty = artri[i].y;
				artri[i].x = ty - centery + centerx;
				artri[i].y = centerx - tx + centery;
			}
		}
		break;
	//第三类方块
	case	TYPET:
	case	TYPEL:
	case	TYPEJ:
		for( i = 1; i < arsize; i++ )
		{
			SINT tx = artri[i].x;
			SINT ty = artri[i].y;
			artri[i].x = centery - ty + centerx;
			artri[i].y = tx - centerx + centery;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

//将方块arCurTri在矩阵arMatrix中的位置设置为status
//status的值只能是BLANK，RUNNING，STOPPING中的一个
void CTetrixGame::SetStatus(SINT arMatrix[][YLEN], TETRIX *arCurTri, INT status)
{
	for( INT i = 1; i < 5; i++ )
	{
		INT xpos, ypos;
		xpos = arCurTri[i].x;
		ypos = arCurTri[i].y;
		arMatrix[ xpos ][ ypos ] = status;
	}
}

void CTetrixGame::MoveLeftTetrix(TETRIX *artri, INT arsize)
{
	if(arsize != 5)
		return;
	for( INT i = 1; i < arsize; i++ )
	{
		artri[i].x -= 1;
	}
}

void CTetrixGame::MoveRightTetrix(TETRIX *artri, INT arsize)
{
	if(arsize != 5)
		return;
	for( INT i = 1; i < arsize; i++ )
	{
		artri[i].x += 1;
	}
}

void CTetrixGame::DropTetrix(TETRIX *artri, INT arsize)
{
	if(arsize != 5)
		return;
	for( INT i = 1; i < arsize; i++ )
	{
		artri[i].y += 1;
	}
}

//ardest和arsrc都是TETRIX[5]的数组,arsize必须为5
//将arsrc的位置信息拷贝给ardest
void CTetrixGame::CopyTetrixArray(TETRIX *ardest, TETRIX *arsrc, INT arsize)
{
	if( arsize != 5 ) 
		return;
	for( INT i = 0; i < arsize; i++ )
	{
		ardest[i].x = arsrc[i].x;
		ardest[i].y = arsrc[i].y;
	}
}

//判断方块artri是否出界或重叠, arMatrix为游戏容器10*20的阵列，它是一个二维数组，它的只分别
//为BLANK（表示该位置空），RUNNING（该位置正有运行方块），STOPPING（该位置正有静止方块），
//返回6表示数组长度出错, 没有出界或重叠返回0
//如果出左界返回1，出右界返回2，出下界返回3，出上界返回4，重叠返回5
INT CTetrixGame::OutOfMatrixOROverlap(SINT arMatrix[][YLEN], TETRIX *artri, INT arsize)
{
	if( arsize != 5 )
		return 6;
	for( INT i = 1; i < arsize; i++ )
	{
		SINT	xpos = artri[i].x;
		SINT	ypos = artri[i].y;
		//出左界
		if( xpos < 0 )
			return 1;
		//出右界
		if( xpos >= XLEN )
			return 2;
		//出下界
		if( ypos >= YLEN )
			return 3;
		//出上界
		if( ypos < 0 )
			return 4;
		//重叠
		if( arMatrix[ xpos ][ ypos ] == STOPPING )
			return 5;
	}
	return 0;
}

//从方块arTetrix中取得方块所在的最小行坐标MinY和最大行坐标MaxY
void CTetrixGame::GetTetrixYPos(TETRIX *arTetrix, SINT &MinY, SINT &MaxY)
{
	SINT miny = arTetrix[1].y;
	SINT maxy = miny;
	for(SINT i = 2; i < 5; i++ )
	{
		if( arTetrix[i].y < miny )
			miny = arTetrix[i].y;
		if(arTetrix[i].y > maxy )
			maxy = arTetrix[i].y;
	}
	MinY = miny;
	MaxY = maxy;
}

//该函数利用从GetTetrixYPos函数中返回的最小行坐标和最大行坐标，
//将MinY传递给startY，将MaxY传递给endY，从而获得扫描行的范围从startY到endY，
//将满足消行条件的行坐标存储在数组arClearedRow中，arsize返回这个数组的大小，
//arsize为零表示没有可以消去的行
void CTetrixGame::GetCanBeClearedRow(SINT arMatrix[][YLEN], SINT startY, 
							SINT endY, SINT *arClearedRow, SINT &arsize)
{
	arsize = 0;
	//采用倒序扫描，从底部向顶部扫描
	for( SINT i = startY; i <= endY; i++ )
	{
		BOOL flag = TRUE;
		for( SINT j = 0; j < XLEN; j++ )
		{
			if( arMatrix[j][i] != STOPPING )
			{
				flag = FALSE;
				break;
			}
		}
		//flag为TRUE表示该行满足消行条件
		if( flag )
			arClearedRow[ arsize++ ] = i;
	}
}

//根据arTetrix方块最后的位置和arMatrix的状态，先通过GetTetrixYPos函数
//来得到扫描行的起始位置，再调用GetCanBeClearedRow得到需要消行的行集合，
//然后将可以消去的行消去，并将该行状态全部置为BLANK，将上面的行进行下移，
//同时更新位置状态;
//arClearedRow数组中的行位置是按坐标的从大到小排列的，也就是从底部到顶部，
//这样的排列有利于消行后其上面的行的下移操作
//函数返回消去的行数
SINT CTetrixGame::DoClearRow(SINT arMatrix[][YLEN], 
							 SINT* arClearedRow, SINT arsize)
{
	//无行可消则返回
	if( arsize == 0 )
		return 0;
	//从可以消除的第一行开始操作
	SINT i, j, k, n = 0;
	SINT clearrow;
		//完成下移
	for( i = 0; i < arsize; i++ )
	{
		//+i是因为每下移一次，需要消除的行的行坐标也相应下移了一位。
		clearrow = arClearedRow[i];	
		//从当前可消除行的行到游戏容器顶部减一行（即第0行下面一行，
		//也就是第1行），将这些行下移一个单位
		for( j = clearrow; j > 1; j-- )
			//将一行的状态设置为BLANK
			for( k = 0; k < XLEN; k++ )
			{
				arMatrix[k][j] = arMatrix[k][j-1];
			}
	}
	return arsize;
}


void CTetrixGame::SetRowStatus(SINT arMatrix[][YLEN], SINT row, SINT status)
{
	for(SINT i = 0;i < XLEN; i++)
	{
		arMatrix[i][row] = status;
	}
}

/**************************************************************************
****完成计分和等级的更新，参数clearedrows表示当前等级下这次消除的行数   ***
****计分和等级的计算方法为(c为消除的行数)：							    ***
****Level(等级): N(1-9):											    ***
****		一次消去一行：s=10+(n-1)*10/2 分							***
****		一次消去两行：2*c*s分										***
****		一次消去三行：2*c*s分										***
****		一次消去四行：2*c*s分										***
****等级的上升是由分数决定的，上升到n级的分数限制是：					***
****		SC(1)=300													***
****		SC(n)= 2*SC(n-1)											***
***************************************************************************/
SINT CTetrixGame::UpdateScoreAndLevel()
{
	if( m_arclearsize == 0 )
		return 1;
	//计分
	if( m_arclearsize == 1 )
		m_iScore += 10 + ( m_iLevel - 1 ) * 5;
	else
		m_iScore += 2 * m_arclearsize * ( 10 + ( m_iLevel - 1 ) * 5 );
	//更新等级
	if( m_iScore > m_iGradeScore )
	{
		m_iLevel++;
		m_iGradeScore *= 2;
		
		return 0;
	}
	else
		return 2;
	
}

//将提示方块拷贝到当前方块，同时完成方块到游戏容器的匹配，
//并判断是否游戏结束，将当前方块在游戏容器中相应的位置状态置为RUNNING
//函数返回FALSE则表示游戏满足结束条件了，
BOOL CTetrixGame::CopyTri(TETRIX *artridest, TETRIX *artrisrc)
{
	BOOL flag = TRUE;
	artridest[0].x = artrisrc[0].x;
	artridest[0].y = artrisrc[0].y;
	for( INT i = 1; i < 5; i++ )
	{
		artridest[i].x = artrisrc[i].x + 2;
		artridest[i].y = artrisrc[i].y - 2;
		INT xpos, ypos;
		xpos = artridest[i].x;
		ypos = artridest[i].y;
		if( m_arMatrix[ xpos ][ ypos ] == STOPPING )
			flag = FALSE;
		m_arMatrix[ xpos ][ ypos ] = RUNNING;
	}
	return flag;
}

int CTetrixGame::GameStart()
{
	SINT type;
	m_GameStatus = GAMERUNNING;

	m_iScore = 0;
	m_iLevel = 1;
	m_iGradeScore = 300;

	
	//游戏屏幕矩阵10*20的初始化，初始状态都为空
	for( INT i = 0; i < XLEN; i++ )
		for(INT j = 0; j < YLEN; j++ )
			m_arMatrix[i][j] = BLANK;

	type =(SINT)( rand() % 7 ) + 1 ;
	BOOL gflag = GenerateOneTetrix(type, m_arNextTri);
	if( !gflag )
	{
		return 1;
	}
	CopyTri(m_arCurrentTri, m_arNextTri);

	type =(SINT)( rand() % 7 ) + 1 ;
	gflag = GenerateOneTetrix(type, m_arNextTri);
	if( !gflag )
	{
		return 1;
	}

	m_rotTimes = 0;
	return 0;
}

int CTetrixGame::DoRotate()
{
	if(m_GameStatus != GAMERUNNING)
		return 1;
	//备份当前方块的位置
	TETRIX tri[5];
	CopyTetrixArray( tri, m_arCurrentTri, 5 );
	//将旋转前的方块的位置设置为BLANK
	BOOL flag = RotateTetrix( tri, 5, m_rotTimes );
	if( !flag )
		return 2;
	INT res = OutOfMatrixOROverlap( m_arMatrix, tri, 5 );
	if( res != 0 )		//出界或重叠则返回
		return 3;
	//将旋转前的方块的位置设置为BLANK
	SetStatus( m_arMatrix, m_arCurrentTri, BLANK );	
	//姿态变化成功，将备份的位置变化写入当前方块
	CopyTetrixArray( m_arCurrentTri, tri, 5 );
	//将旋转后的方块的位置设置为RUNNING
	SetStatus( m_arMatrix, m_arCurrentTri, RUNNING );
	//将成功旋转次数加一
	m_rotTimes++;
	return 0;
}

BOOL CTetrixGame::JudgeMatrixStatus(SINT x, SINT y, SINT status)
{
	if(status == m_arMatrix[x][y])
		return TRUE;
	else
		return FALSE;
}

int CTetrixGame::GoLeft()
{
	if(m_GameStatus != GAMERUNNING)
		return 1;
	//备份当前方块的位置
	TETRIX tri[5];
	CopyTetrixArray( tri, m_arCurrentTri, 5 );
	//使用备份尝试姿态变化
	MoveLeftTetrix( tri, 5 );
	//判断是否出界或重叠
	INT res = OutOfMatrixOROverlap( m_arMatrix, tri, 5 );
	if( res != 0 )		//出界或重叠则返回
		return 2;
	//将旋转前的方块的位置设置为BLANK
	SetStatus( m_arMatrix, m_arCurrentTri, BLANK );	
	//姿态变化成功，将备份的位置变化写入当前方块
	CopyTetrixArray( m_arCurrentTri, tri, 5 );
	//将旋转后的方块的位置设置为RUNNING
	SetStatus( m_arMatrix, m_arCurrentTri, RUNNING );
	return 0;
}

int CTetrixGame::GoRight()
{
	if(m_GameStatus != GAMERUNNING)
		return 1;
	//备份当前方块的位置
	TETRIX tri[5];
	CopyTetrixArray( tri, m_arCurrentTri, 5 );
	//使用备份尝试姿态变化
	MoveRightTetrix( tri, 5 );
	//判断是否出界或重叠
	INT res = OutOfMatrixOROverlap( m_arMatrix, tri, 5 );
	if( res != 0 )		//出界或重叠则返回
		return 2;
	//将旋转前的方块的位置设置为BLANK
	SetStatus( m_arMatrix, m_arCurrentTri, BLANK );	
	//姿态变化成功，将备份的位置变化写入当前方块
	CopyTetrixArray( m_arCurrentTri, tri, 5 );
	//将旋转后的方块的位置设置为RUNNING
	SetStatus( m_arMatrix, m_arCurrentTri, RUNNING );
	return 0;
}

void CTetrixGame::GameOver()
{
	m_GameStatus = GAMEOVER;
}

SINT CTetrixGame::GetGameStatus()
{
	return m_GameStatus;
}

void CTetrixGame::SetGameStatus(SINT status)
{
	m_GameStatus = status;
}

INT CTetrixGame::GetGameLevel()
{
	return m_iLevel;
}

INT CTetrixGame::GetGameScore()
{
	return m_iScore;
}

SINT CTetrixGame::DoDrop()
{
	if(m_GameStatus != GAMERUNNING)
		return 0;
	//备份当前方块的位置
	TETRIX tri[5];
	CopyTetrixArray( tri, m_arCurrentTri, 5 );
	//使用备份尝试姿态变化
	DropTetrix( tri, 5 );
	//判断是否出界或重叠
	INT res = OutOfMatrixOROverlap( m_arMatrix, tri, 5 );
	if( res == 0 )		//未出界或重叠
	{
		//将旋转前的方块的位置设置为BLANK
		SetStatus( m_arMatrix, m_arCurrentTri, BLANK );	
		//姿态变化成功，将备份的位置变化写入当前方块
		CopyTetrixArray( m_arCurrentTri, tri, 5 );
		//将旋转后的方块的位置设置为RUNNING
		SetStatus( m_arMatrix, m_arCurrentTri, RUNNING );
	}
	return res;
}

SINT CTetrixGame::PrepareClear()
{
	SetStatus( m_arMatrix, m_arCurrentTri, STOPPING );
	SINT miny, maxy;
	GetTetrixYPos(m_arCurrentTri, miny, maxy);
	GetCanBeClearedRow(m_arMatrix, miny, maxy,m_arclearRow, m_arclearsize);
	return m_arclearsize;
}

void CTetrixGame::SetClearStatus(SINT status)
{
	SINT i;
	for(i = 0; i < m_arclearsize; i++)
	{
		SetRowStatus(m_arMatrix, m_arclearRow[i], status);
	}
}

void CTetrixGame::DoClear()
{
	DoClearRow(m_arMatrix, m_arclearRow, m_arclearsize);
}

SINT CTetrixGame::GenNew()
{
	BOOL resflag = CopyTri(m_arCurrentTri, m_arNextTri);
	if( !resflag )
	{
		m_GameStatus = GAMEOVER;
		return 1;
	}
	else
	{
		SINT type =(SINT)( rand() % 7 ) + 1 ;
		BOOL gflag = GenerateOneTetrix(type, m_arNextTri);
		m_rotTimes = 0;
		return 0;
	}
}

SINT CTetrixGame::DoDirectDrop()
{
	if(m_GameStatus != GAMERUNNING)
		return 0;
	INT res;
	TETRIX tri[5];
	do
	{
		//备份当前方块的位置
		CopyTetrixArray( tri, m_arCurrentTri, 5 );
		//使用备份尝试姿态变化
		DropTetrix( tri, 5 );
		//判断是否出界或重叠
		res = OutOfMatrixOROverlap( m_arMatrix, tri, 5 );
		if( res == 0 )		//未出界或重叠
		{
			//将旋转前的方块的位置设置为BLANK
			SetStatus( m_arMatrix, m_arCurrentTri, BLANK );	
			//姿态变化成功，将备份的位置变化写入当前方块
			CopyTetrixArray( m_arCurrentTri, tri, 5 );
			//将旋转后的方块的位置设置为RUNNING
			SetStatus( m_arMatrix, m_arCurrentTri, RUNNING );
		}
	}while(res == 0);
	return res;
}

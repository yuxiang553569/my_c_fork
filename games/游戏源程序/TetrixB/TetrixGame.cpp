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
	//��Ϸ��Ļ����10*20�ĳ�ʼ������ʼ״̬��Ϊ��
	for( i = 0; i < XLEN; i++ )
		for(j = 0; j < YLEN; j++ )
			m_arMatrix[i][j] = BLANK;
}

CTetrixGame::~CTetrixGame()
{

}

/******************************************************************************
***����һ�����͵ķ��飬type��ʾ���ɷ�������ͣ��ɹ��򷵻�TRUE�����򷵻�FALSE***
***ÿ������ʹ��m_arCurrentTri�����������������������5��Ԫ��                ***
***��һ��Ԫ�ر�ʾ���ͺ���ת�ᣬ���ĸ���ʾ������6*6�����е����λ��          ***
***����������Ϸ�����У���Ҫ��6*6�ľ���ƥ�䵽��Ϸ����10*20�ľ�����           ***
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
***��7�����ķ����Ϊ���ࣺ                                                 ***
***��һ��ֻ��һ�����͵ķ��飬�� O ���ͣ��������͵ķ���û����ת����Ϊ��ת�� ***
***��ԭ�������ӣ�����һ������֣�������������ͬһ����                      ***
***�ڶ������������͵ķ��飬��I��Z��S���ͣ����������͵ķ���ֻ��������ת��̬�� ***
***һ��״̬��Ĭ�ϵ�ˮƽ״̬����һ������ˮƽ״̬�Ļ�����������˳ʱ����ת90�ȣ�***
***��ÿ����������ɿ�ʼ�ɹ���ת�Ĵ�����һ����������0��ʼ����¼������������� ***
***��Ϊż��ʱ��˳ʱ����ת90�ȣ����������Ϊ����ʱ������ʱ����ת90�ȣ�Ҳ����˳***
***ʱ����ת-90�ȣ��������͸�ԭ��                                             ***
***���������͵ķ���Ϊ T��L�� J������Ҫʹ����ת�����ˣ�ÿ��˳ʱ����ת90�ȣ�   ***
***ÿ�ζ�ʹ��ͬ���Ĺ�ʽ                                                      ***
********************************************************************************
********************************************************************************
***��ת��ʽ����˳ʱ�룩��ͼ�ΰ�����˳ʱ����תa�ȣ�x0��y0Ϊ���ĵ����꣩**********
***		X�� �C x0 = ( x �C x0 )*cos(-a) + ( y �C y0 )*sin(-a)		      **********
***		Y�� �C y0 = -( x �C x0 )*sin(-a) + ( y �C y0 )*cos(-a)		      **********
***��ʱ����ת�Ĺ�ʽ���ǽ�����ĽǶ�-a������a�Ϳ�����				  **********
********************************************************************************
*******************************************************************************/
//artriΪ����ķ���λ�������ͷָ�룬arsizeΪ������ĳ��ȣ��ڱ�������Ӧ��Ϊ5
//rottimesΪÿ����������ɿ�ʼ��¼�ĳɹ���ת�Ĵ���
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
	//��¼��ת���ĵ�����
	SINT	centerx = artri[rotcenter].x;
	SINT	centery = artri[rotcenter].y;
	INT		i = 0;
	switch( type )
	{
	//��һ�෽��
	case	TYPEO:
		//�����κδ���
		break;
	//�ڶ��෽��
	case	TYPEI:
	case	TYPEZ:
	case	TYPES:
	//�ֳɹ���ת��������ż��ѡ���������ת
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
	//�����෽��
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

//������arCurTri�ھ���arMatrix�е�λ������Ϊstatus
//status��ֵֻ����BLANK��RUNNING��STOPPING�е�һ��
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

//ardest��arsrc����TETRIX[5]������,arsize����Ϊ5
//��arsrc��λ����Ϣ������ardest
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

//�жϷ���artri�Ƿ������ص�, arMatrixΪ��Ϸ����10*20�����У�����һ����ά���飬����ֻ�ֱ�
//ΪBLANK����ʾ��λ�ÿգ���RUNNING����λ���������з��飩��STOPPING����λ�����о�ֹ���飩��
//����6��ʾ���鳤�ȳ���, û�г�����ص�����0
//�������緵��1�����ҽ緵��2�����½緵��3�����Ͻ緵��4���ص�����5
INT CTetrixGame::OutOfMatrixOROverlap(SINT arMatrix[][YLEN], TETRIX *artri, INT arsize)
{
	if( arsize != 5 )
		return 6;
	for( INT i = 1; i < arsize; i++ )
	{
		SINT	xpos = artri[i].x;
		SINT	ypos = artri[i].y;
		//�����
		if( xpos < 0 )
			return 1;
		//���ҽ�
		if( xpos >= XLEN )
			return 2;
		//���½�
		if( ypos >= YLEN )
			return 3;
		//���Ͻ�
		if( ypos < 0 )
			return 4;
		//�ص�
		if( arMatrix[ xpos ][ ypos ] == STOPPING )
			return 5;
	}
	return 0;
}

//�ӷ���arTetrix��ȡ�÷������ڵ���С������MinY�����������MaxY
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

//�ú������ô�GetTetrixYPos�����з��ص���С���������������꣬
//��MinY���ݸ�startY����MaxY���ݸ�endY���Ӷ����ɨ���еķ�Χ��startY��endY��
//����������������������洢������arClearedRow�У�arsize�����������Ĵ�С��
//arsizeΪ���ʾû�п�����ȥ����
void CTetrixGame::GetCanBeClearedRow(SINT arMatrix[][YLEN], SINT startY, 
							SINT endY, SINT *arClearedRow, SINT &arsize)
{
	arsize = 0;
	//���õ���ɨ�裬�ӵײ��򶥲�ɨ��
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
		//flagΪTRUE��ʾ����������������
		if( flag )
			arClearedRow[ arsize++ ] = i;
	}
}

//����arTetrix��������λ�ú�arMatrix��״̬����ͨ��GetTetrixYPos����
//���õ�ɨ���е���ʼλ�ã��ٵ���GetCanBeClearedRow�õ���Ҫ���е��м��ϣ�
//Ȼ�󽫿�����ȥ������ȥ����������״̬ȫ����ΪBLANK����������н������ƣ�
//ͬʱ����λ��״̬;
//arClearedRow�����е���λ���ǰ�����ĴӴ�С���еģ�Ҳ���Ǵӵײ���������
//�������������������к���������е����Ʋ���
//����������ȥ������
SINT CTetrixGame::DoClearRow(SINT arMatrix[][YLEN], 
							 SINT* arClearedRow, SINT arsize)
{
	//���п����򷵻�
	if( arsize == 0 )
		return 0;
	//�ӿ��������ĵ�һ�п�ʼ����
	SINT i, j, k, n = 0;
	SINT clearrow;
		//�������
	for( i = 0; i < arsize; i++ )
	{
		//+i����Ϊÿ����һ�Σ���Ҫ�������е�������Ҳ��Ӧ������һλ��
		clearrow = arClearedRow[i];	
		//�ӵ�ǰ�������е��е���Ϸ����������һ�У�����0������һ�У�
		//Ҳ���ǵ�1�У�������Щ������һ����λ
		for( j = clearrow; j > 1; j-- )
			//��һ�е�״̬����ΪBLANK
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
****��ɼƷֺ͵ȼ��ĸ��£�����clearedrows��ʾ��ǰ�ȼ����������������   ***
****�Ʒֺ͵ȼ��ļ��㷽��Ϊ(cΪ����������)��							    ***
****Level(�ȼ�): N(1-9):											    ***
****		һ����ȥһ�У�s=10+(n-1)*10/2 ��							***
****		һ����ȥ���У�2*c*s��										***
****		һ����ȥ���У�2*c*s��										***
****		һ����ȥ���У�2*c*s��										***
****�ȼ����������ɷ��������ģ�������n���ķ��������ǣ�					***
****		SC(1)=300													***
****		SC(n)= 2*SC(n-1)											***
***************************************************************************/
SINT CTetrixGame::UpdateScoreAndLevel()
{
	if( m_arclearsize == 0 )
		return 1;
	//�Ʒ�
	if( m_arclearsize == 1 )
		m_iScore += 10 + ( m_iLevel - 1 ) * 5;
	else
		m_iScore += 2 * m_arclearsize * ( 10 + ( m_iLevel - 1 ) * 5 );
	//���µȼ�
	if( m_iScore > m_iGradeScore )
	{
		m_iLevel++;
		m_iGradeScore *= 2;
		
		return 0;
	}
	else
		return 2;
	
}

//����ʾ���鿽������ǰ���飬ͬʱ��ɷ��鵽��Ϸ������ƥ�䣬
//���ж��Ƿ���Ϸ����������ǰ��������Ϸ��������Ӧ��λ��״̬��ΪRUNNING
//��������FALSE���ʾ��Ϸ������������ˣ�
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

	
	//��Ϸ��Ļ����10*20�ĳ�ʼ������ʼ״̬��Ϊ��
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
	//���ݵ�ǰ�����λ��
	TETRIX tri[5];
	CopyTetrixArray( tri, m_arCurrentTri, 5 );
	//����תǰ�ķ����λ������ΪBLANK
	BOOL flag = RotateTetrix( tri, 5, m_rotTimes );
	if( !flag )
		return 2;
	INT res = OutOfMatrixOROverlap( m_arMatrix, tri, 5 );
	if( res != 0 )		//������ص��򷵻�
		return 3;
	//����תǰ�ķ����λ������ΪBLANK
	SetStatus( m_arMatrix, m_arCurrentTri, BLANK );	
	//��̬�仯�ɹ��������ݵ�λ�ñ仯д�뵱ǰ����
	CopyTetrixArray( m_arCurrentTri, tri, 5 );
	//����ת��ķ����λ������ΪRUNNING
	SetStatus( m_arMatrix, m_arCurrentTri, RUNNING );
	//���ɹ���ת������һ
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
	//���ݵ�ǰ�����λ��
	TETRIX tri[5];
	CopyTetrixArray( tri, m_arCurrentTri, 5 );
	//ʹ�ñ��ݳ�����̬�仯
	MoveLeftTetrix( tri, 5 );
	//�ж��Ƿ������ص�
	INT res = OutOfMatrixOROverlap( m_arMatrix, tri, 5 );
	if( res != 0 )		//������ص��򷵻�
		return 2;
	//����תǰ�ķ����λ������ΪBLANK
	SetStatus( m_arMatrix, m_arCurrentTri, BLANK );	
	//��̬�仯�ɹ��������ݵ�λ�ñ仯д�뵱ǰ����
	CopyTetrixArray( m_arCurrentTri, tri, 5 );
	//����ת��ķ����λ������ΪRUNNING
	SetStatus( m_arMatrix, m_arCurrentTri, RUNNING );
	return 0;
}

int CTetrixGame::GoRight()
{
	if(m_GameStatus != GAMERUNNING)
		return 1;
	//���ݵ�ǰ�����λ��
	TETRIX tri[5];
	CopyTetrixArray( tri, m_arCurrentTri, 5 );
	//ʹ�ñ��ݳ�����̬�仯
	MoveRightTetrix( tri, 5 );
	//�ж��Ƿ������ص�
	INT res = OutOfMatrixOROverlap( m_arMatrix, tri, 5 );
	if( res != 0 )		//������ص��򷵻�
		return 2;
	//����תǰ�ķ����λ������ΪBLANK
	SetStatus( m_arMatrix, m_arCurrentTri, BLANK );	
	//��̬�仯�ɹ��������ݵ�λ�ñ仯д�뵱ǰ����
	CopyTetrixArray( m_arCurrentTri, tri, 5 );
	//����ת��ķ����λ������ΪRUNNING
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
	//���ݵ�ǰ�����λ��
	TETRIX tri[5];
	CopyTetrixArray( tri, m_arCurrentTri, 5 );
	//ʹ�ñ��ݳ�����̬�仯
	DropTetrix( tri, 5 );
	//�ж��Ƿ������ص�
	INT res = OutOfMatrixOROverlap( m_arMatrix, tri, 5 );
	if( res == 0 )		//δ������ص�
	{
		//����תǰ�ķ����λ������ΪBLANK
		SetStatus( m_arMatrix, m_arCurrentTri, BLANK );	
		//��̬�仯�ɹ��������ݵ�λ�ñ仯д�뵱ǰ����
		CopyTetrixArray( m_arCurrentTri, tri, 5 );
		//����ת��ķ����λ������ΪRUNNING
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
		//���ݵ�ǰ�����λ��
		CopyTetrixArray( tri, m_arCurrentTri, 5 );
		//ʹ�ñ��ݳ�����̬�仯
		DropTetrix( tri, 5 );
		//�ж��Ƿ������ص�
		res = OutOfMatrixOROverlap( m_arMatrix, tri, 5 );
		if( res == 0 )		//δ������ص�
		{
			//����תǰ�ķ����λ������ΪBLANK
			SetStatus( m_arMatrix, m_arCurrentTri, BLANK );	
			//��̬�仯�ɹ��������ݵ�λ�ñ仯д�뵱ǰ����
			CopyTetrixArray( m_arCurrentTri, tri, 5 );
			//����ת��ķ����λ������ΪRUNNING
			SetStatus( m_arMatrix, m_arCurrentTri, RUNNING );
		}
	}while(res == 0);
	return res;
}

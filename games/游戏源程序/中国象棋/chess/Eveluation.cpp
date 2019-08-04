// Eveluation.cpp: implementation of the CEveluation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "chess.h"
#include "Eveluation.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//����2�����������ű��ڲ�ͬλ�õĸ���ֵ
//�������ǹ���֮��Խ�����Ͻ�Խ��

//����ĸ���ֵ����
const int BA0[10][9] = 
{
	{0,  0,  0,  0,  0,  0,  0,  0,  0 },
	{90, 90, 110,120,120,120,110,90, 90},
	{90, 90, 110,120,120,120,110,90, 90},
	{70, 90, 110,110,110,110,110,90, 70},
	{70, 70, 70, 70, 70, 70, 70, 70, 70},
	{0,  0,  0,  0,  0,  0,  0,  0,  0 },
	{0,  0,  0,  0,  0,  0,  0,  0,  0 },
	{0,  0,  0,  0,  0,  0,  0,  0,  0 },
	{0,  0,  0,  0,  0,  0,  0,  0,  0 },
	{0,  0,  0,  0,  0,  0,  0,  0,  0 },
};

//��ɫ�ĸ���ֵ����
const int BA1[10][9] = 
{
	{0,  0,  0,  0,  0,  0,  0,  0,  0 },
	{0,  0,  0,  0,  0,  0,  0,  0,  0 },
	{0,  0,  0,  0,  0,  0,  0,  0,  0 },
	{0,  0,  0,  0,  0,  0,  0,  0,  0 },
	{0,  0,  0,  0,  0,  0,  0,  0,  0 },
	{70, 70, 70, 70, 70, 70, 70, 70, 70},
	{70, 90, 110,110,110,110,110,90, 70},
	{90, 90, 110,120,120,120,110,90, 90},
	{90, 90, 110,120,120,120,110,90, 90},
	{0,  0,  0,  0,  0,  0,  0,  0,  0 }
};

//Ϊÿһ�������ظ���ֵ
//x�Ǻ�����,y��������,CurSituation������
//���Ǳ�ֵ������
int GetBingValue(int x,int y,BYTE CurSituation[][9])
{
	//������䷵����λ�ø���ֵ
	if(CurSituation[y][x] == R_PAWN)
		return BA0[y][x];
	//����ڱ�������λ�ø���ֵ
	if(CurSituation[y][x] == B_PAWN)
		return BA1[y][x];

	return 0;
}

CEveluation::CEveluation()
{
	//��ʼ��ÿ�����ӵĻ�����ֵ����
	m_BaseValue[B_KING] = BASEVALUE_KING; 
	m_BaseValue[B_CAR] = BASEVALUE_CAR; 
	m_BaseValue[B_HORSE] = BASEVALUE_HORSE; 
	m_BaseValue[B_BISHOP] = BASEVALUE_BISHOP; 
	m_BaseValue[B_ELEPHANT] = BASEVALUE_ELEPHANT; 
	m_BaseValue[B_CANON] = BASEVALUE_CANON; 
	m_BaseValue[B_PAWN] = BASEVALUE_PAWN; 

	m_BaseValue[R_KING] = BASEVALUE_KING; 
	m_BaseValue[R_CAR] = BASEVALUE_CAR; 
	m_BaseValue[R_HORSE] = BASEVALUE_HORSE; 
	m_BaseValue[R_BISHOP] = BASEVALUE_BISHOP; 
	m_BaseValue[R_ELEPHANT] = BASEVALUE_ELEPHANT; 
	m_BaseValue[R_CANON] = BASEVALUE_CANON; 
	m_BaseValue[R_PAWN] = BASEVALUE_PAWN; 

	m_FlexValue[B_KING] = FLEXIBILITY_KING; 
	m_FlexValue[B_CAR] = FLEXIBILITY_CAR; 
	m_FlexValue[B_HORSE] = FLEXIBILITY_HORSE; 
	m_FlexValue[B_BISHOP] = FLEXIBILITY_BISHOP; 
	m_FlexValue[B_ELEPHANT] = FLEXIBILITY_ELEPHANT; 
	m_FlexValue[B_CANON] = FLEXIBILITY_CANON; 
	m_FlexValue[B_PAWN] = FLEXIBILITY_PAWN; 

	m_FlexValue[R_KING] = FLEXIBILITY_KING; 
	m_FlexValue[R_CAR] = FLEXIBILITY_CAR; 
	m_FlexValue[R_HORSE] = FLEXIBILITY_HORSE; 
	m_FlexValue[R_BISHOP] = FLEXIBILITY_BISHOP; 
	m_FlexValue[R_ELEPHANT] = FLEXIBILITY_ELEPHANT; 
	m_FlexValue[R_CANON] = FLEXIBILITY_CANON; 
	m_FlexValue[R_PAWN] = FLEXIBILITY_PAWN; 
}

CEveluation::~CEveluation()
{

}
int count = 0;	//����һ��ȫ�ֱ���.����ͳ�Ƶ����˹�ֵ���ӽڵ����

//��ֵ����
//position��Ҫ��ֵ������
//bIsRedTurn���ֵ�˭����ı�־,TRUE�Ǻ�,FALSE�Ǻ�
int CEveluation::Eveluate(BYTE position[10][9],BOOL bIsRedTurn)
{
	int i,j,k;
	int nChessType,nTargetType;
	count++;	//ÿ����һ�ι�ֵ����������һ��,����ͳ�Ƶ�����
	//��ֵ�������ӽڵ�Ĵ���

	//��ʼ����ʱ����
	memset(m_chessValue,0, 360);
	memset(m_AttackPos,0, 180); 
	memset(m_GuardPos,0, 90); 
	memset(m_FlexibilityPos, 0, 90);

	//ɨ������,�ҳ�ÿһ������,������в/����������,�����������
	for(i = 0; i < 10; i++)
	{
		for(j = 0; j < 9; j++)
		{
			if(position[i][j] != NOCHESS) //������ǿհ�
			{
				nChessType = position[i][j];//ȡ��������
				GetRelatePiece(position,j,i);//�ҳ��������������λ��
				for(k = 0; k < nPosCount; k++)//��ÿһ��Ŀ��λ��
				{
					//ȡĿ��λ����������
					nTargetType = 
						position[RelatePos[k].y][RelatePos[k].x];
					if(nTargetType == NOCHESS)//����ǿհ�
						m_FlexibilityPos[i][j]++;//���������
					else
					{
						//������
						if(IsSameSide(nChessType,nTargetType))
						{
							//������ҷ�����,Ŀ���ܱ���
							m_GuardPos[RelatePos[k].y][RelatePos[k].x]++;
						}
						else
						{
							//����ǶԷ�����,Ŀ������в
							m_AttackPos[RelatePos[k].y][RelatePos[k].x]++;
							m_FlexibilityPos[i][j]++; //���������
							switch(nTargetType)
							{
							case R_KING:	//����콫
								if(!bIsRedTurn) //����ֵ�������
									return 18888; //����ʧ�ܼ�ֵ
								break;

							case B_KING:	//����Ǻ�˧
								if(bIsRedTurn)//����ֵ�������
									return 18888; //����ʧ��
								break;
							
							//���ǽ�����������
							default:
								//������в�����Ӽ�����в��ֵ
								m_AttackPos[RelatePos[k].y][RelatePos[k].x]
									+= (30 + (m_BaseValue[nTargetType]
									- m_BaseValue[nChessType]) / 10) /10;
								break;

							}
						}
					}

				}
			}
		}
	}

	//������ɨ�����̵Ĳ���
	//�����ѭ��ͳ��ɨ�赽�Ĳ���
	for(i = 0; i < 10; i++)
	{
		for(j = 0; j < 9; j++)
		{
			if(position[i][j] != NOCHESS)
			{
				nChessType = position[i][j];//��������
				m_chessValue[i][j]++;	//������Ӵ������ֵ��Ϊ0
				//��ÿһ�����ӵ�����Լ�ֵ�ӽ����Ӽ�ֵ
				m_chessValue[i][j] += 
					m_FlexValue[nChessType] * m_FlexibilityPos[i][j];

				//���ϱ���λ�ø���ֵ
				m_chessValue[i][j] += GetBingValue(j,i,position);
			}
		}
	}
	
	//�����ѭ������ͳ��ɨ�赽������
	int nHalfvalue;
	for(i = 0; i < 10; i++)
	{
		for(j = 0; j < 9; j++)
		{
			if(position[i][j] != NOCHESS) //������ǿհ�
			{
				nChessType = position[i][j];//ȡ��������
				//���ӻ�����ֵ��1/16��Ϊ��в/��������
				nHalfvalue = m_BaseValue[nChessType] / 16;
				//��ÿ�����ӵĻ�����ֵ�����ܼ�ֵ
				m_chessValue[i][j] += m_BaseValue[nChessType];
				if(IsRed(nChessType)) //����Ǻ���
				{
					if(m_AttackPos[i][j])
					{
						if(bIsRedTurn)
						{
							//����ֵ�������
							if(nChessType == R_KING)
							{
								//����Ǻ콫
								m_chessValue[i][j] -= 20;
								//��ֵ����20
							}
							else
							{
								//��ֵ��ȥ2��nHalfvalue
								m_chessValue[i][j] -= nHalfvalue * 2;
								if(m_GuardPos[i][j]) //�Ƿ��ҷ����ӱ���
									m_chessValue[i][j] += nHalfvalue;
								//�������ټ���nHalfvalue
							}
						}
						else
						{
							//��ǰ���챻��в,�ֵ�������
							if(nChessType == R_KING)	//�Ƿ��Ǻ콫
								return 18888;	//����ʧ�ܵļ�ֵ
							//��ȥ10����nHalfvalue.��ʾ��в�̶ȸ�
							m_chessValue[i][j] -= nHalfvalue * 10;
							if(m_GuardPos[i][j]) //���������
								m_chessValue[i][j] += nHalfvalue * 9;
							//�������ټ���9��nHalfvalue
						}
						//����в�����Ӽ�����в��,��ֹһ������в
						//һ���������ĳ�,����ֵ����û�з�Ӧ֮�������.
						m_chessValue[i][j] -= m_AttackPos[i][j];
					}
					else
					{
						//û�յ���в
						if(m_GuardPos[i][j])
							m_chessValue[i][j] += 5;//�ܱ���.��һ���
					}
				}
				else
				{
					//����Ǻ���
					if(m_AttackPos[i][j])
					{
						//����в
						if(!bIsRedTurn)
						{
							//�ֵ��\����
							if(nChessType == B_KING)	//����Ǻڽ�
								m_chessValue[i][j] -= 20;	//���Ӽ�ֵ����20
							else
							{
								//���Ӽ�ֵ����2��nHalfvalue
								m_chessValue[i][j] -= nHalfvalue * 2;
								if(m_GuardPos[i][j]) //����ܵ�����
									m_chessValue[i][j] += nHalfvalue;
									//���Ӽ�ֵ����nHalfvalue
							}
						}
						else
						{
							//�ֵ�������
							if(nChessType == B_KING)	//����Ǻڽ�
								return 18888;	//����ʧ�ܼ�ֵ
							//���Ӽ�ֵ����10��nHalfvalue
							m_chessValue[i][j] -= nHalfvalue * 10;
							if(m_GuardPos[i][j]) //�ܵ�����
								m_chessValue[i][j] += nHalfvalue * 9;
								//�������ټ���9��nHalfvalue
						}
						//����в�����Ӽ�����в��,��ֹһ������в
						//һ���������ĳ�,����ֵ����û�з�ӳ֮�������
						m_chessValue[i][j] -= m_AttackPos[i][j];
					}
					else
					{
						//û�ܵ���в
						if(m_GuardPos[i][j])
							m_chessValue[i][j] += 5; //�ܱ���,�ӵ����
					}

				}
			}
		}
	}
	//��������ͳ����ÿһ�����ӵ��ܼ�ֵ

	//������ͳ�ƺں��������ܷ�
	int nRedValue = 0;
	int nBlackValue = 0;
	for(i = 0; i < 10; i++)
	{
		for(j = 0; j < 9; j++)
		{
			nChessType = position[i][j];	//ȡ��������
			if(nChessType != NOCHESS)	//������ǿհ�
			{
				if(IsRed(nChessType))
					nRedValue += m_chessValue[i][j];	//�Ѻ����ֵ����
				else
					nBlackValue += m_chessValue[i][j];	//�Ѻ����ֵ����
			}
		}
	}
	if(bIsRedTurn)
		return nRedValue - nBlackValue;	//����ֵ�������,���ع�ֵ
	else
		return nBlackValue - nRedValue;	//�ֵ�����,���ظ��Ĺ�ֵ
}

//��һ��λ�ü�������RelatePos
CEveluation::AddPoint(int x,int y)
{
	RelatePos[nPosCount].x = x;
	RelatePos[nPosCount].y = y;
	nPosCount++;
}

//ö�ٸ���λ�������ӵ��������λ��
//�������ߵ���λ�úͿ��Ա�����λ��
//position�ǵ�ǰ����
//x�����ӵĺ�����,y�����ӵ�������
int CEveluation::GetRelatePiece(BYTE position[10][9],int j, int i)
{
	nPosCount = 0;
	BYTE nChessID;
	BYTE flag;
	int x,y;
	
	nChessID = position[i][j];
	switch(nChessID)
	{
	case R_KING:	//�콫
	case B_KING:	//��˧
		//ѭ�����Ź�֮�ڵ���Щλ�ÿǵ���/����
		//ѭ�����߾Ź���������������
		for(y = 0; y < 3; y++)
		{
			for(x = 3; x < 6; x++)
			{
				if(CanTouch(position,j,i,x,y)) //�ܷ��ߵ�
					AddPoint(x,y);	//����ɵ���/����������
			}
		}
		//ѭ�����Ź�֮�ڵ���Щλ�ÿǵ���/����
		//ѭ�����߾Ź���������������
		for(y = 7; y < 10; y++)
		{
			for(x = 3; x < 6; x++)
			{
				if(CanTouch(position,j,i,x,y)) //�ܷ��ߵ�
					AddPoint(x,y);	//����ɵ���/����������
			}
		}
		break;

	case B_BISHOP:	//��ʿ
		//ѭ�����Ź�֮�ڵ���Щλ�ÿǵ���/����
		for(y = 0; y < 3; y++)
		{
			for(x = 3; x < 6; x++)
			{
				if(CanTouch(position,j,i,x,y)) //�ܷ��ߵ�
					AddPoint(x,y);	//����ɵ���/����������
			}
		}
		break;

	case R_BISHOP:	//����
		//ѭ�����Ź�֮�ڵ���Щλ�ÿǵ���/����
		for(y = 7; y < 10; y++)
		{
			for(x = 3; x < 6; x++)
			{
				if(CanTouch(position,j,i,x,y)) //�ܷ��ߵ�
					AddPoint(x,y);	//����ɵ���/����������
			}
		}
		break;

	case R_ELEPHANT:	//����
	case B_ELEPHANT:	//����
		//����
		x = j + 2;
		y = i + 2;
		if(x < 9 && y < 10 && CanTouch(position,j,i,x,y))
			AddPoint(x,y);
		//����
		x = j + 2;
		y = i - 2;
		if(x < 9 && y >= 0 && CanTouch(position,j,i,x,y))
			AddPoint(x,y);
		//����
		x = j - 2;
		y = i + 2;
		if(x >= 0 && y < 10 && CanTouch(position,j,i,x,y))
			AddPoint(x,y);
		//����
		x = j - 2;
		y = i - 2;
		if(x >= 0 && y >= 0 && CanTouch(position,j,i,x,y))
			AddPoint(x,y);
		break;

	case R_HORSE:	//����
	case B_HORSE:	//����
		//������·��Ƿ�����/����
		x = j + 2;
		y = i + 1;
		if((x < 9 && y < 10) && CanTouch(position,j,i,x,y))
			AddPoint(x,y);
		//������Ϸ��Ƿ�����/����
		x = j + 2;
		y = i - 1;
		if((x < 9 && y >= 0) && CanTouch(position,j,i,x,y))
			AddPoint(x,y);
		//������·��Ƿ�����/����
		x = j - 2;
		y = i + 1;
		if((x >= 0 && y < 10) && CanTouch(position,j,i,x,y))
			AddPoint(x,y);
		//������Ϸ��Ƿ�����/����
		x = j - 2;
		y = i - 1;
		if((x >= 0 && y >= 0) && CanTouch(position,j,i,x,y))
			AddPoint(x,y);

		//������·��Ƿ�����/����
		x = j + 1;
		y = i + 2;
		if((x < 9 && y < 10) && CanTouch(position,j,i,x,y))
			AddPoint(x,y);
		//������Ϸ��Ƿ�����/����
		x = j + 1;
		y = i - 2;
		if((x < 9 && y >= 0) && CanTouch(position,j,i,x,y))
			AddPoint(x,y);
		//������·��Ƿ�����/����
		x = j - 1;
		y = i + 2;
		if((x >= 0 && y < 10) && CanTouch(position,j,i,x,y))
			AddPoint(x,y);
		//������Ϸ��Ƿ�����/����
		x = j - 1;
		y = i - 2;
		if((x >= 0 && y >= 0) && CanTouch(position,j,i,x,y))
			AddPoint(x,y);
		break;

	case R_CAR:		//�쳵
	case B_CAR:		//��܇
		//������ҵ�λ���Ƿ�����/����
		x = j + 1;
		y = i;
		while(x < 9)
		{
			if(NOCHESS == position[y][x]) //�հ�
				AddPoint(x,y);
			else
			{
				//������һ������
				AddPoint(x,y);
				break;	//����λ�ò�������
			}
			x++;
		}
		//��������λ���Ƿ�����/����
		x = j - 1;
		y = i;
		while(x >= 0)
		{
			if(NOCHESS == position[y][x]) //�հ�
				AddPoint(x,y);
			else
			{
				//������һ������
				AddPoint(x,y);
				break;	//����λ�ò�������
			}
			x--;
		}
		//������µ�λ���Ƿ�����/����
		x = j;
		y = i + 1;
		while(y < 10)
		{
			if(NOCHESS == position[y][x]) //�հ�
				AddPoint(x,y);
			else
			{
				//������һ������
				AddPoint(x,y);
				break;	//����λ�ò�������
			}
			y++;
		}
		//������µ�λ���Ƿ�����/����
		x = j;
		y = i - 1;
		while(y > 0)
		{
			if(NOCHESS == position[y][x]) //�հ�
				AddPoint(x,y);
			else
			{
				//������һ������
				AddPoint(x,y);
				break;	//����λ�ò�������
			}
			y--;
		}	
		break;
	
	case R_PAWN:	//����
		//�鿴��ǰ�Ƿ񵽵�
		y = i - 1;
		x = j;
		if(y >= 0)
			AddPoint(x,y);	//û����.����
		if(i < 5)
		{
			//����Ѿ�����
			y = i;
			x = j + 1;//����
			if(x < 9)
				AddPoint(x,y);//δ���ұ�,����
			x = j - 1;//����
			if(x >= 0)
				AddPoint(x,y);//δ�����,����
		}
		break;

	case B_PAWN:	//�ڱ�
		//�鿴��ǰ�Ƿ񵽵�
		y = i + 1;
		x = j;
		if(y < 10) //�Ƿ��Ѿ�����
			AddPoint(x,y);//û����
		if(i < 4)
		{
			//���ѹ���
			y = i;
			x = j + 1;//����
			if(x < 9)
				AddPoint(x,y);//δ���ұ�,����
			x = j - 1;//����
			if(x >= 0)
				AddPoint(x,y);//δ�����,����
		}
		break;

	case B_CANON:	//����
	case R_CANON:	//����
		//�鿴���ҷ����ϵĿ���/������λ��
		x = j + 1;
		y = i;
		flag = FALSE;
		while(x < 9)
		{
			if(NOCHESS == position[y][x])
			{
				//�հ�λ��
				if(!flag)
					AddPoint(x,y);
			}
			else
			{
				//������
				if(!flag)
					flag = TRUE;	//�ǵ�һ������
				else
				{
					//�ǵڶ�������
					AddPoint(x,y);
					break;
				}
			}
			x++; //��������
		}
		//�鿴�������ϵĿ���/������λ��
		x = j - 1;
		y = i;
		flag = FALSE;
		while(x >= 9)
		{
			if(NOCHESS == position[y][x])
			{
				//�հ�λ��
				if(!flag)
					AddPoint(x,y);
			}
			else
			{
				//������
				if(!flag)
					flag = TRUE;	//�ǵ�һ������
				else
				{
					//�ǵڶ�������
					AddPoint(x,y);
					break;
				}
			}
			x--;//��������
		}
		//�鿴���·����ϵĿ���/������λ��
		x = j;
		y = i + 1;
		flag = FALSE;
		while(y < 10)
		{
			if(NOCHESS == position[y][x])
			{
				//�հ�λ��
				if(!flag)
					AddPoint(x,y);
			}
			else
			{
				//������
				if(!flag)
					flag = TRUE;	//�ǵ�һ������
				else
				{
					//�ǵڶ�������
					AddPoint(x,y);
					break;
				}
			}
			y++;	//��������
		}
		//�鿴���·����ϵĿ���/������λ��
		x = j;
		y = i - 1;
		flag = FALSE;
		while(y >= 0)
		{
			if(NOCHESS == position[y][x])
			{
				//�հ�λ��
				if(!flag)
					AddPoint(x,y);
			}
			else
			{
				//������
				if(!flag)
					flag = TRUE;	//�ǵ�һ������
				else
				{
					//�ǵڶ�������
					AddPoint(x,y);
					break;
				}
			}
			y--;	//��������
		}
		break;

		default:
			break;

	}
	return nPosCount;
}

//�ж�����position��λ��from�������Ƿ����ߵ�λ��to
//����ܷ���true.���򷵻�false
BOOL CEveluation::CanTouch(BYTE position[10][9],int nFromX,
						   int nFromY,int nToX,int nToY)
{
	int i,j;
	int nMoveChessID,nTargetID;
	if(nFromY == nToY && nFromX == nToX)
		return FALSE;	//Ŀ����ԭ��λ����ͬ
	nMoveChessID = position[nFromY][nFromX];
	nTargetID = position[nToY][nToX];
	switch(nMoveChessID)
	{
	case B_KING:
		if(nTargetID == R_KING)	//�Ƿ����Ͻ�����
		{
			if(nFromX != nToX)
				return FALSE;
			for(i = nFromX + 1; i < nToY; i++)
				if(position[i][nFromX] != NOCHESS)
					return FALSE;
		}
		else
		{
			if(nToY > 2 || nToX > 5 || nToX < 3)
				return FALSE;	//Ŀ����ھŹ�֮��
			if(abs(nFromY - nToY) + abs(nToX - nFromX) > 1)
				return FALSE;	//��˧ֻ����һ��
		}
		break;

	case R_BISHOP:	//����
		if(nToY < 7 || nToX > 5 || nToX < 3)
			return FALSE;	//�˳��Ź�
		if(abs(nFromY - nToY) != 1 || abs(nToX - nFromX) != 1)
			return FALSE;	//����б��
		break;

	case B_BISHOP:	//����
		if(nToY > 2 || nToX > 5 || nToX < 3)
			return FALSE;	//�˳��Ź�
		if(abs(nFromY - nToY) != 1 || abs(nToX - nFromX) != 1)
			return FALSE;	//����б��
		break;

	case R_ELEPHANT://����
		if(nToY < 5)
			return FALSE;	//�಻�ܹ���
		if(abs(nFromX - nToX) != 2 || abs(nFromY - nToY) != 2)
			return FALSE;	//��������
		if(position[(nFromY + nToY) / 2][(nFromX + nToX) / 2] != NOCHESS)
			return FALSE;	//���۱�����
		break;

	case B_ELEPHANT://����
		if(nToY > 4)
			return FALSE;	//���ܹ���
		if(abs(nFromX - nToX) != 2 || abs(nFromY - nToY) != 2)
			return FALSE;	//��������
		if(position[(nFromY + nToY) / 2][(nFromX + nToX) / 2] != NOCHESS)
			return FALSE;	//���۱�����
		break;

	case B_PAWN:	//�ڱ�
		if(nToY < nFromY)
			return FALSE;	//�����ܺ���
		if(nFromY < 5 && nFromY == nToY)
			return FALSE;	//������ֻ��ֱ��
		if(nToY - nFromY + abs(nToX - nFromX) > 1)
			return FALSE;	//��ֻ��һ��ֱ��
		break;
	
	case R_PAWN:	//����
		if(nToY > nFromY)
			return FALSE;	//�����ܺ���
		if(nFromY > 4 && nFromY == nToY)
			return FALSE;	//������ֻ��ֱ��
		if(nFromY - nToY + abs(nToX - nFromX) > 1)
			return FALSE;	//��ֻ��һ��ֱ��
		break;

	case R_KING:
		if(nTargetID == B_KING)	//�Ƿ����Ͻ�����
		{
			if(nFromX != nToX)
				return FALSE;	//��˧����ͬһ��
			for(i = nFromY - 1; i > nToY; i--)
				if(position[i][nFromX] != NOCHESS)
					return FALSE;	//�м�������
		}
		else
		{
			if(nToY < 7 || nToX > 5 || nToX < 3)
				return FALSE;	//Ŀ����ھŹ�֮��
			if(abs(nFromY - nToY) + abs(nToX - nFromX) > 1)
				return FALSE;	//��˧ֻ����һ��
		}
		break;

	case R_CAR:	//��܇
	case B_CAR:		//��܇
		if(nFromY != nToY && nFromX != nToX)
			return FALSE;	//����ֱ��
		if(nFromY == nToY)
		{
			//����
			if(nFromX < nToX)
			{
				//����
				for(i = nFromX + 1; i < nToX; i++)
					if(position[nFromY][i] != NOCHESS)
						return FALSE;
			}
			else
			{
				//����
				for(i = nToX + 1; i < nFromX; i++)
					if(position[nFromY][i] != NOCHESS)
						return FALSE;
			}
		}
		else
		{
			//����
			if(nFromY < nToY)
			{
				//����
				for(j = nFromY + 1; j < nToY; j++)
					if(position[j][nFromX] != NOCHESS)
						return FALSE;
			}
			else
			{
				//����
				for(j = nToY + 1; j < nFromY; j++)
					if(position[j][nFromX] != NOCHESS)
						return FALSE;
			}
		}
		break;

	case B_HORSE:	//����
	case R_HORSE:	//����
		if(!((abs(nToX - nFromX) == 1 && abs(nToY - nFromY) == 2)
			||(abs(nToX -nFromX) == 2 && abs(nToY - nFromY) == 1)))
			return FALSE;	//��������
		if(nToX - nFromX == 2)
		{
			//��������
			i = nFromX + 1;
			j = nFromY;
		}
		else if(nFromX - nToX == 2)
		{
			//��������
			i = nFromX - 1;
			j = nFromY;
		}
		else if(nToY - nFromY == 2)
		{
			//��������
			i = nFromX;
			j = nFromY + 1;
		}
		else if(nFromY - nToY == 2)
		{
			//��������
			i = nFromX;
			j = nFromY - 1;
		}
		if(position[j][i] != (BYTE)NOCHESS)
			return FALSE;	//������
		break;

	case B_CANON:	//����
	case R_CANON:	//����
		if(nFromY != nToY && nFromX != nToX)
			return FALSE;	//����ֱ��
		//�ڲ�����ʱ������·�߲���������
		if(position[nToY][nToX] == NOCHESS)
		{
			//������
			if(nFromY == nToY)
			{
				//����
				if(nFromX < nToX)
				{
					//����
					for(i = nFromX + 1; i < nToX; i++)
						if(position[nFromY][i] != NOCHESS)
							return FALSE;
				}
				else
				{
					//����
					for(i = nToX + 1; i < nFromX; i++)
						if(position[nFromY][i] != NOCHESS)
							return FALSE;
				}
			}
			else
			{
				//����
				if(nFromY < nToY)
				{
					//����
					for(j = nFromY + 1; j < nToY; j++)
						if(position[j][nFromX] != NOCHESS)
							return FALSE;
				}
				else
				{
					//����
					for(j = nToY + 1; j < nFromY; j++)
						if(position[j][nFromX] != NOCHESS)
							return FALSE;
				}
			}
		}
		else
		{
			//����ʱ
			int count = 0;
			if(nFromY == nToY)
			{
				//����
				if(nFromX < nToX)
				{
					//����
					for(i = nFromX + 1; i < nToX; i++)
						if(position[nFromY][i] != NOCHESS)
							count++;
					if(count != 1)	//���Ǹ�һ���Ӳ��ܳ�
						return FALSE;
				}
				else
				{
					//����
					for(i = nToX + 1; i < nFromX; i++)
						if(position[nFromY][i] != NOCHESS)
							count++;
					if(count != 1)	//���Ǹ�һ���Ӳ��ܳ�
						return FALSE;
				}
			}
			else
			{
				//����
				if(nFromY < nToY)
				{
					//����
					for(j = nFromY + 1; j < nToY; j ++)
						if(position[j][nFromX] != NOCHESS)
							count++;
					if(count != 1)	//���Ǹ�һ���Ӳ��ܳ�
						return FALSE;
				}
				else
				{
					//����
					for(j = nToY + 1; j < nFromY; j ++)
						if(position[j][nFromX] != NOCHESS)
							count++;
					if(count != 1)	//���Ǹ�һ���Ӳ��ܳ�
						return FALSE;
				}
			}

		}
		break;

	default:
		return FALSE;
	}
	return TRUE;

}
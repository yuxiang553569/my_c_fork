// Eveluation.h: interface for the CEveluation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVELUATION_H__9C15A808_D4E9_48BF_A4EF_8A9D8385C967__INCLUDED_)
#define AFX_EVELUATION_H__9C15A808_D4E9_48BF_A4EF_8A9D8385C967__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//����һ��궨��ÿ�����ӵĻ�����ֵ
//��100,ʿ250,��250,��500,��350,��350
//��˧ 10000
#define BASEVALUE_PAWN 100
#define BASEVALUE_BISHOP 250
#define BASEVALUE_ELEPHANT 250
#define BASEVALUE_CAR 500
#define BASEVALUE_HORSE 350
#define BASEVALUE_CANON 350
#define BASEVALUE_KING 10000

//����һ��궨��������ӵ������
//��ÿ��һ������λ����Ӧ���ϵķ�ֵ
//��15,ʿ1,��1,��6,��12,��6,��0
#define FLEXIBILITY_PAWN		15
#define FLEXIBILITY_BISHOP		1
#define FLEXIBILITY_ELEPHANT	1
#define FLEXIBILITY_CAR			6
#define FLEXIBILITY_HORSE		12
#define FLEXIBILITY_CANON		6
#define FLEXIBILITY_KING		0

//��ֵ����
class CEveluation  
{
public:
	CEveluation();
	virtual ~CEveluation();
	//��ֵ����,�Դ�������̴��,BIsRedTurn �����ֵ�˭����
	virtual int Eveluate(BYTE position[10][9], BOOL bIsRedTurn);

protected:
	//�о���ָ��λ�õ�������ص�����
	int GetRelatePiece(BYTE position[10][9],int j,int i);
	//�ж�λ��From�������Ƿ����ߵ�λ��To
	BOOL CanTouch(BYTE position[10][9],int nFromX,
		int nFromY,int nToX,int nToY);
	//��һ��λ�ü������λ�õĶ���
	AddPoint(int x,int y);
	int m_BaseValue[15];//������ӻ�����ֵ������
	int m_FlexValue[15];//�����������Է���������
	short m_AttackPos[10][9];//���ÿһ��λ�ñ���в����Ϣ
	BYTE m_GuardPos[10][9];//���ÿһλ�ñ���������Ϣ
	BYTE m_FlexibilityPos[10][9];//���ÿһ��λ���ϵ���������Է���
	int m_chessValue[10][9];//���ÿһλ���ϵ����ӵ��ܼ�ֵ
	int nPosCount;	//��¼һ���ӵ����λ�ø���
	POINT RelatePos[20];	//��¼һ���������λ�õ�����
};

#endif // !defined(AFX_EVELUATION_H__9C15A808_D4E9_48BF_A4EF_8A9D8385C967__INCLUDED_)

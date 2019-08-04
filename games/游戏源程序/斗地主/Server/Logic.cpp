// Logic.cpp: implementation of the Logic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "server.h"
#include "Logic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// Logic.cpp: implementation of the Logic class.
//
//////////////////////////////////////////////////////////////////////

Logic logic;
//////////////�߼�ȫ�ֱ���������///////////////////////////////////////
//	int PrePoint;//��һ���Ƶ��Ƶ�
	int currentPoint[maxnum];//��ǰ�Ƶ��Ƶ�
	int currentLen[maxnum];
	int preLen[maxnum];
	int multiple[maxnum];//����
	int InitMarks[maxnum];//�Ƶĵ׷�
	enum pokType  //��¼ѹ�ƺͱ�ѹ�ƵĻ�������
	{ 
		err =1,//�����ϵ�����
		single,//����
		twain,//��
		three,//����
		threeOne,//����һ
		ThreeTwain,//������
		list,//����
		sisterTwain,//��ö�
		planeOne,//����һ�ɻ�
		planeTwain,//�������ɻ�
		bomb//ը��
	}currentType[maxnum];
	int pok[maxnum][14][4];//��ά�����������
  

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Logic::Logic()
{

//	multiple[tablenum] = 0;

}

Logic::~Logic()
{

}

////////////////////////////////////////////////////////////
//����

void Logic::Deal()
{
	int poke[54];
	int poke1[20];
	int poke2[20];
	int poke3[20];
	int pokelast[3];
	int number = 1;
	srand( (unsigned)time( NULL ) );

	for(int i = 0; i<54;i++)
	{
		poke[i] = i;
	}


	for(int j = 0; j<54;j++)
	{
		int num = (rand()%(54-j));
		if(j<17)
		{
			poke1[j] =  poke[num];
		}
		else if(j<34)
		{
			poke2[j-17]=poke[num];
		}
		else if(j<51)
		{
			poke3[j-34]=poke[num];
		}
		else
			pokelast[j-51]=poke[num];

		for( int k = num+1;k<54-j; k++)
		{
			poke[k-1]=poke[k];
		}
	}

//	cout<<"���ƣ�"<<endl;
//	cout<<"���һ����Ϊ��";
	for (int m = 0;m<17; m++)//���һ����
	{
		cout<<poke1[m]<<" ";
	}
	cout<<endl;
//	cout<<"��Ҷ�����Ϊ��";
	for (int m1 = 0;m1<17; m1++)//��Ҷ�����
	{
		cout<<poke2[m1]<<" ";
	}
	cout<<endl;
//	cout<<"���������Ϊ��";
	for (int m2 = 0;m2<17; m2++)//���������
	{
		cout<<poke3[m2]<<" ";
	}
//	cout<<endl<<"����Ϊ��"<<pokelast[0]<<" "<<pokelast[1]<<" "<<pokelast[2]<<endl;//����
}



//////////////////////////////////////////////���������ж�

////////////////////////////////////////////////////////////
//�����ݽ�������
void Logic::SortPok(int tablenum,int* CurrentCards,int CurrentLen)
{ 
	int ln	= 0;//14
	int col = 0;//4
	for(ln = 0;ln < 14;ln++)//0��ʾ��λ��û����
	{
		for(col = 0;col < 4;col++)
		{
			pok[tablenum][ln][col] = 0;
		}
	}
	for(int k = 0; k < CurrentLen; k++)
	{
		if(*(CurrentCards+k) == 53)
		{
			pok[tablenum][13][0] = 53;//С��
		}
		else if(*(CurrentCards+k) == 54)
		{
			pok[tablenum][13][1] = 54;//���
		}
		else
		{
			col = *(CurrentCards+k)/13;//�ƵĻ�ɫ
			if(col == 4)
			{
				col--;
			}
			ln = *(CurrentCards+k)%13-2;//�ƵĴ�С
			if(ln == -1)
			{
				ln = 12;//A
			}
			if(ln == -2)
			{
				ln = 11;//K
			}
			if(ln == 0)
			{
				ln = 13;//2
			}
			pok[tablenum][ln-1][col] = *(CurrentCards+k);
		}
	}
}

//////////////////////////////////////////////////////////////////
//���Ƶ���бȽ�
int Logic::pointCheck(int tablenum,int puk)
{
	if(puk == 53)
		return 13;
	else if(puk == 54)
	{
		return 14;
	}
	else
	{
		int temp = puk%13;
		temp-=2;
		if(temp == -1)
		{
			temp = 12;//A
		}
		else if(temp == -2)
		{
			temp = 11;//K
		}
		else if(temp == 0)
		{
			temp = 13;//2
		}
		
		currentPoint[tablenum] = temp-1;
		return currentPoint[tablenum];
	}
}

////////////////////////////////////////////////////////////////////
//�����Ƶ��ж�
bool Logic::DoubleCheck(int tablenum,int* CurrentCards)
{
	if(*(CurrentCards+1)%13 == *(CurrentCards)%13)
	{		
		currentPoint[tablenum] = logic.pointCheck(tablenum,*(CurrentCards));
		currentType[tablenum]  = twain;
	//	cout<<"����Ϊ������"<<endl<<"�Ƶ�Ϊ��"<<currentPoint<<endl;
		return true;
	}
	else if(*(CurrentCards) == 53 && *(CurrentCards+1) == 54)
	{
		currentType[tablenum]  = bomb;
		currentPoint[tablenum] = 14;
		multiple[tablenum]++;
	//	cout<<" ը��---�Ƶ�Ϊ��"<<currentPoint<<endl;
		return true;
	}
	else return false;
}

////////////////////////////////////////////////////////////////////
////�����ж�
bool Logic::ThreeCheck(int tablenum,int* CurrentCards)
{
	if(*(CurrentCards+1)%13  == *(CurrentCards+2)%13 &&
		*(CurrentCards+2)%13 == *(CurrentCards)%13)
	{
		currentPoint[tablenum] = logic.pointCheck(tablenum,*(CurrentCards));
		currentType[tablenum]  = three;
//		cout<<"����---�Ƶ�Ϊ��"<<currentPoint<<endl;
		return true;
	}
	else return false;

}


//////////////////////////////////////////////////////////////////\
////ը���ж�

bool Logic::Bombcheck(int tablenum,int* CurrentCards)
{
	if((*(CurrentCards+1))%13	== (*(CurrentCards+2))%13 &&
		(*(CurrentCards+3))%13	== (*(CurrentCards))%13 && 
		(*(CurrentCards))%13	== (*(CurrentCards+1))%13)
	{
		currentPoint[tablenum]	= logic.pointCheck(tablenum,*(CurrentCards));
		currentType[tablenum]	= bomb;
		multiple[tablenum]++;
	//	cout<<"ը��---�Ƶ�Ϊ��"<<currentPoint<<endl;
		return true;
	}
	else return false;
}


////////////////////////////////////////////////////////////////////
////����һ�ж�
bool Logic::ThreeOneCheck(int tablenum,int* CurrentCards)
{
	int num = 0;
//	int point = 0;
	for(int ln = 0;ln<13;ln++)
	{
		int i = 0;
		for (int col = 0;col < 4;col++)
		{
			if(pok[tablenum][ln][col] != 0)
			{
				i++;
			}
		}
		if(i == 3)
		{
			num++;
			currentPoint[tablenum] = ln;
			currentType[tablenum]  = threeOne;
			//	cout<<"����Ϊ������һ"<<endl<<"�Ƶ�Ϊ��"<<currentPoint<<endl;
			return true;
		}
	}
	return false;
}

////////////////////////////////////////////////////////////////////
//�������ж�
bool Logic::ThreeTowCheck(int tablenum,int* CurrentCards)  
{
	int point;
	int num = 0;
	int two = 0;
	for(int ln=0;ln<14;ln++)
	{
		int i=0;
		for (int col = 0;col<4;col++)
		{
			if(pok[tablenum][ln][col] != 0)
			{
				i++;
			}
		
		}
		if(i==3)
		{
			num++;
			point = ln;
		}
		else if(i == 2)
		{
			two++;
		}
		if(num > 0 && two > 0)
		{
			currentPoint[tablenum] = point;
			currentType[tablenum]  = ThreeTwain;
	//		cout<<"����Ϊ��������"<<endl<<"�Ƶ�Ϊ��"<<currentPoint<<endl;
			return true;
		}
	}
	return false;
}


////////////////////////////////////////////////////////////////////
////�����ж�
bool Logic::ListCheck(int tablenum,int* CurrentCards,int CurrentLen)
{
	int ln = 0;//14
	int col = 0;//4
	int num1 = 0;//�����Ƶ�����
	bool head=false;
	for(ln;ln < 12;ln++)
	{
		int num2 = 0;
		for (col = 0;col < 4;col++)
		{
			if(pok[tablenum][ln][col] != 0)
			{
				num2++;
				head = true;
			}
		//	else head = false;
		}
		if(num2 == 1)
		{
			num1++;
		}
		else if(num2 > 1)//��ʾ�жԻ����������͵���
			return false;
		if((num2 == 0 && head == true) || ln ==11 )
		{				
			if(num1>=5 && num1 == CurrentLen)
			{
				currentPoint[tablenum] = ln-num1;
				currentType[tablenum]  = list;	
			//	cout<<"����Ϊ������"<<endl<<"�Ƶ�Ϊ��"<<currentPoint<<endl;
				return true;			
			}
			else return false;
		}
		
	}
	return false;
}


////////////////////////////////////////////////////////////////////
////��ö��ж�
bool Logic::SisterDoubleCheck(int tablenum,int* CurrentCards,int CurrentLen)
{
	int ln	 = 0;//14
	int col	 = 0;//4
	int num1 = 0;//������
	bool head=false;
	for(ln = 0;ln < 12;ln++)
	{
		int num2 = 0;
		for (col = 0;col < 4;col++)
		{
			if(pok[tablenum][ln][col] != 0)
			{
				num2++;
			
			}
		}
		if(num2 == 2)
		{
			head = true;
			num1++;
		}
		else if(num2 != 2 && num2 != 0)//��ʾ�жԻ����������͵���
		{
			return false;
		}
		if(num2 == 0 && head == true )
		{				
			if(num1>=3 && num1*2 == CurrentLen)
			{
				currentPoint[tablenum] = ln-num1+1;
				currentType[tablenum]  = sisterTwain;
		//		cout<<"����Ϊ����ö�"<<endl<<"�Ƶ�Ϊ��"<<currentPoint<<endl;
				return true;
			}
			else return false;
		}
	}
}


////////////////////////////////////////////////////////////////////
////����һ�ɻ����ж�
bool Logic::PlaneOneCheck(int tablenum,int* CurrentCards,int CurrentLen)
{
	int num    = 0;//��������ͬ����Ŀ
	int single = 0; //������
	bool head  = false;
	int point  = 0;
	bool over  = false ;
	for(int ln = 0;ln<14;ln++)
	{
		int i = 0;
		for (int col = 0;col < 4;col++)
		{
			if(pok[tablenum][ln][col] != 0)
			{
				i++;
			}
		}

		if(i == 1)
		{
			single++;
		}

		else if( i == 3 && !over )
		{
			num++;
			if(num == 1)
			{
				point = ln;
			}
			head = true;
		}
		else 
		{
			if(i != 0)
			{
				return false;
			}
		}
		if(head && i != 3)
		{
			over = true;
		}
	}
	if(num == single)
	{
		currentPoint[tablenum] = point;
		currentType[tablenum]  = planeOne;
//		cout<<"����Ϊ������һ�ɻ�"<<endl<<"�Ƶ�Ϊ��"<<currentPoint<<endl;
		return true;
	}
	return false;
}


////////////////////////////////////////////////////////////////////
//////�������ɻ��ж�
bool Logic::PlaneTwoCheck(int tablenum,int* CurrentCards,int CurrentLen)
{
	int num   = 0;//��������ͬ����Ŀ
	int dbnum = 0; //˫����
	bool head = false;
	bool over = false;
	int point = 0;
	for(int ln = 0;ln<14;ln++)
	{
		int i = 0;
		for (int col = 0;col < 4;col++)
		{
			if(pok[tablenum][ln][col] != 0)
			{
				i++;
			}
		}
		if(i == 1 || i == 4)
			{
				return false;			
			}
		if(i == 2)
		{
			dbnum++;
		}

		else if(i == 3 && !over)
		{
			num++;
			if(num == 1)
			{
				point = ln;
			}
			head = true;
		}

		if(head && i != 3)
		{
			over = true;
		}
	}
	if(num == dbnum)
	{
		currentPoint[tablenum] = point;
		currentType[tablenum]  = planeTwain;
//		cout<<"����Ϊ���������ɻ�"<<endl<<"�Ƶ�Ϊ��"<<currentPoint<<endl;
		return true;
	}
	return false;
}
/////////////////////////////////////////////////////////////////
//��������
int Logic::GetPoint(int tablenum)
{
	return currentPoint[tablenum];
}


/////////////////////////////////////////////////////////////////
//�����Ƶ�
int Logic::GetType(int tablenum)
{
	return currentType[tablenum];
}


bool Logic::RuleCheck(int tablenum,int* CurrentCards,int CurrentLen)//�״γ��ƻ������ƹ����ж�
{
	bool result = false;
	switch (CurrentLen)
	{
	case 1:
		{
			currentPoint[tablenum] = logic.pointCheck(tablenum,*(CurrentCards));
			currentType[tablenum]  = single;
			return true;
		}
	case 2:
		{
			result = (logic.DoubleCheck(tablenum,CurrentCards));
			
			if(result)
			{
				return true;
			}
			break;
		}
	case 3:
		{
			result = (logic.ThreeCheck(tablenum,CurrentCards));
			if(result)
			{
				return true;
			}
			break;
		}
	case 4:
		{
			result = (Bombcheck(tablenum,CurrentCards));
			if(result)
			{
				return true;
			}
			result = (logic.ThreeOneCheck(tablenum,CurrentCards));
			if(result)
			{
				return true;
			}
			break;
		}
	case 5:
		{
			result = (logic.ListCheck(tablenum,CurrentCards,CurrentLen));
			if(result)
			{
				return true;
			}
			result = (logic.ThreeTowCheck(tablenum,CurrentCards));
			if(result)
			{
				return true;
			}
			
			break;
		}
	default:
		{
			if(CurrentLen%2==0)
			{
				if(CurrentLen%4==0)
				{
					result = (logic.PlaneOneCheck(tablenum,CurrentCards,CurrentLen));
				if(result)
				{
					return true;
				}
				}
				if(CurrentLen%5==0)
				{
					result = (logic.PlaneTwoCheck(tablenum,CurrentCards, CurrentLen));
					if(result)
					{
						return true;
					}
				}
				result = (logic.ListCheck(tablenum,CurrentCards,CurrentLen));
				if(result)
				{
					return true;
				}
				result = (logic.SisterDoubleCheck(tablenum,CurrentCards,CurrentLen));
				if(result)
				{
					return true;
				}
				break;
			}
			else
			{
				if(CurrentLen%5 == 0)
				{
					result = (logic.PlaneTwoCheck(tablenum,CurrentCards, CurrentLen));
					if(result)
					{
						return true;
					}
				}
				result = (logic.ListCheck(tablenum,CurrentCards,CurrentLen));
				if(result)
				{
					return true;
				}
			}
		}
		currentType[tablenum]  = err;
		currentPoint[tablenum] = 0;
		return false;
	}
	currentType[tablenum]  = err;
	currentPoint[tablenum] = 0;
	return false;
//	return true;
}

bool Logic::flowCheck(int tablenum,int* CurrentCards,int CurrentLen,int PreType,int PrePoint,int PreLen)				//���ƹ����ж�
{		
	logic.RuleCheck(tablenum,CurrentCards,CurrentLen);
	if((currentType[tablenum] == PreType) && (currentPoint[tablenum] > PrePoint))
	{
		return true;
	}
	return false;
}

bool Logic::bombWarning(int tablenum)
{
	if( multiple[tablenum] != 0)
	{
		multiple[tablenum] = 0;
		return true;
	}
		
	else return false;
}
bool Logic::LogicCheck(int tablenum,int* CurrentCards,int CurrentLen,int PreType,int PrePoint,int PreLen)
{
	currentType[tablenum]  = err;
	currentPoint[tablenum] = 0;
	Logic::SortPok(tablenum,CurrentCards,CurrentLen);
	if(PreLen == 0)//����
	{
		return(logic.RuleCheck(tablenum,CurrentCards,CurrentLen));
	}
	else//ѹ��
	{
		if(CurrentLen != PreLen)
		{
			if ( CurrentLen == 2 )
			{
				if(logic.DoubleCheck(tablenum,CurrentCards) && currentType[tablenum] == bomb)
				{
					return true;
				}
			}
			else if ( CurrentLen == 4)
			{
				if(logic.Bombcheck(tablenum,CurrentCards) && PreType != bomb)
				{
					return true;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			return(logic.flowCheck(tablenum,CurrentCards,CurrentLen,PreType,PrePoint, PreLen));	
		}	
		return false;
	}
	return false;
}

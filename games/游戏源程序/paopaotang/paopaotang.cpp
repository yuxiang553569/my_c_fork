// ���޸ĳ����뱣��ԭ������Ϣ��
// ������ԭ������Ϣ
// ���򿽱��ԣ�http://tieba.baidu.com/f?kz=66726190
/************************************************* 
name :POPO 
writer:LIU wenjie ���Ľ� 
date :2005-10 
����һ��ģ�������õ���Ϸ 
�ж�����Ҳ���  
**************************************************/ 
//
// ԭ���������� Turbo C 2.0 �£�����ֲ���� Visual C++ 6.0 �¡�
// ����������Ȱ�װ VC ��ͼ��(V20091123)����Ŀ��������
// ����޸�����: 2010-3-14
//
#include<graphics.h>/*�õ��Ŀ⺯��*/ 
#include<stdio.h> 
#include<stdlib.h> 
#include<math.h> 
#include <conio.h>
#include <time.h>
#define ESC 27 /*������ʹ�õ��ļ�ֵ*/ 
#define UP1 'w' 
#define DOWN1 's' 
#define LEFT1 'a' 
#define RIGHT1 'd' 
#define UP2 'i' 
#define DOWN2 'k' 
#define LEFT2 'j' 
#define RIGHT2 'l' 
#define Z 'z' 
#define DEL 8 
#define ENTER '\r' 
#define SPACE ' ' 

#define MX 21 /*ÿ�еķ�����*/ 
#define MY 16 /*ÿ�еķ�����*/ 
#define BOXLONG 30 /*����ĳ���*/ 


typedef struct/*������Ϸ ���˵Ľṹ��*/ 
{
	int x; 
	int y;/*�˵�λ��*/ 
	int definetime; /*�Ƿ����ը����ʱ*/ 
	int maxball;/*�����ԷŶ���ը��*/ 
	int power;/*ը����ը�ĳ��ȣ�Ҳ��������*/ 
	int ballnum;/*���ڷ��˶���ը��*/ 
}human; 

typedef struct/*����ը�������ݽṹ��������ֵ������ը������Ϣ*/ 
{ 
	int used;/*��ը���Ƿ�ʹ��*/ 
	int x; 
	int y;/*ը��λ��*/ 
	int man;/*˭�ŵ�ը��*/ 
	int page;/*��ǰը���ǵڼ�֡����������ը���Ķ�̬Ч��*/ 
	int time;/*ը�����õ�ʱ��*/ 
}tball; 


tball ball[10];/*����10��ը��*/ 
human man[2];/*����2����*/ 
IMAGE* tu[13];/*����13��ָ��ͼ���ָ�룬����ָ����Ϸ����Ҫ��ͼ��*/
//�м��мǣ���ָ���ʾͼ��û���⣬����ͨ�������С���������û��д


int map[MX][MY];/*����洢��Ī��Ϣ������*/ 
int ballnum=0;/*�������浱ǰ����ը�����ܸ���*/ 

void BaoZa(int num);

/*���������������ʼ����Ļ*/ 
void initgra() 
{
	initgraph(640,480);
	for(int i=0; i<13; i++)
		tu[i]=new IMAGE();

	// �����˰���˵�����Ǻ�
	setfont(24,0,"����");
	outtextxy(10,50,"����˵����");
	setfont(16,0,"����");
	outtextxy(10, 100, "P1: ����asdw�����ף��ո񣻶�ʱ�ף�z");
	outtextxy(10, 140, "P2: ����jkli�����ף��س�����ʱ�ף��˸�");
	outtextxy(10, 300, "���������ʼ��Ϸ");
	getch();
	cleardevice();
} 



/*********************************** 
�����������������Ϸ�в���һ����Ϣ�Ի��� 

  ����Ϊһ���ַ���ָ�� 
  
	����ֵΪһ���������� 
	�������Ϊ ��n�� 
	����0 
	���򷵻� 1 
*********************************/ 
int message(char *s) 
{
	char c; 
	setfillstyle(RED);
	setcolor(BLUE); 
	//settextstyle(0,0,3); 
	bar(640/2-200,480/2-50,640/2+250,480/2+50); 
	outtextxy(640/2-200,480/2-20,s);
	c=getch(); 
	//sleep(2); 
	if(c=='n'|| c=='N')return(0);else return(1); 
	
} 



/**************************************** 

  
	�ÿ⺯�������Ϸ�����õ���ͼ�񣬱��浽�����пռ���  
	
**************************************/ 
void draw() 
{
	int i=0; 
	cleardevice(); 
	
	/*��һ���հ�ͼ��浽0�ſռ���*/ 
	
	getimage(tu[0],0,0,29,29);
	
	/*�����ǻ�������ը���Ķ�̬Ч�����ĸ�ͼ��1~4 �ſռ���*/ 
	
	setcolor(RED); 
	setfillstyle(RED); 
	for(i=0;i<4;i++) 
	{ 
		fillellipse(15,15,7+i*2,7+i*2); 
		getimage(tu[i+1],0,0,29,29); 
	} 
	
	putimage(0,0,tu[4],SRCINVERT);/*���ͼ���Ի���ͼ*/ 
	
	/*����ʱ����ͼ�񲢴浽5�ſռ���*/ 
	
	setcolor(LIGHTRED); 
	line(3,5,20,25); 
	line(20,25,28,5); 
	line(28,5,3,5); 
	fillellipse(16,15,4,4); 
	getimage(tu[5],0,0,29,29); 
	putimage(0,0,tu[5],SRCINVERT); 
	
	tu[6]=tu[4];/*���ſմ����ը��ͼ�񣬳��˿������ӷŵ�ը������*/ 
	/*�������ʹ��ը������֡��ͼ��*/ 
	
	
	
	/*������ͼ��浽7�ſռ���*/ 
	
	setcolor(RED); 
	setlinestyle(0,0,3);
	line(20,2,7,16); 
	line(20,2,16,12); 
	line(16,12,24,13); 
	line(7,16,15,15); 
	line(15,15,8,29); 
	line(24,13,8,29); 
	getimage(tu[7],0,0,29,29); 
	putimage(0,0,tu[7],SRCINVERT); 
	
	/*��ģ�ⱬըЧ����ͼ��浽8�ſռ���*/ 
	
	for(i=0;i<200;i++) 
		putpixel(rand()%30,rand()%30,rand()%16); 
	getimage(tu[8],0,0,29,29); 
	putimage(0,0,tu[8],SRCINVERT); 
	
	
	
	/*�ѿ��ƶ�������ͼ��浽9�ſռ���*/ 
	
	setcolor(BLUE); 
	setfillstyle(YELLOW); 
	bar(1,1,28,28); 
	setcolor(BLUE); 
	line(15,1,15,10); 
	line(1,10,28,10); 
	line(1,20,29,20); 
	line(15,20,15,28); 
	getimage(tu[9],0,0,29,29); 
	putimage(0,0,tu[9],SRCINVERT); 
	
	/*�Ѳ����ƶ�������ͼ��浽10�ſռ���*/ 
	
	setcolor(LIGHTBLUE); 
	setfillstyle(LIGHTRED); 
	bar3d(1,1,26,26,1,1); 
	getimage(tu[10],0,0,29,29); 
	putimage (0,0,tu[0]); 
	
	
	/*�ѵ�һ������ͼ��浽11�ſռ���*/ 
	
	setlinestyle(0,0,3); 
	setcolor(RED); 
	circle(15,15,13); 
	circle(8,13,4); 
	circle(24,13,4); 
	line(11,18,17,15); 
	line(11,18,15,19); 
	setlinestyle(0,0,3); 
	arc(15,15,225,320,9); 
	getimage(tu[11],0,0,29,29); 
	putimage(0,0,tu[11],SRCINVERT); 
	
	/*�ѵڶ�������ͼ��浽11�ſռ���*/ 
	
	setlinestyle(0,0,3); 
	setcolor(BLUE); 
	circle(15,15,13); 
	circle(8,13,4); 
	circle(24,13,4); 
	line(11,18,17,15); 
	line(11,18,15,19); 
	setlinestyle(0,0,3); 
	arc(15,15,225,320,9); 
	getimage(tu[12],0,0,29,29); 
	putimage(0,0,tu[12],SRCINVERT); 
	
} 

void  GameOver() 
{
	int i; 
	/*�ͷ��ڴ�ռ�*/ 
	for(i=0;i<13;i++) delete tu[i]; 
	/*�ر�ͼ����ʾģʽ*/ 
	closegraph(); 
	
	/*��������*/ 
	exit(1); 
} 



/*************************************** 
��һ�����������ըЧ�� 
����num��Ҫ��ը��ը����� 
x1,y1 ը�ķ��� 
0,1 ������ 
0,-1 ���� 
��1,0 ���� 
1,0 ���� 

****************************************/ 

int ZaLine(int x1,int y1,int num,int *IsHave ) 
{ 
	int x,y,x2,y2,i,l,j; 
	x2=ball[num].x;/* ȡ��ը��λ�� */ 
	y2=ball[num].y; 
	
	l=man[ball[num].man].power;/* ը����ը�ĳ��� */ 
	
	for(i=0,j=0;abs(i)<l&&abs(j)<l;i+=x1,j+=y1)/*���û�е�ָ������ */ 
	{
		x=x2+i;y=y2+j;/* ��ǰը����λ��λ�� */ 
		
		if(x<0||x>20||y<0||y>15) return 0;/* ���������Ļ��Χ���˳�����ִ�� */ 
		
		if ((x==man[0].x&&y==man[0].y)||(x==man[1].x&&y==man[1].y))/* ���ը������ */ 
		{
			if (!(x==man[0].x&&y==man[0].y))/* �������һ�� */ 
				message("the red win!");/* ��ʾ��ɫ���ʤ����Ϣ */ 
			else 
				message("the green win!");/* ��ʾ��ɫ���ʤ����Ϣ */ 
			
			GameOver();/* ������Ϸ */ 
			
		}else if(map[x][y]==0)/* ���Ϊ�� */ 
			
		{
			putimage((x)*30,(y)*30,tu[8]);/*�ű�ըЧ��ͼ */ 
			
		}else if(map[x][y]==9)/* ���Ϊ�������� */ 
			
		{
			putimage((x)*30,(y)*30,tu[0]);/* ��ȥԭʼͼ��*/ 
			
			putimage((x)*30,(y)*30,tu[8]);/*�ű�ըЧ��ͼ */ 
			if (rand()%4==0) /*������������Ч��*/ 
			{ int r; 
			r=(rand()%3)+5; 
			if(r>7)r--; 
			map[x][y]=r; 
			} 
			else map[x][y]=0; 
			return 0;/* ��Ϊը���˿ɳԵĶ���������ֹͣ��ը */ 
		} 
		else if (map[x][y]>=20)  
		{ (*IsHave)++; 
		BaoZa(map[x][y]%10);/* ����鵽ը��������ը */ 
		
		} 
		else if (map[x][y]==10) return 0;/* ���������ը�������ӣ�ֹͣ��ը */ 
		
		else/* ����������϶������������ԳԵĶ������������磬��ʱ������ը��������ը����������ը */ 
		{ putimage((x)*30,(y)*30,tu[0],SRCCOPY); 
		putimage((x)*30,(y)*30,tu[8],SRCCOPY); 
		if (rand()%3==0) 
			map[x][y]=(rand()%3)+5; 
		else 
			map[x][y]=0; 
		return(0); 
		} 
	}/* end of for */ 
}/* end of ZaLine*/ 

 /************************************** 
 ��ը������ը�ֳ� 
 ������Zaline()һ�� 
 �ѱ�ը�����Ķ�����ʾ���� 
 ���ѱ�ըЧ��ͼ��ȥ 
**********************************/ 
int HuanYuan(int x1,int y1,int num) 
{ 
	int x,y,x2,y2,l,i,j; 
	x2=ball[num].x; 
	y2=ball[num].y; 
	l=man[ball[num].man].power; 
	
	for(i=0,j=0;abs(i)<l&&abs(j)<l;i+=x1,j+=y1) 
	{x=x2+i;y=y2+j; 
	if(x<0||x>20||y<0||y>15)return 0; 
	if(map[x][y]==0) 
	{ putimage((x)*30,(y)*30,tu[0],SRCCOPY); 
	map[x][y]=0; 
	}else if (map[x][y]>=5&&map[x][y]<=7) 
	{ putimage(x*30,y*30,tu[0],SRCCOPY); 
	putimage(x*30,y*30,tu[map[x][y]],SRCCOPY); 
	}else return 0; 
	} 
} 

/************************ 
����ZALINE() ��huanyuan()���� 
������ըЧ�� 
******************************/ 
void BaoZa(int num) 
{ 
	int IsHave=0; 
	
	map[ball[num].x][ball[num].y]=0;/* ��ȥ��Ϸ��Ϣ�����������*/ 
	man[ball[num].man].ballnum--;/* ʹ���˵ĵ�ǰ�ŵ�ը������1 */ 
	ballnum--;/* ʹǰ�ŵ���ը������1 */ 
	ball[num].used=0;/*ʹ���ը������ĩʹ�� */ 
	
	/* ��ը */ 
	ZaLine(-1,0,num,&IsHave); 
	ZaLine(1,0,num,&IsHave); 
	ZaLine(0,-1,num,&IsHave); 
	ZaLine(0,1,num,&IsHave); 
	
	if (0 == IsHave ) 
		Sleep(1);/* ��ʱ*/ 
	
	/*��ԭ�ֳ�*/ 
	
	HuanYuan(-1,0,num); 
	HuanYuan(1,0,num); 
	HuanYuan(0,-1,num); 
	HuanYuan(0,1,num); 
	
	
	/*end of for */ 
	
} 






/*************************** 
��һ��ը�� 
����Ϊ��ը�� ���˵ı� �� 
**************************/ 

int PutZaDan(int mann) 
{ 
	int i; 
	SYSTEMTIME s; 
	GetLocalTime(&s);/* ȡ��ǰʱ��*/ 
	if (ballnum>9 || man[mann].ballnum>=man[mann].maxball) return 0; 
	/* �����ǰ��ը�� ��>9���˵ĵ�ǰ������ը����>���������ŵ�������������ִ��*/ 
	
	
	ballnum++;/* ʹ��ǰ�ŵ���ը������1 */ 
	man[mann].ballnum++;/* ʹ���˵ĵ�ǰ�ŵ�ը������1 */ 
	for (i=0;i<10;i++)
		if (ball[i].used==0)
			break;/* �ҵ�ǰĩʹ�õ�ը�� */ 
		ball[i].man=mann;/* ����ը����Ϣ*/ 
		ball[i].time=s.wSecond; 
		ball[i].x=man[mann].x; 
		ball[i].y=man[mann].y; 
		ball[i].page=1; 
		ball[i].used=1; 
		/* ����Ļ�Ϸ�һ��ը����λ��Ϊ�ŵ��˵�λ�� */ 
		putimage(ball[i].x*30,ball[i].y*30,tu[1],SRCCOPY); 
		map[ball[i].x][ball[i].y]=20+i; 
} 
/*********************** 
����ը���Ķ�̬��ʾ 
*************************/ 

void DrawZaDan() 
{
	int i; 
	for (i=0;i<10;i++) 
	{ if (ball[i].used==0)continue;/* ���ը��ĩʹ�ü���ѭ��*/ 
	if (ball[i].page<4)/* ���ը��֡��<4��֡����1��ֱ����ը��λ�÷���һ֡*/ 
	{ball[i].page++; 
	putimage(ball[i].x*30,ball[i].y*30,tu[ball[i].page],SRCCOPY); 
	} 
	else/* ��֡����Ϊ1����ȥԭͼ�����һ֡*/ 
	{ball[i].page=1; 
	putimage(ball[i].x*30,ball[i].y*30,tu[0],SRCCOPY); 
	putimage(ball[i].x*30,ball[i].y*30,tu[1],SRCCOPY); 
	} 
	} 
} 
/***************************** 
����Ƿ��и�ը��ը�� 
������������� 
****************************/ 
void CheckZaDan() 
{ 
	int i,t; 
	SYSTEMTIME t1; 
	GetLocalTime(&t1); 
	t=t1.wSecond; 
	for (i=0;i<10;i++) 
		if (ball[i].used==1&&(t+60-ball[i].time)%60>=2&&man[ball[i].man].definetime==0) BaoZa(i); 
} 

/*********************** 
��ʱ������ը��  
����Ϊ�����˵ı�� 
*************************/ 
int DefineZa(int n) 
{ 
	int i; 
	if (man[n].definetime==0) return 0; 
	for (i=0;i<10;i++) 
		if (ball[i].used==1&&ball[i].man==n)BaoZa(i); 
		
} 

/*************************** 
��ʼ����Ϸ 
�����������ͼ 
****************************/ 
void initgame() 
{
	int i,j; 
	cleardevice(); 
	
	srand(time(NULL)); 
	
	/*�������ը��*/ 
	for(i=0;i<10;i++) ball[i].used=0; 
	/*�Ȱ���Ļ��Ϣ�����ʼ��ʲΪ100*/ 
	for (i=0;i<22;i++) 
		for (j=0;j<16;j++) 
			map[i][j]=100; 
		/*�Ȱ���Ļ��Ϣ�����˵�λ�ã�ʼ������ÿ�ζ�����*/ 
		
		
		man[0].x=0; 
		man[0].y=0; 
		man[0].maxball=1; 
		man[0].ballnum=0; 
		man[0].power=2; 
		
		man[0].definetime=0; 
		man[1].x=MX-1; 
		man[1].y=MY-1; 
		man[1].maxball=1; 
		man[1].ballnum=0; 
		man[1].power=2; 
		man[1].definetime=0; 
		map[0][0]=11; 
		map[0][1]=0; 
		map[1][0]=0; 
		map[MX-1][MY-1]=12; 
		map[MX-1][MY-2]=0 ; 
		map[MX-2][MY-1]=0; 
		/*���˵�ͼ���*/ 
		
		putimage(0,0,tu[11],SRCINVERT); 
		
		putimage(600,15*30,tu[12]); 
		
		/*������������ͼ*/ 
		for (i=0;i<21;i++) 
			for (j=0;j<16;j++) 
			{ if (map[i][j]!=100) continue; 
			
			if (rand()%2==0||rand()%6==0) 
			{ 
				map[i][j]=9; 
				putimage(i*30,j*30,tu[9],SRCCOPY); 
			}else if(rand()%2==0||rand()%5==0) 
			{map[i][j]=10; 
			putimage(i*30,j*30,tu[10]); 
			}else 
				map[i][j]=0; 
			} 
			
			
} 


/*************************** 
�����˵��ƶ�Ч�� 

  ���а����Զ����������ӵȹ��� 
  
	����x1,y1Ϊ�ƶ��ķ���  
	��zaline()��ͬ 
	mannΪҪ�ƶ��˵ı�� 
****************************/ 


int move(int x1 ,int y1,int mann ) 
{ 
	int fx ,fy,x,y;/*x,y Ϊ���ڵ�λ�ã�fx,fy,���Ҫ�ƶ�����λ��*/ 
	
	x=man[mann].x;/*ȡҪ�ƶ��˵�λ��*/ 
	y=man[mann].y; 
	
	fx=x+x1;/*Ҫ�ƶ��� ��λ��Ϊ*/ 
	fy=y+y1; 
	
	if ((fx>=0&&fx<MX&&fy>=0&&fy<MY))/*Ҫ�ƶ�����λ���Ƿ�������Χ��*/ 
		
	{ switch(map[fx][fy]) 
	{ case 0:/*���Ҫ�ƶ�����λ��Ϊ��*/ 
	
	putimage(x*BOXLONG,y*BOXLONG,tu[0],SRCCOPY); 
	putimage(fx*BOXLONG,fy*BOXLONG,tu[11+mann],SRCCOPY); 
	
	break; 
case 5:/*���Ҫ�ƶ�����λ��Ϊ��ʱ��*/ 
	putimage(x*BOXLONG,y*BOXLONG,tu[0],SRCCOPY); 
	putimage(fx*BOXLONG,fy*BOXLONG,tu[11+mann],SRCCOPY); 
	man[mann].definetime=1; 
	break; 
case 6:/*���Ҫ�ƶ�����λ��Ϊ������ը��*/ 
	putimage(x*BOXLONG,y*BOXLONG,tu[0],SRCCOPY); 
	putimage(fx*BOXLONG,fy*BOXLONG,tu[11+mann],SRCCOPY); 
	man[mann].maxball++; 
	break; 
	
case 7:/*���Ҫ�ƶ�����λ��Ϊ���磬��*/ 
	putimage(x*BOXLONG,y*BOXLONG,tu[0],SRCCOPY); 
	putimage(fx*BOXLONG,fy*BOXLONG,tu[11+mann],SRCCOPY); 
	man[mann].power++; 
	break; 
	
case 9:/*���Ҫ�ƶ�����λ��Ϊ���Ƶ����ӣ���������Ч��*/ 
	if(x+x1*2>=0&&x+x1*2<MX&&y+y1*2>=0&&y+y1*2<MY&&map[x+x1*2][y+y1*2]==0) 
	{putimage((x+x1*2)*BOXLONG,(y+y1*2)*BOXLONG,tu[9],SRCCOPY); 
	putimage((fx)*BOXLONG,(fy)*BOXLONG,tu[0],SRCCOPY); 
	putimage((fx)*BOXLONG,(fy)*BOXLONG,tu[mann+11],SRCCOPY); 
	putimage(x*30,y*30,tu[0],SRCCOPY); 
	map[x+x1*2][y+y1*2]=9; 
	map[fx][fy]=mann+11; 
	map[x][y]=0; 
	
	break;} 
default:return 0; 
	}/* end of switch*/ 
	/*�ƶ���ϣ��޸���Ļ������Ϣ*/  
	map[x][y]=0; 
	map[fx][fy]=11+mann; 
	/*�޸��ƶ��˵���Ϣ*/ 
	man[mann].x=fx; 
	man[mann].y=fy; 
	}/*end of if ��Χ*/ 
	
}/* end of funtion*/ 




void main() 
{ 
	
	int key=0,oldtime=0;/*K�������水��ֵ��oldtime������ʱ*/ 
	SYSTEMTIME t1;/*����һ��ʱ���ͽṹ��*/ 
	
	
	initgra();/*��Ļ��ʼ��*/ 
	draw();/*��ͼ������ͼ��*/ 
	initgame();/*��Ϸ��ʼ��*/ 
	
	
	while(1) 
	{
		if (!kbhit())/*û�а���*/ 
		{ /*ÿ90�ٷ��룬���һ��ը���Ƿ񵽱�ըʱ�䣬���ػ�һ��ը����������̬Ч��*/ 
			GetLocalTime(&t1); 
			if(t1.wMilliseconds-oldtime>90) 
			{ 
				CheckZaDan(); 
				DrawZaDan(); 
			} 
			
		}else{ 
			/*���ݰ���ֵ��ִ����Ӧ������*/ 
			
			key=getch(); 
			switch(key) 
			{case UP1: move(0,-1,0);break; 
			case DOWN1: move(0,1,0);break; 
			case LEFT1: move(-1,0,0);break; 
			case RIGHT1:move(1,0,0);break; 
			case UP2:move(0,-1,1);break; 
			case DOWN2:move(0,1,1);break; 
			case LEFT2:move(-1,0,1);break; 
			case RIGHT2:move(1,0,1);break; 
			case ENTER:PutZaDan(1);break; 
			case SPACE:PutZaDan(0);break; 
			case Z:DefineZa(0);break; 
			case DEL:DefineZa(1);break; 
			case ESC: GameOver();break; 
			} 
			
		} 
		
	} 
	
}
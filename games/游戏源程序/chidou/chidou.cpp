// �����޸��߱���ԭ������Ϣ��
// ����Ϸԭ���ߣ�c���� (http://tieba.baidu.com/i/30127775)
// ��Ϸ������ַ��http://tieba.baidu.com/f?z=3651039&ct=335544320&lm=0&sc=0&rn=30&tn=baiduPostBrowser&word=c%D3%EF%D1%D4&pn=0
//
// ԭ���������� Turbo C 2.0 �£�����ֲ���� Visual C++ 6.0 �¡�
// ����������Ȱ�װ VC ��ͼ��(V20091123)����Ŀ��������
// ����޸�����: 2010-3-14
//
#include <conio.h>
#include <time.h>
#include <graphics.h>
#define LEFT 'a'
#define RIGHT 'd'
#define DOWN 's'
#define UP 'w'
#define ESC '27'
#define ENTER '13'
/*2ǽ��,1�����ƶ��ط�,3�Լ�,4����*/ 
int a[15][20]={	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 
				2,1,1,0,0,0,1,0,1,0,0,0,1,1,1,1,1,1,0,2, 
				2,1,2,2,2,1,1,2,1,1,0,0,0,1,1,4,1,1,0,2, 
				2,1,1,0,2,1,1,2,0,1,1,2,2,2,2,2,0,0,0,2, 
				2,4,1,0,2,1,1,2,1,1,1,0,1,1,1,1,0,1,1,2, 
				2,1,2,1,2,1,1,2,1,3,2,2,1,1,1,1,2,2,1,2, 
				2,1,2,1,2,1,1,1,1,1,1,1,1,0,0,0,1,1,1,2, 
				2,1,2,1,0,1,1,1,1,2,1,0,1,2,2,2,1,1,1,2, 
				2,1,0,1,0,1,2,1,1,2,1,0,1,2,1,1,4,1,1,2, 
				2,1,0,2,0,1,2,1,1,2,1,0,1,2,1,1,1,1,1,2, 
				2,1,0,2,1,1,2,1,1,2,1,0,2,2,1,0,0,0,1,2, 
				2,1,1,2,1,1,2,1,1,2,1,0,2,1,1,2,2,1,1,2, 
				2,1,2,2,1,2,2,1,1,1,1,0,1,4,1,2,0,0,1,2, 
				2,1,0,0,0,0,0,4,0,1,1,0,1,1,1,1,0,0,1,2, 
				2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};/*������ǵ�ͼ*/ 
struct play /*��Ϸ������Ľṹ��*/ 
{ 
	int x; 
	int y; 
}; 
struct play you,them[5]; 
int sum=0;/*ͳ�ƳԵĶ��Ӹ���,����50�ž���ʤ��*/ 
int xx[5][2];/*�жϵ��˷����õĽṹ��*/ 
int isfalse=0;
void TimeDelay(unsigned long microsec) /*��ʱ���� ����΢����*/ 
{
	microsec /= 1000;	// ��ɺ���
	Sleep(microsec);
} 
void drawblackdou(int x,int y)/*�Զ��ӵĺ���*/ 
{ 
	setcolor(0); 
	circle(100+y*20,100+x*20,3); 
	sum++;/*�Ե����Ӻ�ͼ�һ*/ 
	a[x][y]=1;/*�Ե�������ͳ�Ϊ��ͨƽ��*/ 
} 

void begain()/*��ʼ����*/ 
{
	int i,j; 
	for(i=0;i<15;i++) 
		for(j=0;j<20;j++) 
			if(a[i][j]==2)/*����ǽ��*/ 
			{ 
				setfillstyle(BLUE); 
				bar(100+j*20-10,100+i*20+10,100+j*20+10,100+i*20-10); 
			} 
			else if(a[i][j]==3)/*�����Լ�*/ 
			{ 
				setcolor(RED); 
				circle(100+j*20,100+i*20,9); 
			} 
			else if(a[i][j]==4)/*�������*/ 
			{ 
				setcolor(GREEN); 
				circle(100+j*20,100+i*20,9); 
			} 
			else if(a[i][j]==0)/*������*/ 
			{ 
				setcolor(YELLOW); 
				circle(100+j*20,100+i*20,3); 
			} 
			you.x=5;you.y=9;/*����Ҳ�Լ��Ŀ�ʼ����*/ 
			them[0].x=2;them[0].y=15; 
			them[1].x=4;them[1].y=1; 
			them[2].x=8;them[2].y=16; 
			them[3].x=12;them[3].y=13; 
			them[4].x=13;them[4].y=7; 
} 
void movethem(struct play *them)/*�����ƶ��Ĺ���*/ 
{
	int i;
	srand(time(NULL));
	for(i=0;i<5;i++) 
	{ 
		if(you.x==them[i].x&&(them[i].y+1)==you.y) 
			them[i].y++; 
		else if(you.x==them[i].x&&(them[i].y-1)==you.y) 
			them[i].y--; 
		else if(you.y==them[i].y&&(them[i].x+1)==you.x) 
			them[i].x++; 
		else if(you.y==them[i].y&&(them[i].x-1)==you.x)/*ֻҪ����������߾���������ȥ*/ 
			them[i].x--; 
		else 
		{ 
loop: 
		xx[i][0]=rand()%4+1;/*����ķ����ȡ�����ֵ,ԭ�����µķ��򲻿��Ժ�ԭ���ķ����෴*/ 
		if(xx[i][0]==1&&xx[i][1]==2||xx[i][0]==2&&xx[i][1]==1) 
			goto loop; 
		if(xx[i][0]==3&&xx[i][1]==4||xx[i][0]==4&&xx[i][1]==3) 
			goto loop; 
		xx[i][1]=xx[i][0]; 
		if(xx[i][0]==1)/*�ĸ�����*/ 
		{them[i].x--; 
		if(a[them[i].x][them[i].y]==2)/*�����ǽ�ڵĻ��ͻص�ԭ���ĵط��ȴ�����ķ���*/ 
		{them[i].x++;goto loop;} 
		} 
		else if(xx[i][0]==2) 
		{them[i].x++; 
		if(a[them[i].x][them[i].y]==2) 
		{them[i].x--;goto loop;} 
		} 
		else if(xx[i][0]==3) 
		{them[i].y++; 
		if(a[them[i].x][them[i].y]==2) 
		{them[i].y--;goto loop;} 
		} 
		else if(xx[i][0]==4) 
		{them[i].y--; 
		if(a[them[i].x][them[i].y]==2) 
		{them[i].y++;goto loop;} 
		} 
		} 
	} 
} 
void fun(struct play *them)/*�ƶ��е��ж�*/ 
{ 
	int i; 
	setcolor(0);/*�ѵ��˵���λ��ɾ��*/ 
	for(i=0;i<5;i++) 
		circle(them[i].y*20+100,them[i].x*20+100,9); 
	movethem(them);/*���ݿ����ߵ�λ�����������˵��ƶ�����*/ 
} 
void win()/*ʤ���Ļ�*/ 
{ 
	cleardevice(); 
	setfont(60, 0, "Arial");
	while(!kbhit()) 
	{
		setcolor(YELLOW); 
		outtextxy(200,200,"YOU WIN!"); 
		Sleep(1000); 
	} 
} 
void false1()/*ʧ�ܻ���*/ 
{ 
	cleardevice(); 
	setfont(60, 0, "Arial");
	while(!kbhit()) 
	{
		setcolor(RED); 
		outtextxy(180,200,"GAME OVER!"); 
		Sleep(1000);
	} 
} 

void loseyes()/*�ж��Ƿ�ʧ��*/ 
{
	int i; 
	for(i=0;i<5;i++) 
		if(them[i].x==you.x&&them[i].y==you.y) 
			isfalse=1;/*���ʧ�ܵĻ�*/ 
} 

void main() 
{
	int gd=DETECT,gm; 
	int key,i; 
	initgraph(&gd,&gm,"c:\\tc"); 
	cleardevice(); 
	begain();/*��ʼ����*/  
	while(1) 
	{ 
		while(!kbhit()) 
		{ 
			setcolor(GREEN);/*�ػ�����*/ 
			for(i=0;i<5;i++) 
				circle(them[i].y*20+100,them[i].x*20+100,9); 
			TimeDelay(280000); 
			fun(them);/*�������*/ 
			for(i=0;i<5;i++) 
				if(them[i].x==you.x&&them[i].y==you.y) 
					isfalse=1;/*���ʧ�ܵĻ�*/ 
				loseyes();/*�ж��Ƿ�ʧ��*/ 
				if(isfalse) 
					break; 
		} 
		if(isfalse) 
			break; 
		key=getch();
		setcolor(0);/*���Լ�ԭ��λ�õ��˸�ɾ����*/ 
		circle(100+you.y*20,100+you.x*20,9); 
		if(key==ESC) 
			break; 
		else if(key==UP)/*���￪ʼ���ж���Ҫ���Ƿ�Ե����Ӻ�����ǽ��*/ 
		{you.x--; 
		if(a[you.x][you.y]==2) you.x++; 
		else if(a[you.x][you.y]==0) 
			drawblackdou(you.x,you.y);} 
		else if(key==DOWN) 
		{you.x++;if(a[you.x][you.y]==2) you.x--; 
		else if(a[you.x][you.y]==0) 
			drawblackdou(you.x,you.y);} 
		else if(key==RIGHT) 
		{you.y++;if(a[you.x][you.y]==2) you.y--; 
		else if(a[you.x][you.y]==0) 
			
			drawblackdou(you.x,you.y);} 
		else if(key==LEFT) 
		{you.y--;if(a[you.x][you.y]==2) you.y++; 
		else if(a[you.x][you.y]==0) 
			drawblackdou(you.x,you.y);} 
		if(sum==50) 
			break; 
		setcolor(RED);/*ִ����һ�μ��̺��ٻ����Լ���λ��*/ 
		circle(100+you.y*20,100+you.x*20,9); 
		loseyes();/*�Լ�����ȥ�������˵Ŀ���*/ 
		if(isfalse) 
			break; 
	} 
	if(sum==50)/*����������*/ 
	{
		win();
		getch();
	} 
	if(isfalse) 
	{
		false1();
		getch();
	} 
	closegraph(); 
}
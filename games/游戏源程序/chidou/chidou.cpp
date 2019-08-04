// （请修改者保留原作者信息）
// 该游戏原作者：c闲人 (http://tieba.baidu.com/i/30127775)
// 游戏拷贝地址：http://tieba.baidu.com/f?z=3651039&ct=335544320&lm=0&sc=0&rn=30&tn=baiduPostBrowser&word=c%D3%EF%D1%D4&pn=0
//
// 原程序运行在 Turbo C 2.0 下，我移植到了 Visual C++ 6.0 下。
// 编译代码请先安装 VC 绘图库(V20091123)，项目中有下载
// 最后修改日期: 2010-3-14
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
/*2墙壁,1可以移动地方,3自己,4敌人*/ 
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
				2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};/*数组就是地图*/ 
struct play /*游戏中人物的结构体*/ 
{ 
	int x; 
	int y; 
}; 
struct play you,them[5]; 
int sum=0;/*统计吃的豆子个数,吃满50颗就算胜利*/ 
int xx[5][2];/*判断敌人方向用的结构体*/ 
int isfalse=0;
void TimeDelay(unsigned long microsec) /*延时函数 传入微秒数*/ 
{
	microsec /= 1000;	// 变成毫秒
	Sleep(microsec);
} 
void drawblackdou(int x,int y)/*吃豆子的函数*/ 
{ 
	setcolor(0); 
	circle(100+y*20,100+x*20,3); 
	sum++;/*吃到豆子后就加一*/ 
	a[x][y]=1;/*吃到后这里就成为普通平地*/ 
} 

void begain()/*开始函数*/ 
{
	int i,j; 
	for(i=0;i<15;i++) 
		for(j=0;j<20;j++) 
			if(a[i][j]==2)/*代表墙壁*/ 
			{ 
				setfillstyle(BLUE); 
				bar(100+j*20-10,100+i*20+10,100+j*20+10,100+i*20-10); 
			} 
			else if(a[i][j]==3)/*代表自己*/ 
			{ 
				setcolor(RED); 
				circle(100+j*20,100+i*20,9); 
			} 
			else if(a[i][j]==4)/*代表敌人*/ 
			{ 
				setcolor(GREEN); 
				circle(100+j*20,100+i*20,9); 
			} 
			else if(a[i][j]==0)/*代表豆子*/ 
			{ 
				setcolor(YELLOW); 
				circle(100+j*20,100+i*20,3); 
			} 
			you.x=5;you.y=9;/*敌人也自己的开始坐标*/ 
			them[0].x=2;them[0].y=15; 
			them[1].x=4;them[1].y=1; 
			them[2].x=8;them[2].y=16; 
			them[3].x=12;them[3].y=13; 
			them[4].x=13;them[4].y=7; 
} 
void movethem(struct play *them)/*敌人移动的过程*/ 
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
		else if(you.y==them[i].y&&(them[i].x-1)==you.x)/*只要控制者在身边就立即靠上去*/ 
			them[i].x--; 
		else 
		{ 
loop: 
		xx[i][0]=rand()%4+1;/*这里的方向采取随机赋值,原则是新的方向不可以和原来的方向相反*/ 
		if(xx[i][0]==1&&xx[i][1]==2||xx[i][0]==2&&xx[i][1]==1) 
			goto loop; 
		if(xx[i][0]==3&&xx[i][1]==4||xx[i][0]==4&&xx[i][1]==3) 
			goto loop; 
		xx[i][1]=xx[i][0]; 
		if(xx[i][0]==1)/*四个方向*/ 
		{them[i].x--; 
		if(a[them[i].x][them[i].y]==2)/*如果碰墙壁的话就回到原来的地方等待随机的方向*/ 
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
void fun(struct play *them)/*移动中的判断*/ 
{ 
	int i; 
	setcolor(0);/*把敌人的老位置删除*/ 
	for(i=0;i<5;i++) 
		circle(them[i].y*20+100,them[i].x*20+100,9); 
	movethem(them);/*根据控制者的位置来决定敌人的移动方向*/ 
} 
void win()/*胜利的话*/ 
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
void false1()/*失败画面*/ 
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

void loseyes()/*判断是否失败*/ 
{
	int i; 
	for(i=0;i<5;i++) 
		if(them[i].x==you.x&&them[i].y==you.y) 
			isfalse=1;/*如果失败的话*/ 
} 

void main() 
{
	int gd=DETECT,gm; 
	int key,i; 
	initgraph(&gd,&gm,"c:\\tc"); 
	cleardevice(); 
	begain();/*开始画面*/  
	while(1) 
	{ 
		while(!kbhit()) 
		{ 
			setcolor(GREEN);/*重画敌人*/ 
			for(i=0;i<5;i++) 
				circle(them[i].y*20+100,them[i].x*20+100,9); 
			TimeDelay(280000); 
			fun(them);/*处理敌人*/ 
			for(i=0;i<5;i++) 
				if(them[i].x==you.x&&them[i].y==you.y) 
					isfalse=1;/*如果失败的话*/ 
				loseyes();/*判断是否失败*/ 
				if(isfalse) 
					break; 
		} 
		if(isfalse) 
			break; 
		key=getch();
		setcolor(0);/*把自己原来位置的人给删除掉*/ 
		circle(100+you.y*20,100+you.x*20,9); 
		if(key==ESC) 
			break; 
		else if(key==UP)/*这里开始的判断主要是是否吃到豆子和碰到墙壁*/ 
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
		setcolor(RED);/*执行了一次键盘后再画出自己的位置*/ 
		circle(100+you.y*20,100+you.x*20,9); 
		loseyes();/*自己走上去碰到敌人的可能*/ 
		if(isfalse) 
			break; 
	} 
	if(sum==50)/*吃满豆子了*/ 
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
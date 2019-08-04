// （请修改者保留原作者信息）
// 该动画原作者：stormbolt (http://tieba.baidu.com/i/20696668)
// 游戏拷贝地址：http://tieba.baidu.com/f?ct=335675392&tn=baiduPostBrowser&sc=7652483537&z=198861553#7652483537
//
// 原程序运行在 Turbo C 2.0 下，我移植到了 Visual C++ 6.0 下。
// 编译代码请先安装 VC 绘图库(V20091123)，项目中有下载
// 最后修改日期: 2010-3-14
//
#include<stdio.h> 
#include<conio.h> 
#include<graphics.h> 
#include<stdlib.h> 
#include<math.h> 
#include <time.h>

/*********************/ 

#define RandRandRand(x) (rand()%(x-1)+(rand()%10000)*1.e-4+(rand()%10000)*1.e-8) 
#define L_MAX 240 

void main() 
{ 
	int i1=7,color=0,interval,width,dots=0,fc2,ci2,bc=0,colour[12]={RED,LIGHTRED,BROWN,YELLOW,LIGHTGREEN,GREEN,LIGHTCYAN,CYAN,BLUE,LIGHTBLUE,MAGENTA,LIGHTMAGENTA}; 
	double x,y,cenx,ceny,pcd=0,pca=0,bpcd=0,incofd,incofa,spdofsp,n,spdofgwth,fs0,rdir; 
	
	
	
	initgraph(640, 480); 
	
	srand(time(NULL));
	
	
	cenx=getwidth()/2; 
	ceny=getheight()/2; 
	fc2=30; 
	width=3; 
	bc=0; 
	incofd=0.1; 
	incofa=-8; 
	spdofgwth=15; 
	spdofsp=-1.3; 
	interval=100; 
	
	
	
	
	
	setbkcolor(bc); 
	setlinestyle(0,0,width); 
	
	rdir=RandRandRand(360); 
	
grow: 
	for(n=0;!kbhit();n+=spdofsp) 
	{
		while(n>360) 
			n-=360; 
		
		bpcd+=spdofgwth; 
		if(bpcd>L_MAX) goto decrease; 
		
		
		moveto(cenx,ceny); 
		pcd=0;pca=0; 
		ci2=0; 
		while(pcd<bpcd) 
		{ 
			if(ci2<fc2) 
				ci2++; 
			else
			{ 
				if(color<12) 
				{ 
					setcolor(colour[color]); 
					color++; 
				} 
				else
				{ 
					color=1; 
					setcolor(colour[0]); 
				} 
				ci2=1; 
			} 
			x=(pcd+=incofd)*cos((pca+=incofa)+n); 
			y=pcd*sin(pca+n); 
			lineto(x+cenx,ceny-y); 
			
			
		} 
		fs0=0.000199186*bpcd*bpcd+0.0303256*bpcd+4.96948; 
		cenx=cenx+fs0*cos(rdir); 
		ceny=ceny+fs0*sin(rdir); 
		
		
		
		if(cenx<=-40)
		{
			if(ceny<=-40) 
				rdir=RandRandRand(90)+270; 
			else if(ceny>=520) 
				rdir=RandRandRand(90); 
			else
				rdir=RandRandRand(180)-90; 
		}
		else if(cenx>=680)
		{
			if(ceny<=-40) 
				rdir=RandRandRand(90)+180; 
			else if(ceny>=520) 
				rdir=RandRandRand(90)+90; 
			else
				rdir=RandRandRand(180)+90;
		}
		else if(ceny<=-40) 
			rdir=RandRandRand(180)+180; 
		else if(ceny>=520) 
			rdir=RandRandRand(180); 
		
		EndBatchDraw();

		Sleep(interval); 
		
		BeginBatchDraw();

		clearviewport(); 
	} 
	exit(0); 
	
decrease: 
	
	for(n=0;!kbhit();n+=spdofsp) 
	{
		while(n>360) 
			n-=360; 
		
		if(bpcd<=0) 
			goto grow; 
		else bpcd-=spdofgwth; 
		
		moveto(cenx,ceny); 
		pcd=0;pca=0; 
		ci2=0; 
		while(pcd<bpcd) 
		{
			if(ci2<fc2) 
				ci2++; 
			else
			{ 
				if(color<12) 
				{ 
					setcolor(colour[color]); 
					color++; 
				} 
				else
				{ 
					color=1; 
					setcolor(colour[0]); 
				} 
				ci2=1; 
			} 
			x=(pcd+=incofd)*cos((pca+=incofa)+n); 
			y=pcd*sin(pca+n); 
			lineto(x+cenx,ceny-y); 
			
			
		} 
		
		fs0=0.000199186*bpcd*bpcd+0.0303256*bpcd+4.96948; 
		cenx=cenx+fs0*cos(rdir); 
		ceny=ceny+fs0*sin(rdir); 
		
		
		
		if(cenx<=-40)
		{
			if(ceny<=-40) 
				rdir=RandRandRand(90)+270; 
			else if(ceny>=520) 
				rdir=RandRandRand(90); 
			else
				rdir=RandRandRand(180)-90;
		}
		else if(cenx>=680)
		{
			if(ceny<=-40) 
				rdir=RandRandRand(90)+180; 
			else if(ceny>=520) 
				rdir=RandRandRand(90)+90; 
			else
				rdir=RandRandRand(180)+90; 
		}
		else if(ceny<=-40) 
			rdir=RandRandRand(180)+180; 
		else if(ceny>=520) 
			rdir=RandRandRand(180); 
		
		EndBatchDraw();

		Sleep(interval); 
		
		BeginBatchDraw();
		
		clearviewport(); 
	} 
	closegraph(); 
}
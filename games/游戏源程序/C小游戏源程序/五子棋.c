#include "graphics.h"  /*ͼ��ϵͳͷ�ļ�*/
#define LEFT 0x4b00  /*������ֵ*/
#define RIGHT 0x4d00 /*����Ҽ�ֵ*/
#define DOWN 0x5000 /*����¼�ֵ*/
#define UP 0x4800 /*����ϼ�ֵ*/
#define ESC 0x011b /* ESC��ֵ*/
#define ENTER 0x1c0d /* �س���ֵ*/
int a[8][8]={0},key,score1,score2;/*��������Լ������������ӵı���*/
char playone[3],playtwo[3];/*�����˵ĵ÷�ת�����ַ������*/
void playtoplay(void);/*���˶�ս����*/
void DrawQp(void);/*�����̺���*/
void SetPlayColor(int x);/*�������ӵ�һ�ε���ɫ*/
void MoveColor(int x,int y);/*�ָ�ԭ������״̬*/
int QpChange(int x,int y,int z);/*�ж����̵ı仯*/
void DoScore(void);/*�������*/
void PrintScore(int n);/*����ɼ�*/
void playWin(void);/*���ʤ������Ϣ*/
/******������*********/
void main(void)
{
   int gd=DETECT,gr;
   initgraph(&gd,&gr,"c:\\tc"); /*��ʼ��ͼ��ϵͳ*/
   DrawQp();/*������*/
   playtoplay();/*���˶�ս*/
   getch();
   closegraph();/*�ر�ͼ��ϵͳ*/
}
void DrawQp()/*������*/
{
   int i,j;
   score1=score2=0;/*����һ��ʼ�÷ֶ�Ϊ0*/
   setbkcolor(BLUE);
   for(i=100;i<=420;i+=40)
   {
      line(100,i,420,i);/*��ˮƽ��*/
      line(i,100,i,420); /*����ֱ��*/
   }
   setcolor(0);/*ȡ��Բ��Χ��һȦ����*/
   setfillstyle(SOLID_FILL,15);/*��ɫʵ�����ģʽ*/
   fillellipse(500,200,15,15); /*����ʾ�÷ֵ�λ�û���*/
   setfillstyle(SOLID_FILL,8); /*��ɫʵ�����ģʽ*/
   fillellipse(500,300,15,15);
   a[3][3]=a[4][4]=1;/*��ʼ��������*/
   a[3][4]=a[4][3]=2;/*��ʼ��������*/
   setfillstyle(SOLID_FILL,WHITE);
   fillellipse(120+3*40,120+3*40,15,15);
   fillellipse(120+4*40,120+4*40,15,15);
   setfillstyle(SOLID_FILL,8);
   fillellipse(120+3*40,120+4*40,15,15);
   fillellipse(120+4*40,120+3*40,15,15);
   score1=score2=2; /*�����ı����*/
   DoScore();/*�����ʼ����*/
}
void playtoplay()/*���˶�ս*/
{
   int x,y,t=1,i,j,cc=0;
   while(1)/*����������*/
   {
      x=120,y=80;/*ÿ������һ��ʼ����������,xΪ������,yΪ������*/
      while(1) /*����һ����������Ĺ���*/
      {
  PrintScore(1);/*�������1�ĳɼ�*/
  PrintScore(2);/*�������2�ĳɼ�*/
  SetPlayColor(t);/*t�����������ж�������ִ���ӵ���ɫ*/
  fillellipse(x,y,15,15);
  key=bioskey(0);/*���հ���*/
  if(key==ESC)/*������Ϸ*/
     break;
  else
  if(key==ENTER)/*�������ȷ���Ϳ�������ѭ��*/
  {
     if(y!=80&&a[(x-120)/40][(y-120)/40]!=1
&&a[(x-120)/40][(y-120)/40]!=2)/*�������λ��û������*/
     {
        if(t%2==1)/*���������1�ƶ�*/
    a[(x-120)/40][(y-120)/40]=1;
        else/*��������2�ƶ�*/
    a[(x-120)/40][(y-120)/40]=2;
     if(!QpChange(x,y,t))/*���Ӻ��ж����̵ı仯*/
     {
        a[(x-120)/40][(y-120)/40]=0;/*�ָ��ո�״̬*/
        cc++;/*��ʼͳ�Ƴ��Դ���*/
        if(cc>=64-score1-score2) /*������Գ����ո�����ͣ��*/
        {
    MoveColor(x,y);
    fillellipse(x,y,15,15);
    break;
        }
        else
    continue;/*���������Ч*/
     }
     DoScore();/*�����ĸı�*/
     break;/*���̱仯�ˣ����ֶԷ�����*/
  }
  else/*�Ѿ������Ӿͼ�������*/
     continue;
      }
      else /*�ĸ����򰴼����ж�*/
  if(key==LEFT&&x>120)/*�����*/
  {
     MoveColor(x,y);
     fillellipse(x,y,15,15);
     SetPlayColor(t);
     x-=40;
     fillellipse(x,y,15,15);
  }
      else
  if(key==RIGHT&&x<400&&y>80)/*�ҷ����*/
  {
     MoveColor(x,y);
     fillellipse(x,y,15,15);
     SetPlayColor(t);
     x+=40;
     fillellipse(x,y,15,15);
  }
      else
  if(key==UP&&y>120)/*�Ϸ����*/
  {
     MoveColor(x,y);
     fillellipse(x,y,15,15);
     SetPlayColor(t);
     y-=40;
     fillellipse(x,y,15,15);
  }
      else
  if(key==DOWN&&y<400)/*�·����*/
  {
     MoveColor(x,y);
     fillellipse(x,y,15,15);
     SetPlayColor(t);
     y+=40;
     fillellipse(x,y,15,15);
  }
      }
      if(key==ESC)/*������Ϸ*/
  break;
      if((score1+score2)==64||score1==0||score2==0)/*�����Ѿ�ռ����һ������Ϊ0�ж�ʤ��*/
      {
  playWin();/*��������*/
  break;
      }
      t=t%2+1; /*һ���ߺ󣬸ı�������ɫ���ֶԷ���*/
      cc=0;  /*����ֵ�ָ�Ϊ0*/
   } /*endwhile*/
}
void SetPlayColor(int t)/*����������ɫ*/
{
   if(t%2==1)
      setfillstyle(SOLID_FILL,15);/*��ɫ*/
   else
      setfillstyle(SOLID_FILL,8);/*��ɫ*/
}
void MoveColor(int x,int y)/*����һ����ָ�ԭ�����ӵ�״̬*/
{
   if(y<100)/*����Ǵ��������ͻָ���ɫ*/
      setfillstyle(SOLID_FILL,BLUE);
   else/*������������1�ͻָ���ɫ����,2�ָ���ɫ����,��ָ���ɫ����*/
      switch(a[(x-120)/40][(y-120)/40])
      {
  case 1:
      setfillstyle(SOLID_FILL,15);break; /*��ɫ*/
  case 2:
      setfillstyle(SOLID_FILL,8);break; /*��ɫ*/
  default:
     setfillstyle(SOLID_FILL,BLUE); /*��ɫ*/
      }
}
int QpChange(int x,int y,int t)/*�ж����̵ı仯*/
{
   int i,j,k,kk,ii,jj,yes;
   yes=0;
   i=(x-120)/40; /*��������Ԫ�ص����±�*/
   j=(y-120)/40; /*��������Ԫ�ص����±�*/
   SetPlayColor(t);/*�������ӱ仯����ɫ*/
   /*��ʼ��8�������жϱ仯*/
   if(j<6)/*���ұ�*/
   {
   for(k=j+1;k<8;k++)
      if(a[i][k]==a[i][j]||a[i][k]==0)/*�����Լ������ӻ�ո����*/
  break;
      if(a[i][k]!=0&&k<8)
      {
  for(kk=j+1;kk<k&&k<8;kk++)/*�ж��ұ�*/
  {
     a[i][kk]=a[i][j]; /*�ı�������ɫ*/
     fillellipse(120+i*40,120+kk*40,15,15);
  }
      if(kk!=j+1) /*���������������Ӹı����ɫ*/
  yes=1;
      }
   }
   if(j>1)/*�ж����*/
   {
      for(k=j-1;k>=0;k--)
  if(a[i][k]==a[i][j]||!a[i][k])
     break;
      if(a[i][k]!=0&&k>=0)
      {
  for(kk=j-1;kk>k&&k>=0;kk--)
  {
     a[i][kk]=a[i][j];
     fillellipse(120+i*40,120+kk*40,15,15);
  }
 if(kk!=j-1)
     yes=1;
      }
   }
   if(i<6)/*�ж��±�*/
   {
      for(k=i+1;k<8;k++)
  if(a[k][j]==a[i][j]||!a[k][j])
     break;
      if(a[k][j]!=0&&k<8)
      {
  for(kk=i+1;kk<k&&k<8;kk++)
  {
     a[kk][j]=a[i][j];
     fillellipse(120+kk*40,120+j*40,15,15);
  }
  if(kk!=i+1)
     yes=1;
      }
   }
   if(i>1)/*�ж��ϱ�*/
   {
      for(k=i-1;k>=0;k--)
  if(a[k][j]==a[i][j]||!a[k][j])
     break;
      if(a[k][j]!=0&&k>=0)
      {
  for(kk=i-1;kk>k&&k>=0;kk--)
  {
     a[kk][j]=a[i][j];
     fillellipse(120+kk*40,120+j*40,15,15);
  }
  if(kk!=i-1)
     yes=1;
      }
   }
   if(i>1&&j<6)/*����*/
   {
      for(k=i-1,kk=j+1;k>=0&&kk<8;k--,kk++)
  if(a[k][kk]==a[i][j]||!a[k][kk])
     break;
      if(a[k][kk]&&k>=0&&kk<8)
      {
  for(ii=i-1,jj=j+1;ii>k&&k>=0;ii--,jj++)
  {
     a[ii][jj]=a[i][j];
     fillellipse(120+ii*40,120+jj*40,15,15);
  }
      if(ii!=i-1)
  yes=1;
      }
   }
   if(i<6&&j>1)/*����*/
   {
      for(k=i+1,kk=j-1;k<8&&kk>=0;k++,kk--)
  if(a[k][kk]==a[i][j]||!a[k][kk])
     break;
      if(a[k][kk]!=0&&k<8&&kk>=0)
      {
  for(ii=i+1,jj=j-1;ii<k&&k<8;ii++,jj--)
  {
     a[ii][jj]=a[i][j];
     fillellipse(120+ii*40,120+jj*40,15,15);
  }
      if(ii!=i+1)
  yes=1;
      }
   }
   if(i>1&&j>1)/*����*/
   {
      for(k=i-1,kk=j-1;k>=0&&kk>=0;k--,kk--)
  if(a[k][kk]==a[i][j]||!a[k][kk])
     break;
      if(a[k][kk]!=0&&k>=0&&kk>=0)
      {
  for(ii=i-1,jj=j-1;ii>k&&k>=0;ii--,jj--)
  {
     a[ii][jj]=a[i][j];
     fillellipse(120+ii*40,120+jj*40,15,15);
  }
      if(ii!=i-1)
  yes=1;
      }
   }
   if(i<6&&j<6)/* ����*/
   {
      for(k=i+1,kk=j+1;kk<8&&kk<8;k++,kk++)
  if(a[k][kk]==a[i][j]||!a[k][kk])
     break;
      if(a[k][kk]!=0&&kk<8&&k<8)
      {
  for(ii=i+1,jj=j+1;ii<k&&k<8;ii++,jj++)
  {
     a[ii][jj]=a[i][j];
     fillellipse(120+ii*40,120+jj*40,15,15);
  }
      if(ii!=i+1)
  yes=1;
      }
   }
   return yes;/*�����Ƿ�ı��������ɫ�ı��*/
}
void DoScore()/*�������*/
{
   int i,j;
   score1=score2=0;/*���¿�ʼ�Ʒ���*/
   for(i=0;i<8;i++)
      for(j=0;j<8;j++)
  if(a[i][j]==1)/*�ֱ�ͳ�������˵ķ���*/
     score1++;
  else
     if(a[i][j]==2)
        score2++;
}
void PrintScore(int playnum)/*����ɼ�*/
{
   if(playnum==1)/*�����ǰ�ĳɼ�*/
   {
      setfillstyle(SOLID_FILL,BLUE);
      bar(550,100,640,400);
   }
   setcolor(RED);
   settextstyle(0,0,4);/*�����ı������ʽ*/
   if(playnum==1)/*�ж�����ĸ����ֵķ�,�ڲ�ͬ��λ�����*/
   {
      sprintf(playone,"%d",score1);
      outtextxy(550,200,playone);
   }
   else
   {
      sprintf(playtwo,"%d",score2);
      outtextxy(550,300,playtwo);
   }
   setcolor(0);
}
void playWin()/*�������ʤ���߽��*/
{
   settextstyle(0,0,4);
   setcolor(12);
   if(score2>score1)/*��ʼ�ж����Ľ��*/
      outtextxy(100,50,"black win!");
   else
      if(score2<score1)
  outtextxy(100,50,"white win!");
      else
  outtextxy(60,50,"you all win!");
} 
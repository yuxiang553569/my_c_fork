�����ұ��һ�����Ƴ�����ĸľ����ˡ�
 Nim��Ϸ��һ�����������кܶ�汾�ľ�����Ϸ�����ʤ������
���������߽����һ��ʯ����ȡ��������Ŀ����Ŀ�в����߾�������
��Ҫ�������ÿ������ȡ��һ��������һ�룬Ȼ������һ�������߼�
��ȡ���õ����һ��ʯ�����䡣�˺͵����漸���Ⱥ�,�����д������޴�ģʽ

���������

#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<cmath>

using namespace std;


/*��������*/
void rand_seed( )
{
int seed=static_cast<int>(time(0));
srand(seed);
}

/*���������*/
int rand_int(int a,int b) 
{
return a+rand( )%(b-a+1);
}

/*�������Ƿ�����*/
int checkwin1(int stoneNum)
{
int flag;
if(stoneNum==0)
{
   cout<<"Congelations!You win the game!\n";
   flag=0;
}

else 
{
   cout<<"It is your turn!Please input your taking stones: \n";
   flag=1;
}
return flag;
}

/*������Ƿ�����*/
int checkwin2(int stoneNum)
{
int flag;
if(stoneNum==0)
{
   cout<<"Sorry!You lost the game!\n";
   flag=0;
}
else 
{
   cout<<"It is computer's turn! \n";
   flag=1;
}
return flag;
}


/*������*/
int main( )
{
int i,j,s,flag;
int stoneNum;
int order,take,pattern,compTake,peoTake;
cout<<"********************** Welcom To Use ************************\n";
cout<<"===================== The Game Of Nim =======================\n";
cout<<"\n";
cout<<"     Nim��Ϸ��һ�����������кܶ�汾�ľ�����Ϸ�����ʤ������\n";
cout<<"���������߽����һ��ʯ����ȡ��������Ŀ����Ŀ�в����߾�������\n";
cout<<"��Ҫ�������ÿ������ȡ��һ��������һ�룬Ȼ������һ�������߼�\n";
cout<<"��ȡ���õ����һ��ʯ�����䡣\n";
cout<<"\n";
cout<<"============================================================\n";
cout<<"===============================================sunjing024����=====\n";
rand_seed( );
stoneNum=rand_int(10,100);
cout<<"There are total "<<stoneNum<<" stones!\n";
order=rand_int(0,1);
pattern=rand_int(0,1);
if(order==0&&pattern==0)          s=0;
else if(order==0&&pattern==1)     s=1;
else if(order==1&&pattern==0)     s=2;
else if(order==1&&pattern==1)     s=3;
switch(s)
{
case 0:
   cout<<"Computer takes first and he choose clever pattern!\n";
   for(i=1;stoneNum!=0&&i<60&&flag!=0;i++)
   {

    for(j=1;j<=7&&take<=stoneNum/2;j++)
    {
     if(stoneNum==pow(2,j)-1)
     flag=1;
    }
    if(stoneNum==1)
    {
     stoneNum=0;
     compTake=1;
    }
    else if(flag==1)
    {
     compTake=rand_int(1,stoneNum/2);
     cout<<"Computer takes "<<compTake<<" stones!\n";
     stoneNum=stoneNum-compTake;
     cout<<"There are "<<stoneNum<<" stones left!\n";
    }

    else 
    {
     for(take=1;take<=stoneNum/2;take++)
     {
      for(j=1;j<=7;j++)
      {
       if(stoneNum-take==pow(2,j)-1&&take<=stoneNum/2)
       {
   
        cout<<"Computer takes "<<take<<" stones!\n";
        stoneNum=stoneNum-take;
        cout<<"There are "<<stoneNum<<" stones left!\n";
        goto loop;
       }
      } 
     }
    }
loop: compTake=take;


    flag=checkwin1(stoneNum);
    cin>>peoTake;
    cout<<"You take "<<peoTake<<" stones!\n";
    stoneNum=stoneNum-peoTake;
    cout<<"There are "<<stoneNum<<" stones left!\n";
    flag=checkwin2(stoneNum);
   }
   break;
    case 1:
   cout<<"Computer takes first and he choose stupy pattern!\n";
   for(i=1;stoneNum!=0&&i<60&&flag!=0;i++)
   {
    if(stoneNum==1)
    {
     cout<<"computer takes 1 stones!\n";
     stoneNum=0;
    }
    else
    {
     compTake=rand_int(1,stoneNum/2);
     cout<<"Computer takes "<<compTake<<" stones!\n";
     stoneNum=stoneNum-compTake;
     cout<<"There are "<<stoneNum<<" stones left!\n";
    }
    flag=checkwin1(stoneNum);
    cin>>peoTake;
    cout<<"You take "<<peoTake<<"stones!\n";
    stoneNum=stoneNum-peoTake;
    cout<<"There are "<<stoneNum<<"stones left!\n";
    flag=checkwin2(stoneNum);
   }
   break;
case 2:
   cout<<"You takes first and computer choose clever pattern!\n";
   for(i=1;stoneNum!=0&&i<60&&flag!=0;i++)
   {
    cout<<"Please input your taking stones: \n";
    cin>>peoTake;
    cout<<"You take "<<peoTake<<" stones!\n";
    stoneNum=stoneNum-peoTake;
    cout<<"There are "<<stoneNum<<" stones left!\n";
    flag=checkwin2(stoneNum);
        

    for(j=1;j<=7&&take<=stoneNum/2;j++)
    {
     if(stoneNum==pow(2,j)-1)
     flag=1;
    }
    if(stoneNum==1)
    {
     stoneNum=0;
     compTake=1;
    }
    else if(flag==1)
    {
     compTake=rand_int(1,stoneNum/2);
     cout<<"Computer takes "<<compTake<<" stones!\n";
     stoneNum=stoneNum-compTake;
     cout<<"There are "<<stoneNum<<" stones left!\n";
    }

    else 
    {
     for(take=1;take<=stoneNum/2;take++)
     {
      for(j=1;j<=7;j++)
      {
       if(stoneNum-take==pow(2,j)-1&&take<=stoneNum/2)
       {
   
        cout<<"Computer takes "<<take<<" stones!\n";
        stoneNum=stoneNum-take;
        cout<<"There are "<<stoneNum<<" stones left!\n";
        goto loop1;
       }
      } 
     }
    }
loop1: compTake=take;


    flag=checkwin1(stoneNum);
   }
   break;
case 3:
   cout<<"You takes first and computer choose stupy pattern!\n";
   for(i=1;stoneNum!=0&&i<60&&flag!=0;i++)
   {
    cout<<"Please input your taking stones: \n";
    cin>>peoTake;
    cout<<"You take "<<peoTake<<" stones!\n";
    stoneNum=stoneNum-peoTake;
    cout<<"There are "<<stoneNum<<" stones left!\n";
    flag=checkwin2(stoneNum);
    if(stoneNum==1)
    {
     cout<<"computer takes 1 stones!\n";
     stoneNum=0;
    }
    else
    {
     compTake=rand_int(1,stoneNum/2);
     cout<<"Computer takes "<<compTake<<" stones!\n";
     stoneNum=stoneNum-compTake;
     cout<<"There are "<<stoneNum<<" stones left!\n";
    }
   
    flag=checkwin1(stoneNum);
   }
   break;
}
cout<<"The end!Welcome to use again!\n";

return 0;
} 
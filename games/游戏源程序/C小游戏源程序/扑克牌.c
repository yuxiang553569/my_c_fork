#include "stdio.h"
#include "stdlib.h"
#include "time.h"
main()
{int n,i,b,c,a[15];
 a[0]=a[1]=1;
 for(i=2,i<15,i++)
  a[i]=a[i-1]+a[i-2];
 do
 {srand((unsigned)time(NULL));
  n=rand()%(2000-1+1)+1;
 }
 printf("There are %d apples!\n Please choose 1 or 2.\n1:man first! \n2:compuer first!\n")
 scanf("%d",&b);
if(b==1)
{printf("You can take 1 to %d aplles!!Please input your apple:",n-1)
 do
 {scanf("%d",&c);
  if(c>=n||c<1);
  printf("You can't take %d apples!Please take the apple again:",c)
 }
   
 }
源程序2：#include"stdio.h"
 #include"stdlib.h"
 #include"time.h"
 main()
 {
  int a,b,x,i,n,m,f[14];
  f[0]=f[1]=1;
  for(i=2;i<14;i++)
  f[i]=f[i-1]+f[i-2];
  do
   {srand(time(NULL));
    n=rand()%100;
   }while(n==0);
   printf("There is %d apples.\n",n);
   printf("Input you want apples:");
   do
   {scanf("%d",&a);
    if(a<=0||a>=n)
    printf(" \nerror!\nTry    again!\nInput you want apples:");
   }while(a<=0||a>=n);
    n=n-a;
    while(n>0)
    {
     {if(n<=2*a) {printf("Computer get %d apple!\nComputer Win! ",n);}}
     if(n>2*a)
      m=n;
      for(i=12;i>=0;i--)
       {
       if(f[i]<=m) m=m-f[i];
       if(m==0){b=f[i];return n;}
       }
   printf("The computer take %d apples",b);
   n=n-b;
   if(n<=0) { printf("GAME OVER!\nComputer Win!");}
   if(n>0)
 {
 do
  {scanf("%d",&x);
   if(x<1||x>(b*2))
   printf("Try again!Input apples:");
  }while(x<1||x>(b*2));
  n=n-x;
  if(n<=0) printf("\nWIN!\n");
      }
}
}

源程序3：

main()
{int i, j, a[40],x,y,m,n,f,d;
a[0]=a[1]=1;
for(i=2;i<40;i++)
{
a[i] = a[i-1]+a[i-2];
}
printf("the num of apple is\n ");
scanf("%d",&x);
printf("you want to choose \n:");
scanf("%d",&y);
m=x-y;
 if(m<=2*y)
{printf("the com choose is %d\n",x-y);
printf("the com is the winner :");
printf("the game is over" );}
if(m>2*y)
{for(j=0;j<20;j++)
if(m>=a[j]&&m<=a[j+1])
{n=m-a[j]; }
if(n>2*y)
n=1;
if(n==0)
 n++;
printf("com choose %d",n);
printf("the rest apple is %d",d=x-y-n) ;
do {
f=fun( d);
d=d-f;}
while(d>0);
printf("the game is over ");}}

fun(int d)
{ int a[40], i,b,c,e;
auto int f;
a[0]=a[1]=1;
for(i=2;i<40;i++)
{a[i]=a[i-1]+a[i-2];}
printf("it turn you to choose :");
scanf("%d",&b) ;
c=d-b;
if(c>0&&c<=2*b)
{printf("the com choose %d",c);
printf("the com is winner ");
 return c+b;}
if(c==0)
{printf("you are the winner ");
return  b;}
if(c>2*b)
{for(i=0;i<20;i++)
if(c>=a[i]&&c<a[i+1])
{e=c-a[i]; }
if(e>2*b)
e=1;
if(e==0)
e++;
printf("the com choose :%d",e) ;
printf("the rest apple is %d\n",d-b-e);
f=b+e;
return  f;}  } 
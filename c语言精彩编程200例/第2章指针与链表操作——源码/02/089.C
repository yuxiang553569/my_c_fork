#include "stdafx.h"
#include <stdio.h>
#include <conio.h>

void main()
{
	int a[3][4]={1,2,3,4,5,6,7,8,9,10,11,12};				/*声明数组*/
	printf("%d,%d\n",a,*a);								/*输出第0行首地址和0行0类元素地址*/
	printf("%d,%d\n",a[0],*(a+0));						/*输出0行0列地址*/
	printf("%d,%d\n",&a[0],&a[0][0]);					/*0行首地址和0行0列地址*/
	printf("%d,%d\n",a[1],a+1);							/*输出1行0列地址和1行首地址*/
	printf("%d,%d\n",&a[1][0],*(a+1)+0);					/*输出1行0列地址*/
	printf("%d,%d\n",a[1][1],*(*(a+1)+1));					/*输出1行1列元素值*/
	getch();
}
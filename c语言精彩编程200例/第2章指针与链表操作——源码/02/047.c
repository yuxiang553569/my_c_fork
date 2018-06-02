#include "stdafx.h"
#include "stdio.h"
int main()
{
    int *p,a[10],i;
	p=&a[0];
	printf("请输入10个数字:\n");
	for(i=0;i<10;i++)
		scanf("%d",&a[i]);						/*为数组a中的元素赋初值*/
				
	printf("数组中的元素为:\n");
	for(i=0;i<10;i++)
		printf("%d",*(p+i)); 						/*输出数组a中的元素*/
	printf("\n");

}


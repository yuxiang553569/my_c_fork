#include "stdafx.h"
#include "stdio.h"
int main()
{
    int *p,a[10],i;
	p=&a[0];
	printf("������10������:\n");
	for(i=0;i<10;i++)
		scanf("%d",&a[i]);						/*Ϊ����a�е�Ԫ�ظ���ֵ*/
				
	printf("�����е�Ԫ��Ϊ:\n");
	for(i=0;i<10;i++)
		printf("%d",*(p+i)); 						/*�������a�е�Ԫ��*/
	printf("\n");

}


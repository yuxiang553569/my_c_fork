#include "stdafx.h"
#include<stdio.h>
int main()
{
	char *strings[]={"��XX",
				"ǮXX",
				"��XX",
				"��XX",
				"��XX"};			/*ʹ��ָ�����鴴���ַ�������*/
	char **p,i;							/*��������*/
	p=strings;
	printf("%s\n",strings[0]);							/*ָ��ָ���ַ��������׵�ַ*/
	for(i=0;i<5;i++)						/*ѭ������ַ���*/
	{
		printf("%s\n",*(p+i));
	}
	return 0;
}


#include "stdafx.h"
#include <stdio.h>
#define N 20

char * MyStrcat(char *dstStr,char *srcStr)        //����һ������ָ��ָ�ĺ�����ǰ���һ��*
{
    char *pStr = dstStr;        //�����ַ����׵�ַָ��
    while(*dstStr != '\0')        //��ָ���Ƶ��ַ���β
    {
        dstStr++;
    }

    for(;*srcStr!='\0';dstStr++,srcStr++)        //���ַ���2�Ƶ�1����
    {
        *dstStr = *srcStr;
    }
    *dstStr = '\0';
    return pStr;        //�������Ӻ���ַ���
}

int main()
{
    char first[2*N];
    char second[N];
    char *result = NULL;
    printf("�����һ�飺");
    gets(first);
    printf("����ڶ��飺");
    gets(second);
    result = MyStrcat(first,second);
    printf("�����%s\n",result);
    return 0;
}
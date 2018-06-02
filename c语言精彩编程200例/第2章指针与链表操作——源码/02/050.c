#include "stdafx.h"
#include <stdio.h>
#define N 20

char * MyStrcat(char *dstStr,char *srcStr)        //声明一个返回指针指的函数，前面多一个*
{
    char *pStr = dstStr;        //保存字符串首地址指针
    while(*dstStr != '\0')        //将指针移到字符串尾
    {
        dstStr++;
    }

    for(;*srcStr!='\0';dstStr++,srcStr++)        //将字符串2移到1后面
    {
        *dstStr = *srcStr;
    }
    *dstStr = '\0';
    return pStr;        //返回连接后的字符串
}

int main()
{
    char first[2*N];
    char second[N];
    char *result = NULL;
    printf("输入第一组：");
    gets(first);
    printf("输入第二组：");
    gets(second);
    result = MyStrcat(first,second);
    printf("结果：%s\n",result);
    return 0;
}
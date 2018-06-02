/* The first C programme */
#include <stdio.h>				/* 包含标准输入输出头文件 */
void main()						/* 主函数 */
{
	int i,*pi,*pj,j;
	i = 5;
	//*pi = i;
	pi = &i;
	printf("%d\n",*pi);
	printf("%d\n",pi);
	printf("Hello World!\n");	/* 打印输出信息 */
}

/* The first C programme */
#include <stdio.h>				/* ������׼�������ͷ�ļ� */
void main()						/* ������ */
{
	int i,*pi,*pj,j;
	i = 5;
	//*pi = i;
	pi = &i;
	printf("%d\n",*pi);
	printf("%d\n",pi);
	printf("Hello World!\n");	/* ��ӡ�����Ϣ */
}

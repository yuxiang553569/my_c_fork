// ����ĸ����Ϸ
// ����������Ȱ�װ VC ��ͼ��(V20091123)�������������أ�http://tieba.baidu.com/f?kz=730592608
// ����޸�����: 2010-3-28
//
#include <graphics.h>
#include <conio.h>
#include <time.h>

// ��ӭ����
void welcome()
{
	// �����Ļ��ʾ
	cleardevice();
	setcolor(YELLOW);
	setfont(64, 0, "����");
	outtextxy(200, 50, "������Ϸ");
	setcolor(WHITE);
	setfont(16, 0, "����");
	outtextxy(100, 200, "���Ǻܴ�ͳ���Ǹ�����ĸȻ����Ӧ������ʧ����Ϸ");
	outtextxy(100, 240, "ֻ�Ǹ���ѧ����һ����ʾ");
	outtextxy(100, 280, "���ܲ��������ƣ������������������ȶ�û��д");
	outtextxy(100, 320, "����Ȥ���Լ��ӽ�ȥ��");

	// ʵ����˸�ġ��������������
	int c=255;
	while(!kbhit())
	{
		setcolor(RGB(c, 0, 0));
		outtextxy(280, 400, "�����������");
		c-=8;
		if (c<0) c=255;
		Sleep(20);
	}
	getch();
	cleardevice();
}

// �˳�����
void goodbye()
{
	cleardevice();
	setcolor(YELLOW);
	setfont(48, 0, "����");
	outtextxy(104, 200, "��д���򡡲����ഺ");
	getch();
}

// ������
void main()
{
	// ��ʼ����ĻΪ 640x480
	initgraph(640, 480);

	welcome();	// ��ʾ��ӭ����

	srand(time(NULL));			// �����������
	setfont(16, 0, "Arial");	// ������ĸ������ʹ�С
	char target[2] = " ";		// ������ĸ�ַ���
	char key;					// �����û���������

	// ��ѭ��
	while(true)
	{
		target[0] = 65 + rand() % 26;	// ���������д��ĸ
		int x = rand()%630;
		for (int y=0; y<460; y++)
		{
			setcolor(WHITE);			// ������ĸ����ɫ
			outtextxy(x, y, target);	// ��ʾ��ĸ

			if(kbhit())
			{
				key = getch();
				if((key == target[0]) || (key == target[0] + 32))
				{
					// �������
					setcolor(BLACK);
					outtextxy(x, y, target);	// ���ԭ�ַ�
					break;						// ����ѭ����������һ���ַ�
				}
				else if (key == 27)
				{
					goto EXIT;					// ����� ESC���˳���Ϸ��ѭ��
				}
			}

			// ��ʱ�������ԭ�ַ�
			Sleep(10);
			setcolor(BLACK);
			outtextxy(x, y, target);
		}
	}

EXIT:
	// �˳�����
	goodbye();

	// �ر�ͼ�ν���
	closegraph();
}
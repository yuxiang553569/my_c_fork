// 打字母的游戏
// 编译代码请先安装 VC 绘图库(V20091123)，贴吧里有下载：http://tieba.baidu.com/f?kz=730592608
// 最后修改日期: 2010-3-28
//
#include <graphics.h>
#include <conio.h>
#include <time.h>

// 欢迎界面
void welcome()
{
	// 输出屏幕提示
	cleardevice();
	setcolor(YELLOW);
	setfont(64, 0, "黑体");
	outtextxy(200, 50, "打字游戏");
	setcolor(WHITE);
	setfont(16, 0, "宋体");
	outtextxy(100, 200, "就是很传统的那个掉字母然后按相应键就消失的游戏");
	outtextxy(100, 240, "只是给初学者做一个演示");
	outtextxy(100, 280, "功能并不很完善，比如生命数、分数等都没有写");
	outtextxy(100, 320, "感兴趣的自己加进去吧");

	// 实现闪烁的“按任意键继续”
	int c=255;
	while(!kbhit())
	{
		setcolor(RGB(c, 0, 0));
		outtextxy(280, 400, "按任意键继续");
		c-=8;
		if (c<0) c=255;
		Sleep(20);
	}
	getch();
	cleardevice();
}

// 退出界面
void goodbye()
{
	cleardevice();
	setcolor(YELLOW);
	setfont(48, 0, "黑体");
	outtextxy(104, 200, "多写程序　不老青春");
	getch();
}

// 主函数
void main()
{
	// 初始化屏幕为 640x480
	initgraph(640, 480);

	welcome();	// 显示欢迎界面

	srand(time(NULL));			// 设置随机种子
	setfont(16, 0, "Arial");	// 设置字母的字体和大小
	char target[2] = " ";		// 定义字母字符串
	char key;					// 定义用户按键变量

	// 主循环
	while(true)
	{
		target[0] = 65 + rand() % 26;	// 产生任意大写字母
		int x = rand()%630;
		for (int y=0; y<460; y++)
		{
			setcolor(WHITE);			// 设置字母的颜色
			outtextxy(x, y, target);	// 显示字母

			if(kbhit())
			{
				key = getch();
				if((key == target[0]) || (key == target[0] + 32))
				{
					// 设置清除
					setcolor(BLACK);
					outtextxy(x, y, target);	// 清除原字符
					break;						// 跳出循环，进行下一个字符
				}
				else if (key == 27)
				{
					goto EXIT;					// 如果按 ESC，退出游戏主循环
				}
			}

			// 延时，并清除原字符
			Sleep(10);
			setcolor(BLACK);
			outtextxy(x, y, target);
		}
	}

EXIT:
	// 退出部分
	goodbye();

	// 关闭图形界面
	closegraph();
}
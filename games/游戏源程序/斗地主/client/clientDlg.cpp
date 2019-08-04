// clientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "clientDlg.h"
#include "Loadbmp.h"

#include <mmsystem.h>
//*************STL***************//
#include <vector>
#include <string>
#include <list>
#include <algorithm>
using namespace std ;
typedef list<int> cardsList;
//**************STL**************//
cardsList mycards;		//自己手上的牌
cardsList sendcards;	//要打的牌
cardsList othercards;	//上家打的牌

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT thread(LPVOID);
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

SOCKET clisock;
sockaddr_in client;
int count,ee;

int		userNum = 0;
#define maxnum 20
user	userInf[maxnum];
puk		pukInf;
char	myname[20];
char    myPwd[20];

BOOL		ask;	//询问当不当地主，控制次数
BOOL		selected;//牌是否被选中
CRect		roomrect;//桌面尺寸
BOOL		show;	//第一次发牌
BOOL 		Right;
CString dir = "images/";
BOOL canhit = FALSE;//鼠标是否停在位置上
int tid		= 0;	//鼠标点的桌号(自己的桌子）
int sid		= 0;	//鼠标点的座位号（自己的座位号）
int prenum, nextnum;//上家和下家牌张数
int mynum;			//自己手中牌张数

int who;			//上家谁出的牌
int whonum;			//上家出的张数
int major;			//出牌权，用来表示，是否前两家都pass
int players;		//大厅玩家数量、
int pok[14][4]	;	//排序过的牌

#define login	1
#define sitdown 2
#define wait	3	//等待游戏开始
#define end		4	//回合结束
#define wrong	5	//登陆失败	
#define gaming	6	//游戏进行中

int hostsit ;		//地主的座位号	
int startsit;		//点开始了的人座位

int state;

CRect LeftRec, RightRec, DownRec, DeskRec;//无效区域

typedef struct Tmp
{
	BOOL selected;	//是否选中
	int  pk;		//牌点
} tmp;

tmp tmpinf[20];

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDlg dialog

CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientDlg)
	DDX_Control(pDX, IDC_cntinf, m_inf);
	DDX_Control(pDX, IDC_leavroom, m_qroom);
	DDX_Control(pDX, IDC_leavgame, m_qgame);
	DDX_Control(pDX, IDC_pass, m_pass);
	DDX_Control(pDX, IDC_playcard, m_playcard);
	DDX_Control(pDX, IDC_start, m_start);
	DDX_Control(pDX, IDC_ListMsg, m_msg);
	DDX_Control(pDX, IDC_StaticRoom, m_room);
	DDX_Control(pDX, IDC_StaticHi2, m_hi2);
	DDX_Control(pDX, IDC_StaticHi, m_hi);
	DDX_Control(pDX, IDC_ListPlayers, m_player);
	DDX_Control(pDX, IDC_PSD, m_staticPsd);
	DDX_Control(pDX, IDC_Name, m_staticName);
	DDX_Control(pDX, IDC_IP, m_staticIP);
	DDX_Control(pDX, IDC_EditPsd, m_psd);
	DDX_Control(pDX, IDC_BTExit, m_exit);
	DDX_Control(pDX, IDC_BTConnect, m_connect);
	DDX_Control(pDX, IDC_EditIP, m_ip);
	DDX_Control(pDX, IDC_EditName, m_name);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	//{{AFX_MSG_MAP(CClientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTConnect, OnBTConnect)
	ON_BN_CLICKED(IDC_BTExit, OnBTExit)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_start, Onstart)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_playcard, Onplaycard)
	ON_BN_CLICKED(IDC_pass, Onpass)
	ON_BN_CLICKED(IDC_leavgame, Onleavgame)
	ON_BN_CLICKED(IDC_leavroom, Onleavroom)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDlg message handlers
//-------------------------------------------------------------------------------
BOOL CClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}	

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	m_player.SetBkColor(RGB(40,111,149));
	m_player.SetTextBkColor(RGB(40,111,149));
	m_player.SetTextColor(RGB(250,250,15)); 	
	init();
	return TRUE;  // return TRUE  unless you set the focus to a control
}
//-------------------------------------------------------------------------------
void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
//-------------------------------------------------------------------------------
void CClientDlg::OnPaint() 
{
	CPaintDC dc(this);
	if (IsIconic())
	{
		//CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}	
	else
	{
		CDialog::OnPaint();
	}
	if(state==gaming)
	{
		m_qgame.EnableWindow(FALSE);
		m_qroom.EnableWindow(FALSE);
	}
	else
	{		
		m_qroom.EnableWindow(TRUE);
	}
	if(state==login)
	{
		m_qgame.EnableWindow(FALSE);
	}
	if(state==end||state==wait||state==sitdown)
	{
		m_qgame.EnableWindow(TRUE);
	}
	if(pukInf.cansend&&sendcards.size()!=0&&state==gaming)
	{
		m_playcard.EnableWindow(TRUE);
	}
	else
	{
		m_playcard.EnableWindow(FALSE);
	}
	if(pukInf.cansend&&state==gaming)
	{
		m_pass.EnableWindow(TRUE);
	}
	else
	{
		m_pass.EnableWindow(FALSE);
	}
	switch(state)
	{
	case wrong://还未登陆的时候
		{	
			drawface();
			break;
		}
	case login://登陆成功，显示大厅
		{
			display();
			break;
		}
	case sitdown://显示点击开始按钮
		{		
			showname();
			break;
		}
	case wait:
		{
			showcards();
			showstart();
			showname();
			break;
		}
	case gaming:
		{		
			showhead();
			playcards();
			showhost();
			showname();
			break;
		}
	default:
		{
			break;
		}
	}	
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//-------------------------------------------------------------------------------
void CClientDlg::OnBTConnect() 
{
	CClientDlg *dlg = (CClientDlg *) AfxGetApp()->GetMainWnd();
	char ipaddress[35];
	m_ip.GetWindowText(ipaddress,30);
	char name[20];
	dlg->m_name.GetWindowText(name, 20);
	char passWord[20];
	dlg->m_psd.GetWindowText(passWord,20);

	if(strlen(name)!=0)
	{	
	//***************隐藏控件*****************//
	dlg->m_ip.ShowWindow(SW_HIDE);
	dlg->m_name.ShowWindow(SW_HIDE);
	dlg->m_connect.ShowWindow(SW_HIDE);
	dlg->m_exit.ShowWindow(SW_HIDE);
	dlg->m_psd.ShowWindow(SW_HIDE);
	dlg->m_staticIP.ShowWindow(SW_HIDE);
	dlg->m_staticName.ShowWindow(SW_HIDE);
	dlg->m_staticPsd.ShowWindow(SW_HIDE);
	dlg->m_msg.ShowWindow(SW_HIDE);
	strcpy(myname, name);//记录自己的名字
	strcpy(myPwd, passWord); 
	dlg->EndModalState();
	//**************隐藏控件******************//
	}
	else
	{
		MessageBox("名字别忘了.....");
		return;
	}	
	client.sin_addr.s_addr=inet_addr(ipaddress);
	client.sin_family=AF_INET;
	client.sin_port=5000;
	//创建socket
	clisock=socket(AF_INET,SOCK_STREAM,0);	
	ee=1;
	dlg->SetForegroundWindow();
	Sleep(100);
	//启动线程
	AfxBeginThread(thread,0);		
}
//-------------------------------------------------------------------------------
UINT thread(LPVOID)
{
	char buff[100];
	char array[25][30]={"192.168.20.71",
						"211.83.152.71",
						"192.168.20.69",
						"192.168.20.26"};
	CSize size;
	size.cx=0;
	size.cy=30;
	int s=1,addcount=0;
	CClientDlg *dlg = (CClientDlg *) AfxGetApp()->GetMainWnd();		
	//连接服务器
	CTime time, time2;
	time = CTime::GetCurrentTime();
	int t1 = time.GetSecond();
	int t2;
	dlg->m_inf.SetWindowText("连接中....");		
	Sleep(50);
	s = connect(clisock,(sockaddr*)&(client),sizeof(client));
	t1 = time.GetSecond();	
	while(s == SOCKET_ERROR &&ee!=0)
	{		
		dlg->m_inf.SetWindowText("连接中-");
		Sleep(20);
		dlg->m_inf.SetWindowText("连接中--");
		Sleep(20);
		dlg->m_inf.SetWindowText("连接中---");
		Sleep(20);
		dlg->m_inf.SetWindowText("连接中----");
		Sleep(20);
		dlg->m_inf.SetWindowText("连接中-----");
		Sleep(20);
		time2 = CTime::GetCurrentTime();
       	t2 = time2.GetSecond();
		if(abs(t2-t1)/2>5)
		{
			dlg->m_inf.SetWindowText("连接超时，请重试……");
			dlg->reshow();
			return 0;
		}	
		client.sin_addr.s_addr=inet_addr(array[addcount++]);
	}	
	if (ee==1)
	{					
		char buf[100];			
		char name[20];
		char passWord[20];
		int  pwdLen = 0;
		int len = 0;
		int f	= 1;
		char a	= (char)f;
		strncpy(buf, &a,1);			
		dlg->m_name.GetWindowText(name,16);
		len = strlen(name);
		char ln = (char)len;
		strncpy(buf+1, &ln,1);
		strncpy(buf+2, name,len);
		dlg->m_pass.GetWindowText(passWord,16);
		pwdLen = strlen(myPwd);
		char cpwdLen;
		cpwdLen = char(pwdLen);
		strncpy(buf+2+len,&cpwdLen,1);
		strncpy(buf+2+len+1,myPwd,pwdLen);		
		send(clisock, buf, 100, 0);
	}
	dlg->m_hi.ShowWindow(SW_HIDE);
	dlg->m_hi2.ShowWindow(SW_HIDE);
	dlg->m_inf.ShowWindow(SW_HIDE);
	state = login;
	dlg->m_qroom.ShowWindow(SW_SHOW);
	dlg->m_qgame.ShowWindow(SW_SHOW);
	dlg->m_qgame.EnableWindow(FALSE);
	dlg->SetForegroundWindow();
	while(s!=SOCKET_ERROR && ee!=0)
	{		
		s=recv(clisock,buff,100,0);
		int flag = (int)(buff[0]);		//取出信息的类型				
		dlg->dealmsg(flag, buff);	    	
	}	
	closesocket(clisock);
	WSACleanup();
	dlg->destroy();
	AfxEndThread(0);
	return 0;
}
//-------------------------------------------------------------------------------
void CClientDlg::dealmsg(int flag, char *buffer)
{
	CClientDlg *dlg = (CClientDlg *) AfxGetApp()->GetMainWnd();	
	switch(flag)
	{
	case 1:
		{
			players++;
			dlg->writeRoom(buffer+1);			
			break;
		}		
	case 2: //当前单击的这个座位是否能坐
		{
			int cansit = (int)buffer[1];
			dlg->ContinueModal();
			if(cansit==1)
			{	
				state = sitdown;
				dlg->m_room.ShowWindow(SW_SHOW);
				m_start.ShowWindow(SW_SHOW);
				dlg->Invalidate();				
			}				
			else
			{
				MessageBox("该位置有人了，大哥");
			}
			break;
		}
	case 3: //接服务器发过来的牌
		{	
			mycards.clear();
			dlg->m_room.Invalidate();
			PostMessage(WM_PAINT, NULL, NULL);
			pukInf.ishost = ((puk*)(buffer+1))->ishost;
			memcpy(pukInf.hostname ,((puk*)(buffer+1))->hostname, sizeof(((puk*)(buffer+1))->hostname));
			pukInf.cansend	= ((puk*)(buffer+1))->cansend;
			memcpy(pukInf.puk, ((puk*)(buffer+1))->puk, sizeof(((puk*)(buffer+1))->puk));
			int myCards[21];		
			
			for(int numb = 0; numb < 20;numb++)
			{
				myCards[numb] = (int)pukInf.puk[numb];
			}		
			dlg->ReSort(myCards,17);
	
			for(int c=17;c<20;c++)
			{
				tmpinf[c].selected = FALSE;
			}	
			show = TRUE;			
			state = wait;//游戏开始
			ask = TRUE;
			m_playcard.ShowWindow(SW_HIDE);
			m_pass.ShowWindow(SW_HIDE);
			dlg->m_room.Invalidate();		
			PostMessage(WM_PAINT,NULL, NULL);
			break;
		}
	case 4: //是否愿意当地主
		{	
			hostsit = (int)buffer[1];
			dealhost();			
			break;
		}
	case 5: //上家出的牌。
		{
			othercards.clear();//先将上次清空			
			m_pass.ShowWindow(SW_SHOW);
			m_playcard.ShowWindow(SW_SHOW);			
			dealplay(buffer+1);
			PostMessage(WM_PAINT, NULL, NULL);
			break;
		}
	case 6: //回合结束，显示分数
		{
			int score = (int)buffer[1];
			pukInf.cansend = FALSE;
			pukInf.ishost  = FALSE;	
			CString res = "";
			CDC *pdc = GetDC();
			if(score < 0)
			{
				res.Format("呜呜~~，又丢了%d个铜板",-1*score);		
				pdc->SetTextColor(RGB(205,100,0));
				pdc->SetBkMode(TRANSPARENT);
				pdc->TextOut(250, 300, res);
				ReleaseDC(pdc);
			}
			else 
			{
				res.Format("哈哈，发财了，我赢了%d个铜板！",score);
				pdc->SetTextColor(RGB(205,100,0));
				pdc->SetBkMode(TRANSPARENT);
				pdc->TextOut(250, 300, res);
				ReleaseDC(pdc);	
			}
			startsit = 0;
			state = wait;
			dlg->m_start.ShowWindow(SW_SHOW);
			dlg->m_start.EnableWindow(TRUE);
			break;
		}
	case 7: //接受服务器发来的大厅信息并进行更新数据
		{
			dlg->updateRoom(buffer+1);
			dlg->showRoom();
			break;
		}
	case 8: // 接服务器发来的判断自己出的牌是否符合出牌规则
		{				
			dealsend(buffer+1);
			break;
		}
	case 9: //能否登陆 
		{
			int log = buffer[1];
			if(log==1)//登陆成功，读信息，贴图片
			{				
				dlg->showRoom();			
				state = login;				
				dlg->Invalidate();
			}
			else if(log == 2)
			{						
				state = wrong;						
				dlg->reshow();
				dlg->Invalidate();
				PostMessage(WM_PAINT, NULL, NULL);
				dlg->MessageBox("密码错误！", NULL, MB_OK);			
			}
			else if(log == 3)
			{				
				state = wrong;				
				dlg->reshow();	
				dlg->Invalidate();
				PostMessage(WM_PAINT, NULL, NULL);
				dlg->MessageBox("你还没有注册呢",NULL,MB_OK);
			}

			break;
		}
	case 10: //有人点开始了，buffer[1]是座位号
		{
			state = wait;
			startsit = (int)buffer[1];
			break;
		}
	case 11://有人当地主了，buffer[1]  是座位号
		{
			state = gaming;
			hostsit=(int)buffer[1];
			//地主的牌多显示三张
			if(hostsit!=sid)//自己不是地主的时候
			{
				decidehost(hostsit);
			}
			break;
		}
		case 12://更新分数信息
		{			
			int ID = ((fenshu*)(buffer+1))->id;
			int Fen = ((fenshu*)(buffer+1))->fen;
			userInf[ID].scores = Fen;			
		}
	default:
		{
			break;
		}
	}
}
//---------------------------------------------------------------------------------------
//读写大厅信息
void CClientDlg::writeRoom(char *buffer)
{
	CClientDlg *dlg = (CClientDlg *) AfxGetApp()->GetMainWnd();	
	int id = ((user*)(buffer))->userID;
	userInf[id].userID	= ((user*)(buffer))->userID;
	userInf[id].tableID = ((user*)(buffer))->tableID;
	userInf[id].sitID	= ((user*)(buffer))->sitID;
	userInf[id].scores	= ((user*)(buffer))->scores;
	userInf[id].Ishost	= ((user*)(buffer))->Ishost;
	memcpy(userInf[id].userName, ((user*)(buffer))->userName, 20);	
}
//---------------------------------------------------------------------------------------
//大厅画面
void CClientDlg::display()
{
	CClientDlg *dlg = (CClientDlg *) AfxGetApp()->GetMainWnd();
	CDC *pdc;
	pdc = GetDC();
	dlg->m_player.ShowWindow(SW_SHOW);
	dlg->m_msg.ShowWindow(SW_SHOW);
	SelectObject(BackDC,tablemap);
	SelectObject(HeadDC, headmap);
	for(int j=0; j<4; j++)//画桌子
	{
		for(int i=0; i<4; i++)
		{				
			pdc->BitBlt(i*w+14,j*h+14,w,h,CDC::FromHandle(BackDC),0,0,SRCCOPY);
		//*********画人头*********************//
			int tableid = userInf[i].tableID;
			int sitid	= userInf[i].sitID;
			int x = (2*(tableid%4)+1)*75;
			int y = (2*(tableid/4)+1)*75;	
			char name[20];
			strcpy(name, userInf[i].userName);
			pdc->SetTextColor(RGB(200, 100, 0));
			pdc->SetBkMode(TRANSPARENT);
			if(tableid>=0)
			{
				if(sitid==1)
				{
					pdc->BitBlt(x-43,y-6,headw,headh,CDC::FromHandle(HeadDC),0,0,SRCCOPY);
					pdc->TextOut(x-43, y-21, name);
					char st[10];
					_itoa(tableid, st, 10);
					pdc->TextOut(x-43,y-41,st);
					_itoa(sitid, st, 10);
					pdc->TextOut(x-33,y-41,st);
				}
				else if(sitid==2)
				{				
					pdc->BitBlt(x+3,y+41,headw,headh,CDC::FromHandle(HeadDC),0,0,SRCCOPY);
					pdc->TextOut(x+3, y+41+30, name);
						char st[10];
					_itoa(tableid, st, 10);
					pdc->TextOut(x-43,y-41,st);
					_itoa(sitid, st, 10);
					pdc->TextOut(x-33,y-41,st);
				}
				else if(sitid==3)
				{
					pdc->BitBlt(x+49,y-6,headw,headh,CDC::FromHandle(HeadDC),0,0,SRCCOPY);
					pdc->TextOut(x+49, y-21, name);				
				}
			}
		//********画人头**********************//			
		}
	}	

	ReleaseDC(pdc);
}
//---------------------------------------------------------------------------------------
//退出时候，销毁
void CClientDlg::destroy()
{
	DeleteObject(backmap);
	for(int i=1; i<55; i++)
	{
		DeleteObject(cardmap[i]);
	}
	DeleteObject(tablemap);
	DeleteObject(HeadDC);
	DeleteObject(BackDC);
	DeleteObject(bkDC);
}
//---------------------------------------------------------------------------------------
//在线用户列表
void CClientDlg::showRoom()
{
	CClientDlg *dlg = (CClientDlg *) AfxGetApp()->GetMainWnd();		
	m_player.DeleteAllItems();
	for(int m=0; m<players; m++)
	{
		if(userInf[m].userName!="\0")
		{
			m_player.InsertItem(m, userInf[m].userName);
		}
		char st[10];
		if(userInf[m].tableID>=0)
		{
			_itoa(userInf[m].tableID, st, 10);
			m_player.SetItemText(m, 1, st);
		}
		if(userInf[m].sitID>0)
		{
		_itoa(userInf[m].sitID, st, 10);
		m_player.SetItemText(m, 2, st);
		}
		_itoa(userInf[m].scores, st, 10);
		m_player.SetItemText(m, 3, st);	
	}
}
//--------------------------------------------------------------------------------------
//更新大厅信息
void CClientDlg::updateRoom(char *buffer)
{
	int flag = buffer[0];
	CClientDlg *dlg = (CClientDlg *) AfxGetApp()->GetMainWnd();	
	int id = (int)buffer[1];
	int tableid = (int)buffer[2];
	int sitid	= (int)buffer[3];
	char tmp[20]={0};	
	strncpy(tmp, buffer+4, 20);
	tmp[19]='\0';
	char name[20]={0};
	strcpy(name, tmp);
	name[19]='\0';
	if(id==-1||strlen(name)==0)
	{
		return;	
	}
	strncpy(userInf[id].userName, name, strlen(name));
	
	if(flag==1)//有人登陆
	{	
		players++;
		userInf[id].userID  = id;
		userInf[id].tableID = -1;
		userInf[id].sitID	= -1;
		userInf[id].scores	= 0;
		userInf[id].Ishost	= -1;
		CString log = "---登陆了";
		m_msg.AddString(userInf[id].userName+log);
	}
	else if(flag==2)//有人离开游戏桌
	{		
		userInf[id].tableID = -1;
		userInf[id].sitID	= -1;
		userInf[id].scores	= 0;
		userInf[id].Ishost	= -1;
		CString log = "----站了起来。";
		if(tableid==tid)//如果和自己同桌
		{
			pukInf.cansend = FALSE;
			state = wait;
		}
		m_msg.AddString(userInf[id].userName+log);
	}
	else if(flag==3)//有人坐下
	{		
		userInf[id].tableID = tableid;
		userInf[id].sitID	= sitid;
		userInf[id].scores	= 0;
		userInf[id].Ishost	= -1;
		CString log = "----选了";
		char st[10];
		_itoa(tableid, st, 10);
		CString log2 = "号桌坐下了";
		m_msg.AddString(userInf[id].userName+log+st+log2);
	}
	else //有人退出
	{		
		players--;
		userInf[id].userID	= -1;
		userInf[id].tableID = -1;
		userInf[id].sitID	= -1;
		userInf[id].scores	= 0;
		userInf[id].Ishost	= -1;
		CString log = "----退出了大厅";
		if(tableid==tid)//如果和自己同桌
		{
			pukInf.cansend = FALSE;
			state = wait;
		}
		m_msg.AddString(userInf[id].userName+log);
		memcpy(userInf[id].userName, "\0", 20);
	}	
//	showRoom();
}
//----------------------------------------------------------------
void CClientDlg::OnBTExit() 
{
	CClientDlg *dlg = (CClientDlg *) AfxGetApp()->GetMainWnd();	
	dlg->DestroyWindow();
}
//--------------------------------------------------------------
//重新显示登陆画面
void CClientDlg::reshow()
{
	CClientDlg *dlg = (CClientDlg *) AfxGetApp()->GetMainWnd();	
	dlg->m_room.ShowWindow(SW_HIDE);
	state = wrong;
	dlg->m_ip.ShowWindow(SW_SHOW);
	dlg->m_name.ShowWindow(SW_SHOW);
	dlg->m_connect.ShowWindow(SW_SHOW);
	dlg->m_exit.ShowWindow(SW_SHOW);	
	dlg->m_staticIP.ShowWindow(SW_SHOW);
	dlg->m_staticName.ShowWindow(SW_SHOW);
	dlg->m_hi.ShowWindow(SW_SHOW);
	dlg->m_hi2.ShowWindow(SW_SHOW);
	dlg->m_psd.ShowWindow(SW_SHOW);
	dlg->m_staticPsd.ShowWindow(SW_SHOW);
	m_qroom.ShowWindow(SW_HIDE);
	m_qgame.ShowWindow(SW_HIDE);
	dlg->m_player.ShowWindow(SW_HIDE);
	dlg->m_msg.ShowWindow(SW_HIDE);
}
//-------------------------------------------------------------
void CClientDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(state!=login||state==wrong)
		return;
	int tx, ty;
	tx = point.x;
	ty = point.y;
	int curh = (ty+14)/150;
	int curw = (tx+14)/150;
	tid = (ty+14)/150*4+((tx+14)/150)%4;
	
	//*********一号位，即左边**************//
	int tmplw1 = curw*150+18+14;
	int tmplw2 = curw*150+48+14;
	int tmplh1 = curh*150+55+14;
	int tmplh2 = curh*150+85+14;
	//*********二号位，即下边**************//
	int tmpdw1 = curw*150+64+14;
	int tmpdw2 = curw*150+94+14;
	int tmpdh1 = curh*150+100+16;
	int tmpdh2 = curh*150+140+16;
	//**********三号位，即右边*************//
	int tmprw1 = curw*150+110+14;
	int tmprw2 = curw*150+140+14;
	int tmprh1 = curh*150+55+14;
	int tmprh2 = curh*150+85+14;
	//**********判断一号位*****************//
	if( (tmplw1<tx)&&(tx<tmplw2) && (tmplh1<ty)&&(ty<tmplh2) )
	{
		note(tmplw1, tmplh1);
		canhit = TRUE;
		sid = 1;
	}
	//**********判断二号位*****************//
	else if((tmpdw1<tx)&&(tx<tmpdw2) && (tmpdh1<ty)&&(ty<tmpdh2))
	{
		note(tmpdw1, tmpdh1);
		canhit = TRUE;
		sid = 2;
	}
	//**********判断三号位*****************//
	else if ((tmprw1<tx)&&(tx<tmprw2) && (tmprh1<ty)&&(ty<tmprh2))
	{	
		note(tmprw1, tmprh1);
		canhit = TRUE;
		sid = 3;
	}
	else 
	{
		display();
		canhit = FALSE;
		sid = 0;	
	}	
	CDialog::OnMouseMove(nFlags, point);
}
//显示人头，表示鼠标移动到了座位上
//------------------------------------------------------------------
void CClientDlg::note(int x, int y)
{
	CDC *pdc;
	pdc = GetDC();
	SelectObject(BackDC, toumap);
	pdc->BitBlt(x,y,30,30,CDC::FromHandle(BackDC),0,0,SRCCOPY);
}
//-----------------------------------------------------------------
//初始化
void CClientDlg::init()
{	
	CClientDlg *dlg = (CClientDlg *) AfxGetApp()->GetMainWnd();	
	major = 0;
	m_ip.SetWindowText("192.168.20.26");	
	DWORD style=m_player.GetExtendedStyle();
	m_player.SetExtendedStyle(style|LVS_EX_GRIDLINES);	
	dlg->m_room.GetClientRect(roomrect);
	players = 1;
	hostsit=0;
	ask = TRUE;
	startsit = 0;
	state = wrong;
	CString cc;
	CLoadbmp map;
	for(int tmp=0; tmp<17; tmp++)
	{
		tmpinf[tmp].selected = FALSE;
	}
	for(int num=1;num<=55;num++)
	{
		char st[10];
		sprintf(st, "%d", num);
		cc= dir+"card"+st+".bmp";
		if(map.loadbmp(cc, cardmap+num) == FALSE)
		{
			AfxMessageBox(cc+"扑克没装进!");
		}	
	}
//********************************************//
	cc = dir+"tablen"+".bmp";
	if(map.loadbmp(cc, &tablemap) == FALSE)
	{
		AfxMessageBox(cc+"桌子没装进!");	}

	cc = dir+"head"+".bmp";
	if(map.loadbmp(cc, &headmap) == FALSE)
	{
		AfxMessageBox(cc+"人头没装进来!");
	}	
	cc = dir+"tou"+".bmp";
	if(map.loadbmp(cc, &toumap) == FALSE)
	{
		AfxMessageBox(cc+"小头没装进来!");
	}	
	cc = dir+"host.bmp";
	if(map.loadbmp(cc, &hostmap)==FALSE)
	{
		AfxMessageBox(cc+"地主头没进来");
	}
	cc = dir+"start.bmp";
	if(map.loadbmp(cc, &startmap)==FALSE)
	{
		AfxMessageBox(cc+"小手没进来");
	}
//*****************************************//
	m_player.InsertColumn(0,"用户名");
	m_player.SetColumnWidth(0,60);
	m_player.InsertColumn(1,"桌号");
	m_player.SetColumnWidth(1,40);
	m_player.InsertColumn(2,"座位");
	m_player.SetColumnWidth(2,40);
	m_player.InsertColumn(3,"分数");
	m_player.SetColumnWidth(3,60);
//******************************************//
	for(int t=0; t<maxnum; t++)
	{
		userInf[t].tableID = -1;
		userInf[t].scores  = 1;
		userInf[t].sitID   = -1;
		userInf[t].Ishost  = FALSE;
	}
	setrect();//初始化无效区域	
}
//-----------------------------------------------------------------
//双击左键，向服务端请求坐下
void CClientDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	if(state!=login)
		return;
	CClientDlg *dlg = (CClientDlg *) AfxGetApp()->GetMainWnd();
	if(!canhit||sid<=0)
	{
		return;
	}
	int fg			= 2;
	char sfg		= (char)fg;
	char sitid		= (char)sid;
	char tableid	= (char)tid;
	char msg[5];
	memcpy(msg, &sfg, 1);
	memcpy(msg+1, &tableid, 1);
	memcpy(msg+2, &sitid, 1);
	msg[4] = '\0';
	send(clisock, msg, strlen(msg), 0);	
	CDialog::OnLButtonDblClk(nFlags, point);
}
//------------------------------------------------------------------------------
//发牌
void CClientDlg::showcards()
{
	CClientDlg *dlg = (CClientDlg *) AfxGetApp()->GetMainWnd();	
	CDC *pdc = GetDC(); 

	list<int>::iterator s = mycards.begin();
	int num = mycards.size();
	mynum = prenum = nextnum = num;
	
	CBitmap bk;
	bk.LoadBitmap(IDB_BITMAP7);
	SelectObject(BackDC, bk);	
	pdc->BitBlt(160, 480, num*20, 100, CDC::FromHandle(BackDC),0,0,SRCCOPY);
	DeleteObject(bk);	
//-------------------------------------------------------------------------------
	//给三家发牌
	for(int i=0; i<num; i++, s++)
	{		
		int pk = *s;
		tmpinf[i].pk = pk;
		SelectObject(BackDC, cardmap[pk]);
		if(show==TRUE)
		{			
			PlaySound("wave/give.wav", NULL, SND_FILENAME);
		}
		pdc->BitBlt(300-num/2*15+i*15, 470, cardw, cardh, CDC::FromHandle(BackDC),0,0,SRCCOPY);
		SelectObject(BackDC, cardmap[55]);
		pdc->BitBlt(50, 250+num/2*15-i*15, cardh, cardw, CDC::FromHandle(BackDC),0,0,SRCCOPY);
		pdc->BitBlt(500, 250+num/2*15-i*15, cardh, cardw, CDC::FromHandle(BackDC),0,0,SRCCOPY);
	}
	//不播放声音了
	show = FALSE;
	//画地主头
//	showhost();		
	//画人头，表示有人点开始了
	showstart();	
//---------------------------------------------------------------------------------------
	if(pukInf.ishost&&state!=gaming&&ask)
	{
		ask = FALSE;
		dealhost();			
	}
	ReleaseDC(pdc);
}
//----------------------------------------------------------------------------------------
void CClientDlg::showhost()
{
	CDC *pdc = GetDC();	
	//画地主
	SelectObject(BackDC, hostmap);
	if(hostsit!=sid&&(hostsit!=0))//自己不是地主的时候
	{
		int tmp=(hostsit+1)%3;
		if(tmp==0)
		{
			tmp = 3;
		}
		if(tmp!=sid)//下家
		{
			pdc->BitBlt(580, 300, 30, 30, CDC::FromHandle(BackDC),0,0,SRCCOPY);
		}
		else//上家
		{
			pdc->BitBlt(20, 300, 30, 30, CDC::FromHandle(BackDC),0,0,SRCCOPY);
		}
	}
	else //自己是地主
	{
		if(hostsit!=0)
		{
			pdc->BitBlt(300, 580, 30, 30, CDC::FromHandle(BackDC),0,0,SRCCOPY);
		}
		else
		{
			pdc->BitBlt(300, 20, 30, 30, CDC::FromHandle(BackDC),0,0,SRCCOPY);
		}
	}	
	ReleaseDC(pdc);
}
//----------------------------------------------------------------------------------
void CClientDlg::showstart()
{
	CDC *pdc = GetDC();
	if(state==wait)
	{
		SelectObject(BackDC, startmap);
		if(startsit!=sid&&(startsit!=0))//别人点开始的时候
		{
			int tmp=(startsit+1)%3;
			if(tmp==0)
			{
				tmp = 3;
			}
			if(tmp!=sid)//下家
			{
				pdc->BitBlt(500, 300, 20, 20, CDC::FromHandle(BackDC),0,0,SRCCOPY);
			}
			else//上家
			{
				pdc->BitBlt(100, 300, 20, 20, CDC::FromHandle(BackDC),0,0,SRCCOPY);
			}
		}		
	}
	ReleaseDC(pdc);
}
//-------------------------------------------------------------------------------
void CClientDlg::dealhost()
{
	CClientDlg *dlg = (CClientDlg *) AfxGetApp()->GetMainWnd();
	int fg = 4;
	char sfg = (char)fg;
	char msg[5];
	memcpy(msg, &sfg, 1);
	if(MessageBox("你愿意当地主么？", NULL, MB_OKCANCEL)==IDOK)
	{			
		int yes = 1;
		char host = (char)yes;			
		memcpy(msg+1, &host, 1);
		msg[4]='\0';
		send(clisock, msg, 2, 0);
		state = gaming;
		pukInf.ishost = TRUE;
		pukInf.cansend= TRUE;
		hostsit = sid;
		for(int i=17; i<17+3; i++)//插入底牌
		{
		  mycards.push_back((int)pukInf.puk[i]);
		  tmpinf[i].pk = (int)pukInf.puk[i];
		}	
		/////////////////////////////////////////////////
		list<int>::iterator first = mycards.begin();
		int puk[20];
		for(i=0; i<20; i++, first++)
		{
			*(puk+i) = *first;
		}
		dlg->ReSort(puk, 20);

		list<int>::iterator tmp = mycards.begin();
		for(i=0; i<20; i++, tmp++)
		{
			tmpinf[i].selected = FALSE;
			tmpinf[i].pk = *tmp;//重新给tmpinf赋值
		}	
		
		/////////////////////////////////////////////////
		m_playcard.ShowWindow(SW_SHOW);
		m_pass.EnableWindow(FALSE);
	}
	else
	{
		int no = 2;
		char nohost = (char)no;
		memcpy(msg+1, &nohost, 1);
		msg[4] = '\0';
		send(clisock, msg, 2, 0);
		pukInf.ishost = FALSE;		
		state = wait;//等待游戏开始
		hostsit = 0;
	}
}
//--------------------------------------------------------------------------------
void CClientDlg::decidehost(int host)
{
	int tmp = (host+1)%3;
	if(tmp==0)
	{
		tmp=3;
	}
	//下家牌+3
	if(tmp!=sid)
	{
		nextnum+=3;
	}
	//上家牌+3
	else
	{
		prenum+=3;
	}	 
	
}
//--------------------------------------------------------------------------------
void CClientDlg::playcards()
{

	CClientDlg *dlg = (CClientDlg *) AfxGetApp()->GetMainWnd();	
	CDC *pdc = GetDC(); 
	list<int>::iterator s = mycards.begin();
	mynum = mycards.size();
	//重画背景//
	CBitmap bk;
	bk.LoadBitmap(IDB_BITMAP7);
	SelectObject(BackDC, bk);	
	pdc->BitBlt(130, 450, 370, 100, CDC::FromHandle(BackDC),0,0,SRCCOPY);
	DeleteObject(bk);	
	//给自己发牌
	for(int i=0; i<mynum; i++, s++)
	{		
		int pk = *s;		
		SelectObject(BackDC, cardmap[pk]);		
		if(tmpinf[i].selected)
		{
			pdc->BitBlt(300-mynum/2*15+i*15, 470-20, cardw, cardh, CDC::FromHandle(BackDC),0,0,SRCCOPY);
		}
		else
		{
			pdc->BitBlt(300-mynum/2*15+i*15, 470, cardw, cardh, CDC::FromHandle(BackDC),0,0,SRCCOPY);
		}
	}
	SelectObject(BackDC, cardmap[55]);//扑克背面
	for(i=0; i<prenum; i++)//画上家
	{		
		pdc->BitBlt(50, 250+prenum/2*15-i*15, cardh, cardw, CDC::FromHandle(BackDC),0,0,SRCCOPY);
	}
	for(i=0; i<nextnum; i++)//画下家
	{
		pdc->BitBlt(500, 250+nextnum/2*15-i*15, cardh, cardw, CDC::FromHandle(BackDC),0,0,SRCCOPY);
	}
	SelectObject(BackDC, cardmap[61]);//扑克背面
	for(i=17; i<17+3; i++)//画底牌
	{

		SelectObject(BackDC, cardmap[(int)pukInf.puk[i]]);		
		pdc->BitBlt(200+(i-17)*80, 50, cardw, cardh, CDC::FromHandle(BackDC),0,0,SRCCOPY);
	}
	
	state = gaming;
	ReleaseDC(pdc);
}
//-------------------------------------------------------------------------------
void CClientDlg::showhead()
{
	CDC *pdc = GetDC();
	SelectObject(BackDC, toumap);
	pdc->BitBlt(580, 300, 30, 30, CDC::FromHandle(BackDC),0,0,SRCCOPY);
	pdc->BitBlt(20, 300, 30, 30, CDC::FromHandle(BackDC),0,0,SRCCOPY);
	pdc->BitBlt(300, 580, 30, 30, CDC::FromHandle(BackDC),0,0,SRCCOPY);
	ReleaseDC(pdc);	
}
//-----------------------------------------------------------------------------
void CClientDlg::showname()
{
	CDC *pdc = GetDC();
	pdc->SetTextColor(RGB(100, 250, 50));
	pdc->SetBkMode(TRANSPARENT);
	//画两边玩家名字
	for(int i=0; i<maxnum; i++)
	{//start for
		if(userInf[i].tableID==tid)//与自己同桌
		{//start if
			int id = userInf[i].userID;
			int hisit = userInf[id].sitID;//该玩家的座位
			int tmp = (hisit+1)%3;
			if(tmp==0)
			{
				tmp=3;
			}
			if(tmp!=sid)
			{
				pdc->TextOut(580, 280, userInf[id].userName);
			}
			else
			{
				pdc->TextOut(20, 280, userInf[id].userName);
			}
		}//end if
	}//end for
	//画自己名字
	pdc->TextOut(300, 560, myname);
	ReleaseDC(pdc);
}
//--------------------------------------------------------------------------
void CClientDlg::showit()
{
	CClientDlg *dlg = (CClientDlg *) AfxGetApp()->GetMainWnd();	
	CDC *pdc = GetDC();
	//判断是下方，还是上方出的牌//
	int tmp = (who+1)%3;
	if(tmp==0)
	{
		tmp=3;
	}
	if(tmp!=sid)
	{
	nextnum-=whonum;
	}
	else
	{
	prenum-=whonum;
	}	 
	PlaySound("wave/da.wav", NULL, SND_FILENAME);
	int what = othercards.size();
	list<int>::iterator c = othercards.begin();	
	
	dlg->InvalidateRect(DeskRec);
	dlg->InvalidateRect(LeftRec);
	dlg->InvalidateRect(RightRec);
	dlg->UpdateWindow();
	playcards();	
	if(what!=0)
	{
		for(int i=0; i<what;c++,i++)
		{
		int pk = *c;		
		SelectObject(BackDC, cardmap[pk]);	
		pdc->BitBlt(200+i*20, 280, cardw, cardh, CDC::FromHandle(BackDC),0,0,SRCCOPY);
		}
	} 
	ReleaseDC(pdc);
}
//-------------------------------------------------------------------------------------
void CClientDlg::dealplay(char *buffer)
{
	CDC *pdc = GetDC();
	who  = (int)buffer[0];
	int can = (int)buffer[1];//能不能出牌	
	int num = (int)buffer[2];//别人出的张数
	if(can==1)
	{	
		pukInf.cansend = TRUE;		
	}
	else if(can==2)
	{
		pukInf.cansend = FALSE;		
	}
	whonum = num;
	if(num<=0)
	{		
		pdc->SetBkMode(TRANSPARENT);
		pdc->SetTextColor(RGB(200, 100,50));
		pdc->TextOut(300, 300, "他pass了");
		ReleaseDC(pdc);
		return;
	}
	//将上家的牌保存
	othercards.clear();//先清空
	for(int i=0; i<num; i++)
	{
		int card = (int)(buffer[3+i]);
		othercards.push_back(card);
	}
	showit();//显示画面效果	
}

//-------------------------------------------------------------------------------
//点击开始按钮
void CClientDlg::Onstart() 
{
	CClientDlg *dlg = (CClientDlg *) AfxGetApp()->GetMainWnd();	
	CDC *pdc = GetDC();
	int fg		= 3;
	char sfg	= (char)fg;
	//自己点开始
	SelectObject(BackDC, startmap);
	pdc->SetBkMode(TRANSPARENT);
	pdc->BitBlt(300, 500, 20, 20, CDC::FromHandle(BackDC),0,0,SRCCOPY);			
	send(clisock, &sfg, 1, 0);
	dlg->m_start.ShowWindow(SW_HIDE);
	dlg->m_start.EnableWindow(FALSE);
	ReleaseDC(pdc);
}
//-------------------------------------------------------------------------------
//选牌
void CClientDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{	
	CClientDlg *dlg = (CClientDlg *) AfxGetApp()->GetMainWnd();	
	if(!gaming)
	{
		return;
	}
	int num = mycards.size();
	CRect rect;
	rect.left	= roomrect.left+300-(num)/2*15;
	rect.top	= roomrect.top+450;
	rect.right	= rect.left+(num-1)*15+cardw;
	rect.bottom	= rect.top+cardh+20;
	if(rect.left>point.x || point.x>rect.right || rect.top>point.y || point.y>rect.bottom)
	{//鼠标不再区域内
		goto god;
	}
	else
	{
		int hitid = (point.x-(300-num/2*15))/15;
		if(hitid>=mycards.size())
		{
			hitid = num-1;
		}		
		if(tmpinf[hitid].selected)
		{
			tmpinf[hitid].selected = FALSE;
			sendcards.remove(tmpinf[hitid].pk);
			if(sendcards.size()==0)//当没选中牌的时候
			{
				if(pukInf.cansend)
				{
				}
			}
		}
		else
		{
		 	tmpinf[hitid].selected = TRUE;
			sendcards.push_back(tmpinf[hitid].pk);	
			if(sendcards.size!=0)
			{
				if(pukInf.cansend)//如果能出牌
				{
				//有牌，则出牌按钮能用
				}
			}
		}	
		PostMessage(WM_PAINT, NULL, NULL);
	}
god:
	CDialog::OnLButtonDown(nFlags, point);
}
//-------------------------------------------------------------------------------
//出牌按钮
void CClientDlg::Onplaycard() 
{	
	int fg = 5;
	char sfg = (char)fg;
	int filish;
	char msg[50];
	//将要打的牌排序
	sendcards.sort();
	list<int>::iterator fst = sendcards.begin();
	//要打的牌张数
	int sendnum = sendcards.size();
	//如果打出成功，还剩的张数
	int left = mynum - sendnum;
	if(left<=0)
	{
		filish = 1;
	}
	else //没打完
	{
		filish = 2;
	}
	char ed = (char)filish;
	char sn = (char)sendnum;
	int mj;
	if(major==2)
		mj=1;
	else
		mj = 2;
	char maj = (char)mj;
	memcpy(msg, &sfg, 1);
	memcpy(msg+1, &maj, 1);//出牌权
	memcpy(msg+2, &ed, 1);
	memcpy(msg+3, &sn, 1);
	for(int i=0; i<sendnum; i++, fst++)
	{
		int pk = *fst;
		char card = (char)pk;
		memcpy(msg+4+i, &card, 1);	
	}
	msg[49]='\0';
	int len = 4+sendnum;
	send(clisock, msg, len, 0);
}
//-------------------------------------------------------------------------------
void CClientDlg::dealsend(char *buffer)
{
	CClientDlg *dlg = (CClientDlg *) AfxGetApp()->GetMainWnd();	
	CDC *pdc = GetDC();
	int yes = buffer[0];
	list<int>::iterator fst = sendcards.begin();
	//要打的牌张数
	int sendnum = sendcards.size();
	if(sendnum==0)return;
	if(yes==1)//通过检测
	{		
		major = 0;//重新开始计算
		//从手中牌去掉打出的牌//
		for(int i=0; i<sendnum; i++, fst++)
		{
			int pk = *fst;
			mycards.remove(pk);
		}
		mynum-=sendnum;//更新手中牌数量
		pukInf.cansend = FALSE;//将自己设置未不能出牌状态

		list<int>::iterator first = mycards.begin();
		int puk[20];	
		for(i=0; i<mynum; i++, first++)
		{
			*(puk+i) = *first;
		}
		dlg->ReSort(puk, mynum);
	
		list<int>::iterator tmp = mycards.begin();
		for(i=0; i<mynum; i++, tmp++)
		{
			tmpinf[i].selected = FALSE;
			tmpinf[i].pk = *tmp;//重新给tmpinf赋值
		}	
		PostMessage(WM_PAINT, NULL, NULL);
		PlaySound("wave/da.wav", NULL, SND_FILENAME);
		int m = sendcards.size();
		list<int>::iterator c = sendcards.begin();		
		
		dlg->InvalidateRect(DownRec);
		playcards();
		dlg->InvalidateRect(DeskRec);		
		if(m!=0)
		{
			for(i=0; i<m;c++,i++)
			{
			int pk = *c;		
			SelectObject(BackDC, cardmap[pk]);	
			pdc->BitBlt(200+i*20, 370, cardw, cardh, CDC::FromHandle(BackDC),0,0,SRCCOPY);
			}			
		}	
		PostMessage(WM_PAINT, NULL, NULL);
		sendcards.clear();		
	}
	else
	{
		MessageBox("请正确出牌！");
	}
	ReleaseDC(pdc);

}
//-------------------------------------------------------------------------------
void CClientDlg::Onpass() 
{
	sendcards.clear();
	int fg = 5;
	char sfg = (char)fg;
	int not = 2;//没出完
	int n = -1;	//0张牌
	char no = (char)not;
	char num = (char)n;
	int mj = 2;
	char maj = (char)mj;//无出牌权
	char msg [5];
	memcpy(msg, &sfg, 1);
	memcpy(msg+1, &maj, 1);
	memcpy(msg+2, &no, 1);
	memcpy(msg+3, &num, 1);
	msg[4]='\0';
	send(clisock, msg, 5, 0);
	m_pass.EnableWindow(FALSE);
	pukInf.cansend = FALSE;
}
//-------------------------------------------------------------------------------
//退出游戏桌
void CClientDlg::Onleavgame() 
{
	CClientDlg *dlg = (CClientDlg *) AfxGetApp()->GetMainWnd();	
	m_room.ShowWindow(SW_HIDE);
	m_start.ShowWindow(SW_HIDE);
	m_playcard.ShowWindow(SW_HIDE);
	m_pass.ShowWindow(SW_HIDE);
	int fg = 6;
	char sfg = (char)fg;
	char sitid = (char)sid;
	char msg[5];
	memcpy(msg, &sfg, 1);
	memcpy(msg+1, &sitid, 1);
	msg[4]='\0';
	send(clisock, msg, 2, 0);
	sid = -1;
	tid = -1;
	state = login;		
}
//-------------------------------------------------------------------------------
//退出大厅
void CClientDlg::Onleavroom() 
{
	int fg = 7;
	char sfg = (char)fg;
	send(clisock, &sfg, 1, 0);
	PostMessage(WM_QUIT, NULL, NULL);	
}
//-------------------------------------------------------------------------------
void CClientDlg::OnTimer(UINT nIDEvent) 
{
	CDialog::OnTimer(nIDEvent);
}
//-------------------------------------------------------------------------------

void CClientDlg::setrect()
{	
	LeftRec.left	= 50;
	LeftRec.right	= 130;
	RightRec.top	= LeftRec.top	= 110;
	RightRec.bottom = LeftRec.bottom= 460;
	RightRec.left	= 500;
	RightRec.right	= 578;

	DownRec.left	= 130;
	DownRec.right	= 490;
	DownRec.top		= 420;
	DownRec.bottom	= 550;	

	DeskRec.left	= LeftRec.right;
	DeskRec.right	= RightRec.left;
	DeskRec.top		= LeftRec.top;
	DeskRec.bottom	= DownRec.top;
}
//-------------------------------------------------------------------------------
void CClientDlg::drawface()
{
	CDC *pdc = GetDC();
	CBitmap mp;
	mp.LoadBitmap(IDB_BITMAP3);
	SelectObject(BackDC, mp);
	pdc->BitBlt(260,50,280,50,CDC::FromHandle(BackDC),0,0,SRCAND);
	DeleteObject(mp);
	CBitmap mmp;
	mmp.LoadBitmap(IDB_BITMAP8);
	SelectObject(BackDC, mmp);
	pdc->BitBlt(730,500,100,100,CDC::FromHandle(BackDC),0,0,SRCAND);
	pdc->BitBlt(30,500,100,100,CDC::FromHandle(BackDC),0,0,SRCAND);
	DeleteObject(mmp);
	SelectObject(BackDC,cardmap[54]);
	pdc->BitBlt(50,220,cardw,cardh,CDC::FromHandle(BackDC),0,0,SRCCOPY);
	SelectObject(BackDC,cardmap[54]);
	pdc->BitBlt(700,220,cardw,cardh,CDC::FromHandle(BackDC),0,0,SRCCOPY);
	SelectObject(BackDC,cardmap[27]);
	pdc->BitBlt(270,500,cardw,cardh,CDC::FromHandle(BackDC),0,0,SRCCOPY);
	SelectObject(BackDC,cardmap[40]);
	pdc->BitBlt(340,500,cardw,cardh,CDC::FromHandle(BackDC),0,0,SRCCOPY);
	SelectObject(BackDC,cardmap[14]);
	pdc->BitBlt(410,500,cardw,cardh,CDC::FromHandle(BackDC),0,0,SRCCOPY);
	SelectObject(BackDC,cardmap[1]);
	pdc->BitBlt(480,500,cardw,cardh,CDC::FromHandle(BackDC),0,0,SRCCOPY);
	ReleaseDC(pdc);
}


void CClientDlg::ReSort(int *CurrentCard,int CurrentLen)
{
	int ln = 0;//14
	int col = 0;//4
	for(ln = 0;ln < 14;ln++)//0表示该位置没有牌
	{
		for(col = 0;col < 4;col++)
		{
			pok[ln][col] = 0;
		}
	}
	for(int k = 0; k < CurrentLen; k++)
	{
		if(*(CurrentCard+k) == 53)
		{
			pok[13][0] = 53;//小鬼
		}
		else if(*(CurrentCard+k) == 54)
		{
			pok[13][1] = 54;//大鬼
		}
		else
		{
			col = *(CurrentCard+k)/13;//牌的花色
			if(col == 4)
			{
				col--;
			}
			ln = *(CurrentCard+k)%13-2;//牌的大小
			if(ln<-2||ln>13)
			{
				return;
			}
			if(ln == -1)
			{
				ln = 12;//A
			}
			if(ln == -2)
			{
				ln = 11;//K
			}
			if(ln == 0)
			{
				ln = 13;//2
			}
			pok[ln-1][col] = *(CurrentCard+k);
		}
	}
	//更新mycards//
	mycards.clear();
	for( ln=0; ln<14; ln++)
	{
		for(col = 0; col < 4;col++)
		{
			if(pok[ln][col] != 0)
			{
				mycards.push_back(pok[ln][col]);
			}
		}		
	}
}

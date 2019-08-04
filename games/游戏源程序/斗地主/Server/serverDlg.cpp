// serverDlg.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "serverDlg.h"
#include "Logic.h"
#include "resource.h"
#include <afxdb.h>
#include "afx.h"

#include <string>
#include <list>
#include <algorithm>
using namespace std ;
typedef list<string> LISTSTR;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CDatabase db;
extern mannum;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
int loop;
//char buff[100];
BOOL cansit;	//判断桌子是否满，然后判断能否坐下
BOOL canstart;//人员坐满坐满后，玩家才能点击开始
BOOL IsRun;

#define offdesk  -1//没上桌子
#define prepare  0//玩家等待（人员未满）

#define login    0//进入大厅
#define sitdown  1//坐上桌子
#define leftdesk 2//离开游戏桌
#define exit     3//退出游戏

#define unfull	 4//人员不满
#define full	 5//人员满

static int playerCount;

CCriticalSection g_cs;
LISTSTR nameList;//用户姓名链表
list<string>::iterator result; 

Logic check;


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
// CServerDlg dialog

CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CServerDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServerDlg)
	DDX_Control(pDX, IDC_EDIT_SCORE, m_scores);
	DDX_Control(pDX, IDC_COMBO_Client, m_name);
	DDX_Control(pDX, IDC_LIST_Clients, m_OnlineUser);
	DDX_Control(pDX, IDC_EDIT_Table, m_Table);
	DDX_Control(pDX, IDC_EDIT_ClientName, m_ClinetName);
	DDX_Control(pDX, IDC_ServerName, m_serverName);
	DDX_Control(pDX, IDC_BTN_STOP, m_stop);
	DDX_Control(pDX, IDC_BTN_RUN, m_run);
	DDX_Control(pDX, IDC_LIST2, m_connectInf);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialog)
	//{{AFX_MSG_MAP(CServerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_RUN, OnBtnRun)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerDlg message handlers

BOOL CServerDlg::OnInitDialog()
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
	
	////*************************************************************////
	CServerDlg *dlg=(CServerDlg*)AfxGetApp()->GetMainWnd();
	for(int i=0; i<60; i++)
		msgsock[i] = NULL;
	count = 0;
	char HostName[60];
	gethostname(HostName, 60);
	m_serverName.SetWindowText(LPCTSTR(HostName));
	loop = 1;
	cansit = TRUE;
	dlg->InitStruct();
	IsRun = FALSE;
	/////************************************************************////
		if(!db.Open("斗地主")) 
	{
		AfxMessageBox("打开数据库失败！");	//		
		return false; // 连接数据库
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CServerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

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
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CServerDlg::InitStruct()
{
	CServerDlg *dlg=(CServerDlg*)AfxGetApp()->GetMainWnd();
	for(int i=0; i<20; i++)
	{
		scoreInf[i] = (scr*)malloc(sizeof(scr));
		userInf[i]	= (user*)malloc(sizeof(user));
		pukInf[i]	= (puk*)malloc(sizeof(puk));
		dlg->userInf[i]->tableID	= -1;
		dlg->userInf[i]->userID		= -1;
		strcpy(dlg->userInf[i]->userName, "\0");	
		dlg->userInf[i]->sitID		= -1;
		dlg->userInf[i]->scores		= 0;
		dlg->userInf[i]->Ishost		= -1;//不是地主
		dlg->tableInf[i].player1	= -1;
		dlg->tableInf[i].player2	= -1;
		dlg->tableInf[i].player3	= -1;
		dlg->tableInf[i].tableID	= i;
		dlg->tableInf[i].tableNum	= 0;
		dlg->tableInf[i].tableState = unfull;
		dlg->tableInf[i].startnum   = 0;
		dlg->tableInf[i].changenum  = 0;
		dlg->tableInf[i].passNum    = 0;
		dlg->pukInf[i]->ishost		= FALSE;
		strcpy(dlg->pukInf[i]->hostname, "\0");
		dlg->pukInf[i]->cansend		= FALSE;
		strcpy(dlg->pukInf[i]->puk,"\0");
		dlg->scoreInf[i]->id          = i;
		dlg->scoreInf[i]->fenshu      = 0;
		dlg->cardsInf[i].num	 = 0;
		dlg->cardsInf[i].point	 = 0;
		dlg->cardsInf[i].type	 = 0;
		dlg->tableInf[i].mutiple = 3;

		playerCount              = 0;

	}
}
void CServerDlg::OnBtnRun() 
{
	IsRun = TRUE;
	m_stop.EnableWindow(FALSE);
	//设定地址
	serv.sin_addr.s_addr=htonl(INADDR_ANY);
	serv.sin_family=AF_INET;
	serv.sin_port=5000;//htons(5000);
	addlen=sizeof(serv);

	CServerDlg *dlg=(CServerDlg*)AfxGetApp()->GetMainWnd();
	//创建socket
	sock=socket(AF_INET,SOCK_STREAM,0);
	//绑定
	if (bind(sock,(sockaddr*)&serv,addlen))
	{	
		dlg->m_connectInf.InsertString(dlg->count++, "绑定错误");
	}
	else
	{	
		dlg->m_connectInf.InsertString(dlg->count++, "服务器创建成功");
		m_run.EnableWindow(FALSE);
		m_stop.EnableWindow(TRUE);	
		//开始侦听	
		listen(sock,5);	
		//启动主线程
		AfxBeginThread(mainThread, 0);	
	}
}

void CServerDlg::OnBtnStop() 
{
	IsRun = FALSE;
	CServerDlg *dlg=(CServerDlg*)AfxGetApp()->GetMainWnd();
	dlg->m_connectInf.InsertString(dlg->count++, "服务器停止运行");
	m_run.EnableWindow(TRUE);
	m_stop.EnableWindow(FALSE);		
	closesocket(dlg->sock);
	for(int i=0; i<60; i++)
	{
		if(msgsock[i]!=NULL)
		{
			send(msgsock[i],"连接断开", 20, 0);
			closesocket(msgsock[i]);
			msgsock[i] = NULL;
		}
	}
	nameList.clear();
}


UINT mainThread(LPVOID)
{
	int msgcount, s;
	char buff[100];
	CServerDlg *dlg=(CServerDlg*)AfxGetApp()->GetMainWnd();
	//获得客户端数量
	msgcount=dlg->getsocket();
	if(msgcount==-1)
		loop = 0;
	if(loop)
	{		
		s = 1;
		if(IsRun)
		{
			dlg->msgsock[msgcount]=accept(dlg->sock,(sockaddr*)&(dlg->serv),&(dlg->addlen));
		}
		if (dlg->msgsock[msgcount]==INVALID_SOCKET)
		{
			if(IsRun)
			{
				dlg->m_connectInf.InsertString(dlg->count++,"Error Accept!");
			}
			else
			{
				dlg->m_connectInf.InsertString(dlg->count++,"The server has been closed!");
			}
		}	
		else
		{			
			dlg->m_connectInf.InsertString(dlg->count++,inet_ntoa(dlg->serv.sin_addr));
			AfxBeginThread(mainThread,0);
			while(s!=SOCKET_ERROR&&IsRun)
			{
				//循环接收数据
				s=recv(dlg->msgsock[msgcount],buff,100,0);
				dlg->SetForegroundWindow();
				if (s!=SOCKET_ERROR)
				{
					//消息处理
					dlg->dealmsg(msgcount, buff);
				}
			}			
			int tableid = dlg->userInf[msgcount]->tableID;
			int sitid	= dlg->userInf[msgcount]->sitID;
			if(tableid<0)
			{
				tableid = 0;
			}
			if(sitid<0)
			{
				sitid = 0;
			}
			char name[20];
			memcpy(name, dlg->userInf[msgcount]->userName, 20);
			name[19] = '\0';
			dlg->updateRoom(exit, msgcount, name, tableid, sitid);		
		}
	}//end if	
	AfxEndThread(0);
	return 0;
}

int CServerDlg::getsocket()
{
	for (int i=0;i<50;i++)
	{
		if (msgsock[i]==NULL)
			return i;
	}
	return -1;
}
//===========================================================================================//
void CServerDlg::dealmsg(int msgcount, char *buff)
{
	CServerDlg *dlg=(CServerDlg*)AfxGetApp()->GetMainWnd();
	CString first;				
	int flag = (int)buff[0];
	switch(flag)
	{
		case 1://用户登陆，
		{							
			dlg->dealLogin(msgcount, buff);		
			break;
		}
		case 2://用户选择某游戏桌某一座位
		{
			dlg->dealSit(msgcount, buff);
			break;
		}
		case 3://用户点击开始，
		{
			dlg->dealStart(msgcount, buff);
			break;
		}
		case 4://有人不愿当地主了
		{
			int yes =(int)buff[1];
			dlg->dealChangeHost(msgcount, yes);
			break;
		}
		case 5://处理在打牌了
		{
			dlg->dealSendCards(msgcount, buff);
			break;
		}
		case 6://离开游戏桌子
		{
			dlg->dealLeftDesk(msgcount);
			break;
		}
		case 7://处理离开大厅
		{
			dlg->dealExit(msgcount);
			break;
		}
		default:
		{			
			//dlg->sendRoomInf(msgcount);
			break;
		}
						
	}//end switch
}
//===========================================================================================//
void CServerDlg::dealLogin(int socknum, char *buffer)
{
	CServerDlg *dlg=(CServerDlg*)AfxGetApp()->GetMainWnd();
	char inname[20]={0};
	CString theName ="";
	int Len = (int)buffer[1];
	char inpassWord[20] = {0};
	int pLen = (int)buffer[2+Len];
	for(int i=0; i<Len; i++)
	{
		if(buffer[i+2]!='.')
		{
			inname[i]=buffer[i+2];
		}
		else 
		{
			break;
		}
	}

	for(int j = 0; j < pLen; j++)
	{
		if(buffer[3+Len+j]!='.')
		{
			inpassWord[j] = buffer[3+Len+j];
			
		}
		else 
		{
			break;
		}
	}

	char msg[10];
	int mfg = 9;
	char msfg = (char)mfg;
	theName = (CString)inname;
	result = find(nameList.begin(), nameList.end(), inname);
	if(result != nameList.end())
	{		
		int tr = 4;///4表示重名
		char t = (char)tr;		
		memcpy(msg, &msfg, 1);
		memcpy(msg+1, &t, 1);
		msg[9]='\0';
		send(msgsock[socknum], msg, 10, 0);	
	}

	CRecordset rs(&db);

	CString strpwd;//密码
	CString strscr;//分数
	CString strgrd;//等级
	CString strhead;//头像
	rs.Open(CRecordset::forwardOnly,
		"select * from playerInfo where name ='"+theName+"'");
	if(!rs.IsEOF())
	{
		rs.GetFieldValue("passWord",strpwd);
		rs.GetFieldValue("grade",strgrd);
		rs.GetFieldValue("score",strscr);
		rs.GetFieldValue("head",strhead);
	}
	if(strpwd == "")
	{
		int tr = 3;//表示还没有注册
		char t = (char)tr;		
		memcpy(msg, &msfg, 1);
		memcpy(msg+1, &t, 1);
		msg[9]='\0';
		send(msgsock[socknum], msg, 10, 0);	
		dlg->updateRoom(exit, socknum, "\0", -1, -1);	
	}
	strpwd.TrimRight();
	strgrd.TrimRight();
	strscr.TrimRight();
	if(strcmp(strpwd,inpassWord) == 0)//登陆成功
	{
		nameList.push_back(inname);
		///////////////从数据库读出玩家的信息
		//分数
		char sc[10];
		strncpy(sc,strscr,strscr.GetLength() );
		int scor = 0;
		int sLen = strscr.GetLength();
		scor = atoi(sc);
		dlg->userInf[socknum]->scores = scor;
		//头像
		int hLen = 0;
		char header[10];
		int hd = 0;
		strncpy(header,strhead,hLen);
		for(int kh = 0;kh < sLen; kh++)
		{
			hd += ((int)sc[kh]-48)*pow(10,sLen-kh-1);
		}
		dlg->userInf[socknum]->head = hd;
		//等级
		memcpy(dlg->userInf[socknum]->grade,strgrd,strgrd.GetLength());
		 
		CString cnt=" connected";								
		dlg->SetForegroundWindow();
		dlg->m_connectInf.InsertString(dlg->count++,inname+cnt);		
		dlg->updateRoom(login, socknum, inname,  -1, -1);	
		dlg->sendRoomInf(socknum);

		int tr = 1;//＝＝1表示登陆成功
		char t = (char)tr;
		memcpy(msg, &msfg, 1);
		memcpy(msg+1, &t, 1);
		msg[9]='\0';
		send(msgsock[socknum], msg, 10, 0);//告诉它登陆成功
		
		
	}
	else
	{
		int tr = 2;//表示密码错误
		char t = (char)tr;		
		memcpy(msg, &msfg, 1);
		memcpy(msg+1, &t, 1);
		msg[9]='\0';
		send(msgsock[socknum], msg, 10, 0);	
		dlg->updateRoom(exit, socknum, "\0", -1, -1);	

	}
	rs.Close();

}
//===========================================================================================//
void CServerDlg::dealSit(int socknum, char *buffer)
{
	CServerDlg *dlg=(CServerDlg*)AfxGetApp()->GetMainWnd();

	int tableid = (int)(buffer[1]);//用户选择的游戏桌
	int sitid	= (int)(buffer[2]);//用户选择的座位号sitid取值为1、2、3
	int sit = dlg->getplayerID(tableid, sitid);
	int fg = 2;
	char sfg = (char)fg;	
	if(sit==-1)//该位置没人
	{			
		char name[20];
		sprintf(name, "%s", dlg->userInf[socknum]->userName);
		dlg->updateRoom(sitdown, socknum, name,	tableid, sitid);
		char msg[5];
		int x = 1;
		char X = (char)x;
		memcpy(msg, &sfg, 1);
		memcpy(msg+1, &X, 1);	
		msg[4] = '\0';
		send(msgsock[socknum], msg, 2, 0);	
	}
	else
	{
		char msg[5];
		int x = 2;//2表示不能坐下
		char X = (char)x;
		memcpy(msg, &sfg, 1);
		memcpy(msg+1, &X, 1);	
		msg[4] = '\0';
		send(msgsock[socknum], msg, 2, 0);		
	}
}
//===========================================================================================//
void CServerDlg::dealStart(int socknum, char *buffer)
{
	CServerDlg *dlg=(CServerDlg*)AfxGetApp()->GetMainWnd();
	int tableid = dlg->userInf[socknum]->tableID;
	dlg->setStartnum(1, tableid);
	
	if(dlg->canstart(tableid))
	{
		dlg->sendCards(tableid);//所有人都点了开始，就发牌
	}	
	else
	{
		int p1 = dlg->tableInf[tableid].player1;
		int p2 = dlg->tableInf[tableid].player2;
		int p3 = dlg->tableInf[tableid].player3;
		int sitid = dlg->userInf[socknum]->sitID;
		char sit = (char)sitid;
		int fg = 10;
		char sfg = (char)fg;
		char msg[5]={0};
		memcpy(msg, &sfg, 1);
		memcpy(msg+1, &sit, 1);
		msg[4] = '\0';	
		send(msgsock[p1], msg, 2, 0);	
		send(msgsock[p2], msg, 2, 0);
		send(msgsock[p3], msg, 2, 0);//通知谁点开始了
	}
}
//===========================================================================================//
void CServerDlg::dealChangeHost(int socknum, int yes)
{
	CServerDlg *dlg=(CServerDlg*)AfxGetApp()->GetMainWnd();
	int tableid = dlg->userInf[socknum]->tableID;
	int mysit	= dlg->userInf[socknum]->sitID;	
	int pnext   = mysit%3+1;//下家
	int ppre	= (mysit%3+2)%3;//上家
	if(ppre==0)
	{
		ppre=3;
	}
	int next = dlg->getplayerID(tableid, pnext);
	int pre	 = dlg->getplayerID(tableid, ppre);
	if(yes!=1)//不同意当地主
	{
		int changed = ++(dlg->tableInf[tableid].changenum);
		//将他重置为不是地主了
		dlg->sethost(0, socknum);
		//所有人都不愿意就重新发牌
		if(changed==3)			
		{
			dlg->sendCards(tableid);
		}
		//询问下一家
		else
		{
			dlg->sethost(1, next);//临时将下家设为host
			char msg[100];
			int fg			= 4;
			char sfg		= (char)fg;
		
			int	 dizu		= 1;		//是地主
			char dz			= (char)dizu;

			int  sendcards	= 1;		//能出牌
			char sdc		= (char)sendcards;

			memcpy(msg, &dz, 1);
			memcpy(msg+1, &sdc, 1);
			msg[99] = '\0';		
			strcpy(msg+2,dlg->userInf[next]->userName);			
			dlg->sendMessage(next,&sfg,msg); 
		}
	}
	else//同意当地主，告诉另外两玩家
	{
		int fg = 11;
		char sfg = (char)fg;
		char msg[5];
		char sit = (char)mysit;
		memcpy(msg, &sfg, 1);
		memcpy(msg+1, &sit, 1);
		msg[4]='\0';
		send(msgsock[next], msg, 2, 0);
		send(msgsock[pre], msg, 2, 0);
	}
}
//===========================================================================================//
void CServerDlg::dealSendCards(int socknum, char *buffer)
{
	CServerDlg *dlg=(CServerDlg*)AfxGetApp()->GetMainWnd();
	//int theTable = CServerDlg::getTableId(socknum);
	int fg	 = 5;
	char sfg = (char)fg;
	int maj  = (int)buffer[1];//是否拥有出牌权
	int end  = (int)buffer[2];//是否打完了
	int num  = (int)buffer[3];//多少张牌
	if(num==-1)
		num=0;	
	char stt[10];
	_itoa(num, stt, 10);
	dlg->m_connectInf.InsertString(dlg->count++, stt);
	int tableid = dlg->userInf[socknum]->tableID;
	int sitid   = dlg->userInf[socknum]->sitID;	

	int next, other;//下一家，和下下家 id;

	if(sitid==1)
	{
		next = 2;
		other= 3;
	}
	else if(sitid == 2)
	{
		next = 3;
		other= 1;
	}
	else
	{
		next = 1;
		other= 2;
	}
	int pNext = dlg->getplayerID(tableid, next);
	int pOther= dlg->getplayerID(tableid, other);
	int N = 1;//下一家能出牌
	int O = 2;//下下家不能出
	char pn = (char)N;
	char po= (char)O;
	char msgN[50]={0};
	char msgO[50]={0};
	msgN[49] = '\0';
	msgO[49] = '\0';
	char sit = (char)sitid;
	strncpy(msgN+0, &sit, 1);//哪个座位出的牌
	strncpy(msgO+0, &sit, 1);
	strncpy(msgN+1, &pn, 1);
	strncpy(msgO+1, &po, 1);//能不能出牌
	strncpy(msgN+2, buffer+3, num+1);//copy信息包括多少张牌和什么牌
	strncpy(msgO+2, buffer+3, num+1);
	int myfg = 8;
	char mysfg = (char)myfg;//告诉玩家是否通过检测，能否出牌
	char mymsg[10]={0};	
	BOOL result;
	if(num>0)
	{	
		char curCards[25]={0};
		memcpy(curCards, buffer+3, num+1);	
		int  cur_cards[21];
		for(int h=0; h<num; h++)
		{
			cur_cards[h]=(int)curCards[h+1];
			char st[10];	
		}		
		curCards[24]='\0';				
		int type = dlg->cardsInf[tableid].type;//上次类型		
		int point= dlg->cardsInf[tableid].point;//上次基点
		int prenum = dlg->cardsInf[tableid].num;//上次张数
		if(maj==1)
		{
			prenum=0;
		}
		
		if(dlg->tableInf[tableid].passNum >= 2)
		{
			type = 0;
			point = 0;
			prenum = 0;
		}
		CRITICAL_SECTION g_cs;
		InitializeCriticalSection(&g_cs);
	//	EnterCriticalSection(&g_cs);
		result = check.LogicCheck(tableid,cur_cards, num, type, point, prenum);
		
		if(result)//通过检测
		{
			CServerDlg *dlg = (CServerDlg*)AfxGetApp()->GetMainWnd();
			dlg->tableInf[tableid].passNum = 0;
			int yes = 1;
			char y	= (char)yes;
			memcpy(mymsg, &mysfg, 1);		
			memcpy(mymsg+1, &y, 1);
			mymsg[9]='\0';
			send(msgsock[socknum], mymsg, 10, 0);//告诉他，通过检测了
			dlg->sendMessage(pNext, &sfg, msgN);
			dlg->sendMessage(pOther, &sfg, msgO);	
			//重置张数，基点，类型
			dlg->cardsInf[tableid].num	= num;			
			dlg->cardsInf[tableid].type = check.GetType(tableid);
			dlg->cardsInf[tableid].point= check.GetPoint(tableid);	
			if(check.bombWarning(tableid))
			{
				if(socknum == dlg->FindHost(tableid) && 
					dlg->tableInf[tableid].passNum < 2)
				{
					(dlg->tableInf[tableid].mutiple) *= 2;
				}
			}
		}
		else
		{
			int no	= 2;
			char n	= (char)no;
			memcpy(mymsg, &mysfg, 1);		
			memcpy(mymsg+1, &n, 1);
			mymsg[9]='\0';			
			send(msgsock[socknum], mymsg, 10, 0);//告诉他，没通过检测
		}
	}
	else//处理pass的情况
	{
		CServerDlg *dlg = (CServerDlg*)AfxGetApp()->GetMainWnd();
		dlg->tableInf[tableid].passNum++;
		int yes = 1;
		char y	= (char)yes;
		strncpy(mymsg, &mysfg, 1);		
		strncpy(mymsg+1, &y, 1);
		mymsg[9]='\0';
		send(msgsock[socknum], mymsg, 10, 0);//告诉他，通过检测了
		char msg1[50], msg2[50];
		msg1[49]='\0';
		msg2[49]='\0';
		strncpy(msg1, &sfg, 1);
		strncpy(msg2, &sfg, 1);
		strncpy(msg1+1, msgN, 20);
		strncpy(msg2+1, msgO, 20);
		send(msgsock[pNext], msg1, 50, 0);
		send(msgsock[pOther], msg2, 50, 0);	
		
	}	
	
	if(end==1&&result)//如果出完了,而且通过了检测
	{
		/////////算分///////////////////////////////
		

		dlg->GetChangScore(socknum,pNext,pOther);
	
		dlg->WriteDb(socknum);
		dlg->WriteDb(pNext);
		dlg->WriteDb(pOther);
		dlg->resetPukInf(tableid);

		//	MessageBox("wan le");
		int fg = 6;
		char sfg = (char)fg;
		char msg[5];
		memcpy(msg, &sfg, 1);
		
		////////////****************//////////
		//调用记分函数，发送统计信息到玩家////		
		////////////****************//////////	
		char ScoreSock;
		char ScoreNext;
		char ScoreOther;
		ScoreSock  = (char)ChangeScore[socknum];
		ScoreNext  = (char)ChangeScore[pNext];
		ScoreOther = (char)ChangeScore[pOther];
		memcpy(msg+1,&ScoreSock,1);
		send(msgsock[socknum], msg, 2, 0);
		memcpy(msg+1,&ScoreNext,1);
		send(msgsock[pNext], msg, 2, 0);
		memcpy(msg+1,&ScoreOther,1);		
		send(msgsock[pOther], msg, 2, 0);
		///////////////////////////////////////////
		//告诉所有玩家现在的更新分数表
		///////////////////////////////////////////
		 fg = 12;
		 sfg = (char)fg;
		char msgscore1[100];
		char msgscore2[100];
		char msgscore3[100];
		strncpy(msgscore1,&sfg,1);	
		strncpy(msgscore2,&sfg,1);
		strncpy(msgscore3,&sfg,1);
		dlg->scoreInf[socknum]->fenshu = dlg->userInf[socknum]->scores;
		dlg->scoreInf[pNext]->fenshu = dlg->userInf[pNext]->scores;
		dlg->scoreInf[pOther]->fenshu = dlg->userInf[pOther]->scores;
		memcpy(msgscore1+1, (char*)dlg->scoreInf[socknum], sizeof(dlg->scoreInf));
		memcpy(msgscore2+1, (char*)dlg->scoreInf[pNext], sizeof(dlg->scoreInf));
		memcpy(msgscore3+1, (char*)dlg->scoreInf[pOther], sizeof(dlg->scoreInf));
		Sleep(500);
		for ( int i = 0; i < 3; i++)
		{
			send(msgsock[i],msgscore1,sizeof(dlg->scoreInf)+1,0);
			send(msgsock[i],msgscore2,sizeof(dlg->scoreInf)+1,0);
			send(msgsock[i],msgscore3,sizeof(dlg->scoreInf)+1,0);
			//send(msgsock[socknum],"heloo", 6, 0);
			
		}
		
		   
	}	
}

//===========================================================================================//
void CServerDlg::dealLeftDesk(int socknum)
{
	CServerDlg *dlg=(CServerDlg*)AfxGetApp()->GetMainWnd();
	int flag = leftdesk;
	char name[20];
	strcpy(name, dlg->userInf[socknum]->userName);
	int tableid = dlg->userInf[socknum]->tableID;
	int sitid	= dlg->userInf[socknum]->sitID;
	dlg->updateRoom(flag, socknum, name, tableid, sitid);	
}
//===========================================================================================//
void CServerDlg::dealExit(int socknum)
{
	CServerDlg *dlg=(CServerDlg*)AfxGetApp()->GetMainWnd();
	int flag = exit;
	char name[20];
	strcpy(name, dlg->userInf[socknum]->userName);
	int tableid = dlg->userInf[socknum]->tableID;
	int sitid	= dlg->userInf[socknum]->sitID;
	dlg->updateRoom(flag, socknum, name, tableid, sitid);
}
//===========================================================================================//
void CServerDlg::updateRoom(int flag, int socknum, char *name, int tableid, int sitid)
{
	g_cs.Lock();	
	CServerDlg *dlg=(CServerDlg*)AfxGetApp()->GetMainWnd();
	int len =	strlen(name);
	if(flag==exit)
	{
		playerCount--;
		char name[20];
		strcpy(name, dlg->userInf[socknum]->userName);
		name[19] = '\0';
		if(len!=0)
		{
			nameList.remove(name);//在线用户里头删除离开的玩家
		}
		memcpy(dlg->userInf[socknum]->userName, "\0", 20);
		dlg->userInf[socknum]->userName[19] = '\0';
		dlg->userInf[socknum]->userID	= -1;
		dlg->userInf[socknum]->tableID	= -1;		
		dlg->userInf[socknum]->sitID	= -1;
	//	dlg->userInf[socknum]->scores	= 0;
		dlg->userInf[socknum]->Ishost	= -1;
		if(tableid>=0)
		{
			dlg->setStartnum(0, tableid);
		}
		dlg->tableInf[socknum].changenum= 0;	
		dlg->msgsock[socknum] = NULL;
		closesocket(msgsock[socknum]);	
		if(sitid>0)
		{
			dlg->writeTableInf(0, tableid);		 //更新信息
			dlg->setplayerID(-1, tableid, sitid);//设置某位置现在没人坐		
			dlg->resetPukInf(tableid);
		}
		
	}
	else if(flag==login)
	{
		playerCount++;
		dlg->userInf[socknum]->userID	= socknum;		
		dlg->userInf[socknum]->tableID	= -1;
		dlg->userInf[socknum]->sitID	= -1;
	//	dlg->userInf[socknum]->scores	= 0;
		memcpy(dlg->userInf[socknum]->userName, name, 20);		
		dlg->userInf[socknum]->userName[19] = '\0';
	}
	else if(flag==sitdown)
	{
		dlg->userInf[socknum]->tableID	= tableid;
		dlg->userInf[socknum]->sitID	= sitid;
		//更新桌子信息
		if(tableid>=0)
		{
			dlg->writeTableInf(1,tableid); 
			dlg->setplayerID(socknum, tableid, sitid);
		}
	}
	else if(flag==leftdesk)//玩家离开游戏桌
	{
		dlg->userInf[socknum]->tableID	= -1;
		dlg->userInf[socknum]->sitID	= -1;
	//	dlg->userInf[socknum]->scores	= 0;
		dlg->userInf[socknum]->Ishost	= -1;
		dlg->setStartnum(0, tableid);
		dlg->tableInf[socknum].changenum= 0;
		if(sitid>0)
		{
			dlg->writeTableInf(0, tableid);		 //删除信息
			dlg->setplayerID(-1, tableid, sitid);//设置某位置现在没人坐
			dlg->resetPukInf(tableid);
		}
	}
	
//***************通知所有人更新********************//	
	int fg = 7;
	char sfg = (char)fg;
//===========================================================================================//

char	msg[100];
int		myfg ;
if(flag==login)
{
	myfg = 1;
}
else if(flag==leftdesk)
{
	myfg = 2;
}
else if(flag==sitdown)
{
	myfg = 3;
}
else 
{
	myfg = 4;
}
char	ffg = (char)myfg;
char	who = (char)socknum;
char	tab = (char)tableid;
char	st	= (char)sitid;
char    sc  = (char)dlg->userInf[socknum]->scores; 
if(len!=0)
{
	memcpy(msg+0, &sfg, 1);
	memcpy(msg+1, &ffg, 1);
	memcpy(msg+2, &who, 1);
	memcpy(msg+3, &tab, 1);
	memcpy(msg+4, &st,  1);
	memcpy(msg+5, &sc,  1);
	strncpy(msg+6, name, strlen(name));
	msg[99] = '\0';
	int len = strlen(name)+6;
	for(int i=0; i<playerCount; i++)
	{
		if(msgsock[i]!=NULL&&i!=socknum)
		{			
			send(msgsock[i], msg, len, 0);
		}
	}	
}

//===========================================================================================//
	//服务端显示在线用户名
	dlg->m_OnlineUser.DeleteAllItems();	
	dlg->m_name.ResetContent();
	for(int m=0; m<playerCount; m++)
	{
		if(dlg->userInf[m]->userID!=-1)
		{
			dlg->m_OnlineUser.InsertItem(dlg->count++, dlg->userInf[m]->userName);
			dlg->m_name.AddString(dlg->userInf[m]->userName);			
		}
	}	
	g_cs.Unlock();
}
//===========================================================================================//
//发送大厅信息
void CServerDlg::sendRoomInf(int socknum)
{
	g_cs.Lock();
	CServerDlg *dlg=(CServerDlg*)AfxGetApp()->GetMainWnd();	
	int fg = 1;
	char sfg = (char)fg;	

	//////////////给msg付值，然后发送到登陆的玩家//////////		
	for(int i=0; i<playerCount; i++)
	{
		char msg[100] = {0};		
		strcpy(msg, &sfg);
		memcpy(msg+1, (char*)dlg->userInf[i], sizeof(dlg->userInf));
		msg[99] = '\0';
		int len = sizeof(userInf)+1;
		if(dlg->userInf[i]->userID!=-1)
		{
			send(msgsock[socknum], msg, len,0);
		}		
	}
	g_cs.Unlock();
}

//===========================================================================================//
void CServerDlg::sendMessage(int socknum, char *flag, char *buffer)
{
	char fg = (char)(*flag);
	char Inf[100];
	memcpy(Inf, &fg, 1);
	memcpy(Inf+1, buffer, 100);
	Inf[99] = '\0';
//	int len = sizeof(buffer)+1;
	send(msgsock[socknum], Inf, 100, 0);
}

//===========================================================================================//
void CServerDlg::writeTableInf(int flag, int tableid)
{
	CServerDlg *dlg=(CServerDlg*)AfxGetApp()->GetMainWnd();	
	dlg->tableInf[tableid].tableID = tableid;
	if(flag==1)
	{		
		dlg->tableInf[tableid].tableNum++;	
		if(dlg->tableInf[tableid].tableNum==3)
		{
			dlg->setTableState(tableid, full);
		}
		else//小于3
		{
			dlg->setTableState(tableid, unfull);
		}
	}
	else
	{
		dlg->tableInf[tableid].tableNum--;
		dlg->setTableState(tableid, unfull);
	}	
}

//===========================================================================================//
void CServerDlg::setTableState(int tableid, int state)
{
	CServerDlg *dlg=(CServerDlg*)AfxGetApp()->GetMainWnd();
	dlg->tableInf[tableid].tableState = state;
}
//===========================================================================================//
int CServerDlg::gettableState(int tableid)
{
	CServerDlg *dlg=(CServerDlg*)AfxGetApp()->GetMainWnd();
	return dlg->tableInf[tableid].tableState;
}
//===========================================================================================//
void CServerDlg::setplayerID(int socknum, int tableid, int sitid)
{
	CServerDlg *dlg=(CServerDlg*)AfxGetApp()->GetMainWnd();
	if(sitid==1)
	{
		dlg->tableInf[tableid].player1 = socknum;
	}
	else if(sitid==2)
	{
		dlg->tableInf[tableid].player2 = socknum;
	}
	else
	{
		dlg->tableInf[tableid].player3 = socknum;
	}
}
//===========================================================================================//
int CServerDlg::getplayerID(int tableid, int sitid)
{
	CServerDlg *dlg=(CServerDlg*)AfxGetApp()->GetMainWnd();	
	if(sitid==1)
	{
		return dlg->tableInf[tableid].player1;
	}
	else if(sitid==2)
	{
		return dlg->tableInf[tableid].player2;
	}
	else
	{
		return dlg->tableInf[tableid].player3;
	}
}
//===========================================================================================//
void CServerDlg::sethost(int flag, int socknum)
{	
	CServerDlg *dlg=(CServerDlg*)AfxGetApp()->GetMainWnd();
	if(flag==0)
	{
		dlg->userInf[socknum]->Ishost = -1;
	}
	else
	{
		dlg->userInf[socknum]->Ishost = 1;
	}
}
//===========================================================================================//
void CServerDlg::setStartnum(int flag, int tableid)
{
	CServerDlg *dlg=(CServerDlg*)AfxGetApp()->GetMainWnd();
	if(flag==0)
	{
		if(dlg->tableInf[tableid].startnum>0)
		{
			dlg->tableInf[tableid].startnum--;
		}
	}
	else
	{
		if(dlg->tableInf[tableid].startnum<3)
		{
			dlg->tableInf[tableid].startnum++;
		}
	}
}

//===========================================================================================//
BOOL CServerDlg::canstart(int tableid)
{
	CServerDlg *dlg=(CServerDlg*)AfxGetApp()->GetMainWnd();
	if(dlg->tableInf[tableid].startnum==3)
	{
		return TRUE;
	}
	else
	{	
		return FALSE;
	}
}
//===========================================================================================//
void CServerDlg::sendCards(int tableid)
{
	CServerDlg *dlg=(CServerDlg*)AfxGetApp()->GetMainWnd();
/////////更新基点和类型////////////////////////////////////////
	
		dlg->cardsInf[tableid].num	= 0;
		dlg->cardsInf[tableid].point	= 0;
		dlg->cardsInf[tableid].type	= 0;
		dlg->tableInf[tableid].mutiple = 3;
	
/////////////////////////////////////////////////////////
	
	dlg->tableInf[tableid].changenum = 0;
	dlg->tableInf[tableid].startnum  = 0;

	int p1 = dlg->getplayerID(tableid, 1);
	int p2 = dlg->getplayerID(tableid, 2);
	int p3 = dlg->getplayerID(tableid, 3);
////////////获得三份牌，发送到三家/////////////////////
	char *puk;
	//随机洗牌
	puk = produceCards();
	char puk1[20], puk2[20], puk3[20];
	strncpy(puk1, puk+0, 17);
	strncpy(puk2, puk+17, 17);
	strncpy(puk3, puk+34, 17);
	//后三张为底牌
	strncpy(puk1+17, puk+51, 3);
	strncpy(puk2+17, puk+51, 3);
	strncpy(puk3+17, puk+51, 3);
	//随机产生个地主
	int s=rand()%3;
	char dizu[20];
	if(s==0)
	{
		int pl = dlg->tableInf[tableid].player1;		
		memcpy(dizu, dlg->userInf[pl]->userName, strlen(dlg->userInf[pl]->userName));		
		dlg->pukInf[p1]->ishost  = TRUE;
		dlg->pukInf[p2]->ishost  = FALSE;
		dlg->pukInf[p3]->ishost  = FALSE;
		dlg->pukInf[p1]->cansend = TRUE;
		dlg->pukInf[p2]->cansend = FALSE;
		dlg->pukInf[p3]->cansend = FALSE;		
	}
	else if(s==1)
	{		
		int pl = dlg->tableInf[tableid].player2;		
		memcpy(dizu, dlg->userInf[pl]->userName, strlen(dlg->userInf[pl]->userName));
		dlg->pukInf[p2]->ishost  = TRUE;
		dlg->pukInf[p1]->ishost  = FALSE;
		dlg->pukInf[p3]->ishost  = FALSE;
		dlg->pukInf[p2]->cansend = TRUE;
		dlg->pukInf[p1]->cansend = FALSE;
		dlg->pukInf[p3]->cansend = FALSE;

	}
	else
	{	
		int pl = dlg->tableInf[tableid].player3;		
		memcpy(dizu, dlg->userInf[pl]->userName, strlen(dlg->userInf[pl]->userName));
		dlg->pukInf[p3]->ishost	 = TRUE;
		dlg->pukInf[p2]->ishost	 = FALSE;
		dlg->pukInf[p1]->ishost	 = FALSE;
		dlg->pukInf[p3]->cansend = TRUE;
		dlg->pukInf[p2]->cansend = FALSE;
		dlg->pukInf[p1]->cansend = FALSE;
	}
	//插入地主名字
	strncpy(dlg->pukInf[p1]->hostname, dizu, strlen(dizu));
	strncpy(dlg->pukInf[p2]->hostname, dizu, strlen(dizu));
	strncpy(dlg->pukInf[p3]->hostname, dizu, strlen(dizu));
	//插入扑克
	strncpy(dlg->pukInf[p1]->puk, puk1, strlen(puk1));
	strncpy(dlg->pukInf[p2]->puk, puk2, strlen(puk2));
	strncpy(dlg->pukInf[p3]->puk, puk3, strlen(puk3));
	
	int fg = 3;//表示发牌
	char sfg = (char)fg;
		
	char msg1[100], msg2[100], msg3[100];		
	strcpy(msg1, &sfg);
	strcpy(msg2, &sfg);
	strcpy(msg3, &sfg);

	memcpy(msg1+1, (char*)dlg->pukInf[p1], sizeof(dlg->pukInf));
	memcpy(msg2+1, (char*)dlg->pukInf[p2], sizeof(dlg->pukInf));
	memcpy(msg3+1, (char*)dlg->pukInf[p3], sizeof(dlg->pukInf));
	msg1[99]='\0';
	msg2[99]='\0';
	msg3[99]='\0';	

	int len = sizeof(dlg->pukInf)+1;
	send(msgsock[p1], msg1, len, 0);
	send(msgsock[p2], msg2, len, 0);
	send(msgsock[p3], msg3, len, 0);
}
//===========================================================================================//
void CServerDlg::OnBtnSearch() 
{
	CServerDlg *dlg=(CServerDlg*)AfxGetApp()->GetMainWnd();	
	int num = dlg->m_name.GetCurSel();
	char name[20];
	int len = m_name.GetLBText(num, name);
	dlg->m_Table.Clear();
	dlg->m_scores.Clear();
	for(int i=0; i<20; i++)
	{
		CString na, na2;
		na.Format("%s", dlg->userInf[i]->userName);
		na2.Format("%s", name);
		if(!na.Compare(na2))
		{
			int tableid = dlg->userInf[i]->tableID;
			char st[10];
			_itoa(tableid, st, 10);
			dlg->m_Table.SetWindowText(st);
			int scores = dlg->userInf[i]->scores;
			_itoa(scores, st, 10);
			dlg->m_scores.SetWindowText(st);
			return;
		}
	}
	
}
//===========================================================================================//
void CServerDlg::resetPukInf(int tableid)
{
	CServerDlg *dlg=(CServerDlg*)AfxGetApp()->GetMainWnd();
	strcpy(dlg->pukInf[tableid]->puk,"0");
	dlg->cardsInf[tableid].num		= 0;
	dlg->cardsInf[tableid].point	= 0;
	dlg->cardsInf[tableid].type		= 0;
	dlg->tableInf[tableid].mutiple	= 3;
}
//===========================================================================================//
char *CServerDlg::produceCards()
{
	CServerDlg *dlg=(CServerDlg*)AfxGetApp()->GetMainWnd();	
	int poke[54];
	int poke1[54];	
	int number = 1;
	srand( (unsigned)time( NULL ) );

	for(int i = 1; i<55;i++)
	{
		poke[i-1] = i;
	}

	for(int j = 1; j<55;j++)
	{
		int num = (rand()%(55-j));	
			poke1[j-1] =  poke[num];

		for( int k = num+1;k<55-j; k++)
		{
			poke[k-1]=poke[k];
		}
	}
	char buff[60];
	for(int m=0; m<54; m++)
	{
		char c = (char)poke1[m];
		strcpy(buff+m, &c);		
	}
	return buff;
}
//===========================================================================================//

int CServerDlg::getTableId(int playerId)
{
	CServerDlg *dlg = (CServerDlg*)AfxGetApp()->GetMainWnd();
	return dlg->userInf[playerId]->tableID;
}

int CServerDlg::FindHost(int tableid)
{
	CServerDlg *dlg = (CServerDlg*)AfxGetApp()->GetMainWnd();
	if(dlg->tableInf[tableid].player1 == 1)
	{
		return dlg->userInf[dlg->tableInf[tableid].player1]->userID;
	}
	else if(dlg->tableInf[tableid].player2 == 1)
	{
		return dlg->userInf[dlg->tableInf[tableid].player2]->userID;
	}
	else 
	{
		return dlg->userInf[dlg->tableInf[tableid].player3]->userID;
	}
}

int CServerDlg::GetChangScore(int theUserid, int pNext,int pOther)
{
	CServerDlg *dlg = (CServerDlg*)AfxGetApp()->GetMainWnd();
	int tableid = dlg->userInf[theUserid]->tableID;
		//地主胜
		if(dlg->userInf[theUserid]->userID  == dlg->FindHost(theUserid))
		{
			
			dlg->userInf[theUserid]->scores += 2*dlg->tableInf[tableid].mutiple;
			dlg->userInf[pNext]->scores   -= dlg->tableInf[tableid].mutiple;
			dlg->userInf[pOther]->scores  -= dlg->tableInf[tableid].mutiple;
			ChangeScore[theUserid]           =  2*dlg->tableInf[tableid].mutiple;
			ChangeScore[pNext]             =  -dlg->tableInf[tableid].mutiple;
			ChangeScore[pOther]            =  -dlg->tableInf[tableid].mutiple;
		}
		else
		{
			ChangeScore[theUserid]           =  2*dlg->tableInf[tableid].mutiple;
			//地主败
			dlg->userInf[dlg->FindHost(tableid)]->scores -= 2*dlg->tableInf[tableid].mutiple;
			dlg->userInf[theUserid]->scores			     += dlg->tableInf[tableid].mutiple;
			ChangeScore[theUserid]                          = dlg->tableInf[tableid].mutiple;
			ChangeScore[dlg->FindHost(tableid)]           = -2*dlg->tableInf[tableid].mutiple;
			if(pNext == dlg->FindHost(tableid))
			{
				dlg->userInf[pOther]->scores             += dlg->tableInf[tableid].mutiple;
				ChangeScore[pOther]                       = dlg->tableInf[tableid].mutiple;
			}
			else
			{
				dlg->userInf[pNext]->scores              += dlg->tableInf[tableid].mutiple;
				ChangeScore[pNext]                        = dlg->tableInf[tableid].mutiple;
			}
		}
 return 0;
}

void CServerDlg::WriteDb(int userid)
{
	CServerDlg *dlg = (CServerDlg*)AfxGetApp()->GetMainWnd();
	CString strSQL;
	CString sname = (CString)dlg->userInf[userid]->userName;
	int currentScores = dlg->userInf[userid]->scores;
	CString cScore;
	cScore.Format("%d",currentScores);
	strSQL = "update playerInfo set score=" + cScore + " where name ='"+sname+"'";
	db.ExecuteSQL(strSQL); // 执行
}

void CServerDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	CServerDlg *dlg=(CServerDlg*)AfxGetApp()->GetMainWnd();
	for(int i=0; i<20; i++)
	{
		free(scoreInf[i]);
		free(userInf[i]);
		free(pukInf[i]);	
	}
	CDialog::OnCancel();
}

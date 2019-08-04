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
cardsList mycards;		//�Լ����ϵ���
cardsList sendcards;	//Ҫ�����
cardsList othercards;	//�ϼҴ����

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

BOOL		ask;	//ѯ�ʵ��������������ƴ���
BOOL		selected;//���Ƿ�ѡ��
CRect		roomrect;//����ߴ�
BOOL		show;	//��һ�η���
BOOL 		Right;
CString dir = "images/";
BOOL canhit = FALSE;//����Ƿ�ͣ��λ����
int tid		= 0;	//���������(�Լ������ӣ�
int sid		= 0;	//�������λ�ţ��Լ�����λ�ţ�
int prenum, nextnum;//�ϼҺ��¼�������
int mynum;			//�Լ�����������

int who;			//�ϼ�˭������
int whonum;			//�ϼҳ�������
int major;			//����Ȩ��������ʾ���Ƿ�ǰ���Ҷ�pass
int players;		//�������������
int pok[14][4]	;	//���������

#define login	1
#define sitdown 2
#define wait	3	//�ȴ���Ϸ��ʼ
#define end		4	//�غϽ���
#define wrong	5	//��½ʧ��	
#define gaming	6	//��Ϸ������

int hostsit ;		//��������λ��	
int startsit;		//�㿪ʼ�˵�����λ

int state;

CRect LeftRec, RightRec, DownRec, DeskRec;//��Ч����

typedef struct Tmp
{
	BOOL selected;	//�Ƿ�ѡ��
	int  pk;		//�Ƶ�
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
	case wrong://��δ��½��ʱ��
		{	
			drawface();
			break;
		}
	case login://��½�ɹ�����ʾ����
		{
			display();
			break;
		}
	case sitdown://��ʾ�����ʼ��ť
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
	//***************���ؿؼ�*****************//
	dlg->m_ip.ShowWindow(SW_HIDE);
	dlg->m_name.ShowWindow(SW_HIDE);
	dlg->m_connect.ShowWindow(SW_HIDE);
	dlg->m_exit.ShowWindow(SW_HIDE);
	dlg->m_psd.ShowWindow(SW_HIDE);
	dlg->m_staticIP.ShowWindow(SW_HIDE);
	dlg->m_staticName.ShowWindow(SW_HIDE);
	dlg->m_staticPsd.ShowWindow(SW_HIDE);
	dlg->m_msg.ShowWindow(SW_HIDE);
	strcpy(myname, name);//��¼�Լ�������
	strcpy(myPwd, passWord); 
	dlg->EndModalState();
	//**************���ؿؼ�******************//
	}
	else
	{
		MessageBox("���ֱ�����.....");
		return;
	}	
	client.sin_addr.s_addr=inet_addr(ipaddress);
	client.sin_family=AF_INET;
	client.sin_port=5000;
	//����socket
	clisock=socket(AF_INET,SOCK_STREAM,0);	
	ee=1;
	dlg->SetForegroundWindow();
	Sleep(100);
	//�����߳�
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
	//���ӷ�����
	CTime time, time2;
	time = CTime::GetCurrentTime();
	int t1 = time.GetSecond();
	int t2;
	dlg->m_inf.SetWindowText("������....");		
	Sleep(50);
	s = connect(clisock,(sockaddr*)&(client),sizeof(client));
	t1 = time.GetSecond();	
	while(s == SOCKET_ERROR &&ee!=0)
	{		
		dlg->m_inf.SetWindowText("������-");
		Sleep(20);
		dlg->m_inf.SetWindowText("������--");
		Sleep(20);
		dlg->m_inf.SetWindowText("������---");
		Sleep(20);
		dlg->m_inf.SetWindowText("������----");
		Sleep(20);
		dlg->m_inf.SetWindowText("������-----");
		Sleep(20);
		time2 = CTime::GetCurrentTime();
       	t2 = time2.GetSecond();
		if(abs(t2-t1)/2>5)
		{
			dlg->m_inf.SetWindowText("���ӳ�ʱ�������ԡ���");
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
		int flag = (int)(buff[0]);		//ȡ����Ϣ������				
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
	case 2: //��ǰ�����������λ�Ƿ�����
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
				MessageBox("��λ�������ˣ����");
			}
			break;
		}
	case 3: //�ӷ���������������
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
			state = wait;//��Ϸ��ʼ
			ask = TRUE;
			m_playcard.ShowWindow(SW_HIDE);
			m_pass.ShowWindow(SW_HIDE);
			dlg->m_room.Invalidate();		
			PostMessage(WM_PAINT,NULL, NULL);
			break;
		}
	case 4: //�Ƿ�Ը�⵱����
		{	
			hostsit = (int)buffer[1];
			dealhost();			
			break;
		}
	case 5: //�ϼҳ����ơ�
		{
			othercards.clear();//�Ƚ��ϴ����			
			m_pass.ShowWindow(SW_SHOW);
			m_playcard.ShowWindow(SW_SHOW);			
			dealplay(buffer+1);
			PostMessage(WM_PAINT, NULL, NULL);
			break;
		}
	case 6: //�غϽ�������ʾ����
		{
			int score = (int)buffer[1];
			pukInf.cansend = FALSE;
			pukInf.ishost  = FALSE;	
			CString res = "";
			CDC *pdc = GetDC();
			if(score < 0)
			{
				res.Format("����~~���ֶ���%d��ͭ��",-1*score);		
				pdc->SetTextColor(RGB(205,100,0));
				pdc->SetBkMode(TRANSPARENT);
				pdc->TextOut(250, 300, res);
				ReleaseDC(pdc);
			}
			else 
			{
				res.Format("�����������ˣ���Ӯ��%d��ͭ�壡",score);
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
	case 7: //���ܷ����������Ĵ�����Ϣ�����и�������
		{
			dlg->updateRoom(buffer+1);
			dlg->showRoom();
			break;
		}
	case 8: // �ӷ������������ж��Լ��������Ƿ���ϳ��ƹ���
		{				
			dealsend(buffer+1);
			break;
		}
	case 9: //�ܷ��½ 
		{
			int log = buffer[1];
			if(log==1)//��½�ɹ�������Ϣ����ͼƬ
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
				dlg->MessageBox("�������", NULL, MB_OK);			
			}
			else if(log == 3)
			{				
				state = wrong;				
				dlg->reshow();	
				dlg->Invalidate();
				PostMessage(WM_PAINT, NULL, NULL);
				dlg->MessageBox("�㻹û��ע����",NULL,MB_OK);
			}

			break;
		}
	case 10: //���˵㿪ʼ�ˣ�buffer[1]����λ��
		{
			state = wait;
			startsit = (int)buffer[1];
			break;
		}
	case 11://���˵������ˣ�buffer[1]  ����λ��
		{
			state = gaming;
			hostsit=(int)buffer[1];
			//�������ƶ���ʾ����
			if(hostsit!=sid)//�Լ����ǵ�����ʱ��
			{
				decidehost(hostsit);
			}
			break;
		}
		case 12://���·�����Ϣ
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
//��д������Ϣ
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
//��������
void CClientDlg::display()
{
	CClientDlg *dlg = (CClientDlg *) AfxGetApp()->GetMainWnd();
	CDC *pdc;
	pdc = GetDC();
	dlg->m_player.ShowWindow(SW_SHOW);
	dlg->m_msg.ShowWindow(SW_SHOW);
	SelectObject(BackDC,tablemap);
	SelectObject(HeadDC, headmap);
	for(int j=0; j<4; j++)//������
	{
		for(int i=0; i<4; i++)
		{				
			pdc->BitBlt(i*w+14,j*h+14,w,h,CDC::FromHandle(BackDC),0,0,SRCCOPY);
		//*********����ͷ*********************//
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
		//********����ͷ**********************//			
		}
	}	

	ReleaseDC(pdc);
}
//---------------------------------------------------------------------------------------
//�˳�ʱ������
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
//�����û��б�
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
//���´�����Ϣ
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
	
	if(flag==1)//���˵�½
	{	
		players++;
		userInf[id].userID  = id;
		userInf[id].tableID = -1;
		userInf[id].sitID	= -1;
		userInf[id].scores	= 0;
		userInf[id].Ishost	= -1;
		CString log = "---��½��";
		m_msg.AddString(userInf[id].userName+log);
	}
	else if(flag==2)//�����뿪��Ϸ��
	{		
		userInf[id].tableID = -1;
		userInf[id].sitID	= -1;
		userInf[id].scores	= 0;
		userInf[id].Ishost	= -1;
		CString log = "----վ��������";
		if(tableid==tid)//������Լ�ͬ��
		{
			pukInf.cansend = FALSE;
			state = wait;
		}
		m_msg.AddString(userInf[id].userName+log);
	}
	else if(flag==3)//��������
	{		
		userInf[id].tableID = tableid;
		userInf[id].sitID	= sitid;
		userInf[id].scores	= 0;
		userInf[id].Ishost	= -1;
		CString log = "----ѡ��";
		char st[10];
		_itoa(tableid, st, 10);
		CString log2 = "����������";
		m_msg.AddString(userInf[id].userName+log+st+log2);
	}
	else //�����˳�
	{		
		players--;
		userInf[id].userID	= -1;
		userInf[id].tableID = -1;
		userInf[id].sitID	= -1;
		userInf[id].scores	= 0;
		userInf[id].Ishost	= -1;
		CString log = "----�˳��˴���";
		if(tableid==tid)//������Լ�ͬ��
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
//������ʾ��½����
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
	
	//*********һ��λ�������**************//
	int tmplw1 = curw*150+18+14;
	int tmplw2 = curw*150+48+14;
	int tmplh1 = curh*150+55+14;
	int tmplh2 = curh*150+85+14;
	//*********����λ�����±�**************//
	int tmpdw1 = curw*150+64+14;
	int tmpdw2 = curw*150+94+14;
	int tmpdh1 = curh*150+100+16;
	int tmpdh2 = curh*150+140+16;
	//**********����λ�����ұ�*************//
	int tmprw1 = curw*150+110+14;
	int tmprw2 = curw*150+140+14;
	int tmprh1 = curh*150+55+14;
	int tmprh2 = curh*150+85+14;
	//**********�ж�һ��λ*****************//
	if( (tmplw1<tx)&&(tx<tmplw2) && (tmplh1<ty)&&(ty<tmplh2) )
	{
		note(tmplw1, tmplh1);
		canhit = TRUE;
		sid = 1;
	}
	//**********�ж϶���λ*****************//
	else if((tmpdw1<tx)&&(tx<tmpdw2) && (tmpdh1<ty)&&(ty<tmpdh2))
	{
		note(tmpdw1, tmpdh1);
		canhit = TRUE;
		sid = 2;
	}
	//**********�ж�����λ*****************//
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
//��ʾ��ͷ����ʾ����ƶ�������λ��
//------------------------------------------------------------------
void CClientDlg::note(int x, int y)
{
	CDC *pdc;
	pdc = GetDC();
	SelectObject(BackDC, toumap);
	pdc->BitBlt(x,y,30,30,CDC::FromHandle(BackDC),0,0,SRCCOPY);
}
//-----------------------------------------------------------------
//��ʼ��
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
			AfxMessageBox(cc+"�˿�ûװ��!");
		}	
	}
//********************************************//
	cc = dir+"tablen"+".bmp";
	if(map.loadbmp(cc, &tablemap) == FALSE)
	{
		AfxMessageBox(cc+"����ûװ��!");	}

	cc = dir+"head"+".bmp";
	if(map.loadbmp(cc, &headmap) == FALSE)
	{
		AfxMessageBox(cc+"��ͷûװ����!");
	}	
	cc = dir+"tou"+".bmp";
	if(map.loadbmp(cc, &toumap) == FALSE)
	{
		AfxMessageBox(cc+"Сͷûװ����!");
	}	
	cc = dir+"host.bmp";
	if(map.loadbmp(cc, &hostmap)==FALSE)
	{
		AfxMessageBox(cc+"����ͷû����");
	}
	cc = dir+"start.bmp";
	if(map.loadbmp(cc, &startmap)==FALSE)
	{
		AfxMessageBox(cc+"С��û����");
	}
//*****************************************//
	m_player.InsertColumn(0,"�û���");
	m_player.SetColumnWidth(0,60);
	m_player.InsertColumn(1,"����");
	m_player.SetColumnWidth(1,40);
	m_player.InsertColumn(2,"��λ");
	m_player.SetColumnWidth(2,40);
	m_player.InsertColumn(3,"����");
	m_player.SetColumnWidth(3,60);
//******************************************//
	for(int t=0; t<maxnum; t++)
	{
		userInf[t].tableID = -1;
		userInf[t].scores  = 1;
		userInf[t].sitID   = -1;
		userInf[t].Ishost  = FALSE;
	}
	setrect();//��ʼ����Ч����	
}
//-----------------------------------------------------------------
//˫���������������������
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
//����
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
	//�����ҷ���
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
	//������������
	show = FALSE;
	//������ͷ
//	showhost();		
	//����ͷ����ʾ���˵㿪ʼ��
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
	//������
	SelectObject(BackDC, hostmap);
	if(hostsit!=sid&&(hostsit!=0))//�Լ����ǵ�����ʱ��
	{
		int tmp=(hostsit+1)%3;
		if(tmp==0)
		{
			tmp = 3;
		}
		if(tmp!=sid)//�¼�
		{
			pdc->BitBlt(580, 300, 30, 30, CDC::FromHandle(BackDC),0,0,SRCCOPY);
		}
		else//�ϼ�
		{
			pdc->BitBlt(20, 300, 30, 30, CDC::FromHandle(BackDC),0,0,SRCCOPY);
		}
	}
	else //�Լ��ǵ���
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
		if(startsit!=sid&&(startsit!=0))//���˵㿪ʼ��ʱ��
		{
			int tmp=(startsit+1)%3;
			if(tmp==0)
			{
				tmp = 3;
			}
			if(tmp!=sid)//�¼�
			{
				pdc->BitBlt(500, 300, 20, 20, CDC::FromHandle(BackDC),0,0,SRCCOPY);
			}
			else//�ϼ�
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
	if(MessageBox("��Ը�⵱����ô��", NULL, MB_OKCANCEL)==IDOK)
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
		for(int i=17; i<17+3; i++)//�������
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
			tmpinf[i].pk = *tmp;//���¸�tmpinf��ֵ
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
		state = wait;//�ȴ���Ϸ��ʼ
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
	//�¼���+3
	if(tmp!=sid)
	{
		nextnum+=3;
	}
	//�ϼ���+3
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
	//�ػ�����//
	CBitmap bk;
	bk.LoadBitmap(IDB_BITMAP7);
	SelectObject(BackDC, bk);	
	pdc->BitBlt(130, 450, 370, 100, CDC::FromHandle(BackDC),0,0,SRCCOPY);
	DeleteObject(bk);	
	//���Լ�����
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
	SelectObject(BackDC, cardmap[55]);//�˿˱���
	for(i=0; i<prenum; i++)//���ϼ�
	{		
		pdc->BitBlt(50, 250+prenum/2*15-i*15, cardh, cardw, CDC::FromHandle(BackDC),0,0,SRCCOPY);
	}
	for(i=0; i<nextnum; i++)//���¼�
	{
		pdc->BitBlt(500, 250+nextnum/2*15-i*15, cardh, cardw, CDC::FromHandle(BackDC),0,0,SRCCOPY);
	}
	SelectObject(BackDC, cardmap[61]);//�˿˱���
	for(i=17; i<17+3; i++)//������
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
	//�������������
	for(int i=0; i<maxnum; i++)
	{//start for
		if(userInf[i].tableID==tid)//���Լ�ͬ��
		{//start if
			int id = userInf[i].userID;
			int hisit = userInf[id].sitID;//����ҵ���λ
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
	//���Լ�����
	pdc->TextOut(300, 560, myname);
	ReleaseDC(pdc);
}
//--------------------------------------------------------------------------
void CClientDlg::showit()
{
	CClientDlg *dlg = (CClientDlg *) AfxGetApp()->GetMainWnd();	
	CDC *pdc = GetDC();
	//�ж����·��������Ϸ�������//
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
	int can = (int)buffer[1];//�ܲ��ܳ���	
	int num = (int)buffer[2];//���˳�������
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
		pdc->TextOut(300, 300, "��pass��");
		ReleaseDC(pdc);
		return;
	}
	//���ϼҵ��Ʊ���
	othercards.clear();//�����
	for(int i=0; i<num; i++)
	{
		int card = (int)(buffer[3+i]);
		othercards.push_back(card);
	}
	showit();//��ʾ����Ч��	
}

//-------------------------------------------------------------------------------
//�����ʼ��ť
void CClientDlg::Onstart() 
{
	CClientDlg *dlg = (CClientDlg *) AfxGetApp()->GetMainWnd();	
	CDC *pdc = GetDC();
	int fg		= 3;
	char sfg	= (char)fg;
	//�Լ��㿪ʼ
	SelectObject(BackDC, startmap);
	pdc->SetBkMode(TRANSPARENT);
	pdc->BitBlt(300, 500, 20, 20, CDC::FromHandle(BackDC),0,0,SRCCOPY);			
	send(clisock, &sfg, 1, 0);
	dlg->m_start.ShowWindow(SW_HIDE);
	dlg->m_start.EnableWindow(FALSE);
	ReleaseDC(pdc);
}
//-------------------------------------------------------------------------------
//ѡ��
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
	{//��겻��������
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
			if(sendcards.size()==0)//��ûѡ���Ƶ�ʱ��
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
				if(pukInf.cansend)//����ܳ���
				{
				//���ƣ�����ư�ť����
				}
			}
		}	
		PostMessage(WM_PAINT, NULL, NULL);
	}
god:
	CDialog::OnLButtonDown(nFlags, point);
}
//-------------------------------------------------------------------------------
//���ư�ť
void CClientDlg::Onplaycard() 
{	
	int fg = 5;
	char sfg = (char)fg;
	int filish;
	char msg[50];
	//��Ҫ���������
	sendcards.sort();
	list<int>::iterator fst = sendcards.begin();
	//Ҫ���������
	int sendnum = sendcards.size();
	//�������ɹ�����ʣ������
	int left = mynum - sendnum;
	if(left<=0)
	{
		filish = 1;
	}
	else //û����
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
	memcpy(msg+1, &maj, 1);//����Ȩ
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
	//Ҫ���������
	int sendnum = sendcards.size();
	if(sendnum==0)return;
	if(yes==1)//ͨ�����
	{		
		major = 0;//���¿�ʼ����
		//��������ȥ���������//
		for(int i=0; i<sendnum; i++, fst++)
		{
			int pk = *fst;
			mycards.remove(pk);
		}
		mynum-=sendnum;//��������������
		pukInf.cansend = FALSE;//���Լ�����δ���ܳ���״̬

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
			tmpinf[i].pk = *tmp;//���¸�tmpinf��ֵ
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
		MessageBox("����ȷ���ƣ�");
	}
	ReleaseDC(pdc);

}
//-------------------------------------------------------------------------------
void CClientDlg::Onpass() 
{
	sendcards.clear();
	int fg = 5;
	char sfg = (char)fg;
	int not = 2;//û����
	int n = -1;	//0����
	char no = (char)not;
	char num = (char)n;
	int mj = 2;
	char maj = (char)mj;//�޳���Ȩ
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
//�˳���Ϸ��
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
//�˳�����
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
	for(ln = 0;ln < 14;ln++)//0��ʾ��λ��û����
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
			pok[13][0] = 53;//С��
		}
		else if(*(CurrentCard+k) == 54)
		{
			pok[13][1] = 54;//���
		}
		else
		{
			col = *(CurrentCard+k)/13;//�ƵĻ�ɫ
			if(col == 4)
			{
				col--;
			}
			ln = *(CurrentCard+k)%13-2;//�ƵĴ�С
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
	//����mycards//
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

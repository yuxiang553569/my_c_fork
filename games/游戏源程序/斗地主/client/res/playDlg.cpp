// playDlg.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "playDlg.h"
#include "Loadbmp.h"
#include "clientDlg.h"

#include <string>
#include <list>
#include <algorithm>
using namespace std ;
typedef list<int> cardsList;

cardsList mycards;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CplayDlg dialog


CplayDlg::CplayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CplayDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CplayDlg)
	//}}AFX_DATA_INIT
}


void CplayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CplayDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CplayDlg, CDialog)
	//{{AFX_MSG_MAP(CplayDlg)
	ON_BN_CLICKED(IDC_host, Onhost)
	ON_BN_CLICKED(IDC_nohost, Onnohost)
	ON_BN_CLICKED(IDC_start, Onstart)
	ON_WM_PAINT()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CplayDlg message handlers

BOOL CplayDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	CplayDlg dlg;
	dlg.EndModalState();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CplayDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting	
}

int CplayDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;	
	return 0;
}

void CplayDlg::recvcards(char *cards)
{
	
	CDC *pdc;
	pdc = GetDC();
	//***********读取扑克信息***************//
	pukInf.ishost = ((puk*)cards)->ishost;
	memcpy(pukInf.hostname ,((puk*)cards)->hostname, sizeof(((puk*)cards)->hostname));
	pukInf.cansend	= ((puk*)cards)->cansend;
	memcpy(pukInf.puk, ((puk*)cards)->puk, sizeof(((puk*)cards)->puk));
	//***********读取扑克信息**************//	
/*	for (int i=0; i<17; i++)
	{
		int puk = (int)pukInf.puk[i];
		mycards.push_front(puk);
	}
	
	if(pukInf.cansend==TRUE)//自己是地主的话
	{	
		m_host.ShowWindow(SW_SHOW);
		m_nohost.ShowWindow(SW_SHOW);
	}*/
	char buff[100];
	int ms = 1;	
	BOOL mm = TRUE;
//	ms=connect(clisock,(sockaddr*)&(client),sizeof(client));
	while(ms!=SOCKET_ERROR)
	{	
		
		if(mm)
		{
			CplayDlg play;			
			CClientDlg *dlg = (CClientDlg *) AfxGetApp()->GetMainWnd();	

			mm= FALSE;					
		}
		ms=recv(clisock,buff,100,0);
		int flag = (int)(buff[0]);		//取出信息的类型				
		mymsg(flag, buff+1);		
	}	
	MessageBox("end");
	
		
}

void CplayDlg::showcards()
{
	CDC *pdc = GetDC(); 
	for(int i=0; i<17; i++)
	{
		SelectObject(BackDC, cardmap[(int)pukInf.puk[i]]);
		pdc->BitBlt(20+i*5, 500, cardw, cardh, CDC::FromHandle(BackDC),0,0,SRCCOPY);
	}		
}
void CplayDlg::mymsg(int flag, char *buffer)
{
	MessageBox("i got it");
}

void CplayDlg::Onhost() 
{
	
	
}

void CplayDlg::Onnohost() 
{

	
}

void CplayDlg::Onstart() 
{
	CClientDlg *dlg = (CClientDlg *) AfxGetApp()->GetMainWnd();
	int fg = 3;
	char sfg = (char)fg;
	send(clisock, &sfg, 1, 0);
}





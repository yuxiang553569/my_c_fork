// TetrixBDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TetrixB.h"
#include "TetrixBDlg.h"
#include "assert.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTetrixBDlg dialog

CTetrixBDlg::CTetrixBDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTetrixBDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTetrixBDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	//初始化各DC指针和位图指针
	m_pMemDC		=	new CDC;	
	m_pMemBmp		=	new CBitmap;	
	
	m_pMapDC		=	new CDC; 
	m_pMapBmp		=	new CBitmap;

	m_pTriDC		=	new CDC; 
	m_pTriBmp		=	new CBitmap; 
	
	m_pTriDarkDC	=	new CDC; 
	m_pTriDarkBmp	=	new CBitmap;

	m_pTriDarkCDC	=	new CDC; 
	m_pTriDarkCBmp	=	new CBitmap;

	m_pNoteMapDC		=	new CDC; 
	m_pNoteMapBmp		=	new CBitmap;

	m_pTriRedDC		=	new CDC; 
	m_pTriRedBmp		=	new CBitmap; 


	
}

CTetrixBDlg::~CTetrixBDlg()
{
	delete m_pMemDC;	
	delete m_pMemBmp;	
	
	delete m_pMapDC; 
	delete m_pMapBmp;

	delete m_pTriDC; 
	delete m_pTriBmp;  

	delete m_pTriDarkDC; 
	delete m_pTriDarkBmp;

	delete m_pTriDarkCDC; 
	delete m_pTriDarkCBmp;

	delete m_pNoteMapDC; 
	delete m_pNoteMapBmp;

	delete m_pTriRedDC; 
	delete m_pTriRedBmp;  

}

void CTetrixBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTetrixBDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTetrixBDlg, CDialog)
	//{{AFX_MSG_MAP(CTetrixBDlg)
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_UP, OnButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, OnButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, OnButtonRight)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, OnButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_GAMEOVER, OnButtonGameover)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, OnButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_DIDOWN, OnButtonDidown)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTetrixBDlg message handlers

BOOL CTetrixBDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	CenterWindow(GetDesktopWindow());	// center to the hpc screen

	// TODO: Add extra initialization here
	CDC *pDC = GetDC();

	m_pMemDC->CreateCompatibleDC(pDC);
	m_pMapDC->CreateCompatibleDC(pDC);
	m_pTriDC->CreateCompatibleDC(pDC);
	m_pTriDarkDC->CreateCompatibleDC( pDC );
	m_pTriDarkCDC->CreateCompatibleDC( pDC );
	m_pNoteMapDC->CreateCompatibleDC(pDC);
	m_pTriRedDC->CreateCompatibleDC(pDC);
	
	m_pMemBmp->CreateCompatibleBitmap(pDC, MAPWIDTH, MAPHEIGHT);
	CBitmap* pOldMemBmp = m_pMemDC->SelectObject(m_pMemBmp);

	m_pMapBmp->LoadBitmap(IDB_BITMAP_MAP);
	CBitmap* pOldMapBmp = m_pMapDC->SelectObject(m_pMapBmp);

	m_pTriBmp->LoadBitmap(IDB_BITMAP_TRI);
	CBitmap* pOldTriBmp = m_pTriDC->SelectObject(m_pTriBmp);

	//装载灰色方块位图资源，并载入到对应的DC
	m_pTriDarkBmp->LoadBitmap(IDB_BITMAP_TRIDARK);
	CBitmap* pOldbtridarkbmp = m_pTriDarkDC->SelectObject( m_pTriDarkBmp) ;
	//装载灰色方块位图资源，并载入到对应的DC
	m_pTriDarkCBmp->LoadBitmap(IDB_BITMAP_TRIDARKC);
	CBitmap* pOldbtridarkcbmp = m_pTriDarkCDC->SelectObject( m_pTriDarkCBmp) ;
	
	m_pNoteMapBmp->LoadBitmap(IDB_BITMAP_NOTEMAP);
	CBitmap* pOldNoteMapBmp = m_pNoteMapDC->SelectObject(m_pNoteMapBmp);

	m_pTriRedBmp->LoadBitmap(IDB_BITMAP_TRIRED);
	CBitmap* pOldTriRedBmp = m_pTriRedDC->SelectObject(m_pTriRedBmp);

	ReleaseDC(pDC);

	return TRUE;  // return TRUE  unless you set the focus to a control
}



void CTetrixBDlg::OnButtonStart() 
{
	// TODO: Add your control notification handler code here
	SetTimer(1,1000, NULL);
	int gflag = m_tetrixGame.GameStart();
	if( gflag != 0 )
	{
		MessageBox( _T("Fail to Generate a Tetrix!"), _T("Error!"), MB_OK );
		return;
	}
	UpdateControl();
	DrawAll();
	DrawNote();
}


void CTetrixBDlg::OnButtonUp() 
{
	// TODO: Add your control notification handler code here
	if(0 == m_tetrixGame.DoRotate())
	{
		//重绘游戏区
		DrawAll();
	}
}

void CTetrixBDlg::DrawAll()
{
	//获取系统的绘图DC
	CDC* pDC = GetDC();							
		//将容器底图的DC全部粘贴到内存DC
	m_pMemDC->BitBlt( 0, 0, MAPWIDTH, MAPHEIGHT, 
						m_pMapDC, 0, 0, SRCCOPY );
	//运行测试程序第一步，将生成的方块画在游戏容器中
	for( INT i = 0; i < XLEN; i++ )
		for( INT j = 0; j < YLEN; j++ )
		{
			INT xpos = i * TETRIXLEN;
			INT ypos = j * TETRIXLEN;
			if(m_tetrixGame.JudgeMatrixStatus(i,j, RUNNING))
				m_pMemDC->BitBlt( xpos, ypos, TETRIXLEN, TETRIXLEN,
					m_pTriDC, 0, 0, SRCCOPY );
			else
				if(m_tetrixGame.JudgeMatrixStatus(i,j, STOPPING))
				m_pMemDC->BitBlt( xpos, ypos, TETRIXLEN, TETRIXLEN,
					m_pTriDarkDC, 0, 0, SRCCOPY );
				else
					if( m_tetrixGame.JudgeMatrixStatus(i,j, CLEARING))
						m_pMemDC->BitBlt( xpos, ypos, TETRIXLEN, TETRIXLEN,
							m_pTriDarkCDC, 0, 0, SRCCOPY );
		}
	//将内存DC全部粘贴到系统DC，并在左边和上边各留出20各像素的宽度
	pDC->BitBlt( LEFTSPAN, TOPSPAN, MAPWIDTH, MAPHEIGHT, m_pMemDC, 
					0, 0, SRCCOPY );
	ReleaseDC(pDC);
}

void CTetrixBDlg::OnButtonLeft() 
{
	// TODO: Add your control notification handler code here
	if(0 == m_tetrixGame.GoLeft())
	{
		//重绘游戏区
		DrawAll();
	}
}

void CTetrixBDlg::OnButtonRight() 
{
	// TODO: Add your control notification handler code here
	if(0 == m_tetrixGame.GoRight())
	{
		//重绘游戏区
		DrawAll();
	}
}

void CTetrixBDlg::OnButtonDown() 
{
	// TODO: Add your control notification handler code here
	SINT res = m_tetrixGame.DoDrop();
	if( ( res == 3 ) || ( res == 5 ) )		//出下界或重叠
	{
		//将停止的方块的位置设置为STOPPING
		SINT arsize = m_tetrixGame.PrepareClear();
		if(arsize > 0)
		{
			m_tetrixGame.SetClearStatus(CLEARING);
			DrawAll();
			Sleep(300);
			m_tetrixGame.SetClearStatus(BLANK);
			DrawAll();
			Sleep(200);

			m_tetrixGame.DoClear();
			DrawAll();
			Sleep(300);

			SINT flagu = m_tetrixGame.UpdateScoreAndLevel();
			if(flagu == 0)
			{
				//重新设定时间间隔以适合不同等级
				INT interval=(INT)(1000 / m_tetrixGame.GetGameLevel());
				//重新定义记时器  
				SetTimer(1, interval, NULL); 
			}
			UpdateControl();
		}
		SINT flag = m_tetrixGame.GenNew();
		if( 1 == flag)
		{
			KillTimer(1);
			MessageBox( _T("Game Over!"), _T("NOTING!"), MB_OK );
		}
	}
	else 
		if(res != 0)
			return;
	//重绘游戏区
	DrawAll();
	DrawNote();
}




void CTetrixBDlg::OnButtonGameover() 
{
	// TODO: Add your control notification handler code here
	m_tetrixGame.GameOver();
	KillTimer(1);
	MessageBox( _T("Game Over!"), _T("NOTING!"), MB_OK );
			
}

void CTetrixBDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent == 1)
	{
		if(m_tetrixGame.GetGameStatus() == GAMERUNNING)
			OnButtonDown();
	}
	CDialog::OnTimer(nIDEvent);
}

void CTetrixBDlg::OnButtonPause() 
{
	// TODO: Add your control notification handler code here
	if(m_tetrixGame.GetGameStatus() == GAMERUNNING)
		m_tetrixGame.SetGameStatus(GAMEPAUSE);
	else
		if(m_tetrixGame.GetGameStatus() == GAMEPAUSE)
			m_tetrixGame.SetGameStatus(GAMERUNNING);
}


void CTetrixBDlg::UpdateControl(void)
{
	CString sv;
	sv.Format( _T("%d"), (INT)m_tetrixGame.GetGameLevel());
	SetDlgItemText( IDC_STATIC_LEVEL, sv );//显示等级数
	sv.Format( _T("%d"), (INT)m_tetrixGame.GetGameScore());
	SetDlgItemText(IDC_STATIC_SCORE, sv );//显示分数
}


void CTetrixBDlg::DrawNote()
{
	//获取系统的绘图DC
	CDC* pDC = GetDC();							
	//将视图区域底图的DC全部粘贴到pDC
	pDC->BitBlt( NOTELEFTSPAN, NOTETOPSPAN, NOTEMAPWIDTH, NOTEMAPHEIGHT, 
						m_pNoteMapDC, 0, 0, SRCCOPY );
	//将提示方块画在pDC上
	for( INT i =1;  i < 5; i++ )
	{
		INT xpos = m_tetrixGame.GetNoteTriXPos(i) * TETRIXLEN;
		INT ypos = m_tetrixGame.GetNoteTriYPos(i) * TETRIXLEN;
		pDC->BitBlt( NOTELEFTSPAN + xpos, NOTETOPSPAN + ypos, 
			TETRIXLEN, TETRIXLEN, m_pTriRedDC, 0, 0, SRCCOPY );
	}	
	ReleaseDC(pDC);
}

void CTetrixBDlg::OnButtonDidown() 
{
	// TODO: Add your control notification handler code here
	SINT res = m_tetrixGame.DoDirectDrop();
	if( ( res == 3 ) || ( res == 5 ) )		//出下界或重叠
	{
		//将停止的方块的位置设置为STOPPING
		SINT arsize = m_tetrixGame.PrepareClear();
		if(arsize > 0)
		{
			m_tetrixGame.SetClearStatus(CLEARING);
			DrawAll();
			Sleep(300);
			m_tetrixGame.SetClearStatus(BLANK);
			DrawAll();
			Sleep(200);

			m_tetrixGame.DoClear();
			DrawAll();
			Sleep(300);

			SINT flagu = m_tetrixGame.UpdateScoreAndLevel();
			if(flagu == 0)
			{
				//重新设定时间间隔以适合不同等级
				INT interval=(INT)(1000 / m_tetrixGame.GetGameLevel());
				//重新定义记时器  
				SetTimer(1, interval, NULL); 
			}
			UpdateControl();
		}
		SINT flag = m_tetrixGame.GenNew();
		if( 1 == flag)
		{
			KillTimer(1);
			MessageBox( _T("Game Over!"), _T("NOTING!"), MB_OK );
		}
	}
	else 
		if(res != 0)
			return;
	//重绘游戏区
	DrawAll();
	DrawNote();
}

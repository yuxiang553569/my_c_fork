// chessDlg.cpp : implementation file
//

#include "stdafx.h"
#include "chess.h"
#include "chessDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChessDlg dialog

#define BORDERWIDTH			15 //棋盘(左右)边缘的宽度
#define BORDERHEIGHT		14 //棋盘(上下)边缘的高度
#define GRILLEWIDTH			39 //棋盘上每个格子的高度
#define GRILLEHEIGHT		39 //棋盘上每个格子的宽度
//定义常量保存棋盘的初始状态
const BYTE InitChessBoard[10][9]=
{
	{B_CAR,   B_HORSE, B_ELEPHANT, B_BISHOP, B_KING,  B_BISHOP, B_ELEPHANT, B_HORSE, B_CAR},
	{NOCHESS, NOCHESS, NOCHESS,    NOCHESS,  NOCHESS, NOCHESS,  NOCHESS,    NOCHESS, NOCHESS},
	{NOCHESS, B_CANON, NOCHESS,    NOCHESS,  NOCHESS, NOCHESS,  NOCHESS,    B_CANON, NOCHESS},
	{B_PAWN,  NOCHESS, B_PAWN,     NOCHESS,  B_PAWN,  NOCHESS,  B_PAWN,     NOCHESS, B_PAWN},
	{NOCHESS, NOCHESS, NOCHESS,    NOCHESS,  NOCHESS, NOCHESS,  NOCHESS,    NOCHESS, NOCHESS},
	
	{NOCHESS, NOCHESS, NOCHESS,    NOCHESS,  NOCHESS, NOCHESS,  NOCHESS,    NOCHESS, NOCHESS},
	{R_PAWN,  NOCHESS, R_PAWN,     NOCHESS,  R_PAWN,  NOCHESS,  R_PAWN,     NOCHESS, R_PAWN},
	{NOCHESS, R_CANON, NOCHESS,    NOCHESS,  NOCHESS, NOCHESS,  NOCHESS,    R_CANON, NOCHESS},
	{NOCHESS, NOCHESS, NOCHESS,    NOCHESS,  NOCHESS, NOCHESS,  NOCHESS,    NOCHESS, NOCHESS},
	{R_CAR,   R_HORSE, R_ELEPHANT, R_BISHOP, R_KING,  R_BISHOP, R_ELEPHANT, R_HORSE, R_CAR}
};

CChessDlg::CChessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChessDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChessDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChessDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_NODECOUNT,m_OutputInfo);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CChessDlg, CDialog)
	//{{AFX_MSG_MAP(CChessDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_NEWGAME, OnBtnNewgame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChessDlg message handlers

BOOL CChessDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//创建含有棋子图形的ImgList,用于绘制棋子
	m_Chessman.Create(IDB_CHESSMAN,36,14,RGB(0,255,0));
	//下面代码取棋盘的宽,搞
	BITMAP	BitMap;
	m_BoardBmp.LoadBitmap(IDB_CHESSBOARD);
	//取BitMap对象
	m_BoardBmp.GetBitmap(&BitMap);
	//棋盘宽度
	m_nBoardWidth = BitMap.bmWidth;
	//棋盘高度
	m_nBoardHeight = BitMap.bmHeight;
	m_BoardBmp.DeleteObject();
	//初始化棋盘
	memcpy(m_ChessBoard,InitChessBoard,90);
	CMoveGenerator	*pMG;
	CEveluation		*pEvel;
	//创建负极大值搜索引擎
	m_pSE = new CNegaMaxEngine;
	//创建走法产生器
	pMG = new CMoveGenerator;
	//创建估值核心
	pEvel = new CEveluation;

	//设定搜索层数为3
	m_pSE->SetSearchDepth(3);
	//给搜索引擎设定走法产生器
	m_pSE->SetMoveGenerator(pMG);
	//给搜索引擎设定估值核心
	m_pSE->SetEveluator(pEvel);
	//将移动的棋子清空
	m_MoveChess.nChessID = NOCHESS;


	//加载界面库
	ClassXP = NULL;
	HMODULE	ClassXPModule;
	ClassXPModule = LoadLibrary("ClassXP.dll");
	if(!ClassXPModule)
	{
		MessageBox("加载看界面库失败,这可能影响界面!");
	}
	else
	{
		ClassXP = (CLASSXP)GetProcAddress(ClassXPModule,"ClassXP");
		ClassXP(NULL,TRUE);
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CChessDlg::OnPaint() 
{
	//相应WM_PAINT 消息,绘制棋盘,棋子
	CPaintDC dc(this);
	CDC		 MemDC;
	int		 i,j;
	POINT	 pt;
	CBitmap  *pOldBmp;
	MemDC.CreateCompatibleDC(&dc);
	m_BoardBmp.LoadBitmap(IDB_CHESSBOARD);
	pOldBmp = MemDC.SelectObject(&m_BoardBmp);
	
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (m_ChessBoard[i][j] == NOCHESS)
				continue;
			pt.x = j * GRILLEHEIGHT + 14;
			pt.y = i * GRILLEWIDTH + 15;
			m_Chessman.Draw(&MemDC, m_ChessBoard[i][j] - 1, pt, ILD_TRANSPARENT);		
		}
	}
	//绘制用户正在拖动的棋子
	if (m_MoveChess.nChessID != NOCHESS)
			m_Chessman.Draw(&MemDC, m_MoveChess.nChessID - 1, 
			m_MoveChess.ptMovePoint, ILD_TRANSPARENT);
	//将绘制内容刷新到屏幕
	dc.BitBlt(0,0,m_nBoardWidth,m_nBoardHeight,
		&MemDC,0,0,SRCCOPY);
	//恢复内存DC的原位图
	MemDC.SelectObject(&pOldBmp);	
	//释放内存DC
	MemDC.DeleteDC();
	//删除棋盘位图对象
	m_BoardBmp.DeleteObject();

/*	CPaintDC dc(this);
	CDC MemDC;
	int i, j;
	POINT pt;
	CBitmap *pOldBmp;
	
	MemDC.CreateCompatibleDC( &dc );
	m_BoardBmp.LoadBitmap(IDB_CHESSBOARD);
	pOldBmp = MemDC.SelectObject(&m_BoardBmp);
	for (i = 0; i < 10; i++)
		for (j = 0; j < 9; j++)
		{
			if (m_ChessBoard[i][j] == NOCHESS)
				continue;
			pt.x = j*GRILLEHEIGHT+14;
			pt.y = i*GRILLEWIDTH+15;
			m_Chessman.Draw(&MemDC, m_ChessBoard[i][j]-1, pt, ILD_TRANSPARENT);		
		}
		if (m_MoveChess.nChessID != NOCHESS)
			m_Chessman.Draw(&MemDC, m_MoveChess.nChessID - 1, m_MoveChess.ptMovePoint, ILD_TRANSPARENT);		
		
		dc.BitBlt(0, 0, m_nBoardWidth, m_nBoardHeight, &MemDC, 0, 0, SRCCOPY);
		MemDC.SelectObject(&pOldBmp);
		MemDC.DeleteDC();
		m_BoardBmp.DeleteObject();*/

/*
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
	}*/
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CChessDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//鼠标左键按下的处理,WM_LBUTTONDOWN的相应函数
void CChessDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int x,y;
	//将坐标换算成棋盘上的格子
	y = (point.y - 14) / GRILLEHEIGHT;
	x = (point.x - 15) / GRILLEWIDTH;
	//备份当前棋盘
	memcpy(m_BackupChessBoard,m_ChessBoard,90);
	//判断鼠标是否在棋盘内,并且点钟了红方(用户)棋子
	if(point.x > 0 && point.y > 0 && point.x < m_nBoardWidth
		&& point.y < m_nBoardHeight && IsRed(m_ChessBoard[y][x]))
	{
		//备份棋盘
		memcpy(m_BackupChessBoard,m_ChessBoard,90);
		m_ptMoveChess.x = x;
		m_ptMoveChess.y = y;
		m_MoveChess.nChessID = m_ChessBoard[y][x];
		//将该棋子原位置棋子去掉
		m_ChessBoard[m_ptMoveChess.y][m_ptMoveChess.x] = NOCHESS;
		//让棋子中点坐标位于鼠标所在点
		point.x -= 18;
		point.y -= 18;
		m_MoveChess.ptMovePoint = point;
		//重绘屏幕
		InvalidateRect(NULL,FALSE);
		UpdateWindow();
		SetCapture();
	}
	CDialog::OnLButtonDown(nFlags, point);
}

//全局变量申明,用于统计叶子节点数目
extern int count;	
//鼠标左键松开时的处理,WM_LBUTTONUP的相应函数
void CChessDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	BOOL bTurnSide = FALSE;
	int timecount;
	int x,y;
	//将坐标换算成棋盘上的格子
	y = (point.y - 14) / GRILLEHEIGHT;
	x = (point.x - 14) / GRILLEWIDTH;
	//判断是否有移动棋子,并且该棋子的移动是一个合法走法
	if(m_MoveChess.nChessID && CMoveGenerator::IsValidMove(m_BackupChessBoard,
		m_ptMoveChess.x,m_ptMoveChess.y,x,y))
	{
		m_ChessBoard[y][x] = m_MoveChess.nChessID;
		bTurnSide = TRUE;
	}
	else
		//恢复移动 钱的棋盘状态
		memcpy(m_ChessBoard,m_BackupChessBoard,90);
	//将移动的棋子清空
	m_MoveChess.nChessID = NOCHESS;
	//重绘屏幕
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
	//释放鼠标焦点
	ReleaseCapture();

	if(bTurnSide == TRUE)
	{
		//取初始化时间
		timecount = GetTickCount();
		//让电脑走下一步
		m_pSE->SearchAGoodMove(m_ChessBoard);	
		CString sNodeCount;
		//将电脑花费的时间,评估的节点数格式化成一个字符串
		sNodeCount.Format("电脑共花费:%d毫秒, 评估:%d个走法!",
			GetTickCount() - timecount,count);
		//输出上述信息
		m_OutputInfo.SetWindowText(sNodeCount);
	}
	//计数器清零
	count = 0;
	//重绘屏幕
	InvalidateRect(NULL,FALSE);
	UpdateWindow();

	CDialog::OnLButtonUp(nFlags, point);
}

//WM_MOUSEMOVE的相应函数
void CChessDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_MoveChess.nChessID)
	{
		//防止将棋子拖出棋盘
		if(point.x < 15) //左面
			point.x = 15;
		if(point.y < 15) //上面
			point.y = 15;
		if(point.x > m_nBoardWidth -15) //右边
			point.x = m_nBoardWidth -15;
		if(point.y > m_nBoardHeight - 15) //下面
			point.y = m_nBoardHeight - 15;

		//让棋子的中心位于鼠标所在处
		point.x -= 18;
		point.y -= 18;
		//保存移动棋子的坐标
		m_MoveChess.ptMovePoint =point;
		//刷新窗口
		InvalidateRect(NULL,FALSE);
		//立即刷新
		UpdateWindow();

	}
	CDialog::OnMouseMove(nFlags, point);
}

void CChessDlg::OnBtnNewgame() 
{
	// TODO: Add your control notification handler code here
	CMoveGenerator  *pMG;
	CEveluation	    *pEvel;
	//创建对话框
	CNewGame		newGameDlg;
	if(newGameDlg.DoModal() == IDOK)
	{
		//用户做了新选择
		if(m_pSE)
			//释放旧的搜索引擎
			delete m_pSE;
		//以后添加引擎时候用到switch选择引擎
		//目前只有负极大值引擎
		switch(newGameDlg.GetSelectedEngine())
		{
		case 0:
			m_pSE = new CNegaMaxEngine;
			break;

		default:
			m_pSE = new CNegaMaxEngine;
			break;
		}
		//设置搜索深度
		m_pSE->SetSearchDepth(newGameDlg.GetSelectedPly());
		pEvel = new CEveluation;
	}
	else
	{
		//维持原状.不重新开始
		return;
	}
	//初始化棋盘
	memcpy(m_ChessBoard,InitChessBoard,90);
	//清楚移动棋子
	m_MoveChess.nChessID = NOCHESS;
	//创建走法产生器
	pMG = new CMoveGenerator;
	//将走法传声器传给搜索引擎
	m_pSE->SetMoveGenerator(pMG);
	//将估值核心传给搜索引擎
	m_pSE->SetEveluator(pEvel);
	//刷新窗口
	InvalidateRect(NULL,FALSE);
	//立即刷新
	UpdateWindow();
	
}

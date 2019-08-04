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

#define BORDERWIDTH			15 //����(����)��Ե�Ŀ��
#define BORDERHEIGHT		14 //����(����)��Ե�ĸ߶�
#define GRILLEWIDTH			39 //������ÿ�����ӵĸ߶�
#define GRILLEHEIGHT		39 //������ÿ�����ӵĿ��
//���峣���������̵ĳ�ʼ״̬
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
	//������������ͼ�ε�ImgList,���ڻ�������
	m_Chessman.Create(IDB_CHESSMAN,36,14,RGB(0,255,0));
	//�������ȡ���̵Ŀ�,��
	BITMAP	BitMap;
	m_BoardBmp.LoadBitmap(IDB_CHESSBOARD);
	//ȡBitMap����
	m_BoardBmp.GetBitmap(&BitMap);
	//���̿��
	m_nBoardWidth = BitMap.bmWidth;
	//���̸߶�
	m_nBoardHeight = BitMap.bmHeight;
	m_BoardBmp.DeleteObject();
	//��ʼ������
	memcpy(m_ChessBoard,InitChessBoard,90);
	CMoveGenerator	*pMG;
	CEveluation		*pEvel;
	//����������ֵ��������
	m_pSE = new CNegaMaxEngine;
	//�����߷�������
	pMG = new CMoveGenerator;
	//������ֵ����
	pEvel = new CEveluation;

	//�趨��������Ϊ3
	m_pSE->SetSearchDepth(3);
	//�����������趨�߷�������
	m_pSE->SetMoveGenerator(pMG);
	//�����������趨��ֵ����
	m_pSE->SetEveluator(pEvel);
	//���ƶ����������
	m_MoveChess.nChessID = NOCHESS;


	//���ؽ����
	ClassXP = NULL;
	HMODULE	ClassXPModule;
	ClassXPModule = LoadLibrary("ClassXP.dll");
	if(!ClassXPModule)
	{
		MessageBox("���ؿ������ʧ��,�����Ӱ�����!");
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
	//��ӦWM_PAINT ��Ϣ,��������,����
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
	//�����û������϶�������
	if (m_MoveChess.nChessID != NOCHESS)
			m_Chessman.Draw(&MemDC, m_MoveChess.nChessID - 1, 
			m_MoveChess.ptMovePoint, ILD_TRANSPARENT);
	//����������ˢ�µ���Ļ
	dc.BitBlt(0,0,m_nBoardWidth,m_nBoardHeight,
		&MemDC,0,0,SRCCOPY);
	//�ָ��ڴ�DC��ԭλͼ
	MemDC.SelectObject(&pOldBmp);	
	//�ͷ��ڴ�DC
	MemDC.DeleteDC();
	//ɾ������λͼ����
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

//���������µĴ���,WM_LBUTTONDOWN����Ӧ����
void CChessDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int x,y;
	//�����껻��������ϵĸ���
	y = (point.y - 14) / GRILLEHEIGHT;
	x = (point.x - 15) / GRILLEWIDTH;
	//���ݵ�ǰ����
	memcpy(m_BackupChessBoard,m_ChessBoard,90);
	//�ж�����Ƿ���������,���ҵ����˺췽(�û�)����
	if(point.x > 0 && point.y > 0 && point.x < m_nBoardWidth
		&& point.y < m_nBoardHeight && IsRed(m_ChessBoard[y][x]))
	{
		//��������
		memcpy(m_BackupChessBoard,m_ChessBoard,90);
		m_ptMoveChess.x = x;
		m_ptMoveChess.y = y;
		m_MoveChess.nChessID = m_ChessBoard[y][x];
		//��������ԭλ������ȥ��
		m_ChessBoard[m_ptMoveChess.y][m_ptMoveChess.x] = NOCHESS;
		//�������е�����λ��������ڵ�
		point.x -= 18;
		point.y -= 18;
		m_MoveChess.ptMovePoint = point;
		//�ػ���Ļ
		InvalidateRect(NULL,FALSE);
		UpdateWindow();
		SetCapture();
	}
	CDialog::OnLButtonDown(nFlags, point);
}

//ȫ�ֱ�������,����ͳ��Ҷ�ӽڵ���Ŀ
extern int count;	
//�������ɿ�ʱ�Ĵ���,WM_LBUTTONUP����Ӧ����
void CChessDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	BOOL bTurnSide = FALSE;
	int timecount;
	int x,y;
	//�����껻��������ϵĸ���
	y = (point.y - 14) / GRILLEHEIGHT;
	x = (point.x - 14) / GRILLEWIDTH;
	//�ж��Ƿ����ƶ�����,���Ҹ����ӵ��ƶ���һ���Ϸ��߷�
	if(m_MoveChess.nChessID && CMoveGenerator::IsValidMove(m_BackupChessBoard,
		m_ptMoveChess.x,m_ptMoveChess.y,x,y))
	{
		m_ChessBoard[y][x] = m_MoveChess.nChessID;
		bTurnSide = TRUE;
	}
	else
		//�ָ��ƶ� Ǯ������״̬
		memcpy(m_ChessBoard,m_BackupChessBoard,90);
	//���ƶ����������
	m_MoveChess.nChessID = NOCHESS;
	//�ػ���Ļ
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
	//�ͷ���꽹��
	ReleaseCapture();

	if(bTurnSide == TRUE)
	{
		//ȡ��ʼ��ʱ��
		timecount = GetTickCount();
		//�õ�������һ��
		m_pSE->SearchAGoodMove(m_ChessBoard);	
		CString sNodeCount;
		//�����Ի��ѵ�ʱ��,�����Ľڵ�����ʽ����һ���ַ���
		sNodeCount.Format("���Թ�����:%d����, ����:%d���߷�!",
			GetTickCount() - timecount,count);
		//���������Ϣ
		m_OutputInfo.SetWindowText(sNodeCount);
	}
	//����������
	count = 0;
	//�ػ���Ļ
	InvalidateRect(NULL,FALSE);
	UpdateWindow();

	CDialog::OnLButtonUp(nFlags, point);
}

//WM_MOUSEMOVE����Ӧ����
void CChessDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_MoveChess.nChessID)
	{
		//��ֹ�������ϳ�����
		if(point.x < 15) //����
			point.x = 15;
		if(point.y < 15) //����
			point.y = 15;
		if(point.x > m_nBoardWidth -15) //�ұ�
			point.x = m_nBoardWidth -15;
		if(point.y > m_nBoardHeight - 15) //����
			point.y = m_nBoardHeight - 15;

		//�����ӵ�����λ��������ڴ�
		point.x -= 18;
		point.y -= 18;
		//�����ƶ����ӵ�����
		m_MoveChess.ptMovePoint =point;
		//ˢ�´���
		InvalidateRect(NULL,FALSE);
		//����ˢ��
		UpdateWindow();

	}
	CDialog::OnMouseMove(nFlags, point);
}

void CChessDlg::OnBtnNewgame() 
{
	// TODO: Add your control notification handler code here
	CMoveGenerator  *pMG;
	CEveluation	    *pEvel;
	//�����Ի���
	CNewGame		newGameDlg;
	if(newGameDlg.DoModal() == IDOK)
	{
		//�û�������ѡ��
		if(m_pSE)
			//�ͷžɵ���������
			delete m_pSE;
		//�Ժ��������ʱ���õ�switchѡ������
		//Ŀǰֻ�и�����ֵ����
		switch(newGameDlg.GetSelectedEngine())
		{
		case 0:
			m_pSE = new CNegaMaxEngine;
			break;

		default:
			m_pSE = new CNegaMaxEngine;
			break;
		}
		//�����������
		m_pSE->SetSearchDepth(newGameDlg.GetSelectedPly());
		pEvel = new CEveluation;
	}
	else
	{
		//ά��ԭ״.�����¿�ʼ
		return;
	}
	//��ʼ������
	memcpy(m_ChessBoard,InitChessBoard,90);
	//����ƶ�����
	m_MoveChess.nChessID = NOCHESS;
	//�����߷�������
	pMG = new CMoveGenerator;
	//���߷�������������������
	m_pSE->SetMoveGenerator(pMG);
	//����ֵ���Ĵ�����������
	m_pSE->SetEveluator(pEvel);
	//ˢ�´���
	InvalidateRect(NULL,FALSE);
	//����ˢ��
	UpdateWindow();
	
}

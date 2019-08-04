// NewGame.cpp : implementation file
//

#include "stdafx.h"
#include "chess.h"
#include "NewGame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewGame dialog


CNewGame::CNewGame(CWnd* pParent /*=NULL*/)
	: CDialog(CNewGame::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewGame)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CNewGame::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewGame)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_PLY,m_SetPly);
	DDX_Control(pDX,IDC_LISTENGINE,m_SearchEngineList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewGame, CDialog)
	//{{AFX_MSG_MAP(CNewGame)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewGame message handlers
void CNewGame::OnOK()
{
	//�����û�ѡ��������������
	m_nSelectedEngine = m_SearchEngineList.GetCurSel();
	//�����û�ѡ����������
	m_nSelectedPly = m_SetPly.GetPos();
	CDialog::OnOK();
}

BOOL CNewGame::OnInitDialog()
{
	CDialog::OnInitDialog();
		//��ListBox�м��븺����ֵ��������
		m_SearchEngineList.AddString("������ֵ��������");
		m_SearchEngineList.SetCurSel(0);	//Ĭ��ѡ���һ������
		m_SetPly.SetRange(1,10);	//�趨������ȷ�Χ
		m_SetPly.SetPos(3);	//Ĭ�ϵ��������

		return TRUE;
}

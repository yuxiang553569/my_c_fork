// chessDlg.h : header file
//

#if !defined(AFX_CHESSDLG_H__0D47287F_4EE8_495F_8ECA_59C8265969F5__INCLUDED_)
#define AFX_CHESSDLG_H__0D47287F_4EE8_495F_8ECA_59C8265969F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "define.h"
#include "SearchEngine.h"
#include "NegaMaxEngine.h"
#include "NewGame.h"
#include "MoveGenerator.h"

typedef struct _movechess
{
	BYTE	nChessID;
	POINT	ptMovePoint;
}MOVECHESS;

/////////////////////////////////////////////////////////////////////////////
// CChessDlg dialog

class CChessDlg : public CDialog
{
// Construction
public:
	CChessDlg(CWnd* pParent = NULL);	// standard constructor

	//���ý����
	typedef BOOL (__stdcall *CLASSXP)(HWND,BOOL);
	CLASSXP ClassXP;

// Dialog Data
	//{{AFX_DATA(CChessDlg)
	enum { IDD = IDD_CHESS_DIALOG };
		// NOTE: the ClassWizard will add data members here
	CStatic	m_OutputInfo;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChessDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CChessDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBtnNewgame();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	//������������.������ʾ����
	BYTE		m_ChessBoard[10][9];
	//������������.���ڳ���ָ�
	BYTE		m_BackupChessBoard[10][9];
	//���ڱ��浱ǰ����ק�����ӵĽṹ
	MOVECHESS	m_MoveChess;
	//���뱣�浱ǰ����ק�����ӵ�λ��
	POINT		m_ptMoveChess;	
	//������ʾ����
	CBitmap		m_BoardBmp;
	//�û��������ӵ�ImageList����
	CImageList	m_Chessman;
	//���̸߶�
	int			m_nBoardWidth;
	//���̿��
	int			m_nBoardHeight;
	//��������ָ��
	CSearchEngine	*m_pSE;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHESSDLG_H__0D47287F_4EE8_495F_8ECA_59C8265969F5__INCLUDED_)

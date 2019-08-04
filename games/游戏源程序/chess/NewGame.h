#if !defined(AFX_NEWGAME_H__49657271_EDBE_4E89_AA79_0E36B1E69B4D__INCLUDED_)
#define AFX_NEWGAME_H__49657271_EDBE_4E89_AA79_0E36B1E69B4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewGame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewGame dialog

class CNewGame : public CDialog
{
// Construction
public:
	CNewGame(CWnd* pParent = NULL);   // standard constructor

	//ȡ�û�ѡ�е������������
	int GetSelectedEngine() {return m_nSelectedEngine; };
	//ȥ�û�ѡ�е��������
	int GetSelectedPly(){return m_nSelectedPly; };

// Dialog Data
	//{{AFX_DATA(CNewGame)
	enum { IDD = IDD_NEWGAME };
	CSpinButtonCtrl		m_SetPly;	//SpinButton����
	CListBox			m_SearchEngineList;	//�����б����
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewGame)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	int m_nSelectedEngine;	//��¼�û�ѡ�������
	int m_nSelectedPly;		//��¼�û�ѡ�����������
	// Generated message map functions
	//{{AFX_MSG(CNewGame)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWGAME_H__49657271_EDBE_4E89_AA79_0E36B1E69B4D__INCLUDED_)

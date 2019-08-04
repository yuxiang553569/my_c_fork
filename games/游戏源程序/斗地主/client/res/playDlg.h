#if !defined(AFX_PLAYDLG_H__BC89FF2A_9644_4AE2_A4D0_7B3809821951__INCLUDED_)
#define AFX_PLAYDLG_H__BC89FF2A_9644_4AE2_A4D0_7B3809821951__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// playDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CplayDlg dialog

class CplayDlg : public CDialog
{
// Construction
public:
	CplayDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CplayDlg)
	enum { IDD = IDD_PlayDlg };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CplayDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CplayDlg)
	virtual BOOL OnInitDialog();
	afx_msg void Onhost();
	afx_msg void Onnohost();
	afx_msg void Onstart();
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void recvcards(char *cards);	//���շ���
	void showcards();				//��ʾ�˿���������
	void playcards();				//�Լ�����
	void showpre(char *cards);		//��ʾ�ϼҴ����
	void mymsg(int flag, char *buffer);
};

//UINT mythread(LPVOID);
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYDLG_H__BC89FF2A_9644_4AE2_A4D0_7B3809821951__INCLUDED_)

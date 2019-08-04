// TetrixBDlg.h : header file
//

#if !defined(AFX_TETRIXBDLG_H__BEA75EEE_48BA_476D_9264_851991353D2F__INCLUDED_)
#define AFX_TETRIXBDLG_H__BEA75EEE_48BA_476D_9264_851991353D2F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CTetrixBDlg dialog

#include "TetrixGame.h"

#define		MAPWIDTH		120
#define		MAPHEIGHT		240
#define		LEFTSPAN		20
#define		TOPSPAN			20

#define		NOTEMAPWIDTH	72		//��ʾ����ĵ�ͼ���
#define		NOTEMAPHEIGHT	72		//��ʾ����ĵ�ͼ�߶�
#define		NOTELEFTSPAN	195		//��ʾ�������Ͻ��ڶԻ����еĺ�����λ��
#define		NOTETOPSPAN		40		//��ʾ�������Ͻ��ڶԻ����е�������λ��

#define		TETRIXLEN		12



class CTetrixBDlg : public CDialog
{
// Construction
public:
	void DrawNote();
	void UpdateControl(void);
	void DrawAll();
	
	CTetrixBDlg(CWnd* pParent = NULL);	// standard constructor
	~CTetrixBDlg();
// Dialog Data
	//{{AFX_DATA(CTetrixBDlg)
	enum { IDD = IDD_TETRIXB_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTetrixBDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	CDC*		m_pMemDC;				//�ڴ�DC��Ҳ���Ǳ��ݻ���
	CBitmap*	m_pMemBmp;				//�ڴ�DC��Ӧ��λͼ

	CDC*		m_pMapDC;				//��Ϸ�����ĵ�ͼDC����������
	CBitmap*	m_pMapBmp;				//��Ϸ������λͼ

	CDC*		m_pTriDC;				//�����еķ����ͼ�ε�DC���������黭��
	CBitmap*	m_pTriBmp;				//���������λͼ

	CDC*		m_pTriDarkDC;				//�����еķ����ͼ�ε�DC����ɫ���黭��
	CBitmap*	m_pTriDarkBmp;				//��ɫ�����λͼ

	CDC*		m_pTriDarkCDC;				//��������еķ����ͼ�ε�DC���Һ���ɫ���黭��
	CBitmap*	m_pTriDarkCBmp;				//�Һ���ɫɫ�����λͼ

	CDC*		m_pNoteMapDC;				//��Ϸ�����ĵ�ͼDC����������
	CBitmap*	m_pNoteMapBmp;				//��Ϸ������λͼ

	CDC*		m_pTriRedDC;				//�����еķ����ͼ�ε�DC���������黭��
	CBitmap*	m_pTriRedBmp;				//���������λͼ

	CTetrixGame m_tetrixGame;
	// Generated message map functions
	//{{AFX_MSG(CTetrixBDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonStart();
	afx_msg void OnButtonUp();
	afx_msg void OnButtonLeft();
	afx_msg void OnButtonRight();
	afx_msg void OnButtonDown();
	afx_msg void OnButtonGameover();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonPause();
	afx_msg void OnButtonDidown();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TETRIXBDLG_H__BEA75EEE_48BA_476D_9264_851991353D2F__INCLUDED_)

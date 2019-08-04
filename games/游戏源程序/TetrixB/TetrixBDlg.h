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

#define		NOTEMAPWIDTH	72		//提示区域的底图宽度
#define		NOTEMAPHEIGHT	72		//提示区域的底图高度
#define		NOTELEFTSPAN	195		//提示区域左上角在对话框中的横坐标位置
#define		NOTETOPSPAN		40		//提示区域左上角在对话框中的纵坐标位置

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

	CDC*		m_pMemDC;				//内存DC，也就是备份画布
	CBitmap*	m_pMemBmp;				//内存DC对应的位图

	CDC*		m_pMapDC;				//游戏容器的底图DC，容器画布
	CBitmap*	m_pMapBmp;				//游戏容器的位图

	CDC*		m_pTriDC;				//运行中的方块的图形的DC，基础方块画布
	CBitmap*	m_pTriBmp;				//基础方块的位图

	CDC*		m_pTriDarkDC;				//运行中的方块的图形的DC，灰色方块画布
	CBitmap*	m_pTriDarkBmp;				//灰色方块的位图

	CDC*		m_pTriDarkCDC;				//正在清楚中的方块的图形的DC，灰黑杂色方块画布
	CBitmap*	m_pTriDarkCBmp;				//灰黑杂色色方块的位图

	CDC*		m_pNoteMapDC;				//游戏容器的底图DC，容器画布
	CBitmap*	m_pNoteMapBmp;				//游戏容器的位图

	CDC*		m_pTriRedDC;				//运行中的方块的图形的DC，基础方块画布
	CBitmap*	m_pTriRedBmp;				//基础方块的位图

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

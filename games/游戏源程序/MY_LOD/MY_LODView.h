// MY_LODView.h : interface of the CMY_LODView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MY_LODVIEW_H__9C962E11_B3D2_41C9_9F03_193985BF196F__INCLUDED_)
#define AFX_MY_LODVIEW_H__9C962E11_B3D2_41C9_9F03_193985BF196F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Lod.h"

class CMY_LODView : public CView
{
protected: // create from serialization only
	CMY_LODView();
	DECLARE_DYNCREATE(CMY_LODView)

// Attributes
public:
	CMY_LODDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMY_LODView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void check_height();
	bool RenderScene();
	void colorTerrain();
	void randomTerrain();
	GLuint texName[100];
	void move(int type, GLfloat amount, int update);
	void update_world();
	void initTerrain();
	void Init(void);
	BOOL InitializeOpenGL(CDC* pDC);
	
	int flying_mode ;
	CLod m_Lod;
	HGLRC m_hRC;               //OpenGL绘制描述表
	HPALETTE m_hPalette;       //OpenGL调色板 
	CDC* m_pDC;                //OpenGL设备描述表
	virtual ~CMY_LODView();

	int winWidth ;  
	int winHeight ;
	float sin_t[256];
	float cos_t[256];
	GLfloat xpos, ypos, zpos; 
	GLfloat lookx, looky, lookz; // 当前的视觉方向
	GLfloat speed ; // 当前的运动速度
	GLfloat timer , wTimer ;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMY_LODView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MY_LODView.cpp
inline CMY_LODDoc* CMY_LODView::GetDocument()
   { return (CMY_LODDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MY_LODVIEW_H__9C962E11_B3D2_41C9_9F03_193985BF196F__INCLUDED_)

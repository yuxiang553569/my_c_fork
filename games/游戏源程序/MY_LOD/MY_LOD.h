// MY_LOD.h : main header file for the MY_LOD application
//

#if !defined(AFX_MY_LOD_H__95036709_40C6_46BF_B9A0_23CA7B9FA48C__INCLUDED_)
#define AFX_MY_LOD_H__95036709_40C6_46BF_B9A0_23CA7B9FA48C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMY_LODApp:
// See MY_LOD.cpp for the implementation of this class
//

class CMY_LODApp : public CWinApp
{
public:
	CMY_LODApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMY_LODApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMY_LODApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MY_LOD_H__95036709_40C6_46BF_B9A0_23CA7B9FA48C__INCLUDED_)

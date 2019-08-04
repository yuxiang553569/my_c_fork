// TetrixB.h : main header file for the TETRIXB application
//

#if !defined(AFX_TETRIXB_H__FC97ED20_D879_4C93_A99B_D960B879CE99__INCLUDED_)
#define AFX_TETRIXB_H__FC97ED20_D879_4C93_A99B_D960B879CE99__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTetrixBApp:
// See TetrixB.cpp for the implementation of this class
//

class CTetrixBApp : public CWinApp
{
public:
	CTetrixBApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTetrixBApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTetrixBApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TETRIXB_H__FC97ED20_D879_4C93_A99B_D960B879CE99__INCLUDED_)

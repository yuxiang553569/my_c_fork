// MY_LODDoc.h : interface of the CMY_LODDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MY_LODDOC_H__C0E2CFFA_34BF_4DDD_95BB_B63B09CE1802__INCLUDED_)
#define AFX_MY_LODDOC_H__C0E2CFFA_34BF_4DDD_95BB_B63B09CE1802__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMY_LODDoc : public CDocument
{
protected: // create from serialization only
	CMY_LODDoc();
	DECLARE_DYNCREATE(CMY_LODDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMY_LODDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMY_LODDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMY_LODDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MY_LODDOC_H__C0E2CFFA_34BF_4DDD_95BB_B63B09CE1802__INCLUDED_)

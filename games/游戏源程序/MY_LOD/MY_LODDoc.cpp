// MY_LODDoc.cpp : implementation of the CMY_LODDoc class
//

#include "stdafx.h"
#include "MY_LOD.h"

#include "MY_LODDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMY_LODDoc

IMPLEMENT_DYNCREATE(CMY_LODDoc, CDocument)

BEGIN_MESSAGE_MAP(CMY_LODDoc, CDocument)
	//{{AFX_MSG_MAP(CMY_LODDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMY_LODDoc construction/destruction

CMY_LODDoc::CMY_LODDoc()
{
	// TODO: add one-time construction code here

}

CMY_LODDoc::~CMY_LODDoc()
{
}

BOOL CMY_LODDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMY_LODDoc serialization

void CMY_LODDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMY_LODDoc diagnostics

#ifdef _DEBUG
void CMY_LODDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMY_LODDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMY_LODDoc commands

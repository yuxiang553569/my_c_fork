// Loadbmp.cpp: implementation of the CLoadbmp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Loadbmp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

 HBITMAP backmap,cardmap[57],tablemap, headmap, toumap, hostmap, startmap;	
 HDC		HeadDC,bkDC;	
 HDC		BackDC;
 int		w,cardw, headw;
 int        h,cardh, headh;

CLoadbmp::CLoadbmp()
{
	HeadDC =CreateCompatibleDC(0);
	BackDC =CreateCompatibleDC(0);
	bkDC = CreateCompatibleDC(0);
	w = 150;
	h = 150;
	cardw = 54;
	cardh = 78;
	headw = 30;
	headh = 30;

}

CLoadbmp::~CLoadbmp()
{	

}

BOOL CLoadbmp::loadbmp(CString cc, HBITMAP *bit)
{	
	DeleteObject(*bit);	
	*bit=(HBITMAP)LoadImage	
				(AfxGetInstanceHandle(),
				 cc,
				 IMAGE_BITMAP,	
				 0,	
				 0,	
				 LR_LOADFROMFILE|LR_CREATEDIBSECTION
				);
	if(*bit==NULL) return FALSE;	
/*	DIBSECTION ds;
	BITMAPINFOHEADER &bm = ds.dsBmih;
	GetObject(*bit,sizeof(ds),&ds);	
	w = bm.biWidth;	
	h = bm.biHeight;*/
	return TRUE;
}
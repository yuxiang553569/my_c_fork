// Loadbmp.h: interface for the CLoadbmp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOADBMP_H__2B973A2A_E6AF_4E9F_AD61_3EF7D723AF22__INCLUDED_)
#define AFX_LOADBMP_H__2B973A2A_E6AF_4E9F_AD61_3EF7D723AF22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

extern HBITMAP backmap,cardmap[57],tablemap, headmap, toumap, hostmap, startmap;	
extern HDC		HeadDC,bkDC;	
extern HDC		BackDC;
extern int		w, cardw, headw;
extern int      h, cardh, headh;

class CLoadbmp : public CObject  
{
public:
	CLoadbmp();
	virtual ~CLoadbmp();
public:
	BOOL loadbmp(CString cc, HBITMAP *bit);

};

#endif // !defined(AFX_LOADBMP_H__2B973A2A_E6AF_4E9F_AD61_3EF7D723AF22__INCLUDED_)

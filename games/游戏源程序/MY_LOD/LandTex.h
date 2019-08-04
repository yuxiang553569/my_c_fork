// LandTex.h: interface for the CLandTex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LANDTEX_H__5DFB96DC_14FD_46E7_99E3_9FC9FBC3952E__INCLUDED_)
#define AFX_LANDTEX_H__5DFB96DC_14FD_46E7_99E3_9FC9FBC3952E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "BMPLoad.h"

class CLandTex  
{
public:
	void NEW_BITMAP(unsigned int *, int *);
	CLandTex();
	virtual ~CLandTex();
	unsigned int texture_name[4][4];

};

#endif // !defined(AFX_LANDTEX_H__5DFB96DC_14FD_46E7_99E3_9FC9FBC3952E__INCLUDED_)

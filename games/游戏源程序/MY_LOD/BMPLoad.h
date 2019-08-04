// BMPLoad.h: interface for the CBMPLoad class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BMPLOAD_H__EE61514F_5B1B_4441_A094_A93DD78B5885__INCLUDED_)
#define AFX_BMPLOAD_H__EE61514F_5B1B_4441_A094_A93DD78B5885__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define PI 3.1415926
#define M_SIZE 256 
#define IX(x,z) (((x)&255)+(((z)&255)<<8)) // ��2D����ת��Ϊ1D����
#define f4(a,b,c,d) ((a)+(b)+(c)+(d))/4
class CBMPLoad  
{
public:
	CBMPLoad();
	virtual ~CBMPLoad();

};

#endif // !defined(AFX_BMPLOAD_H__EE61514F_5B1B_4441_A094_A93DD78B5885__INCLUDED_)

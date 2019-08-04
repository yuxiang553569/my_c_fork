// Lod.h: interface for the CLod class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOD_H__E1D74535_1964_48E5_850E_68ACD80A71A6__INCLUDED_)
#define AFX_LOD_H__E1D74535_1964_48E5_850E_68ACD80A71A6__INCLUDED_
#define DISTANCE(v1,v2) sqrt((v1[0]-v2[0])*(v1[0]-v2[0])+(v1[2]-v2[2])*(v1[2]-v2[2]))

#define MAP 256
#define QUAD_MAP (MAP+1)
#define IX_QT(x,z) (((x)%QUAD_MAP)+(((z)%QUAD_MAP)*QUAD_MAP))
#define EDGE_POINT 0
#define NODE_POINT 1
#define UNKNOWN 2

#define COMP 128 
//方向的宏定义
#define NORTH   0
#define WEST    1
#define SOUTH   2
#define EAST    3
#define NW      4
#define NE      5
#define SW      6
#define SE      7
#define NORTH_L 8
#define NORTH_R 9
#define WEST_T  10
#define WEST_B  11
#define SOUTH_L 12
#define SOUTH_R 13
#define EAST_T  14
#define EAST_B  15
#define SHIFT 7 
#define FORWARD 1
#define ROTATE 2
#define LOOKUP 3
#define texScale 64.0 

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct COLOUR {
	int r,g,b;
} COLOUR;

class CLod  
{
public:
	void draw_point(int x, int z, int width, int direction);
	void triangle2(int x1, int z1, int x2, int z2, int x3, int z3);
	void setVertex(int x, int z);
	void triangle1(int x1,int z1,int x2,int z2,int x3,int z3);
	void draw(int x,int z,int width,int direction);
	void setup_quadtree(int x,int z,int width);
	void reset_quad_tree();
	CLod();
	bool m_bFlag;
	virtual ~CLod();

};

#endif // !defined(AFX_LOD_H__E1D74535_1964_48E5_850E_68ACD80A71A6__INCLUDED_)

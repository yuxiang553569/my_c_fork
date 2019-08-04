// Lod.cpp: implementation of the CLod class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MY_LOD.h"
#include "Lod.h"
#include "math.h"
#include "BMPLoad.h"
#include "LandTex.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
extern int quadtree[];
extern int location[];
extern int lod_lever;
extern int* y;
extern CLandTex lt;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLod::CLod()
{

}

CLod::~CLod()
{

}

void CLod::reset_quad_tree()
{
	int i;
	for(i=0;i<(QUAD_MAP*QUAD_MAP);i++) {
		quadtree[i]=UNKNOWN;
	}
}



void CLod::setup_quadtree(int x, int z, int width)
{
	int width2;
	int v1[3];
	v1[0]=x;
	v1[2]=z;
	width2=width/2;
	if ((width>1)&&DISTANCE(v1,location)<width*lod_lever) {
		quadtree[IX_QT(x,z)]=NODE_POINT;

		quadtree[IX_QT(x-width2,z-width2)]=EDGE_POINT;
		quadtree[IX_QT(x-width2,z+width2)]=EDGE_POINT;
		quadtree[IX_QT(x+width2,z-width2)]=EDGE_POINT;
		quadtree[IX_QT(x+width2,z+width2)]=EDGE_POINT;

		setup_quadtree(x-width2,z-width2,width2);
		setup_quadtree(x-width2,z+width2,width2);
		setup_quadtree(x+width2,z-width2,width2);
		setup_quadtree(x+width2,z+width2,width2);
	}
	else {
		quadtree[IX_QT(x,z)]=EDGE_POINT;
	}
}

void CLod::draw(int x, int z, int width, int direction)
{
	int width2;
	if (width>1) {
		if(width > 16) {
			glBindTexture(GL_TEXTURE_2D, lt.texture_name[(int)((x) / 64)][(int)((z) / 64)]);
		}
		width2=width/2;
		if (quadtree[IX_QT(x,z)]==NODE_POINT) {
			//NORTH
			if (quadtree[IX_QT(x-width2,z-width2)]==EDGE_POINT&&
				quadtree[IX_QT(x+width2,z-width2)]==EDGE_POINT) {
				if (quadtree[IX_QT(x,z-2*width)]==NODE_POINT||(z-width)%MAP==0) {
					draw_point(x,z,width,NORTH_L);
				    draw_point(x,z,width,NORTH_R);
				}
			    else {
					draw_point(x,z,width,NORTH);
				}
			}
			else if (quadtree[IX_QT(x-width2,z-width2)]==EDGE_POINT) {
				draw_point(x,z,width,NORTH_L);
			}
			else if (quadtree[IX_QT(x+width2,z-width2)]==EDGE_POINT) {
				draw_point(x,z,width,NORTH_R);
			}
			//SOUTH
			if (quadtree[IX_QT(x-width2,z+width2)]==EDGE_POINT&&
				quadtree[IX_QT(x+width2,z+width2)]==EDGE_POINT) {
				if (quadtree[IX_QT(x,z+2*width)]==NODE_POINT||(z+width)%MAP==0) {
					draw_point(x,z,width,SOUTH_L);
					draw_point(x,z,width,SOUTH_R);
				}
				else {
					draw_point(x,z,width,SOUTH);
				}
			}
			else if (quadtree[IX_QT(x-width2,z+width2)]==EDGE_POINT) {
				draw_point(x,z,width,SOUTH_L);
			}
			else if (quadtree[IX_QT(x+width2,z+width2)]==EDGE_POINT) {
				draw_point(x,z,width,SOUTH_R);
			}
			//EAST
			if (quadtree[IX_QT(x+width2,z+width2)]==EDGE_POINT&&
				quadtree[IX_QT(x+width2,z-width2)]==EDGE_POINT) {
				if (quadtree[IX_QT(x+2*width,z)]==NODE_POINT||(x+width)%MAP==0) {
					draw_point(x,z,width,EAST_T);
				    draw_point(x,z,width,EAST_B);
				}
				else {
					draw_point(x,z,width,EAST);
				}
			}
			else if (quadtree[IX_QT(x+width2,z-width2)]==EDGE_POINT) {
				draw_point(x,z,width,EAST_T);
			}
			else if (quadtree[IX_QT(x+width2,z+width2)]==EDGE_POINT) {
				draw_point(x,z,width,EAST_B);
			}
			//WEST
			if (quadtree[IX_QT(x-width2,z-width2)]==EDGE_POINT&&
				quadtree[IX_QT(x-width2,z+width2)]==EDGE_POINT) {
				if (quadtree[IX_QT(x-2*width,z)]==NODE_POINT||(x-width)%MAP==0) {
					draw_point(x,z,width,WEST_T);
					draw_point(x,z,width,WEST_B);
				}
				else {
					draw_point(x,z,width,WEST);
				}
			}
			else if (quadtree[IX_QT(x-width2,z-width2)]==EDGE_POINT) {
				draw_point(x,z,width,WEST_T);
			}
			else if (quadtree[IX_QT(x-width2,z+width2)]==EDGE_POINT) {
				draw_point(x,z,width,WEST_B);
			}
		}
		else {
			return;
		}
		draw(x-width2,z-width2,width2,NW);
		draw(x+width2,z-width2,width2,NE);
		draw(x-width2,z+width2,width2,SW);
		draw(x+width2,z+width2,width2,SE);
	}
}

void CLod::draw_point(int x, int z, int width, int direction)
{
	switch(direction) {
	case NORTH:
		if (m_bFlag) 
			triangle1(x,z,x+width,z-width,x-width,z-width);
		else
			triangle2(x,z,x+width,z-width,x-width,z-width);
		break;
	case SOUTH:
		if (m_bFlag) 
			triangle1(x,z,x-width,z+width,x+width,z+width);
		else
			triangle2(x,z,x-width,z+width,x+width,z+width);
		break;
	case EAST:
		if (m_bFlag) 
			triangle1(x,z,x+width,z+width,x+width,z-width);
		else
			triangle2(x,z,x+width,z+width,x+width,z-width);
		break;
	case WEST:
		if (m_bFlag) 
			triangle1(x,z,x-width,z-width,x-width,z+width);
		else
			triangle2(x,z,x-width,z-width,x-width,z+width);
		break;
	case NORTH_L:
		if (m_bFlag)
			triangle1(x,z,x,z-width,x-width,z-width);
		else
			triangle2(x,z,x,z-width,x-width,z-width);
		break;
	case NORTH_R:
		if (m_bFlag) 
			triangle1(x,z,x+width,z-width,x,z-width);
		else
			triangle2(x,z,x+width,z-width,x,z-width);
		break;
	case SOUTH_L:
		if (m_bFlag)
			triangle1(x,z,x-width,z+width,x,z+width);
		else
			triangle2(x,z,x-width,z+width,x,z+width);
		break;
	case SOUTH_R:
		if (m_bFlag) 
			triangle1(x,z,x,z+width,x+width,z+width);
		else
			triangle2(x,z,x,z+width,x+width,z+width);
		break;
	case EAST_T:
		if (m_bFlag) 
			triangle1(x,z,x+width,z,x+width,z-width);
		else
			triangle2(x,z,x+width,z,x+width,z-width);
		break;
	case EAST_B:
		if (m_bFlag) 
			triangle1(x,z,x+width,z+width,x+width,z);
		else
			triangle2(x,z,x+width,z+width,x+width,z);
		break;
	case WEST_T:
		if (m_bFlag) 
			triangle1(x,z,x-width,z-width,x-width,z);
		else
			triangle2(x,z,x-width,z-width,x-width,z);
		break;
	case WEST_B:
		if (m_bFlag) 
			triangle1(x,z,x-width,z,x-width,z+width);
		else
			triangle2(x,z,x-width,z,x-width,z+width);
		break;
	default:
		break;
	}
}

void CLod::triangle1(int x1, int z1, int x2, int z2, int x3, int z3)
{
	glBegin(GL_TRIANGLES);
	    glColor3f(1,1,1);
		setVertex(x1,z1);
		glColor3f(0,0,0);
		setVertex(x2,z2);
		glColor3f(0,0,0);
		setVertex(x3,z3);
	glEnd();
}

void CLod::triangle2(int x1, int z1, int x2, int z2, int x3, int z3)
{
	glBegin(GL_LINE_LOOP);
		setVertex(x1,z1);
		setVertex(x2,z2);
		setVertex(x3,z3);
	glEnd();
}

void CLod::setVertex(int x, int z)
{
	glVertex3f((x<<SHIFT),y[IX(x,z)]*8,(z<<SHIFT));
}





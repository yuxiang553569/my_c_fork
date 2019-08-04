// MY_LODView.cpp : implementation of the CMY_LODView class
//

#include "stdafx.h"
#include "MY_LOD.h"

#include "MY_LODDoc.h"
#include "MY_LODView.h"

#include "math.h"
#include "BMPLoad.h"
#include "Lod.h"
#include "LandTex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int *y;  //保存地形高程数组
COLOUR *color_map; //保存地形的颜色值
CLandTex lt;
int quadtree[QUAD_MAP*QUAD_MAP];
int location[3];
int lod_lever=8;
/////////////////////////////////////////////////////////////////////////////
// CMY_LODView

IMPLEMENT_DYNCREATE(CMY_LODView, CView)

BEGIN_MESSAGE_MAP(CMY_LODView, CView)
	//{{AFX_MSG_MAP(CMY_LODView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMY_LODView construction/destruction

CMY_LODView::CMY_LODView()
{
	// TODO: add construction code here
	speed = 0.0; // 移动速度初始化
	timer = 0.0; wTimer = 0.0;
	flying_mode = 1;
}

CMY_LODView::~CMY_LODView()
{
}

BOOL CMY_LODView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	////////////////////////////////////////////////////////////////
	//设置窗口类型
	cs.style |=WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	////////////////////////////////////////////////////////////////
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMY_LODView drawing

void CMY_LODView::OnDraw(CDC* pDC)
{
	CMY_LODDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	RenderScene();	//渲染场景
}

/////////////////////////////////////////////////////////////////////////////
// CMY_LODView printing

BOOL CMY_LODView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMY_LODView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMY_LODView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMY_LODView diagnostics

#ifdef _DEBUG
void CMY_LODView::AssertValid() const
{
	CView::AssertValid();
}

void CMY_LODView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMY_LODDoc* CMY_LODView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMY_LODDoc)));
	return (CMY_LODDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMY_LODView message handlers

int CMY_LODView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	//初始化OpenGL和设置定时器
	m_pDC=new CClientDC(this);
	SetTimer(1,20,NULL);
	InitializeOpenGL(m_pDC);
	
	Init();
	return 0;
}

void CMY_LODView::OnDestroy() 
{                  
	CView::OnDestroy();
	
	// TODO: Add your message handler code here
	//删除调色板和渲染上下文、定时器
	::wglMakeCurrent(0,0);
	::wglDeleteContext(m_hRC);
	if (m_hPalette) 
		DeleteObject(m_hPalette);
	if (m_pDC)
		delete m_pDC;
	KillTimer(1);
	delete[] y;
	delete[] color_map;
	//##调用删除m_Bmpload
}

void CMY_LODView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	//添加窗口缩放时的图形变换函数
	glViewport(0,0,cx,cy);
	winWidth=cx;
	winHeight=cy;
}

void CMY_LODView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your 0+message handler code here and/or call default
	Invalidate(false);
	update_world();
	CView::OnTimer(nIDEvent);
}

BOOL CMY_LODView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return 1;//CView::OnEraseBkgnd(pDC);
}

BOOL CMY_LODView::InitializeOpenGL(CDC *pDC)
{
	pDC=m_pDC;
	//设置像素格式
	PIXELFORMATDESCRIPTOR pfd={
		sizeof(PIXELFORMATDESCRIPTOR),   //pfd结构的大小
		1,                               //版本号
		PFD_DRAW_TO_WINDOW|              //支持在窗口中绘图
		PFD_SUPPORT_OPENGL|              //支持 OpenGL
		PFD_DOUBLEBUFFER,                //双缓存模式
		PFD_TYPE_RGBA,                   //RGBA颜色模式
		24,                              //24位颜色深度
		0,0,0,0,0,0,                     //忽略颜色位
		0,                               //没有非透明度缓存
		0,                               //忽略移动位
		0,                               //无累加缓存
		0,0,0,0,                         //忽略累加位
		32,                              //32位深度缓存
		0,                               //无模板缓存
		0,                               //无辅助缓存
		PFD_MAIN_PLANE,                  //主层
		0,                               //保留
		0,0,0                            //忽略层，可见性和损毁掩模 	
	};
	int pixelformat;
	pixelformat=::ChoosePixelFormat(m_pDC->GetSafeHdc(),&pfd);//选择像素格式
	::SetPixelFormat(m_pDC->GetSafeHdc(),pixelformat,&pfd);   //设置像素格式
	//设置调色板
	if (pfd.dwFlags & PFD_NEED_PALETTE) {
		struct  {
			WORD Version;
			WORD NumberOfEntries;
			PALETTEENTRY aEntries[256];
		} logicalpalette = {0x300,256};
		
		byte reds[]={0, 36, 72, 109, 145, 182, 218, 255};
		byte greens[]={0, 36, 72, 109, 145, 182, 218, 255};
		byte blues[]={0, 85, 170, 255};

		for (int colourNum=0;colourNum<256;colourNum++) {
			logicalpalette.aEntries[colourNum].peRed=
				reds[colourNum & 0x07];
			logicalpalette.aEntries[colourNum].peGreen=
				greens[(colourNum >> 0x03) & 0x07];
			logicalpalette.aEntries[colourNum].peBlue=
				blues[(colourNum >> 0x06) & 0x03];
			logicalpalette.aEntries[colourNum].peFlags=0;
		}

		m_hPalette=CreatePalette ((LOGPALETTE *) &logicalpalette);
	}
	
	m_hRC=::wglCreateContext(m_pDC->GetSafeHdc()); //生成绘制描述表
	::wglMakeCurrent(m_pDC->GetSafeHdc(),m_hRC);   //置当前绘制描述表
	return true;
}

void CMY_LODView::Init()
{
	GLfloat fogColor[]={0.12,0.27,0.7,1.0};
	GLfloat lightDiffuse[]={1.0,0.75,0.5,1.0};
	
	glClearColor(0.12,0.27,0.7,1.0);
//	glClearColor(1,1,1,1);
	for (int i=0;i<256;i++) {
		sin_t[i]=sin((i/128.0)*PI);
		cos_t[i]=cos((i/128.0)*PI);
	}

	initTerrain();  // 初始化地形数据
	
	xpos=0*COMP;//118
	ypos=10.0;
	zpos=0*COMP;//125

	lookx=120.0*COMP;
	looky=0.0*COMP;
	lookz=120.0*COMP;

	speed=50;

	update_world();

	glFogi(GL_FOG_MODE,GL_LINEAR);
	glFogfv(GL_FOG_COLOR,fogColor);
	glFogf(GL_FOG_DENSITY,1);
	glFogf(GL_FOG_START,(M_SIZE/2)*0.1*COMP);
	glFogf(GL_FOG_END,(M_SIZE/2)*0.5*COMP);

	glGenTextures(100,texName);

	srand(1111111);
	randomTerrain();
	
	srand((unsigned)time(NULL));

	glShadeModel(GL_SMOOTH);
	m_Lod.m_bFlag=false;
	move(ROTATE, 2.6, 0);
	move(LOOKUP, -0.2, 0);
}

void CMY_LODView::initTerrain()
{
	y=new int[M_SIZE*M_SIZE];
	color_map=new COLOUR[M_SIZE*M_SIZE];
}

void CMY_LODView::update_world()
{
	timer+=0.05;
	wTimer+=0.0005;

	if (wTimer>=1.0) {
		wTimer=0.0;
	}

	move(FORWARD,speed,1);
	
}

void CMY_LODView::move(int type, GLfloat amount, int update)
{
	GLfloat lightposition[]={-1.0, 0.0, 0.2, 0.0};
	GLfloat a;
	switch(type) {
	case FORWARD:
		location[0]=xpos/128;
		location[2]=zpos/128;
		xpos+=lookx*amount;
		zpos+=lookz*amount;
		break;
	case ROTATE:
		lookx=lookx*cos(amount)+lookz*sin(amount);
		lookz=lookz*cos(amount)-lookx*sin(amount);
		a=1/sqrt(lookx*lookx+lookz*lookz);
		lookx*=a;
		lookz*=a;
		break;
	case LOOKUP:
		looky+=amount;
	}

	if (update) {
		check_height();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		glLightfv(GL_LIGHT0,GL_POSITION,lightposition);
	}
}

void CMY_LODView::check_height()
{
	float x0, x1, lx, lz, x, z, midpoint;
	int fx, fz;
	
	x = xpos/(COMP*1.0);
	z = zpos/(COMP*1.0);
	fx = (int)(x);
	fz = (int)(z);
	lx = x - fx;
	lz = z - fz;
	
	x0 = y[IX(fx,fz)] + (y[IX(fx,fz+1)] - y[IX(fx,fz)])*lz;
	x1 = y[IX(fx+1,fz)] + (y[IX(fx+1,fz+1)] - y[IX(fx+1,fz)])*lz;
	midpoint = x0 + (x1 - x0)*lx;
	
	if(flying_mode	> 0) {
		ypos = (midpoint * 8) + 1024.0f;
	}
	else {
		ypos = (midpoint * 8) + 16.0f;
	}
	
	if(x<0)
		xpos = 0;
	else if(x>(M_SIZE))
		xpos = ((M_SIZE) << SHIFT);
	if(z<0)
		zpos = 0;
	else if(z>(M_SIZE))
		zpos = ((M_SIZE) << SHIFT);	
}

void CMY_LODView::randomTerrain()
{
	int x,z;
	int i,j;
	int bsize,csize;
	int rnd;
	
	for(i=0;i<M_SIZE*M_SIZE;i++) {
		y[i]=0;
	}

	bsize=M_SIZE;
	csize=M_SIZE/2;
	
	rnd=256;
	
	while (csize>0) {
		for (x=0;x<M_SIZE;x+=bsize) {
			for (z=0;z<M_SIZE;z+=bsize) {
				y[IX(x+csize,z+csize)]=f4(y[IX(x,z)],y[IX(x+bsize,z)],y[IX(x+bsize,z+bsize)],y[IX(x,z+bsize)])+rand()%(rnd+1)-(rnd/2);
			}
		}

		for (x=0;x<M_SIZE;x+=bsize) {
			for (z=0;z<M_SIZE;z+=bsize) {
				y[IX(x+csize,z)]=f4(y[IX(x,z)],y[IX(x+bsize,z)],y[IX(x+csize,z+csize)],y[IX(x+csize,z-csize)])+rand()%(rnd+1)-(rnd/2);
			}
		}

		for (x=0;x<M_SIZE;x+=bsize) {
			for (z=0;z<M_SIZE;z+=bsize) {
				y[IX(x,z+csize)]=f4(y[IX(x,z)],y[IX(x,z+bsize)],y[IX(x-csize,z+csize)],y[IX(x+csize,z+csize)])+rand()%(rnd+1)-(rnd/2);
			}
		}

		bsize/=2;
		csize/=2;
		if (csize<16)
			rnd/=2;
	}

	for (i=0;i<M_SIZE*M_SIZE;i++) {
		if (y[i]<0) 
			y[i]=0;
	}

	for (j=0;j<4;j++) {
		x=rand()%M_SIZE;
		z=rand()%M_SIZE;
		for (i=0;i<100;i++) {
			x+=rand()%17-8;
			z+=rand()%17-8;

			y[IX(x, z)] = 1000; 
		}
	}
	
	//高程数据的平滑处理
	for (j=0;j<8;j++) {
		for (x=0;x<M_SIZE;x++) {
			for (z=0;z<M_SIZE;z++) {
				i=y[IX(x-1,z-1)]+
				  y[IX(x,  z-1)]+
				  y[IX(x+1,z-1)]+
				  y[IX(x-1,  z)]+
				  y[IX(x,  z)]+
				  y[IX(x+1,  z)]+
				  y[IX(x-1,z+1)]+
				  y[IX(x,z+1)]+
				  y[IX(x+1,z+1)];

				y[IX(x,z)]=i/9;
			}
		}
	}

	colorTerrain();
}

void CMY_LODView::colorTerrain()
{
	int x,z;
	int h;
	for (x=0;x<M_SIZE;x++) {
		for (z=0;z<M_SIZE;z++) {
			h=200+(y[IX(x,z)]-y[IX(x+1,z)])*8;

			if (h>255) 
				h=255;
			else if (h<0) 
				h=0;

			color_map[IX(x,z)].r=h;
			color_map[IX(x,z)].g=h;
			color_map[IX(x,z)].b=h;
		}
	}
	lt.NEW_BITMAP(texName,y);
}

bool CMY_LODView::RenderScene()
{
	int i;
	int x, z;
	int aX, aZ;
	int r;
	float v1[3];
	float location_f[3];
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glViewport(0,0,(GLsizei)winWidth,(GLsizei)winHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0,(GLfloat)winWidth/(GLfloat)winHeight,1.0,((M_SIZE+4)*2)<<SHIFT);
	// 设置摄像机位置和观看的矢量
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(xpos,ypos,zpos,xpos+lookx,ypos+looky,zpos+lookz,0.0,1.0,0.0);
/*	glTranslatef(-20000,26500,0);
	glScalef(1.65,1.65,1);
	glRotatef(27,0,0,1);
	
	gluLookAt(0,50000,0,lookx,looky,lookz,0.0,1.0,0.0);*/

	m_Lod.reset_quad_tree();
	m_Lod.setup_quadtree(128,128,128);
	
	glColor3f(0.0, 0.0, 0.0);
	m_Lod.draw(128,128,128,0);

	glFlush();
	::SwapBuffers(m_pDC->GetSafeHdc());
	return true;
}



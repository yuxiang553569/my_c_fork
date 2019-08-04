// clientDlg.h : header file
//

#if !defined(AFX_CLIENTDLG_H__5877A519_B754_4AF7_B17A_FA88366904CE__INCLUDED_)
#define AFX_CLIENTDLG_H__5877A519_B754_4AF7_B17A_FA88366904CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define maxnum 20
/////////////////////////////////////////////////////////////////////////////
// CClientDlg dialog

extern	SOCKET clisock;
extern	sockaddr_in client;
extern	int count,ee;

typedef struct userInf   
{
	int		userID;		//等于socket号,
	char	userName[20];//用户名
	int		tableID;	//用户桌号，初始为-1
	int		sitID;		//坐的方位
	int		scores;		//分数
	int		Ishost;		//是否地主
	int     head;       //头像
	char    grade[10];  //等级
} user;

typedef struct Puk		//发给玩家的牌
{	
	BOOL	ishost;		//是否地主
	char	hostname[20];
	BOOL	cansend;	//能否打牌
	char	puk[20];	//后三张是底牌
}puk;
typedef struct Fenshu
{
	int id;
	int fen;
}fenshu;

extern fenshu score[maxnum];
extern user userInf[maxnum];
extern puk	pukInf;
extern char myname[20];

class CClientDlg : public CDialog
{
// Construction
public:
	CClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CClientDlg)
	enum { IDD = IDD_CLIENT_DIALOG };
	CStatic	m_inf;
	CButton	m_qroom;
	CButton	m_qgame;
	CButton	m_pass;
	CButton	m_playcard;
	CButton	m_start;
	CListBox	m_msg;
	CStatic	m_room;
	CStatic	m_hi2;
	CStatic	m_hi;
	CListCtrl	m_player;
	CStatic	m_staticPsd;
	CStatic	m_staticName;
	CStatic	m_staticIP;
	CEdit	m_psd;
	CButton	m_exit;
	CButton	m_connect;
	CEdit	m_ip;
	CEdit	m_name;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBTConnect();
	afx_msg void OnBTExit();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void Onstart();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void Onplaycard();
	afx_msg void Onpass();
	afx_msg void Onleavgame();
	afx_msg void Onleavroom();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:

public:
	void ReSort(int *CurrentCards,int CurrentLen);//对牌进行排序
	void destroy();
	void dealmsg(int flag, char *buffer);
	void writeRoom(char *buffer);
	void display();						//根据玩家信息贴图,画大厅
	void showcards();					//发牌
	void showstart();					//画头，表示有人点开始了
	void showhead();					//画玩家头像
	void playcards();					//游戏进行状态，绘制函数
	void showhost();					//画地主头
	void showRoom();
	void updateRoom(char *buffer);		//更新大厅
	void reshow();						//显示控件
	void dealhost();					//处理当不当地主的问题
	void dealplay(char *buffer);		//处理上家出牌
	void dealsend(char *buffer);		//处理自己出牌
	void showit();						//显示上家出的牌
	void init();						//装载图片
	void showname();					//显示与自己同桌的玩家姓名
	void note(int x, int y);			//贴图，表示鼠标移动到了座位上
	void decidehost(int host);			//将地主的牌多显示三张
	void setrect();						//设置无效区域，避免屏幕过分闪烁
	void drawface();					//画封面
//	void updataScore();					//更新完家分数
};
extern UINT thread(LPVOID);
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTDLG_H__5877A519_B754_4AF7_B17A_FA88366904CE__INCLUDED_)

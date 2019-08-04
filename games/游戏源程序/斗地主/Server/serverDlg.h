// serverDlg.h : header file
//

#if !defined(AFX_SERVERDLG_H__D8F77558_2D5D_4BF3_8E86_C6F1314E09E7__INCLUDED_)
#define AFX_SERVERDLG_H__D8F77558_2D5D_4BF3_8E86_C6F1314E09E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "server.h"
#include "afxdb.h"
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CServerDlg dialog

#define maxnum 20

typedef struct userInf     
{
	int		userID;		//等于socket号,
	char	userName[20];//用户名	
	int		tableID;	//用户桌号，初始为-1
	int		sitID;		//坐的方位
	int		scores;		//分数
	int		Ishost;		//是否地主
	int     head;       //头像
	char    grade[10];      //等级
} user;

typedef struct tableInf
{
	int		tableID;	//桌号
	int		tableNum;	//坐下的人数，初始为0
	int		player1;	
	int		player2;	//玩家id，-1表示没人坐
	int		player3;
	int		tableState;	//游戏桌状态, 0:人员未满，1：人员满
	int		startnum;	//多少人点击开始了,初始为0;
	int		changenum;	//不愿意当地主的次数
	int     passNum;	//pass的次数
	int     mutiple;	//倍数
} table;

typedef struct sendCards//玩家打的牌和上家打的牌
{	
	char	cur_buff[25];//当前玩家出的牌
	int		num;		 //上一家出的张数
	int		type;		 //出牌类型 初始-1
	int		point;		 //牌点 初始-1
	
//	int		
}sendcards;

typedef struct Puk		//发给玩家的牌
{	
	BOOL	ishost;		//是否地主
	char	hostname[20];
	BOOL	cansend;	//能否打牌
	char	puk[20];	//后三张是底牌
}puk;

typedef struct score
{
	int id;
	int fenshu;
}scr;

class CServerDlg : public CDialog
{
// Construction
public:
	scr*        scoreInf[maxnum];
	user*		userInf[maxnum];
	table		tableInf[maxnum];
	sendcards	cardsInf[maxnum];
	puk*		pukInf[maxnum];
	void		InitStruct();
	int ChangeScore[maxnum];
	CServerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CServerDlg)
	enum { IDD = IDD_SERVER_DIALOG };
	CEdit	m_scores;
	CComboBox	m_name;
	CListCtrl	m_OnlineUser;
	CEdit	m_Table;
	CEdit	m_ClinetName;
	CEdit	m_serverName;
	CButton	m_stop;
	CButton	m_run;
	CListBox	m_connectInf;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	void WriteDb(int userid);
	int GetChangScore(int theUserid,int pNext,int pOther);
	int FindHost(int tableid);
	int getTableId(int playerId);
	HICON	m_hIcon;
	SOCKET	sock, msgsock[50];
	sockaddr_in serv;
	int		addlen;
	int		count;
	int		getsocket();//获得还没使用的socket

	void	writeTableInf(int flag, int tableid);	//flag表示是增加还是删除（0:删除，1：增加）
	void	setTableState(int tableid, int state);
	int		gettableState(int tableid);
	void	sendMessage(int socknum, char *flag, char *buffer);	//向socknum发送消息
	void	setplayerID(int socknum, int tableid, int sitid);				
	int		getplayerID(int tableid, int sitid);	//分配某游戏桌某玩家的座位号															//的msgtype消息
	void	setStartnum(int flag, int tableid);		//flag ：1表++， 0表--
	BOOL	canstart(int tableid);					//返回3，则服务器发牌
	void	sethost(int flag, int socknum);			//flag==1设置socknum为地主，flag==0不是地主

	void	dealmsg(int msgcount, char *buff);
	void	dealLogin(int socknum, char *buffer);	//处理登陆
	void	dealSit(int socknum, char *buffer);		//处理选择桌子
	void	dealStart(int socknum, char *buffer);	//处理用户是否可以开始
	void	dealChangeHost(int socknum, int yes);			//处理更换地主
	void	dealSendCards(int socknum, char *buffer);//处理打牌
	void	dealLeftDesk(int socknum);				//处理离开游戏桌
	void	dealExit(int socknum);					//处理离开大厅

	void	updateRoom(int flag, int socknum, char *name, 
						 int tableid, int sitid);//flag 表示删除/增加

	void	sendRoomInf(int socknum);				//发送大厅信息	
	void	sendCards(int tableid);					//给tableid 这桌子的玩家发牌
	
	void	resetPukInf(int tableid);

	char	*produceCards();
	

	// Generated message map functions
	//{{AFX_MSG(CServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnRun();
	afx_msg void OnBtnStop();
	afx_msg void OnBtnSearch();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
UINT mainThread(LPVOID);
//UINT acceptThread(LPVOID);
//UINT sendThread(LPVOID);
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERDLG_H__D8F77558_2D5D_4BF3_8E86_C6F1314E09E7__INCLUDED_)

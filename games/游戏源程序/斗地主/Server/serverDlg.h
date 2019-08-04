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
	int		userID;		//����socket��,
	char	userName[20];//�û���	
	int		tableID;	//�û����ţ���ʼΪ-1
	int		sitID;		//���ķ�λ
	int		scores;		//����
	int		Ishost;		//�Ƿ����
	int     head;       //ͷ��
	char    grade[10];      //�ȼ�
} user;

typedef struct tableInf
{
	int		tableID;	//����
	int		tableNum;	//���µ���������ʼΪ0
	int		player1;	
	int		player2;	//���id��-1��ʾû����
	int		player3;
	int		tableState;	//��Ϸ��״̬, 0:��Աδ����1����Ա��
	int		startnum;	//�����˵����ʼ��,��ʼΪ0;
	int		changenum;	//��Ը�⵱�����Ĵ���
	int     passNum;	//pass�Ĵ���
	int     mutiple;	//����
} table;

typedef struct sendCards//��Ҵ���ƺ��ϼҴ����
{	
	char	cur_buff[25];//��ǰ��ҳ�����
	int		num;		 //��һ�ҳ�������
	int		type;		 //�������� ��ʼ-1
	int		point;		 //�Ƶ� ��ʼ-1
	
//	int		
}sendcards;

typedef struct Puk		//������ҵ���
{	
	BOOL	ishost;		//�Ƿ����
	char	hostname[20];
	BOOL	cansend;	//�ܷ����
	char	puk[20];	//�������ǵ���
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
	int		getsocket();//��û�ûʹ�õ�socket

	void	writeTableInf(int flag, int tableid);	//flag��ʾ�����ӻ���ɾ����0:ɾ����1�����ӣ�
	void	setTableState(int tableid, int state);
	int		gettableState(int tableid);
	void	sendMessage(int socknum, char *flag, char *buffer);	//��socknum������Ϣ
	void	setplayerID(int socknum, int tableid, int sitid);				
	int		getplayerID(int tableid, int sitid);	//����ĳ��Ϸ��ĳ��ҵ���λ��															//��msgtype��Ϣ
	void	setStartnum(int flag, int tableid);		//flag ��1��++�� 0��--
	BOOL	canstart(int tableid);					//����3�������������
	void	sethost(int flag, int socknum);			//flag==1����socknumΪ������flag==0���ǵ���

	void	dealmsg(int msgcount, char *buff);
	void	dealLogin(int socknum, char *buffer);	//�����½
	void	dealSit(int socknum, char *buffer);		//����ѡ������
	void	dealStart(int socknum, char *buffer);	//�����û��Ƿ���Կ�ʼ
	void	dealChangeHost(int socknum, int yes);			//�����������
	void	dealSendCards(int socknum, char *buffer);//�������
	void	dealLeftDesk(int socknum);				//�����뿪��Ϸ��
	void	dealExit(int socknum);					//�����뿪����

	void	updateRoom(int flag, int socknum, char *name, 
						 int tableid, int sitid);//flag ��ʾɾ��/����

	void	sendRoomInf(int socknum);				//���ʹ�����Ϣ	
	void	sendCards(int tableid);					//��tableid �����ӵ���ҷ���
	
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

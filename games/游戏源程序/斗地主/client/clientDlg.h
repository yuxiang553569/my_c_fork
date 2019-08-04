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
	int		userID;		//����socket��,
	char	userName[20];//�û���
	int		tableID;	//�û����ţ���ʼΪ-1
	int		sitID;		//���ķ�λ
	int		scores;		//����
	int		Ishost;		//�Ƿ����
	int     head;       //ͷ��
	char    grade[10];  //�ȼ�
} user;

typedef struct Puk		//������ҵ���
{	
	BOOL	ishost;		//�Ƿ����
	char	hostname[20];
	BOOL	cansend;	//�ܷ����
	char	puk[20];	//�������ǵ���
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
	void ReSort(int *CurrentCards,int CurrentLen);//���ƽ�������
	void destroy();
	void dealmsg(int flag, char *buffer);
	void writeRoom(char *buffer);
	void display();						//���������Ϣ��ͼ,������
	void showcards();					//����
	void showstart();					//��ͷ����ʾ���˵㿪ʼ��
	void showhead();					//�����ͷ��
	void playcards();					//��Ϸ����״̬�����ƺ���
	void showhost();					//������ͷ
	void showRoom();
	void updateRoom(char *buffer);		//���´���
	void reshow();						//��ʾ�ؼ�
	void dealhost();					//������������������
	void dealplay(char *buffer);		//�����ϼҳ���
	void dealsend(char *buffer);		//�����Լ�����
	void showit();						//��ʾ�ϼҳ�����
	void init();						//װ��ͼƬ
	void showname();					//��ʾ���Լ�ͬ�����������
	void note(int x, int y);			//��ͼ����ʾ����ƶ�������λ��
	void decidehost(int host);			//���������ƶ���ʾ����
	void setrect();						//������Ч���򣬱�����Ļ������˸
	void drawface();					//������
//	void updataScore();					//������ҷ���
};
extern UINT thread(LPVOID);
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTDLG_H__5877A519_B754_4AF7_B17A_FA88366904CE__INCLUDED_)

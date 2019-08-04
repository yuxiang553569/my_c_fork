; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CServerDlg
LastTemplate=CSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "server.h"

ClassCount=4
Class1=CServerApp
Class2=CServerDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CSocketApp
Resource3=IDD_SERVER_DIALOG

[CLS:CServerApp]
Type=0
HeaderFile=server.h
ImplementationFile=server.cpp
Filter=N

[CLS:CServerDlg]
Type=0
HeaderFile=serverDlg.h
ImplementationFile=serverDlg.cpp
Filter=D
LastObject=CServerDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=serverDlg.h
ImplementationFile=serverDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SERVER_DIALOG]
Type=1
Class=CServerDlg
ControlCount=22
Control1=IDC_STATIC,static,1342308352
Control2=IDC_LIST_Clients,SysListView32,1350634531
Control3=IDC_BTN_SEARCH,button,1342242816
Control4=IDC_COMBO_Client,combobox,1344340226
Control5=IDC_LIST2,listbox,1352728835
Control6=IDC_EDIT_ClientName,edit,1350631552
Control7=IDC_EDIT_SCORE,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_BTN_STOP,button,1342242816
Control12=IDC_BTN_RUN,button,1342242816
Control13=IDC_EDIT_Table,edit,1350631552
Control14=IDC_STATIC,button,1342177287
Control15=IDC_STATIC,button,1342177287
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,button,1342177287
Control20=IDCANCEL,button,1342242816
Control21=IDC_STATIC,static,1342308352
Control22=IDC_ServerName,edit,1350631552

[CLS:CSocketApp]
Type=0
HeaderFile=SocketApp.h
ImplementationFile=SocketApp.cpp
BaseClass=CSocket
Filter=N
LastObject=CSocketApp


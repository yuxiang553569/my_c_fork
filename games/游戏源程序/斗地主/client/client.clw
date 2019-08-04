; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CClientDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "client.h"

ClassCount=4
Class1=CClientApp
Class2=CClientDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CplayDlg
Resource3=IDD_CLIENT_DIALOG

[CLS:CClientApp]
Type=0
HeaderFile=client.h
ImplementationFile=client.cpp
Filter=N

[CLS:CClientDlg]
Type=0
HeaderFile=clientDlg.h
ImplementationFile=clientDlg.cpp
Filter=D
LastObject=IDC_ListPlayers
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=clientDlg.h
ImplementationFile=clientDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CLIENT_DIALOG]
Type=1
Class=CClientDlg
ControlCount=21
Control1=IDC_StaticRoom,static,1073807374
Control2=IDC_StaticHi2,static,1342308352
Control3=IDCANCEL,button,1073807360
Control4=IDOK,button,1073807361
Control5=IDC_IP,static,1342308352
Control6=IDC_EditIP,edit,1350631552
Control7=IDC_EditName,edit,1350631552
Control8=IDC_Name,static,1342308352
Control9=IDC_PSD,static,1342308352
Control10=IDC_EditPsd,edit,1350631552
Control11=IDC_BTExit,button,1342242816
Control12=IDC_BTConnect,button,1342242816
Control13=IDC_StaticHi,static,1342308353
Control14=IDC_start,button,1073807360
Control15=IDC_pass,button,1073807360
Control16=IDC_playcard,button,1073807360
Control17=IDC_ListMsg,listbox,1084293379
Control18=IDC_ListPlayers,SysListView32,1082195969
Control19=IDC_leavgame,button,1073807360
Control20=IDC_leavroom,button,1073807360
Control21=IDC_cntinf,static,1342308352

[CLS:CplayDlg]
Type=0
HeaderFile=playDlg.h
ImplementationFile=playDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_bitmap1


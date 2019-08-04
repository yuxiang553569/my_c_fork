; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CChessDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "chess.h"

ClassCount=3
Class1=CChessApp
Class2=CChessDlg

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_CHESS_DIALOG
Class3=CNewGame
Resource3=IDD_NEWGAME

[CLS:CChessApp]
Type=0
HeaderFile=chess.h
ImplementationFile=chess.cpp
Filter=N

[CLS:CChessDlg]
Type=0
HeaderFile=chessDlg.h
ImplementationFile=chessDlg.cpp
Filter=D
LastObject=CChessDlg
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_CHESS_DIALOG]
Type=1
Class=CChessDlg
ControlCount=3
Control1=IDC_BTN_NEWGAME,button,1342242816
Control2=IDC_STATIC,button,1342177287
Control3=IDC_NODECOUNT,static,1342308352

[DLG:IDD_NEWGAME]
Type=1
Class=CNewGame
ControlCount=7
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_LISTENGINE,listbox,1352728833
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT1,edit,1350631552
Control6=IDC_PLY,msctls_updown32,1342177334
Control7=IDOK,button,1342242816

[CLS:CNewGame]
Type=0
HeaderFile=NewGame.h
ImplementationFile=NewGame.cpp
BaseClass=CDialog
Filter=D
LastObject=CNewGame


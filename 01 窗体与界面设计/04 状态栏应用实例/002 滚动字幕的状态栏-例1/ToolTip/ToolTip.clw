; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CToolTipDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ToolTip.h"

ClassCount=4
Class1=CToolTipApp
Class2=CToolTipDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_TOOLTIP_DIALOG

[CLS:CToolTipApp]
Type=0
HeaderFile=ToolTip.h
ImplementationFile=ToolTip.cpp
Filter=N

[CLS:CToolTipDlg]
Type=0
HeaderFile=ToolTipDlg.h
ImplementationFile=ToolTipDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=ToolTipDlg.h
ImplementationFile=ToolTipDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_TOOLTIP_DIALOG]
Type=1
Class=CToolTipDlg
ControlCount=1
Control1=IDC_BUTTONUPDATE,button,1342242816


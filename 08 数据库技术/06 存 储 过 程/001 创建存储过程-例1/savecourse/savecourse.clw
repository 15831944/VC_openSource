; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSavecourseDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "savecourse.h"

ClassCount=3
Class1=CSavecourseApp
Class2=CSavecourseDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_SAVECOURSE_DIALOG

[CLS:CSavecourseApp]
Type=0
HeaderFile=savecourse.h
ImplementationFile=savecourse.cpp
Filter=N

[CLS:CSavecourseDlg]
Type=0
HeaderFile=savecourseDlg.h
ImplementationFile=savecourseDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=savecourseDlg.h
ImplementationFile=savecourseDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SAVECOURSE_DIALOG]
Type=1
Class=CSavecourseDlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_DATAGRID1,{CDE57A43-8B86-11D0-B3C6-00A0C90AEA82},1342242816
Control4=IDC_ADODC1,{67397AA3-7FB1-11D0-B148-00A0C922E820},1342177280
Control5=IDC_EDIT1,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT2,edit,1350635588


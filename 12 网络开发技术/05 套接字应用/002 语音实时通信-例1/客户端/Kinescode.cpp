// Kinescode.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Kinescode.h"
#include "KinescodeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include <MMSystem.h>
#pragma comment(lib, "winmm.lib")

/////////////////////////////////////////////////////////////////////////////
// CKinescodeApp

BEGIN_MESSAGE_MAP(CKinescodeApp, CWinApp)
	//{{AFX_MSG_MAP(CKinescodeApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKinescodeApp construction

CKinescodeApp::CKinescodeApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CKinescodeApp object

CKinescodeApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CKinescodeApp initialization

BOOL CKinescodeApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	//��ʼ���׽���
	WSADATA wsd;
	AfxSocketInit(&wsd);

	CKinescodeDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	return FALSE;
}

// Shaddlg2.cpp : implementation file
//

#include "stdafx.h"
#include "Shadow.h"
#include "Shaddlg2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShaddlg2 dialog


CShaddlg2::CShaddlg2(CWnd* pParent /*=NULL*/)
	: CDialog(CShaddlg2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShaddlg2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CShaddlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShaddlg2)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShaddlg2, CDialog)
	//{{AFX_MSG_MAP(CShaddlg2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShaddlg2 message handlers

BOOL CShaddlg2::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//���ô�����չ���
	SetWindowLong(GetSafeHwnd(),GWL_EXSTYLE,
		GetWindowLong(GetSafeHwnd(),GWL_EXSTYLE) | 0x80000);
	//���庯��ָ������
	typedef BOOL (WINAPI *FSetLayeredWindowAttributes)(HWND,COLORREF,BYTE,DWORD);
	FSetLayeredWindowAttributes SetLayeredWindowAttributes ;//���庯��ָ��
	HINSTANCE hInst = LoadLibrary("User32.DLL");//����DLL
	SetLayeredWindowAttributes = (FSetLayeredWindowAttributes)
	GetProcAddress(hInst,"SetLayeredWindowAttributes");//��ȡ����ָ���ַ
	if(SetLayeredWindowAttributes)
	SetLayeredWindowAttributes(GetSafeHwnd(),RGB(0,0,0),128,1);//����͸��
	FreeLibrary(hInst);//�ͷ�DLL
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

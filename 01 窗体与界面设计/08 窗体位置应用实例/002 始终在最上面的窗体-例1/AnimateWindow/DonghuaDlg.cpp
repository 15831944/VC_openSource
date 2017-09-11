// DonghuaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Donghua.h"
#include "DonghuaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define AW_CENTER                   0x00000010 //����
#define AW_HIDE                     0x00010000 //����
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDonghuaDlg dialog

CDonghuaDlg::CDonghuaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDonghuaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDonghuaDlg)
	m_edit = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDonghuaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDonghuaDlg)
	DDX_Text(pDX, IDC_EDIT1, m_edit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDonghuaDlg, CDialog)
	//{{AFX_MSG_MAP(CDonghuaDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDonghuaDlg message handlers

BOOL CDonghuaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	m_edit = "�˴���Ϊ������ʾ���塣";
	this->UpdateData(false);
	// TODO: Add extra initialization here
	CenterWindow();	//��������
	DWORD dwStyle=AW_CENTER;	//����
	HINSTANCE hInst=LoadLibrary("User32.DLL"); //���붯̬��
	typedef BOOL(WINAPI MYFUNC(HWND,DWORD,DWORD));	//���庯������
	MYFUNC* AnimateWindow;	//���庯��ָ��
	AnimateWindow=(MYFUNC *)::GetProcAddress(hInst,"AnimateWindow");	//��ȡ������ַ
	AnimateWindow(this->m_hWnd,1000,dwStyle);//���ô��嶯��
	FreeLibrary(hInst);	//�ͷŶ�̬��
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDonghuaDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDonghuaDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDonghuaDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDonghuaDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	DWORD dwStyle=AW_CENTER;	//���ж���
	HINSTANCE hInst=LoadLibrary("User32.DLL"); //���붯̬��
	typedef BOOL(WINAPI MYFUNC(HWND,DWORD,DWORD));//���庯������
	MYFUNC* AnimateWindow;//���庯��ָ��
	AnimateWindow=(MYFUNC *)::GetProcAddress(hInst,"AnimateWindow");//��ȡ������ַ
	AnimateWindow(this->GetSafeHwnd(),700,AW_HIDE|dwStyle);//���ô��嶯��
	FreeLibrary(hInst);//�ͷŶ�̬��
	CDialog::OnClose();
}

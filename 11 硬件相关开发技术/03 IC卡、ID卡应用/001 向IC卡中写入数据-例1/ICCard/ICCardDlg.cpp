// ICCardDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Mwic_32.h"
#include "ICCard.h"
#include "ICCardDlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
// CICCardDlg dialog

CICCardDlg::CICCardDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CICCardDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CICCardDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	icdev = 0;
}

void CICCardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CICCardDlg)
	DDX_Control(pDX, IDC_HINT, m_Hint);
	DDX_Control(pDX, IDC_ICDATA, m_ICData);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CICCardDlg, CDialog)
	//{{AFX_MSG_MAP(CICCardDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CICCardDlg message handlers

BOOL CICCardDlg::OnInitDialog()
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
	

	//��ʼ���˿� COM1 9600
	icdev= auto_init(0,9600);
	if (icdev<0)
		MessageBox("�˿ڳ�ʼ��ʧ��,����ӿ����Ƿ�������ȷ.");

	//��������ģʽ,ʹ�豸������Ч,�������豸�ӵ�ʱ,����˶�������ܽ��к�������
	setsc_md(icdev,1);
	__int16 rpass;
	//��ȡID��״̬
	__int16 status = -1;
	
	__int16 result =get_status(icdev,&status);

	if (result<0)
	{
		MessageBox("��ȡIC��״̬����");
	}
	else if ((result==0)&&(status==0))
		MessageBox("�����ID��");
	
	//������4442IC����������Ϊffffff
	unsigned char pass[3]={0xff,0xff,0xff};
	//��֤����
	rpass =csc_4442(icdev,3,pass);
	if (rpass<0)
	{
		MessageBox("IC������˶Դ���,ֻ�ܶ�ȡ����");
	}	
	return TRUE;  

}

void CICCardDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CICCardDlg::OnPaint() 
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
HCURSOR CICCardDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CICCardDlg::OnOK() 
{
	if (MessageBox("ȷʵҪд��������?","��ʾ",MB_YESNO)==IDYES)
	{
		CString str;
		m_ICData.GetWindowText(str);
		if (str.IsEmpty())
		{
			MessageBox("����������");
			return;
		}
		if (str.GetLength()>224)
		{
			MessageBox("д�����ݲ��ܳ���224���ַ�","��ʾ",64);
			return;
		}

		__int16 result;
		
		//��IC����Ӧ������д������
		result =swr_4442(icdev,33,str.GetLength(),(unsigned char*)str.GetBuffer(0));
			
		if (result==0)
		{
			MessageBox("����д��ɹ�.","��ʾ",64);
		}
		else
		{
			MessageBox("����д��ʧ��.","��ʾ",64);
		}
	}
}

void CICCardDlg::OnCancel() 
{	
	ic_exit(icdev);
	CDialog::OnCancel();
}

HBRUSH CICCardDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
		CBrush brush(RGB(255,0,0));	
	if ((nCtlColor==CTLCOLOR_STATIC)&&(pWnd->m_hWnd==m_Hint.m_hWnd))
	{
		CBrush brush(RGB(255,0,0));
		pDC->SelectObject(&brush);
		pDC->SetTextColor(RGB(255,0,0));
		pDC->SetBkMode(TRANSPARENT);
		return brush;
	}
	return brush;
	// TODO: Return a different brush if the default is not desired
	//return hbr;
}

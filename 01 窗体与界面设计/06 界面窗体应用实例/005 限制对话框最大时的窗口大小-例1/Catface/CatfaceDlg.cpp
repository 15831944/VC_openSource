// CatfaceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Catface.h"
#include "CatfaceDlg.h"

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
// CCatfaceDlg dialog

CCatfaceDlg::CCatfaceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCatfaceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCatfaceDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCatfaceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCatfaceDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCatfaceDlg, CDialog)
	//{{AFX_MSG_MAP(CCatfaceDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCatfaceDlg message handlers

BOOL CCatfaceDlg::OnInitDialog()
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
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCatfaceDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCatfaceDlg::OnPaint() 
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
	CDC *pDC = GetDC();									//����豸������
	CDC	 memDC;
	CBitmap	bitmap;									//����λͼ����
	CBitmap* bmp = NULL;
	COLORREF col;
	CRect rc;
	int	x, y;
	CRgn rgn, tmp;
	GetWindowRect(&rc);									//��ô�������
	bitmap.LoadBitmap(IDB_BITMAP1);						//װ��ģ��λͼ
	memDC.CreateCompatibleDC(pDC);						//�������ڴ���ݵ��豸������
	bmp = memDC.SelectObject(&bitmap);
	rgn.CreateRectRgn(0, 0, rc.Width(), rc.Height());				//��ʼ������
	//����õ�����
	for(x=0; x<=rc.Width(); x++)
	{
		for(y=0; y<=rc.Height(); y++)
		{
			//����������ȥ��
			col = memDC.GetPixel(x, y);						//�õ�������ɫ
			if(col == RGB(255,255,255))						//����Ǳ�����ɫ
			{
				tmp.CreateRectRgn(x, y, x+1, y+1);			//��������
				rgn.CombineRgn(&rgn, &tmp,RGN_XOR);		//ȥ���໥�ص�������
				tmp.DeleteObject();						//ɾ���������
			}
		}
	}
	SetWindowRgn((HRGN)rgn,TRUE);						//���ô���Ϊ�������״
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCatfaceDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

HBRUSH CCatfaceDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	CBitmap m_BKGround;
	m_BKGround.LoadBitmap(IDB_BITMAP1);
	if (nCtlColor==CTLCOLOR_DLG)
	{
		CBrush m_Brush(&m_BKGround);		//����һ��λͼ��ˢ
		CRect rect;
		GetClientRect(rect);
		pDC->SelectObject(&m_Brush);		//ѡ�л�ˢ
		pDC->FillRect(rect,&m_Brush);		//���ͻ�����
		return m_Brush;
	}
	else
		hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

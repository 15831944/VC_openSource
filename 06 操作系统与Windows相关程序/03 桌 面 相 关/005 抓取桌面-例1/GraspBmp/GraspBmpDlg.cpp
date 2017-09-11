// GraspBmpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GraspBmp.h"
#include "GraspBmpDlg.h"
#include <windowsx.h>
#include "math.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define HOTKEY_GRASP		10000
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
// CGraspBmpDlg dialog

CGraspBmpDlg::CGraspBmpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGraspBmpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGraspBmpDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGraspBmpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGraspBmpDlg)
	DDX_Control(pDX, IDC_HOTKEY1, m_HotKey);
	DDX_Control(pDX, IDC_CHECK1, m_Cursor);
	DDX_Control(pDX, IDC_EDIT1, m_Path);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGraspBmpDlg, CDialog)
	//{{AFX_MSG_MAP(CGraspBmpDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTPATH, OnButpath)
	ON_MESSAGE(WM_HOTKEY,OnHotKey)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTSAVE, OnButsave)
	ON_BN_CLICKED(IDC_BUTEXIT, OnButexit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraspBmpDlg message handlers

BOOL CGraspBmpDlg::OnInitDialog()
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
	m_Num = 1;
	WORD wvk,wmod;
	char bufwvk[8],bufwmod[8],bufpath[256],bufmouse[2];
	GetPrivateProfileString("Set","path","",bufpath,256,"./System.ini");
	m_Path.SetWindowText(bufpath);
	GetPrivateProfileString("Set","wvk","",bufwvk,8,"./System.ini");
	wvk = atoi(bufwvk);
	GetPrivateProfileString("Set","wmod","",bufwmod,8,"./System.ini");
	wmod = atoi(bufwmod);
	GetPrivateProfileString("Set","capmouse","",bufmouse,2,"./System.ini");
	m_Cursor.SetCheck(atoi(bufmouse));
	m_HotKey.SetHotKey(wvk,wmod);
	BOOL result = RegisterHotKey(this->GetSafeHwnd(),HOTKEY_GRASP,wmod,wvk);
	if(!result)
	{
		MessageBox("ע���ȼ�ʧ��");
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGraspBmpDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGraspBmpDlg::OnPaint() 
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
HCURSOR CGraspBmpDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGraspBmpDlg::OnButpath() 
{
	// TODO: Add your control notification handler code here
	CString ReturnPach;								//�ַ�������
	TCHAR szPath[_MAX_PATH];                       	//����·������
	BROWSEINFO bi;                                 	// BROWSEINFO�ṹ����
	bi.hwndOwner    = NULL;                        	//HWND���
	bi.pidlRoot       = NULL;                       //Ĭ��ֵΪNULL
	bi.lpszTitle       = _T("�ļ�����Ի���");      //�Ի������
	bi.pszDisplayName = szPath;                     //ѡ���ļ���·��
	bi.ulFlags        = BIF_RETURNONLYFSDIRS;       //���
	bi.lpfn           = NULL;                       //Ĭ��ֵΪNULL
	bi.lParam         = NULL;                      	//�ص���Ϣ
	LPITEMIDLIST pItemIDList = SHBrowseForFolder(&bi);//��ʾ�ļ�����Ի���
	if(pItemIDList)
	{
		if(SHGetPathFromIDList(pItemIDList,szPath)) //�ж��Ƿ����ļ���·��
			ReturnPach = szPath;					//����ļ���·��
	}
	else
	{
		ReturnPach = ""; 							//�ļ���·��Ϊ��
	}
	m_Path.SetWindowText(ReturnPach);
}

void CGraspBmpDlg::OnHotKey(WPARAM wParam,LPARAM lParam)
{
	if(HOTKEY_GRASP == (int)wParam)
	{
		StartGrasp();						//ץͼ
	}
}

void CGraspBmpDlg::StartGrasp()
{
	CString path;
	m_Path.GetWindowText(path);
	if(path.IsEmpty())
	{
		MessageBox("��ѡ���ļ��洢λ��");
		return;
	}
	CDC* pDeskDC =  GetDesktopWindow()->GetDC();		//��ȡ���滭������
	CRect rc;
	GetDesktopWindow()->GetClientRect(rc);				//��ȡ��Ļ�Ŀͻ�����
	CDC  memDC;											//����һ���ڴ滭��
	memDC.CreateCompatibleDC(pDeskDC);					//����һ�����ݵĻ���
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDeskDC,rc.Width(),rc.Height());	//��������λͼ
	memDC.SelectObject(&bmp);							//ѡ��λͼ����	
	BITMAP bitmap;
	bmp.GetBitmap(&bitmap);								//���ͼƬ��Ϣ
	memDC.BitBlt(0,0,bitmap.bmWidth,bitmap.bmHeight,pDeskDC,0,0,SRCCOPY);//����ͼƬ

	if(m_Cursor.GetCheck())								//ѡ��ץȡ���
	{
		CPoint point;
		GetCursorPos(&point);							//���λ��
		HICON hicon = (HICON)GetCursor();				//������ͼ����
		memDC.DrawIcon(point.x-10,point.y-10,hicon);					//�������ͼ��
	}


	DWORD size=bitmap.bmWidthBytes*bitmap.bmHeight;		//ͼƬ���ݴ�С
	LPSTR lpData=(LPSTR)GlobalAllocPtr(GPTR,size);
	int panelsize  = 0;									//��¼��ɫ���С
	if(bitmap.bmBitsPixel<16)							//�ж��Ƿ�Ϊ���ɫλͼ
		panelsize = pow(2,bitmap.bmBitsPixel*sizeof(RGBQUAD));
	BITMAPINFOHEADER *pBInfo = (BITMAPINFOHEADER*)LocalAlloc(LPTR,
		sizeof(BITMAPINFO)+panelsize);					//λͼͷָ��
	pBInfo->biBitCount       = bitmap.bmBitsPixel;		//λͼ����
	pBInfo->biClrImportant   = 0;
	pBInfo->biCompression    = 0;
	pBInfo->biHeight         = bitmap.bmHeight;			//λͼ��
	pBInfo->biPlanes         = bitmap.bmPlanes;
	pBInfo->biSize           = sizeof(BITMAPINFO);
	pBInfo->biSizeImage      = bitmap.bmWidthBytes*bitmap.bmHeight;	//����
	pBInfo->biWidth          = bitmap.bmWidth;			//λͼ��
	pBInfo->biXPelsPerMeter  = 0;
	pBInfo->biYPelsPerMeter  = 0;
	GetDIBits(memDC.m_hDC,bmp,0,pBInfo->biHeight,lpData,
		(BITMAPINFO*)pBInfo,DIB_RGB_COLORS);

	CString name,str;
	CTime time = CTime::GetCurrentTime();				//ץͼʱ��
	str.Format("%04d",m_Num++);
	if(path.Right(1) == "\\")
		name = path+time.Format("%Y%m%d")+str+".bmp";//�����ļ�����·��
	else
		name = path+"\\"+time.Format("%Y%m%d")+str+".bmp";//�����ļ�����·��

	BITMAPFILEHEADER bfh;								//λͼ�ļ�ͷ
	bfh.bfReserved1 = bfh.bfReserved2 = 0;
	bfh.bfType      = ((WORD)('M'<< 8)|'B');
	bfh.bfSize      = 54+size;
	bfh.bfOffBits   = 54;
	CFile file;
	if(file.Open(name,CFile::modeCreate|CFile::modeWrite))//����λͼ�ļ�
	{
		file.WriteHuge(&bfh,sizeof(BITMAPFILEHEADER));	//д��λͼ�ļ�ͷ
		file.WriteHuge(pBInfo,sizeof(BITMAPINFOHEADER));//д���ļ�ͷ
		file.WriteHuge(lpData,size);					//д������
		file.Close();									//�ر��ļ�
	}
}

void CGraspBmpDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	::UnregisterHotKey(this->GetSafeHwnd(),HOTKEY_GRASP);
}

void CGraspBmpDlg::OnButsave() 
{
	// TODO: Add your control notification handler code here
	::UnregisterHotKey(this->GetSafeHwnd(),HOTKEY_GRASP);
	WORD wvk,wmod;
	m_HotKey.GetHotKey(wvk,wmod);
	BOOL result=RegisterHotKey(this->GetSafeHwnd(),HOTKEY_GRASP,wmod,wvk);
	if(!result)
	{
		MessageBox("ע���ȼ�ʧ��");
		return;
	}

	CString path,strwvk,strwmod,strmouse;
	m_Path.GetWindowText(path);
	WritePrivateProfileString("Set","path",path,"./System.ini");
	strwvk.Format("%d",wvk);
	WritePrivateProfileString("Set","wvk",strwvk,"./System.ini");
	strwmod.Format("%d",wmod);
	WritePrivateProfileString("Set","wmod",strwmod,"./System.ini");
	strmouse.Format("%d",m_Cursor.GetCheck());
	WritePrivateProfileString("Set","capmouse",strmouse,"./System.ini");
}

void CGraspBmpDlg::OnButexit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

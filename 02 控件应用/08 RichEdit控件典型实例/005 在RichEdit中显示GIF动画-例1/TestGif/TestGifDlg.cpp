// TestGifDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestGif.h"
#include "TestGifDlg.h"

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
// CTestGifDlg dialog

CTestGifDlg::CTestGifDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestGifDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestGifDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestGifDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestGifDlg)
	DDX_Control(pDX, IDC_RICHEDIT, m_RichEdit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestGifDlg, CDialog)
	//{{AFX_MSG_MAP(CTestGifDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestGifDlg message handlers

BOOL CTestGifDlg::OnInitDialog()
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

void CTestGifDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestGifDlg::OnPaint() 
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
HCURSOR CTestGifDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestGifDlg::OnOK() 
{
	CFileDialog flDlg(TRUE,"","",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"ͼƬ�ļ�|*.bmp;*.gif;*.jpg;*.jpeg;*.ico;||",this);
	if (flDlg.DoModal()==IDOK)
	{
		CString csFile = flDlg.GetPathName();
		IRichEditOle *lpRichOle = m_RichEdit.GetIRichEditOle();
		if (lpRichOle != NULL)
		{
			InsertImage(lpRichOle,csFile);
			lpRichOle->Release();
			lpRichOle = NULL;
		}
	}
}

BOOL CTestGifDlg::InsertImage(IRichEditOle *lpRichEditOle, CString &csFileName)
{
	IStorage *lpStorage = NULL;        					//�洢�ӿ�
	IOleObject *lpOleObject = NULL;   					//����Ole����ָ��
	LPLOCKBYTES lpLockBytes = NULL;				//����LOCKBYTESָ�룬���ڴ����洢����
	IOleClientSite *lpOleClientSite = NULL;				//����IOleClientSite�ӿ�ָ��
	GIFLib::ICGifPtr lpAnimator;						//����ATL�ؼ��ӿ�ָ��
	CLSID clsid;									//������ID����
	REOBJECT reobject;								//����InsertOjbect�����Ĳ���
	HRESULT hr;
	if (lpRichEditOle == NULL)
	{
		return FALSE;
	}
	hr = ::CoInitialize(NULL);							//��ʼ��Com
	if (FAILED(hr))
	{
		_com_issue_error(hr);
	}
	hr = lpAnimator.CreateInstance(GIFLib::CLSID_CGif);		//����ATL�ؼ�ʵ��
	if (FAILED(hr))
	{
		_com_issue_error(hr);
	}
	lpRichEditOle->GetClientSite(&lpOleClientSite);			//��ȡIOleClientSite
	try
	{
		//��ȡOLE����ӿ�
		hr = lpAnimator->QueryInterface(IID_IOleObject,(void**)&lpOleObject);
		if (FAILED(hr))
		{
			AfxMessageBox("Error QueryInterface");
		}
		hr = lpOleObject->GetUserClassID(&clsid);			//��ȡ��ID
		if (FAILED(hr))
		{
			AfxMessageBox("Error GetUserClassID");
		}
		lpOleObject->SetClientSite(NULL);				//��ֹ���ִ�����ʾ
		lpOleObject->SetClientSite(lpOleClientSite);			//����ATL�ؼ���OleClientSite
		hr = ::CreateILockBytesOnHGlobal(NULL,TRUE,&lpLockBytes); //����LOCKBYTE����
		if (FAILED(hr))
		{
			AfxThrowOleException(hr);
		}
		ASSERT(lpLockBytes != NULL);
		hr = ::StgCreateDocfileOnILockBytes(lpLockBytes, STGM_SHARE_EXCLUSIVE | STGM_CREATE | 
			STGM_READWRITE, 0,&lpStorage);			//�������洢����
		if (FAILED(hr))
		{
			VERIFY(lpLockBytes->Release() == 0);
			lpLockBytes = NULL;
			AfxThrowOleException(hr);
		}
		ZeroMemory(&reobject,sizeof(REOBJECT)); 	//��ʼ����������
		reobject.cbStruct = sizeof(REOBJECT);			//���ýṹ�Ĵ�С
		reobject.clsid = clsid;						//������ID
		reobject.cp = REO_CP_SELECTION;
		reobject.dvaspect = DVASPECT_CONTENT;
		reobject.dwFlags = REO_BLANK;
		reobject.poleobj = lpOleObject;				//����Ole����
		reobject.polesite =lpOleClientSite;				//����OleeClientSite
		reobject.pstg = lpStorage;					//���ø��洢
		hr = lpRichEditOle->InsertObject(&reobject);		//�������
		hr = lpAnimator->LoadFromFile(csFileName.AllocSysString());	//�����ļ�
	  if (FAILED(hr))
		{
			AfxThrowOleException(hr);
		}
		RedrawWindow();    						//ˢ�´���
		lpOleClientSite->SaveObject();				//����Ole����
		OleSetContainedObject(lpOleObject,TRUE);		//������������
	}
	catch (CException* e)
	{
		e->Delete();
	}
	lpAnimator->Release();					//�ͷ�ATL�ӿ�ָ��
	lpStorage->Release();						//�ͷŴ洢�ӿ�ָ��
	return TRUE;
}


// ServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About


//�����̺߳�����ʵ���ļ��ķ���
DWORD __stdcall ThreadProc(LPVOID lpParameter)
{
	CServerDlg* pDlg = (CServerDlg*) lpParameter;

	//�ְ������ļ�
	//��ȡ�ļ�����
	CFile file;
	file.Open(pDlg->m_szFileName, CFile::modeRead);
	DWORD dwLen = file.GetLength() + 128;	//128��ʾ�ļ���ռ�õĿռ�
	//����ÿ�η������ݵĴ�С
	int nPerSendSize = 1024*6;
	//������Ҫ�ֶ��ٸ����ݰ������ļ�
	int nPackageCount = dwLen / nPerSendSize;
	int nMod = dwLen % nPerSendSize;
	
	//���͵�һ�����ݰ����öԷ�ȷ���Ƿ�����ļ�
	//ȷ����һ�����ݰ��Ĵ�С
	int nFirstPackSize = 0;
	if (nPackageCount > 0)
	{
		nFirstPackSize = nPerSendSize;
	}
	else
	{
		nFirstPackSize = nMod;
	}

	int nPackageSize = sizeof(CPackage);
	HGLOBAL hGlobal = GlobalAlloc(GHND, nFirstPackSize + nPackageSize);
	BYTE* pBuffer = (BYTE*)GlobalLock(hGlobal);
	CPackage* pPackage = (CPackage*) pBuffer;
	pPackage->m_Type = PTFILE;
	pPackage->m_Flag = SFBEGIN;
	pPackage->m_dwFileSize = dwLen;
	pPackage->m_dwSize = nPackageSize;
	pPackage->m_dwData = nFirstPackSize;

	BYTE* pTmp = pBuffer + nPackageSize;
	//�����ļ���
	memset(pTmp, 0, 128);
	CString szName = file.GetFileName();
	memcpy(pTmp, szName.GetBuffer(0), szName.GetLength());
	szName.ReleaseBuffer();
	pTmp = pTmp + 128;
	//�����ļ�����
	file.ReadHuge(pTmp, nFirstPackSize - 128);
	pDlg->m_ClientSock.Send(pBuffer, nFirstPackSize + nPackageSize);
	GlobalUnlock(hGlobal);
	GlobalFree(hGlobal);

	pDlg->m_Progress.SetRange32(0, dwLen);
	pDlg->m_Progress.SetPos(nFirstPackSize - 128);

	//�ж��ļ������Ƿ����
	if (nFirstPackSize >= dwLen)	//һ�����ݰ���������ļ��ķ���
	{
		file.Close();
		pDlg->m_Progress.SetPos(0);
		pDlg->m_bSending = FALSE;
		return 0;
	}

	//�ȴ��Է����ܷ��������ȡ����������
	pDlg->m_RequestInfo = RIUNKNOWN;
	while (true)
	{
		if (pDlg->m_RequestInfo != RIUNKNOWN)
			break;
	}
	if (pDlg->m_RequestInfo == RIDENY)	//�Է��ܾ������ļ�
	{
		pDlg->m_Progress.SetPos(0);
		file.Close();
		pDlg->m_bSending = FALSE;
		return 0;
	}
	else if (pDlg->m_RequestInfo == RICANCEL)	//�Է�ȡ�������ļ�
	{
		pDlg->m_Progress.SetPos(0);
		file.Close();
		pDlg->m_bSending = FALSE;
		return 0;		
	}
	else if (pDlg->m_RequestInfo == RIACCEPT)	//�Է�ͬ�ⷢ���ļ�
	{
		//�ְ����������ļ�
		for(int i=1; i<nPackageCount; i++)
		{
			//�ڷ��͹������ж϶Է��Ƿ�ȡ������
			if (pDlg->m_RequestInfo == RICANCEL)
			{	
				pDlg->m_Progress.SetPos(0);
				file.Close();
				pDlg->m_bSending = FALSE;
				return 0;			
			}

			hGlobal = GlobalAlloc(GHND, nPerSendSize + nPackageSize);

			BYTE* pBuffer = (BYTE*)GlobalLock(hGlobal);
			CPackage* pPackage = (CPackage*) pBuffer;
			pPackage->m_Type = PTFILE;
			if (nMod == 0 && i == nPackageCount-1)
				pPackage->m_Flag = SFEND;
			else
				pPackage->m_Flag = SFSENDING;

			pPackage->m_dwFileSize = dwLen;
			pPackage->m_dwSize = nPackageSize;
			pPackage->m_dwData = nPerSendSize;			
			//�����ļ���	
			BYTE* pTmp = pBuffer + nPackageSize;
			//�����ļ�����
			file.ReadHuge(pTmp, nPerSendSize);
			pDlg->m_ClientSock.Send(pBuffer, nPerSendSize + nPackageSize);
			int nPos = pDlg->m_Progress.GetPos();
			nPos += nPerSendSize;
			pDlg->m_Progress.SetPos(nPos);

			GlobalUnlock(hGlobal);
			GlobalFree(hGlobal);			
		}
		if (nPackageCount > 0 && nMod != 0)	//��ֹ�ļ�̫С�������·����ļ�
		{
			//�������һ�����ݰ�
			hGlobal = GlobalAlloc(GHND, nMod + nPackageSize);

			BYTE* pBuffer = (BYTE*)GlobalLock(hGlobal);
			CPackage* pPackage = (CPackage*) pBuffer;
			pPackage->m_Type = PTFILE;
			pPackage->m_Flag = SFEND;
			pPackage->m_dwFileSize = dwLen;
			pPackage->m_dwSize = nPackageSize;
			pPackage->m_dwData = nMod;			
			//�����ļ���	
			BYTE* pTmp = pBuffer + nPackageSize;
			//�����ļ�����
			file.ReadHuge(pTmp, nMod);
			pDlg->m_ClientSock.Send(pBuffer, nMod + nPackageSize);
			GlobalUnlock(hGlobal);
			GlobalFree(hGlobal);
		}
	}
	pDlg->m_Progress.SetPos(0);
	file.Close();
	return 0;
}


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
// CServerDlg dialog

CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CServerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	m_bSending = FALSE;
	m_hSendThread = NULL;
	m_RequestInfo = RIUNKNOWN;
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServerDlg)
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
	DDX_Control(pDX, IDC_FILENAME, m_FileName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialog)
	//{{AFX_MSG_MAP(CServerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_SEND_FILE, OnSendFile)
	ON_BN_CLICKED(IDC_SEND_CANCEL, OnSendCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerDlg message handlers

BOOL CServerDlg::OnInitDialog()
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
	
	m_ServerSock.SetDlg(this);
	m_ServerSock.Create(945);
	m_ServerSock.Listen();
	m_ClientSock.SetDlg(this);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CServerDlg::OnPaint() 
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
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CServerDlg::OnOK() 
{
	
//	CDialog::OnOK();
}

void CServerDlg::OnCancel() 
{
	
	CDialog::OnCancel();
}

void CServerDlg::OnBrowse() 
{
	CFileDialog flDlg(TRUE, "", "", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
						"�����ļ�|*.*||");
	if (flDlg.DoModal()==IDOK)
	{
		CString szFileName = flDlg.GetPathName();
		m_FileName.SetWindowText(szFileName);
	}
}

//���տͻ�������
void CServerDlg::AcceptConnect()
{
	m_ClientSock.ShutDown();
	m_ClientSock.Close();
	m_ServerSock.Accept(m_ClientSock);
}

//��������
void CServerDlg::ReveiveData()
{
	//���նԷ�������Ӧ����Ϣ
	int nPackageSize = sizeof(CPackage);
	BYTE* pBuffer = new BYTE[nPackageSize];
	int nFact = m_ClientSock.Receive(pBuffer, nPackageSize);
	if (nFact >= nPackageSize)
	{
		CPackage* pPackage = (CPackage*)pBuffer;
		if (pPackage->m_Flag == SFCANCEL)	//�Է�ȡ���ļ�����
		{
			m_RequestInfo = RICANCEL;
		}
		else if (pPackage->m_Flag == SFDENY)	//�Է��ܾ������ļ�
		{
			m_RequestInfo = RIDENY;
		}
		else if (pPackage->m_Flag == SFACCEPT)	//�Է�ͬ������ļ�
		{
			m_RequestInfo = RIACCEPT;
		}
	}

	delete [] pBuffer;
}

//�����ļ�
void CServerDlg::OnSendFile() 
{
	if (m_bSending)
	{
		MessageBox("��ǰ�ļ�����û�����������ܷ������ļ�");
		return;
	}
	//�ж��ļ��Ƿ����
	CString szFileName;
	m_FileName.GetWindowText(szFileName);


	if (!szFileName.IsEmpty())
	{
		CFileFind flFind;
		BOOL bRet = flFind.FindFile(szFileName);
		if (bRet)
		{
			//����һ���߳�ʵ�ַ����ļ�
			m_szFileName = szFileName;
			m_hSendThread = CreateThread(NULL, 0, ThreadProc, this, 0, 0);
		}
		else
		{
			MessageBox("�ļ�������!");
		}
	}
}

void CServerDlg::OnSendCancel() 
{
	if (m_bSending)
	{
		//������������
		//...
		//ȡ���ļ�����
		CPackage Package;
		Package.m_Type = PTFILE;
		Package.m_Flag = SFCANCEL;
		Package.m_dwFileSize = 0;
		Package.m_dwSize = sizeof(CPackage);
		Package.m_dwData = 0;
		m_ClientSock.Send(&Package, sizeof(CPackage));

		m_bSending = FALSE;
	}
}

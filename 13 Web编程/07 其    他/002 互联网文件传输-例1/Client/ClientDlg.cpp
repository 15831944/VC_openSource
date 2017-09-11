// ClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"

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
// CClientDlg dialog

CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	m_bSending = FALSE;
	m_hGlobal = NULL;
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientDlg)
	DDX_Control(pDX, IDC_SERVERIP, m_ServerIP);
	DDX_Control(pDX, IDC_PORT, m_Port);
	DDX_Control(pDX, IDC_FILERECPROGRESS, m_Progress);
	DDX_Control(pDX, IDC_CANCELREC, m_Cancel);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	//{{AFX_MSG_MAP(CClientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_BN_CLICKED(IDC_CANCELREC, OnCancelRec)
	ON_BN_CLICKED(IDC_CONNECT, OnConnect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDlg message handlers

BOOL CClientDlg::OnInitDialog()
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
	m_ClientSock.SetDlg(this);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CClientDlg::OnPaint() 
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
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CClientDlg::OnOK() 
{
	
}

//��������
void CClientDlg::ReceiveData()
{
	static int nMaxLen = 1024*100;//���������󳤶�
	HGLOBAL hGlobal = GlobalAlloc(GHND, nMaxLen);//�������ȫ�ֻ�����
	BYTE* pBuffer = (BYTE*)GlobalLock(hGlobal);//��ȡָ��ȫ�ֻ�����ָ��
	int nFact = m_ClientSock.Receive(pBuffer, nMaxLen);//��������
	int nPackage = sizeof(CPackage);	//�������ݰ���С
	int SunSize = 0;//���δ��������ܴ�С
	BYTE *Ptemp = NULL;//������������ָ��
	BYTE * temp = NULL;//ȫ�ֻ�����ָ��
	if (m_hGlobal != NULL)//��ȫ�ֻ������д�������
	{
		BYTE* pData = (BYTE*)GlobalLock(m_hGlobal);
		int GSize = GlobalSize(m_hGlobal);//��ȡ���ݴ�С
		SunSize = GSize + nFact;//ȫ�ֻ�����������������ݴ�С
		temp = new BYTE[SunSize];//���屾�δ������ʱ������
		Ptemp = temp;
		memcpy(temp,pData,GSize);//����ȫ�ֻ�����������
		memcpy(temp + GSize,pBuffer,nFact);//���Ʊ��ν��յ�����
		GlobalUnlock(m_hGlobal);
		GlobalFree(m_hGlobal);
		m_hGlobal = NULL;
	}
	else
	{
		SunSize = nFact;
		Ptemp = pBuffer;
	}

	CPackage* pPackage = (CPackage*)Ptemp;//��ȡ��Ҫ����ĵ�һ����
	while ((SunSize >= nPackage) && (SunSize >= pPackage->m_dwData))	
	{
		HandleRecData(pPackage);//�����
		SunSize -= nPackage + pPackage->m_dwData;//�ܴ�С��ȥ�Ѵ������С
		Ptemp += nPackage + pPackage->m_dwData;//��ָ��ָ����һ�����ĵ�ַ
		pPackage = (CPackage*)Ptemp;//��ȡ���δ���İ�
	}
	if (SunSize > 0)//��ʣ������д��ȫ�ֻ�����
	{
		m_hGlobal = GlobalAlloc(GHND, SunSize);
		BYTE* pData = (BYTE*)GlobalLock(m_hGlobal);
		memcpy(pData,Ptemp,SunSize);
		GlobalUnlock(m_hGlobal);
	}
	else
	{
		GlobalUnlock(m_hGlobal);
		GlobalFree(m_hGlobal);
		m_hGlobal = NULL;
	}

	if (temp != NULL)
		delete temp;

	GlobalUnlock(hGlobal);
	GlobalFree(hGlobal);
}

void CClientDlg::HandleRecData(CPackage *pPackage)
{
	if (pPackage != NULL)
	{
		if (pPackage->m_Type==PTFILE)				//ֻ�����ļ�����
		{
			static CFile file;			
			
			if (pPackage->m_Flag==SFBEGIN)			//��ʼ����
			{
				//��ȡ�ļ���
				char szFileName[128] = {0};
				memcpy(szFileName, pPackage->m_Data, 128);				
				CFileDialog flDlg(FALSE, "", szFileName);				
				if (flDlg.DoModal()==IDOK) 
				{
					if (m_bSending)						//��ǰ�ļ�����û�н������ַ���һ���ļ�
					{
						file.Close();
					}

					m_Progress.SetPos(0);
					//ȷ������ļ���С
					DWORD dwFileSize = pPackage->m_dwFileSize;
					//���ý������ı�ʾ��Χ
					m_Progress.SetRange32(0, dwFileSize);
					
					CString szFile = flDlg.GetPathName();
					file.Open(szFile, CFile::modeCreate|CFile::modeReadWrite);
					//�������ݱ����ļ����ݵĴ�С
					int nFileLen = pPackage->m_dwData - 128;
					
					if (nFileLen >= dwFileSize)	//�ļ��Ƚ�С��ֻ����һ�����ݰ���������ļ�����
					{
						m_bSending = FALSE;					//���ý������
						file.Close();
						m_Progress.SetPos(0);
						m_Cancel.EnableWindow(FALSE);
						return;
					}

					//��ȡ���ݱ��е��ļ�����
					BYTE* pTmp = pPackage->m_Data;
					pTmp += 128;	//�ӹ��ļ������ݣ���λ���ļ�����
					file.WriteHuge(pTmp, nFileLen);
					m_Progress.SetPos(nFileLen);
					//���ͽ��ձ��
					CPackage package;
					package.m_Type = PTFILE;
					package.m_Flag = SFACCEPT;
					package.m_dwSize = sizeof(CPackage);
					package.m_dwData = 0;
					package.m_dwFileSize = 0;
					m_ClientSock.Send(&package, sizeof(CPackage));	

					m_bSending = TRUE;
					m_Cancel.EnableWindow();
				}
				else
				{
					//ȡ���ļ�����
					CPackage package;
					package.m_Type = PTFILE;
					package.m_Flag = SFDENY;
					package.m_dwSize = sizeof(CPackage);
					package.m_dwData = 0;
					package.m_dwFileSize = 0;
					m_ClientSock.Send(&package, sizeof(CPackage));
					m_Cancel.EnableWindow();

				}
			}
			else if (pPackage->m_Flag==SFSENDING)	//�ļ�������
			{
				file.WriteHuge(pPackage->m_Data, pPackage->m_dwData);
				int nPos = m_Progress.GetPos();
				nPos += pPackage->m_dwData;
				m_Progress.SetPos(nPos);
			}
			else if (pPackage->m_Flag==SFEND)		//�ļ����ͽ���
			{
				file.WriteHuge(pPackage->m_Data, pPackage->m_dwData);
				m_bSending = FALSE;					//���ý������
				m_Cancel.EnableWindow(FALSE);
				file.Close();
				m_Progress.SetPos(0);
			}
			else if (pPackage->m_Flag==SFCANCEL)	//�Է�ȡ�����ļ�����
			{
				m_bSending = FALSE;					//���ý������
				file.Close();
				m_Cancel.EnableWindow(FALSE);
				m_Progress.SetPos(0);
				MessageBox("�Է�ȡ�����ļ�����!");
			}
		}
	}
}

void CClientDlg::OnExit() 
{
	CDialog::OnCancel();	
}

//ȡ�������ļ�
void CClientDlg::OnCancelRec() 
{
	if (m_bSending)
	{
		CPackage package;
		package.m_Type = PTFILE;
		package.m_Flag = SFCANCEL;	//ȡ�������ļ�
		package.m_dwSize = sizeof(CPackage);
		package.m_dwData = 0;
		package.m_dwFileSize = 0;
		m_ClientSock.Send(&package, sizeof(CPackage));		
	}
}

//���������������
void CClientDlg::OnConnect() 
{
	CString szServerIP, szPort;
	m_ServerIP.GetWindowText(szServerIP);
	m_Port.GetWindowText(szPort);
	int nPort = atoi(szPort.GetBuffer(0));
	szPort.ReleaseBuffer(0);
	if (!m_bSending)		//��ǰû�н����ļ�����
	{
		m_ClientSock.ShutDown();
		m_ClientSock.Close();
		m_ClientSock.Create();
		BOOL bRet = m_ClientSock.Connect(szServerIP, nPort);	
		if (!bRet)
		{
			MessageBox("����ʧ��!");
		}
	}
}

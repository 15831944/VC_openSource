// BindAppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BindApp.h"
#include "BindAppDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

#define FINDFLAG 0x12345678

//����һ���ṹ,fileFlagΪȫ�ֱ��������ڼ�¼��ִ���ļ��ĳ���
struct FILE_FLAG
{
	UINT	nFindFlag;		//���ұ�ʶ
	UINT	nFileLen;		//�ļ�����
} fileFlag = {FINDFLAG, 0};


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
// CBindAppDlg dialog

CBindAppDlg::CBindAppDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBindAppDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBindAppDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_MAINICON);
}

void CBindAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBindAppDlg)
	DDX_Control(pDX, IDC_FILE3, m_File3);
	DDX_Control(pDX, IDC_FILE2, m_File2);
	DDX_Control(pDX, IDC_FILE1, m_File1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBindAppDlg, CDialog)
	//{{AFX_MSG_MAP(CBindAppDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUILD, OnBuild)
	ON_BN_CLICKED(IDC_BROWSE1, OnBrowse1)
	ON_BN_CLICKED(IDC_BROWSE2, OnBrowse2)
	ON_BN_CLICKED(IDC_CANCEL, OnCancel)
	ON_BN_CLICKED(IDC_BROWSE3, OnBrowse3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBindAppDlg message handlers

BOOL CBindAppDlg::OnInitDialog()
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
	
	memset(m_szSelfName, 0, MAX_PATH);
	//��ȡ��ִ���ļ�������
	GetModuleFileName(NULL, m_szSelfName, MAX_PATH);

	struct _stat fileState;
	_stat(m_szSelfName, &fileState);
	
	//��ǰ�ļ��ѱ�����
	if (fileFlag.nFileLen !=0)
	{
		RunBindExe();
		exit(0);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBindAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBindAppDlg::OnPaint() 
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
HCURSOR CBindAppDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBindAppDlg::OnOK() 
{
	
}

void CBindAppDlg::OnCancel() 
{
	CDialog::OnCancel();	
}

//���ɿ�ִ���ļ�
void CBindAppDlg::OnBuild() 
{
	//��ȡ�ļ�1
	CString szFile1, szFile2, szFile3;
	m_File1.GetWindowText(szFile1);
	m_File2.GetWindowText(szFile2);
	m_File3.GetWindowText(szFile3);

	if (!szFile1.IsEmpty() && !szFile2.IsEmpty() && !szFile3.IsEmpty())
	{
		FILE* pflSelf	= NULL;	//��ִ���ļ�����
		FILE* pflFinal	= NULL;	//�������ɵĿ�ִ���ļ�
		FILE* pflFirst	= NULL;	//��һ��������ļ�
		FILE* pflSecond	= NULL;	//�ڶ���������ļ�
		struct _stat fileState;
		//��ȡ����Ŀ�ִ���ļ���Ϣ
		_stat(m_szSelfName, &fileState);
		//��ȡ�ļ�����
		DWORD dwFileLen = fileState.st_size;
		fileFlag.nFileLen = dwFileLen;
		//Ϊ�ļ����仺����
		BYTE* pFileBuffer = (BYTE*)	malloc(dwFileLen);
		//�򿪵�ǰ�ļ�
		pflSelf = fopen(m_szSelfName, "rb");
		if (pflSelf == NULL)
		{
			MessageBox("�������ļ�ʧ��!", "��ʾ");
			return;
		}
		//��ȡ�ļ�
		DWORD dwRead = fread(pFileBuffer, sizeof(char), dwFileLen, pflSelf);
		fclose(pflSelf);
		if (dwRead != dwFileLen)
		{
			MessageBox("��ȡ�����ļ���������!", "��ʾ");
			return;
		}
		
		//д���ļ��ĳ���
		UINT nFlag  = FINDFLAG;
		//�ڿ�ִ���ļ��в���FINDFLAG����ֵ��Ŀ���Ƕ�λ��ȫ�ֱ���fileFlag�����ݴ洢λ��
		for(int i=0; i<dwFileLen-sizeof(UINT); i+=sizeof(UINT))
		{
			//�ڿ�ִ���ļ��в���FINDFLAG��0x12345678����Ϊȫ�ֱ���fileFlag�а�����0x12345678
			for(int j=0; j<sizeof(UINT); j++)
			{
				if (pFileBuffer[i+j] != ((BYTE*)&nFlag)[j])
					break;
			}
			if (j == sizeof(UINT))	//�ڿ�ִ���ļ��з�����0x12345678����
			{
				//�޸Ŀ�ִ���ļ���fileFlag�����ݴ洢λ���ϵ�����
				memcpy(pFileBuffer+i, &fileFlag, sizeof(FILE_FLAG));
				break;
			}
		}
		if (i >= dwFileLen-sizeof(UINT))	//�ڿ�ִ���ļ���û�з���0x12345678����
		{
			free(pFileBuffer);
			MessageBox("�����ִ���ļ�����!", "��ʾ");
			return;
		}
		
		//д���һ����ִ���ļ�
		if (_stat(szFile1.GetBuffer(0), &fileState) != 0 || fileState.st_size ==0)
		{
			free(pFileBuffer);
			MessageBox("��ȡ��һ���󶨵��ļ�ʧ��!", "��ʾ");			
			return;
		}
		szFile1.ReleaseBuffer();
		//�������յĿ�ִ���ļ�
		pflFinal = fopen(szFile3.GetBuffer(0), "wb");
		if (pflFinal == NULL)
		{
			free(pFileBuffer);
			MessageBox("������ִ���ļ�ʧ��!", "��ʾ");			
			return;
		}
		szFile3.ReleaseBuffer();
		//����д�������ļ������յĿ�ִ���ļ���
		fwrite(pFileBuffer, sizeof(char), dwFileLen, pflFinal);
		//�򿪵�һ����ִ���ļ�
		pflFirst = fopen(szFile1.GetBuffer(0), "rb");
		if (pflFirst == NULL)
		{
			fclose(pflFinal);
			//ɾ�����ɵ��ļ�
			//...
			free(pFileBuffer);
			MessageBox("�򿪵�һ���󶨵��ļ�ʧ��!", "��ʾ");
			return;
		}
		szFile1.ReleaseBuffer();
		//д���һ��Ҫ������ļ�����
		fwrite(&fileState.st_size, sizeof(char), sizeof(fileState.st_size), pflFinal);
		//����һ���ļ�д�뵽���յĿ�ִ���ļ���
		free(pFileBuffer);
		pFileBuffer = (BYTE*)malloc(fileState.st_size);
		fread(pFileBuffer, sizeof(char), fileState.st_size, pflFirst);
		fwrite(pFileBuffer, sizeof(char), fileState.st_size, pflFinal);
		fclose(pflFirst);
		free(pFileBuffer);
		//д��ڶ���Ҫ������ļ�
		if (_stat(szFile2.GetBuffer(0), &fileState) != 0 || fileState.st_size ==0)
		{
			MessageBox("��ȡ�ڶ����󶨵��ļ�ʧ��!", "��ʾ");			
			return;
		}
		szFile2.ReleaseBuffer();	
		pflSecond = fopen(szFile2.GetBuffer(0), "rb");
		if (pflSecond == NULL)
		{
			MessageBox("�򿪵ڶ����󶨵��ļ�ʧ��!", "��ʾ");
			return;
		}
		szFile2.ReleaseBuffer();
		pFileBuffer = (BYTE*)malloc(fileState.st_size);
		fread(pFileBuffer, sizeof(char), fileState.st_size, pflFirst);
		fwrite(pFileBuffer, sizeof(char), fileState.st_size, pflFinal);
		fclose(pflSecond);
		free(pFileBuffer);
		MessageBox("�����!", "��ʾ");

	}
}

void CBindAppDlg::OnBrowse1() 
{
	CFileDialog flDlg(TRUE, "", "", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
						"��ִ���ļ�|*.exe||");
	if (flDlg.DoModal()==IDOK)
	{
		CString szFileName = flDlg.GetPathName();
		m_File1.SetWindowText(szFileName);
	}
}

void CBindAppDlg::OnBrowse2() 
{
	CFileDialog flDlg(TRUE, "", "", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
						"��ִ���ļ�|*.exe||");
	if (flDlg.DoModal()==IDOK)
	{
		CString szFileName = flDlg.GetPathName();
		m_File2.SetWindowText(szFileName);
	}	
}

void CBindAppDlg::OnBrowse3() 
{
	CFileDialog flDlg(TRUE, "", "", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
						"��ִ���ļ�|*.exe||");
	if (flDlg.DoModal()==IDOK)
	{
		CString szFileName = flDlg.GetPathName();
		m_File3.SetWindowText(szFileName);
	}	
}

//���а󶨵�Exe�ļ�
void CBindAppDlg::RunBindExe()
{
	FILE* pflSelf	= NULL;		//��ǰ�ļ�����
	FILE* pflFirst	= NULL;		//����ĵ�һ���ļ�
	FILE* pflSecond = NULL;		//����ĵڶ����ļ�
	char  pszFirstFile[]  = "First.exe";
	char  pszSecondFile[] = "Second.exe";
	
	pflSelf = fopen(m_szSelfName, "rb");

	if (pflSelf == NULL)
	{
		return;
	}
	pflFirst = fopen(pszFirstFile, "wb");
	if (pflFirst == NULL)
	{
		fclose(pflSelf);
		return;
	}
	//��λ����һ���ļ��Ľ�β
	fseek(pflSelf, fileFlag.nFileLen, SEEK_SET);
	//��ȡ��һ���󶨵��ļ�����
	
	UINT nFileLen = 0;
	if (fread(&nFileLen, sizeof(char), sizeof(UINT), pflSelf)==0)
	{
		fclose(pflSelf);
		fclose(pflFirst);
		return;
	}
	//��󶨵ĵ�һ���ļ���д������
	BYTE* pBuffer = (BYTE*) malloc(nFileLen);
	fread(pBuffer, sizeof(char), nFileLen, pflSelf);
	fwrite(pBuffer, sizeof(char), nFileLen, pflFirst);
	fclose(pflFirst);

	//��󶨵ĵڶ����ļ���д������
	pflSecond = fopen(pszSecondFile, "wb");
	if (pflSecond == NULL)
	{
		fclose(pflSelf);
		free(pBuffer);
		return;
	}	
	int nReadSize = 0;
	while(nReadSize = fread(pBuffer, sizeof(char), nFileLen, pflSelf))
	{
		fwrite(pBuffer, sizeof(char), nReadSize, pflSecond);
	}
	fclose(pflSecond);
	free(pBuffer);
	fclose(pflSelf);

	RunExeFile(pszFirstFile);
	RunExeFile(pszSecondFile);

}

void CBindAppDlg::RunExeFile(LPCTSTR lpExeFile)
{
     HANDLE hProc;
     PROCESS_INFORMATION procInfo;
     STARTUPINFO startInfo;
     memset(&startInfo, 0, sizeof(STARTUPINFO));
     startInfo.cb = sizeof(STARTUPINFO);
	 CreateProcess(lpExeFile, NULL, NULL, NULL, FALSE,
					NORMAL_PRIORITY_CLASS, NULL, NULL, &startInfo, &procInfo);	 
	 hProc = procInfo.hProcess;       
     WaitForSingleObject(hProc, INFINITE);
     unlink(lpExeFile);
}


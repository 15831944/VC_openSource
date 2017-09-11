// ForceDeleteDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ForceDelete.h"
#include "ForceDeleteDlg.h"


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
// CForceDeleteDlg dialog

CForceDeleteDlg::CForceDeleteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CForceDeleteDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CForceDeleteDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	m_dwProcSize = 0x20000;
	m_pProcInfo = (UCHAR*)VirtualAlloc ((void*)0x100000, m_dwProcSize, 
										MEM_COMMIT, PAGE_READWRITE);
}

void CForceDeleteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CForceDeleteDlg)
	DDX_Control(pDX, IDC_FILENAME, m_FileName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CForceDeleteDlg, CDialog)
	//{{AFX_MSG_MAP(CForceDeleteDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CForceDeleteDlg message handlers

BOOL CForceDeleteDlg::OnInitDialog()
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

	hMod = LoadLibrary("Psapi.dll");
	if (hMod)
	{
		GetModuleFileNameEx = (funGetModuleFileNameExA)GetProcAddress(hMod, "GetModuleFileNameExA");
	//FreeLibrary(hMod);	
	}
	
	NtQueryObject = (PNtQueryObject)GetProcAddress(GetModuleHandle(_T("ntdll.dll")), 
								_T("NtQueryObject"));

	NtQuerySystemInformation = (PNtQuerySystemInformation)GetProcAddress(GetModuleHandle(_T("ntdll.dll")),
								_T("NtQuerySystemInformation"));

	AdjustPrivilege();


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CForceDeleteDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CForceDeleteDlg::OnPaint() 
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
HCURSOR CForceDeleteDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CForceDeleteDlg::OnOK() 
{

}

void CForceDeleteDlg::OnClear() 
{
	//�о������еĽ���
	EnumRunningProc();
	//�оٽ��̴򿪵��ļ����
	EnumProcessOpenedFile();
	//�����ļ����

	m_bFindFile = FALSE;
	DWORD	dwCurProcID = GetCurrentProcessId();
	int nCount = 0;
		CString szFileName, szDiviceName;
		m_FileName.GetWindowText(szFileName);
		GetDiviceName(szFileName, szDiviceName);			

	for (POSITION pos = m_FileHandles.GetHeadPosition(); pos != NULL;)
	{
		SYSTEM_HANDLE& fileHandle = m_FileHandles.GetNext(pos);

		//�ڽ����в��Ҿ��
		SYSTEM_PROCESS_INFORMATION* pProcInfo = NULL;
		
		BOOL bFindRet =  m_SysProcesses.Lookup(fileHandle.ProcessID, pProcInfo);
		if (!bFindRet)
		{
			continue;
		}
		m_hFile = (HANDLE)fileHandle.HandleNumber;
	
		if (dwCurProcID != fileHandle.ProcessID)
		{
			HANDLE hProcess = OpenProcess(PROCESS_DUP_HANDLE, TRUE, fileHandle.ProcessID);	
			HANDLE hSysFile = (HANDLE)fileHandle.HandleNumber;
			//����Զ�̽��̾������ǰ������
			DuplicateHandle(hProcess, hSysFile, GetCurrentProcess(), &m_hFile, 0, FALSE, DUPLICATE_SAME_ACCESS);
			CloseHandle(hProcess);
		}

		memset(m_FileNames, 0, MAX_FILENAME);
		NtQueryObject(m_hFile, 1, m_FileNames, MAX_FILENAME, NULL);
		CloseHandle(m_hFile);
		//�ж��ļ��Ƿ�����ɾ�����ļ�
		//���Ƚ�DOS�ļ���ת��Ϊ�豸�ļ���
		UCHAR* pchData = m_FileNames;
		pchData += 8;
		if (wcscmp((unsigned short*)pchData, szDiviceName.AllocSysString()) == 0)
		{
			//�ر��ļ����
			CloseFileHandle(fileHandle.ProcessID, (HANDLE)fileHandle.HandleNumber);	
			m_bFindFile = TRUE;
		//	CloseHandle(m_hFile);
		}
		szDiviceName.ReleaseBuffer();
		nCount ++;   
	}
	if (m_bFindFile == FALSE)
	{
		//�ж��ļ��Ƿ���һ��ֱ�����е��ļ�
		for (POSITION ps = m_SysProcesses.GetStartPosition(); ps != NULL;)
		{
			DWORD dwProcID;
			SYSTEM_PROCESS_INFORMATION* pProcInfo = NULL;
			m_SysProcesses.GetNextAssoc(ps, dwProcID, pProcInfo);
			if (pProcInfo != NULL)
			{
				HANDLE hProcess = OpenProcess( PROCESS_ALL_ACCESS , TRUE, dwProcID);
				if (hProcess)
				{
					char chFileName[MAX_PATH] = {0};

					GetModuleFileNameEx(hProcess, NULL, chFileName, MAX_PATH);
					//����ϵͳ�����еĽ���
					if (strcmp(szFileName.GetBuffer(0), chFileName) == 0)
					{
						TerminateProcess(hProcess, 0);
						m_bFindFile = true;					
					}
					CloseHandle(hProcess);
				}
			}
		}
	}
	if (m_bFindFile == TRUE && MessageBox("ȷʵҪɾ���ļ���?", "��ʾ", MB_YESNO)==IDYES)
	{
		//ɾ���ļ�
		BOOL bDeleted = DeleteFile(szFileName);
		if (bDeleted)
		{
			m_FileName.SetWindowText("");
			MessageBox("ɾ���ɹ�!");
		}
	}
}

void CForceDeleteDlg::OnBrowse() 
{
	CFileDialog flDlg(TRUE, "", "", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
						"�����ļ�|*.*||");
	if (flDlg.DoModal() == IDOK)
	{
		CString szFileName = flDlg.GetPathName();
		m_FileName.SetWindowText(szFileName);
	}
}


//����������Ȩ��ʹ�����DEBUG��Ȩ
BOOL CForceDeleteDlg::AdjustPrivilege()
{
	HANDLE hToken = NULL;
	LUID uID;
	TOKEN_PRIVILEGES privValue;
	//�򿪽��̷��ʱ�ʶ
	BOOL bPened = OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
	if (!bPened)
	{
		return FALSE;
	}
	//������Ȩֵ
	BOOL bLooked = LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &uID);
	if (!bLooked)
	{
		CloseHandle(hToken);
		return FALSE;
	}
	
	privValue.PrivilegeCount = 1;
	privValue.Privileges[0].Luid = uID;
	privValue.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	BOOL bAdjusted = AdjustTokenPrivileges(hToken, FALSE, &privValue, sizeof(privValue), NULL, NULL);
	if(!bAdjusted)
	{
		CloseHandle(hToken);
		return FALSE;
	}
	
	CloseHandle(hToken);
	return TRUE;
}

//��Զ���߳��йر��ļ����
BOOL CForceDeleteDlg::CloseFileHandle(DWORD dwProcessID, HANDLE hFile)
{
	//���ݽ���ID�򿪽��У���ȡ���̾��
	HANDLE hProcess = OpenProcess(PROCESS_CREATE_THREAD|PROCESS_VM_OPERATION|PROCESS_VM_WRITE|PROCESS_VM_READ,
									FALSE, dwProcessID);
	if (hProcess == NULL)
	{
		return FALSE;
	}

	HMODULE hMod = LoadLibrary("kernel32.dll");

	for (POSITION pos = m_FileHandles.GetHeadPosition(); pos != NULL;)
	{
		SYSTEM_HANDLE& fileHandle = m_FileHandles.GetNext(pos);

		//�ڽ����в��Ҿ��
		SYSTEM_PROCESS_INFORMATION* pProcInfo = NULL;
		BOOL bFindRet =  m_SysProcesses.Lookup(dwProcessID, pProcInfo);
		if (!bFindRet)
		{
			continue;
		}

		HANDLE hFile = (HANDLE)fileHandle.HandleNumber;
		
		DWORD	dwThreadID = 0;
		HANDLE	hThread;
		//����Զ���߳�
		hThread = CreateRemoteThread(hProcess, NULL, 0, 
						(DWORD (__stdcall*)(void *))GetProcAddress(hMod, "CloseHandle"),
						hFile, 0, &dwThreadID);

		if (hThread == NULL)
		{
			CloseHandle(hProcess);
			FreeLibrary(hMod);
			return FALSE;
		}

	}

	CloseHandle(hProcess);
	FreeLibrary(hMod);	
	return TRUE;	
}

//�оٽ��̴򿪵��ļ�
 void CForceDeleteDlg::EnumProcessOpenedFile()
{
	//�оٴ򿪵Ķ�����
	int nCount = 0;
	DWORD dwBufferSize = 0x200;
	DWORD dwFactSize = 0;
	//�ڵ�ǰ������ΪSYSTEM_HANDLE_INFORMATION�ṹ�����洢�ռ�
	SYSTEM_HANDLE_INFORMATION* pSysHandleInformation = (SYSTEM_HANDLE_INFORMATION*)
				VirtualAlloc(NULL, dwBufferSize, MEM_COMMIT, PAGE_READWRITE);
	//��ȡSYSTEM_HANDLE_INFORMATION�ṹ��Ϣ�Ĵ�С
	NtQuerySystemInformation( 16, pSysHandleInformation, dwBufferSize, &dwFactSize);

	VirtualFree(pSysHandleInformation, 0, MEM_RELEASE);
	//����ʵ�ʿռ��С
	pSysHandleInformation = (SYSTEM_HANDLE_INFORMATION*)
				VirtualAlloc(NULL, dwBufferSize = dwFactSize + 256, MEM_COMMIT, PAGE_READWRITE);
	//��ȡϵͳ�������߳̾����Ϣ
	NtQuerySystemInformation( 16, pSysHandleInformation, dwBufferSize, NULL);
	//�����������
	int nCurrentID = GetCurrentProcessId();
	//����б��е��ļ����
	m_FileHandles.RemoveAll();

	for(int i=0; i<pSysHandleInformation->Count; i++)
	{
		int nProcessID = pSysHandleInformation->Handles[i].ProcessID;//����ID
		HANDLE hDup = (HANDLE)pSysHandleInformation->Handles[i].HandleNumber;
		if (nProcessID != nCurrentID)	//Զ�̽���
		{
			HANDLE hProcess = NULL;
			hProcess = ::OpenProcess(PROCESS_DUP_HANDLE, TRUE, nProcessID);//�򿪽���
			HANDLE hFile = (HANDLE)pSysHandleInformation->Handles[i].HandleNumber;
			//����Զ�̽��̾������ǰ������
			DuplicateHandle(hProcess, hFile, GetCurrentProcess(), &hDup, 0, FALSE, DUPLICATE_SAME_ACCESS);
			CloseHandle(hProcess);
		
			//�ж��Ƿ�Ϊ�ļ����
			int nSize = 0;
			NtQueryObject(hDup, 2, NULL, 0, &nSize);
			UCHAR *lpBuffer = new UCHAR[nSize];
			NtQueryObject(hDup, 2, lpBuffer, nSize, NULL);
			UCHAR* pTmp = lpBuffer;
			pTmp += 0x60;	
			if (wcscmp((unsigned short*)pTmp, L"File") == 0)
			{
				//��һ���жϵ�ǰ����Ƿ�Ϊ�������ļ����
				HANDLE hTmp = CreateFileMapping(hDup, NULL, PAGE_READONLY, 0, 20, NULL);
				DWORD dwError = GetLastError();
				//dwError == 8 ,������Ϣ�Ǵ洢�ռ䲻�㣬�޷������������ݴ���Ϣ��������Ϊ�ļ��Ѵ���
				if (hTmp != NULL || dwError==8)	//�ж��Ƿ�Ϊ�ļ����
				{
					m_FileHandles.AddTail(pSysHandleInformation->Handles[i]);
					CloseHandle(hTmp);
				}
			}
			CloseHandle(hDup);
			delete [] lpBuffer;
		}
	}
	VirtualFree(pSysHandleInformation, 0, MEM_RELEASE);
}

//�����ļ����
void CForceDeleteDlg::LoadFileHanle()
{
	

}

//�о�ϵͳ���еĽ�����Ϣ
void CForceDeleteDlg::EnumRunningProc()
{
	//�оٴ򿪵Ķ�����
	int nCount = 0;
	SYSTEM_PROCESS_INFORMATION* pSysProcess = NULL;
	//��ȡϵͳ�н�����Ϣ��һ���ṹ
	DWORD dwRet = NtQuerySystemInformation(5, m_pProcInfo, m_dwProcSize, NULL);
	if (dwRet != 0)
	{
		return;
	}
	m_SysProcesses.RemoveAll();
	pSysProcess = (SYSTEM_PROCESS_INFORMATION*)m_pProcInfo;
	do
	{
		//��ӵ�������Ϣ�б�
		m_SysProcesses.SetAt(pSysProcess->dUniqueProcessId, pSysProcess);
		if (pSysProcess->dNext != 0)
		{
			//��ȡ��һ��������Ϣ
			pSysProcess = (SYSTEM_PROCESS_INFORMATION*)((UCHAR*)pSysProcess + pSysProcess->dNext);
		}
		else
		{
			pSysProcess = NULL;
		}
	}
	while (pSysProcess != NULL);
}

void CForceDeleteDlg::OnCancel()
{
	VirtualFree(m_pProcInfo, m_dwProcSize, MEM_RELEASE);
	GetModuleFileNameEx = NULL;
	FreeLibrary(hMod);
	CDialog::OnCancel();
}

BOOL CForceDeleteDlg::GetDiviceName(LPCTSTR lpDosName, CString &szDiviceName)
{
	TCHAR szDrive[3];
	_tcsncpy(szDrive, lpDosName, 2);	//�����̷�
	szDrive[2] = _T('\0');				//������ֹ��
	TCHAR szDeviceName[0x1000];
	if (QueryDosDevice(szDrive, szDeviceName, 0x1000) != 0)
	{
		_tcscat( szDeviceName, lpDosName + 2 );
		szDiviceName = szDeviceName;
		return TRUE;
	}
	return FALSE;
}



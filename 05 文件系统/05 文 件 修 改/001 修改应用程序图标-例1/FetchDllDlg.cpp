// FetchDllDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FetchDll.h"
#include "FetchDllDlg.h"

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
// CFetchDllDlg dialog

CFetchDllDlg::CFetchDllDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFetchDllDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFetchDllDlg)
	m_FileName = _T("");
	m_IconFile = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CFetchDllDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFetchDllDlg)
	DDX_Control(pDX, IDC_ICON, m_Icon);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Text(pDX, IDC_FILENAME, m_FileName);
	DDX_Text(pDX, IDC_ICONFILE, m_IconFile);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFetchDllDlg, CDialog)
	//{{AFX_MSG_MAP(CFetchDllDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BROWN, OnBrown)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_ICONBROWN, OnIconbrown)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFetchDllDlg message handlers

BOOL CFetchDllDlg::OnInitDialog()
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

void CFetchDllDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFetchDllDlg::OnPaint() 
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
HCURSOR CFetchDllDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFetchDllDlg::OnOK() 
{
	UpdateData();
	if (m_FileName.IsEmpty())
	{
		MessageBox("��ѡ���ִ���ļ�");
		return;
	}
	m_List.ResetContent();
	
	HANDLE hFile;                               //�ļ����
	HANDLE hMap;                                //�ڴ�ӳ����
	char  *pBase;	                            //PE�ļ�����ַ
	IMAGE_DOS_HEADER*          peDos_Header;      //DOSͷ
	IMAGE_NT_HEADERS*          peNT_Header;       //PE�ļ�ͷ
	IMAGE_SECTION_HEADER*      peSection_Header;  //�α�ͷ
	IMAGE_IMPORT_DESCRIPTOR*   peImport_Descript; //���ñ�
	IMAGE_RESOURCE_DIRECTORY*  peResource_Dir;
	IMAGE_RESOURCE_DIRECTORY_ENTRY* peReSource_Entry; 
	
	hFile=CreateFile(m_FileName.GetBuffer(0),GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ,0,OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL,0);	
	if (hFile==INVALID_HANDLE_VALUE)
		return ; 
	if (!(hMap=CreateFileMapping(hFile,0,PAGE_READWRITE|SEC_COMMIT,0,0,0)))
	{									
		CloseHandle(hFile);
		CloseHandle(hMap);
		return ;
	}
	if (!(pBase=(char*)::MapViewOfFile(hMap,FILE_MAP_ALL_ACCESS|FILE_MAP_COPY,0,0,0)))
	{									
		CloseHandle(hFile);
		CloseHandle(hMap);
		return ;
	}
	
	peDos_Header=(IMAGE_DOS_HEADER *)pBase;	//��ȡPE�ļ���ʽ����ʼ��ַ
	
	//e_lfanew��������ַ,��ƫ����,ָ��������PE��ͷ
	peNT_Header=(IMAGE_NT_HEADERS *)(pBase+peDos_Header->e_lfanew);//NTͷָ���
	
	//��ȡ�α������
	int secCount =  peNT_Header->FileHeader.NumberOfSections;
	
	//��ȡ�α�ͷ��λ��
	peSection_Header = (IMAGE_SECTION_HEADER *)((char*)peNT_Header+sizeof(IMAGE_NT_HEADERS));
	
	
	char* pDllName = NULL;
	
	//��Addr����ĳ�����е���Ե�ַ��ȡʵ�ʵ�ַ
	#define Addr(offset) (void*)( (char*)((char*) pBase+peSection_Header->PointerToRawData) +  ((DWORD)(offset)- peSection_Header->VirtualAddress))

	#define isValid(addr,begin,len) ((char*)(addr)>=(char*)(begin) && (char*)(addr)<(char*)(begin)+(len))
	//�����α�	
	for (int i = 0; i< secCount; i++,peSection_Header++)
	{
		for(int directory = 0; directory < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; directory++)
		{
			if(peNT_Header->OptionalHeader.DataDirectory[directory].VirtualAddress && isValid(peNT_Header->OptionalHeader.DataDirectory[directory].VirtualAddress,peSection_Header->VirtualAddress,peSection_Header->SizeOfRawData))
				
			{//�����
				if (directory==IMAGE_DIRECTORY_ENTRY_IMPORT)
				{
					//��ȡ�������.idata���е�λ��
					peImport_Descript =(IMAGE_IMPORT_DESCRIPTOR *) Addr( peNT_Header->OptionalHeader.DataDirectory[directory ].VirtualAddress);
					for (int j = 0; !IsBadReadPtr(peImport_Descript,sizeof(*peImport_Descript))&& peImport_Descript->Name;peImport_Descript++,j++)
					{
						pDllName = (char*)Addr(peImport_Descript->Name);
						m_List.AddString(pDllName);
					}
				}
				else if (directory==IMAGE_DIRECTORY_ENTRY_RESOURCE)
				{
					//һ����ԴĿ¼
					peResource_Dir = (IMAGE_RESOURCE_DIRECTORY*)Addr(peNT_Header->OptionalHeader.DataDirectory[directory].VirtualAddress);			
					
					//��Դ����
					int ReCount = peResource_Dir->NumberOfIdEntries+peResource_Dir->NumberOfNamedEntries; 
					
					//һ����ԴĿ¼ʵ�����
					peReSource_Entry = (IMAGE_RESOURCE_DIRECTORY_ENTRY*)((char*)peResource_Dir+sizeof(IMAGE_RESOURCE_DIRECTORY) );
					
					IMAGE_RESOURCE_DIRECTORY* peTempDir,*pe3Dir,*pe4Dir;
					
					IMAGE_RESOURCE_DIRECTORY_ENTRY* peTempEntry,*peIconDir;
					IMAGE_RESOURCE_DATA_ENTRY* peDataEntry;
					
					for (int m = 0; m<ReCount; m++,peReSource_Entry++)
					{
						int type = peReSource_Entry->Id; //3��ʾͼ��,5��ʾ�Ի���,14��ʾͼ����
						
						if (type==3 )
						{
							//�������Ŀ¼
							peTempDir = (IMAGE_RESOURCE_DIRECTORY*)((char*)peResource_Dir+peReSource_Entry->OffsetToDirectory);
							
							//��ȡ����Ŀ¼ʵ������
							int iconCount =  peTempDir->NumberOfIdEntries+peTempDir->NumberOfNamedEntries;
							
							//����Ŀ¼ʵ�����
							peTempEntry = (IMAGE_RESOURCE_DIRECTORY_ENTRY*)((char*)peTempDir+sizeof(IMAGE_RESOURCE_DIRECTORY));
							
							for (int c=0; c<iconCount; c++,peTempEntry++)
							{
								if (peTempEntry->DataIsDirectory>0)
								{	
									//����Ŀ¼
									pe3Dir = (IMAGE_RESOURCE_DIRECTORY*)((char*)peResource_Dir+peTempEntry->OffsetToDirectory);
									//����ʵ��
									peIconDir = (IMAGE_RESOURCE_DIRECTORY_ENTRY*)((char*)pe3Dir+ sizeof(IMAGE_RESOURCE_DIRECTORY));
									
									//ͼ��ID
									int id =  peTempEntry->Id;
									peDataEntry = (IMAGE_RESOURCE_DATA_ENTRY*) ((char*)peResource_Dir+peIconDir->OffsetToDirectory);
									
									int size = peDataEntry->Size;
									unsigned char* pData;
									if (c==0)
									{
										pData = (unsigned  char*)((char*) Addr(peDataEntry->OffsetToData));// pBase+peDataEntry->OffsetToData);
										
										if (!m_IconFile.IsEmpty())
										{
											CFile file;
											file.Open(m_IconFile,CFile::modeRead);
											int len =file.GetLength();
											m_pIconData = new char[len+1];
											memset(m_pIconData,0,len+1);
											file.ReadHuge(m_pIconData,len);
											char* temp = m_pIconData;
											m_pIconData+=22;
											file.Close();
											memcpy(pData,m_pIconData,size);

											delete temp;
										}
										
										
									}	
								}
							}
						}
						
					}
				}
					
			}
		}		
	}
	FlushFileBuffers(hFile);
	CloseHandle(hMap);
	CloseHandle(hFile);
	SetFileAttributes(m_FileName,FILE_ATTRIBUTE_READONLY);
	SetFileAttributes(m_FileName,FILE_ATTRIBUTE_NORMAL);
}

void CFetchDllDlg::OnBrown() 
{
	CFileDialog fDlg (TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"��ִ���ļ�(exe)|*.exe",this);
	if (fDlg.DoModal()==IDOK)
	{
		m_FileName = fDlg.GetPathName();
		UpdateData(FALSE);
		OnOK();
	}
}

void CFetchDllDlg::OnButton1() 
{
}

void CFetchDllDlg::OnButton2() 
{


}

void CFetchDllDlg::OnIconbrown() 
{
	CFileDialog fDlg (TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"ͼ���ļ�(ico)|*.ico",this);
	if (fDlg.DoModal()==IDOK)
	{
		m_IconFile = fDlg.GetPathName();
		m_Icon.SetIcon((HICON) LoadImage(NULL,m_IconFile,IMAGE_ICON,0,0,LR_LOADFROMFILE));
		UpdateData(FALSE);
	}	
}

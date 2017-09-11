// GetPropDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GetProp.h"
#include "GetPropDlg.h"
#include "ole2.h"
#include "locale.h"

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
// CGetPropDlg dialog

CGetPropDlg::CGetPropDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetPropDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGetPropDlg)
	m_FileName = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CGetPropDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGetPropDlg)
	DDX_Control(pDX, IDC_LIST, m_PropertyList);
	DDX_Text(pDX, IDC_FILENAME, m_FileName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGetPropDlg, CDialog)
	//{{AFX_MSG_MAP(CGetPropDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PROPERTY, OnProperty)
	ON_BN_CLICKED(IDC_BROWN, OnBrown)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetPropDlg message handlers

BOOL CGetPropDlg::OnInitDialog()
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
	//�����б���

	m_PropertyList.SetExtendedStyle(LVS_EX_FLATSB|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_TRACKSELECT);

	//������
	m_PropertyList.InsertColumn(0,"����",LVCFMT_LEFT,100);
	m_PropertyList.InsertColumn(1,"����",LVCFMT_LEFT,80);
	m_PropertyList.InsertColumn(2,"����",LVCFMT_LEFT,80);
	m_PropertyList.InsertColumn(3,"ģ��",LVCFMT_LEFT,100);
	m_PropertyList.InsertColumn(4,"��ע",LVCFMT_LEFT,100);

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGetPropDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGetPropDlg::OnPaint() 
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
HCURSOR CGetPropDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGetPropDlg::OnOK() 
{


}

void CGetPropDlg::OnProperty() 
{
	UpdateData(TRUE);
	if (m_FileName.IsEmpty())
	{
		MessageBox("��ѡ��Word�ĵ�");
		return;
	}
	m_PropertyList.DeleteAllItems();
	IStorage* pStorage = NULL;
	IPropertySetStorage* pSetprop = NULL;

	WCHAR  filename[MAX_PATH];
	

	wcscpy(filename,m_FileName.AllocSysString()) ;

	::StgOpenStorage( filename,NULL,STGM_READ|STGM_SHARE_EXCLUSIVE,NULL,0,&pStorage);

	if (pStorage==NULL)
	{
		MessageBox("���ļ�����");
		return;
	}

	pStorage->QueryInterface(IID_IPropertySetStorage,(void**)&pSetprop);

	if (pSetprop==NULL)
	{
		MessageBox("��ȡ���Դ���");
		return;
	}
	IPropertyStorage * pPropStorage = NULL;

	pSetprop->Open(FMTID_SummaryInformation,STGM_READ|STGM_SHARE_EXCLUSIVE,&pPropStorage);

	if (pPropStorage==NULL)
	{
		MessageBox("��ȡ���Դ���");
		return;
	}

	//�������Խṹ
	struct PropStrct{
		char* proName;
		long  proFlag;
	}Props[] = {
		{"Title",PIDSI_TITLE},                 //����
		{"Subject",PIDSI_SUBJECT},             //����
		{"Author",PIDSI_AUTHOR},               //����
		{"Keywords",PIDSI_KEYWORDS},           //�ؼ���
		{"Comments",PIDSI_COMMENTS},           //��ע
		{"Template",PIDSI_TEMPLATE},           // ģ��
		{"Last Author",PIDSI_LASTAUTHOR},      //��󱣴���
		{"Revision Number",PIDSI_REVNUMBER},   //�޶���
		{"Edit Time",PIDSI_EDITTIME},          //�༭ʱ��
		{"Last Printed",PIDSI_LASTPRINTED},    //���һ�δ�ӡʱ��
		{"Created",PIDSI_CREATE_DTM},          //��������
		{"Last Saved",PIDSI_LASTSAVE_DTM},     //���һ�α�������
		{"Page Count",PIDSI_PAGECOUNT},        //ҳ��
		{"Word Count",PIDSI_WORDCOUNT},        //����
		{"Char Count",PIDSI_CHARCOUNT},        //�ַ���
		{"Thumb nail",PIDSI_THUMBNAIL},        
		{"AppName",PIDSI_APPNAME},             //Ӧ�ó�������
		{"Doc Security",PIDSI_DOC_SECURITY},   //��ȫ��
		{0,0}
	};


	int PropCount = sizeof(Props)/sizeof(PropStrct)-1;
	
	PROPSPEC * pPropSpec = new PROPSPEC[PropCount];
	PROPVARIANT* pPropVariant = new PROPVARIANT[PropCount];

	for (int i =0; i<PropCount; i++)
	{
		ZeroMemory(&pPropSpec[i],sizeof(PropStrct));
		pPropSpec[i].ulKind = PRSPEC_PROPID;
		pPropSpec[i].propid = Props[i].proFlag;
	}
	//��ȡ������Ϣ
	HRESULT hr =  pPropStorage->ReadMultiple(PropCount,pPropSpec,pPropVariant);

	if (FAILED(hr))
	{
		MessageBox("��ȡ����ʧ��");
	}
	else
	{
		m_PropertyList.InsertItem(0,"");
		for (int m = 0; m<PropCount; m++)
		{
			if (pPropVariant[m].vt==VT_LPSTR)
			{
				char* pbstr = (char*)pPropVariant[m].bstrVal;
				
				switch (m)
				{
				case 1:
					m_PropertyList.SetItemText(0,0,pbstr);
					break;
				case  0:
					m_PropertyList.SetItemText(0,1,pbstr);
					break;
				case  2:
					m_PropertyList.SetItemText(0,2,pbstr);
					break;				
				case  5:
					m_PropertyList.SetItemText(0,3,pbstr);
					break;					
				case  4:
					m_PropertyList.SetItemText(0,4,pbstr);
					break;				
				}
			}

		}
	}
	delete [] pPropSpec;
	delete [] pPropVariant;

	pPropStorage->Release();
	pSetprop->Release();
	pStorage->Release();

}

void CGetPropDlg::OnBrown() 
{
	CFileDialog fDlg(TRUE,"doc",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"Word�ĵ�|*.doc",this);
	if (fDlg.DoModal()==IDOK)
	{
		m_FileName = fDlg.GetPathName();
		UpdateData(FALSE);
	}
}


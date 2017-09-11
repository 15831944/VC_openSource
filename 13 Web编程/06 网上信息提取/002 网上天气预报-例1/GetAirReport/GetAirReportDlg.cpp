// GetAirReportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GetAirReport.h"
#include "GetAirReportDlg.h"
#include "afxinet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
CString city[]={"������","����","����","����",
			"���","ʯ��ׯ","��³ľ��","���ͺ���",
	"����","̫ԭ","����","����",
	"�Ϸ�","֣��","����","����",
	"�Ϻ�","�Ͼ�","�人","�ɶ�",
	"����","����","����","�ϲ�",
	"��ɳ","����","����",
	"����","����","����"
	,"����"};
CString city2[31][2]={"������","50953",
	"����","54161",
	"����","54342",
	"����","54511",
	"���","54527",
	"ʯ��ׯ","53698",
	"��³ľ��","51463",
	"���ͺ���","53463",
	"����","54823",
	"̫ԭ","53772",
	"����","53614",
	"����","52866",
	"�Ϸ�","58321",
	"֣��","57083",
	"����","57036",
	"����","52889",
	"�Ϻ�","58362",
	"�Ͼ�","58238",
	"�人","57494",
	"�ɶ�","56294",
	"����","55591",
	"����","58457",
	"����","57516",
	"�ϲ�","58606",
	"��ɳ","57687",
	"����","57816",
	
	"����","58847",
	"����","56778",
	"����","59287",
	"����","59431",
	
	
	"����","59758"};
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
// CGetAirReportDlg dialog

CGetAirReportDlg::CGetAirReportDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetAirReportDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGetAirReportDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGetAirReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGetAirReportDlg)
	DDX_Control(pDX, IDC_REPORTLIST, m_reportlist);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGetAirReportDlg, CDialog)
	//{{AFX_MSG_MAP(CGetAirReportDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTGET, OnGet)
	ON_BN_CLICKED(IDC_BTEXIT, OnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetAirReportDlg message handlers

BOOL CGetAirReportDlg::OnInitDialog()
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
	addressfront="http://www.nmc.gov.cn/weatherdetail";
	m_reportlist.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_reportlist.InsertColumn(0,"����",LVCFMT_LEFT,70);
	m_reportlist.InsertColumn(1,"����",LVCFMT_LEFT,90);
	m_reportlist.InsertColumn(2,"����",LVCFMT_LEFT,120);
	m_reportlist.InsertColumn(3,"����",LVCFMT_LEFT,70);
	//ͨ���ַ����������б�ؼ����������
	for(int i=0;i<31;i++)
	{
		m_reportlist.InsertItem(i,city[i],0);
	}

	return TRUE;
}

void CGetAirReportDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGetAirReportDlg::OnPaint() 
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
HCURSOR CGetAirReportDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
/*
void CGetAirReportDlg::OnGet()
{
	//�������ҳ���ҵ��������ƣ���Ϊ��
	BOOL bTable=FALSE;
	//�ֱ��ǻ�����������£����������к���Ϊ��
	BOOL bGet1=TRUE,bGet2=TRUE,bGet3=TRUE;
	//���<TD class>��</TD>����Դ���������
	BOOL bNext1=FALSE,bNext2=FALSE,bNext3=FALSE;
	int line=0;    //��Դ�����е�λ��
	int leftpos;   //ȡĳ��Դ�롰</TD>����λ��
	int rightpos;  //ȡĳ��Դ�롰>����λ��
	//address="http://192.168.1.165/default.htm";
	int isel=m_reportlist.GetSelectionMark();
	if(isel<0)
	{
		AfxMessageBox("��ѡ�����");
		return;
	}
	//CString tmp;
	strtmp1=city2[isel][0];
	//strtmp1="����";
	address.Format("%s/%s.html",addressfront,city2[isel][1]);

		//tmp.Format("%s/%s_full.htm",addressfront,city2[i][1]);
	CString strsource;
	CInternetSession mySession(NULL,0);
	CHttpFile* myHttpFile=NULL;
	myHttpFile=(CHttpFile*)mySession.OpenURL(address);
	while(myHttpFile->ReadString(strsource))
	{
		//���ĳ��Դ��������ȡ���ַ�����ʼ���д���
		if(strsource.Find(strtmp1)>0)
			bTable=TRUE;
		if(bTable)
		{
			if(strsource.Find("TD class")>0)
				line++;
		}
		//�õ�������λ��
		if(line==6&&bGet1)
		{
			leftpos=strsource.Find("</TD>");
			if(leftpos>0)
			{
				strtmp2=strsource.Left(leftpos);
				rightpos=strtmp2.Find(">");
				strweather=strtmp2.Right(strtmp2.GetLength()-rightpos-1);
				bGet1=FALSE;
			}
			else
			{
				bNext1=TRUE;
				strtmp3=strsource;
				goto end;
			}
		}
		if(bNext1)
		{
			//����һ�к���һ�н��кϲ���Ȼ����кϲ�
			strtmp3+=strsource;
			strtmp3.Replace(" ","");
			leftpos=strsource.Find("</TD>");
			strtmp2=strsource.Left(leftpos);
			rightpos=strtmp2.Find(">");
			strweather=strtmp2.Right(strtmp2.GetLength()-rightpos-1);
			bGet1=FALSE;
			bNext1=FALSE;
		}
		//�õ����µ�λ��
		if(line==12&&bGet2)
		{
			leftpos=strsource.Find("</TD>");
			if(leftpos>0)
			{
				
				strtmp2=strsource.Left(leftpos);
				rightpos=strtmp2.Find(">");
				strtemperature=strtmp2.Right(strtmp2.GetLength()-rightpos-1);
				bGet2=FALSE;
			}
			else
			{
				bNext2=TRUE;
				strtmp3=strsource;
				goto end;
			}
		}
		if(bNext2)
		{
			strtmp3+=strsource;
			strtmp3.Replace(" ","");
			leftpos=strsource.Find("</TD>");
			strtmp2=strsource.Left(leftpos);
			rightpos=strtmp2.Find(">");
			strtemperature=strtmp2.Right(strtmp2.GetLength()-rightpos)-1;
			bGet2=FALSE;
			bNext2=FALSE;
		}
		//�õ�������λ��
		if(line==16&&bGet3)
		{
			leftpos=strsource.Find("</TD>");
			if(leftpos>0)
			{
				
				strtmp2=strsource.Left(leftpos);
				rightpos=strtmp2.Find(">");
				strwind=strtmp2.Right(strtmp2.GetLength()-rightpos-1);
				goto stop;
			
			}
			else
			{
				bNext3=TRUE;
				strtmp3=strsource;
				goto end;
			}
		}
		if(bNext3)
		{
			strtmp3+=strsource;
			strtmp3.Replace(" ","");
			leftpos=strsource.Find("</TD>");
			strtmp2=strsource.Left(leftpos);
			rightpos=strtmp2.Find(">");
			strwind=strtmp2.Right(strtmp2.GetLength()-rightpos-1);
			bGet3=FALSE;
			bNext3=FALSE;
			goto stop;
		}
		
end:
		{}
	}
stop:
	myHttpFile->Close();
	mySession.Close();	
	m_reportlist.SetItemText(isel,1,strweather);
	m_reportlist.SetItemText(isel,2,strtemperature);
	m_reportlist.SetItemText(isel,3,strwind);
}
*/
void CGetAirReportDlg::OnExit()
{
	this->OnCancel();	
}

void CGetAirReportDlg::OnGet()
{
	BOOL bNext1=FALSE,bNext2=FALSE,bNext3=FALSE;
	int leftpos=0;   //ȡĳ��Դ�롰</TD>����λ��
	int rightpos=0;  //ȡĳ��Դ�롰>����λ��
	int isel=m_reportlist.GetSelectionMark();
	if(isel<0)
	{
		AfxMessageBox("��ѡ�����");
		return;
	}
	address.Format("%s/%s.html",addressfront,city2[isel][1]);
	strtmp1.Format("city\" >%s",city2[isel][0]);
	CString strsource;
	CInternetSession mySession(NULL,0);
	CHttpFile* myHttpFile=NULL;
	myHttpFile=(CHttpFile*)mySession.OpenURL(address);
	while(myHttpFile->ReadString(strsource))
	{
		//���ĳ��Դ��������ȡ���ַ�����ʼ���д���
		if(strsource.Find(strtmp1)>0)
			bNext1=TRUE;
		if(bNext1)
		{
			int leftpos=strsource.Find("map-layer-weaher");
	
			if(leftpos>0)
			{
				strtmp2=strsource.Right(strsource.GetLength()-strlen("map-layer-weaher")-leftpos-2);
				rightpos=strtmp2.Find("</div>");
				strtmp2=strtmp2.Left(rightpos);
				strweather=strtmp2;
				bNext1=FALSE;
				bNext2=TRUE;
			}
		}
		if(bNext2)
		{
			int leftpos=strsource.Find("map-layer-temp");
			if(leftpos>0)
			{
				strtmp2=strsource.Right(strsource.GetLength()-strlen("map-layer-temp")-leftpos-2);
				rightpos=strtmp2.Find("</div>");
				strtmp2=strtmp2.Left(rightpos);
				strtemperature=strtmp2;
				bNext2=FALSE;
				bNext3=TRUE;
			}
		}
		if(bNext3)
		{
			int leftpos=strsource.Find("map-layer-wind");
			if(leftpos>0)
			{
				strtmp2=strsource.Right(strsource.GetLength()-strlen("map-layer-wind")-leftpos-2);
				rightpos=strtmp2.Find("</div>");
				strtmp2=strtmp2.Left(rightpos);
				strwind=strtmp2;
				bNext3=FALSE;
			goto end;
			}
		}
		
	}
end:
	myHttpFile->Close();
	mySession.Close();	
	m_reportlist.SetItemText(isel,1,strweather);
	m_reportlist.SetItemText(isel,2,strtemperature);
	m_reportlist.SetItemText(isel,3,strwind);
}

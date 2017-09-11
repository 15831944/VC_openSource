// SeriesPortDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SeriesPort.h"
#include "SeriesPortDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//�Զ���һ����Ϣ
const CM_RECEIVE = WM_USER+100;

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
// CSeriesPortDlg dialog

CSeriesPortDlg::CSeriesPortDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSeriesPortDlg::IDD, pParent) 
{
	//{{AFX_DATA_INIT(CSeriesPortDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);

}

void CSeriesPortDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSeriesPortDlg)
	DDX_Control(pDX, IDC_EDIT1, m_info);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSeriesPortDlg, CDialog)
	//{{AFX_MSG_MAP(CSeriesPortDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_MESSAGE(CM_RECEIVE,OnRecieveData)
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSeriesPortDlg message handlers

BOOL CSeriesPortDlg::OnInitDialog()
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

void CSeriesPortDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSeriesPortDlg::OnPaint() 
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
OVERLAPPED tOverLaped=  {0};  //�̺߳���ʹ�õ�OVERLAPPED�ṹ
OVERLAPPED wOverLaped = {0};  //д����ʹ�õ�OVERLAPPED�ṹ
OVERLAPPED rOverLaped = {0};  //������ʹ�õ�OVERLAPPED�ṹ
BOOL IsFun = TRUE;            //�߳��Ƿ�����
BOOL IsStop = FALSE;          //�����Ƿ������

HCURSOR CSeriesPortDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//�̺߳���
DWORD ThreadFunction(LPVOID pParam)
{
	DWORD  dwEvtMask ,dwResult;
	tOverLaped.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);//����һ���¼�
	while (IsFun)
	{
		WaitCommEvent(((CSeriesPortDlg*)AfxGetMainWnd())->hCom,&dwEvtMask,&tOverLaped);//�ȴ������¼�
		dwResult = WaitForSingleObject(tOverLaped.hEvent,100); //����¼�û���ź�,��ʱ0.1��

		switch (dwResult)
		{
		case WAIT_OBJECT_0: //�¼��������ź�
			switch (dwEvtMask)
			{
			case EV_RXCHAR: //���յ�����
				{
					if (IsStop)//����ֹͣ
					{
						IsStop = FALSE;
						//������Ϣ,����Ϣ��������������
						::PostMessage(AfxGetMainWnd()->m_hWnd, CM_RECEIVE,0,(LPARAM)EV_RXCHAR);
					}
					break;
				}			
			}
			break;		
		}
	}
	return 0;
}


void CSeriesPortDlg::OnOK() 
{
	hCom = CreateFile("COM1",       //�򿪴���1
		GENERIC_READ|GENERIC_WRITE, //�������д����
		0,                          //��ռ��ʽ
		NULL,
		OPEN_EXISTING,              //��һ�����ڵĴ���
		FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED, //�첽��ʽ��
		NULL
		);
	if (hCom==INVALID_HANDLE_VALUE)
	{
		MessageBox("�˿ڴ�ʧ��.");
		return;
	}
}


void CSeriesPortDlg::OnButton1() 
{
	DWORD res;
	DWORD factdata = 0;

	m_info.GetWindowText(str);
	//����һ���¼�����
	wOverLaped.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL); 
	IsStop = FALSE;
	//��ʼ��������
	if (WriteFile(hCom,str,str.GetLength(),&factdata,&wOverLaped))
	{
		IsStop = TRUE;
		MessageBox("���ͳɹ�");
	}
	else
	{
		res = WaitForSingleObject(wOverLaped.hEvent,5000); //��ʱ5��,�ȴ����ݷ���
		if (WAIT_OBJECT_0 == res) //����¼��������ź�״̬,��ʾ�������
		{
			IsStop = TRUE;
		}
		else
			IsStop = FALSE;
		Sleep(1000); //��ʱ1����		
	}	
}

//�Զ�����Ϣ������,���ڽ�������		
void CSeriesPortDlg::OnRecieveData(WPARAM wParam, LPARAM lParam)
{

	DWORD res,factbyte;

	memset(DataBuffer,0,1024); //��ʼ�����ݻ�����
	COMSTAT rst;

	ClearCommError(hCom,&res,&rst);//��մ��ڴ����־,��¼��ǰͨ��״̬

	rOverLaped.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL); //����һ���¼�����
	if (ReadFile(hCom,DataBuffer,rst.cbInQue,&factbyte,&rOverLaped))  //��ȡ���ݵ���������
	{
		DataBuffer[rst.cbInQue]= 0;
		IsStop = FALSE;
	}
	else
	{	
		res = WaitForSingleObject(rOverLaped.hEvent,5000);
	}
	IsStop = FALSE;
	MessageBox(DataBuffer);
}

//���ô�����Ϣ
void CSeriesPortDlg::OnButton2() 
{
	SetupComm(hCom,1024,1024); //���÷��ͺͽ��ջ�������С
	//���ô�����Ϣ
	DCB dcb;
	GetCommState(hCom,&dcb);
	dcb.BaudRate = 9600;
	dcb.fBinary = TRUE;
	dcb.fParity = TRUE;
	dcb.ByteSize = 8;
	dcb.Parity = ODDPARITY;

	dcb.StopBits = ONESTOPBIT;

	if (!SetCommState(hCom,&dcb))
	{
		MessageBox("����ʧ��.","��ʾ");
		return;		
	}

	if (!SetCommMask(hCom,EV_RXCHAR | EV_TXEMPTY))
	{
		MessageBox("��������ʧ��.","��ʾ");
		return;
	}

	DWORD param;
	hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadFunction,&param,0,&dwThreadID);
	if (hThread==INVALID_HANDLE_VALUE)
	{
		MessageBox("�̴߳���ʧ��.","��ʾ",64);
		return;
	}
	IsFun = TRUE;	
}

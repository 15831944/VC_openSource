// BuildAviDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BuildAvi.h"
#include "BuildAviDlg.h"
#include "Vfw.h"
#include "mmsystem.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#pragma comment (lib,"winmm.lib")
#pragma comment (lib,"Vfw32.lib")				//���ӿ��ļ�

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
// CBuildAviDlg dialog

CBuildAviDlg::CBuildAviDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBuildAviDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBuildAviDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBuildAviDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBuildAviDlg)
	DDX_Control(pDX, IDC_EDIT1, m_BmpDir);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBuildAviDlg, CDialog)
	//{{AFX_MSG_MAP(CBuildAviDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBuildAviDlg message handlers

BOOL CBuildAviDlg::OnInitDialog()
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

void CBuildAviDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBuildAviDlg::OnPaint() 
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
HCURSOR CBuildAviDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBuildAviDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	char folder[MAX_PATH] = {0};				//����һ���ַ�����
	BROWSEINFO binfo;					//���������Ϣ
	memset(&binfo,0,sizeof(BROWSEINFO));		//��ʼ��binfo
	ITEMIDLIST* ilist;						//����һ��ITEMIDLISTָ��
	binfo.hwndOwner      = 0;					//���öԻ���ӵ����
	binfo.pidlRoot       = NULL;					//���ø�Ŀ¼
	binfo.pszDisplayName = folder;				//������ʾ����
	binfo.lpszTitle      = "����ļ�";				//���ñ���
	binfo.ulFlags        = BIF_VALIDATE;			//���ñ��
	binfo.lpfn           = NULL;			//���ûص�����
	binfo.lParam         = 0;						//���ûص������Ĳ���
	ilist                = SHBrowseForFolder(&binfo);			//��ʾ����ļ��жԻ���
	SHGetPathFromIDList(ilist,folder);			//��ȡѡ����ļ�������
	m_BmpDir.SetWindowText(folder);			//���ñ༭���ı�
}

void CBuildAviDlg::OnOK() 
{
	// TODO: Add extra validation here
	CFileDialog flDlg(FALSE,"avi","demo",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
		,"AVI�ļ�|*.avi||",this);	//�����ļ�����Ի���
	if(flDlg.DoModal()==IDOK)				//�ж��û��Ƿ�OK��ť
	{
		CString flname = flDlg.GetPathName();	//��ȡ�ļ�����
		CString folder;
		m_BmpDir.GetWindowText(folder);	
		BmpsToAvi(flname,folder);
	}

	//CDialog::OnOK();
}

void CBuildAviDlg::BmpsToAvi(LPCSTR szFileName, LPCSTR szDir)
{
	CString BmpDir = szDir;					//����һ���ַ���
	BmpDir += _T("\\*.*"); 					//�޸��ַ���
	AVIFileInit(); 							//��ʼ��AVIFile������
	AVISTREAMINFO strhdr;					//����AVI�ļ�����Ϣ
	PAVIFILE pFile;						//����AVI�ļ�ָ��
	PAVISTREAM ps; 						//����AVI������
	PAVISTREAM pComStream;									//ѹ����Ƶ������
	AVICOMPRESSOPTIONS pCompressOption; 						//ѹ��ģʽ
	AVICOMPRESSOPTIONS FAR * opts[1] = {&pCompressOption};  
	int nFrames =0; 						//�������ͱ�������ʾ֡��
	CFileFind flFind;						//�����ļ����Ҷ���
	BOOL bret = flFind.FindFile(BmpDir);		//�����ļ�
	while(bret)							//�Ƿ����ļ�
	{
		bret = flFind.FindNextFile();			//������һ���ļ�
		if(!flFind.IsDots() && !flFind.IsDirectory())	//�ж��ļ�����
		{
			CString flname = flFind.GetFilePath();//��ȡ�ļ�����
			FILE *pf = fopen(flname,"rb");		//���ļ�
			BITMAPFILEHEADER bmpFileHdr;	//����λͼ�ļ�ͷ
			BITMAPINFOHEADER bmpInfoHdr;	//����λͼ��Ϣͷ
			fseek(pf,0,SEEK_SET);							//�����ļ�
			fread(&bmpFileHdr,sizeof(BITMAPFILEHEADER),1, pf);	//��ȡλͼ�ļ�ͷ
			fread(&bmpInfoHdr,sizeof(BITMAPINFOHEADER),1, pf);	//��ȡλͼ��Ϣͷ
			if(nFrames == 0)								//�Ƿ�Ϊ��һ֡
			{
				//��������avi�ļ�
				AVIFileOpen(&pFile,szFileName,OF_WRITE | OF_CREATE,NULL);
				memset(&strhdr, 0, sizeof(strhdr));				//��ʼ���ļ�����Ϣ
				strhdr.fccType    = streamtypeVIDEO;				//����������
				strhdr.fccHandler = 0;						//���ô�����
				strhdr.dwScale    = 1;							//����ʱ��̶�
				strhdr.dwRate     = 3; 							//�����ٶ�
				//����ͼ�����
				strhdr.dwSuggestedBufferSize = bmpInfoHdr.biSizeImage ;	
				//������ʾ����
				SetRect(&strhdr.rcFrame, 0, 0, bmpInfoHdr.biWidth, bmpInfoHdr.biHeight);
				AVIFileCreateStream(pFile,&ps,&strhdr); 			//����������
				opts[0]->fccType = streamtypeVIDEO;					//��Ƶģʽ
				opts[0]->fccHandler = mmioStringToFOURCC("MSVC", 0);	//ѹ������
				opts[0]->dwQuality = 7500;
				opts[0]->dwBytesPerSecond = 0;
				opts[0]->dwFlags = AVICOMPRESSF_VALID || AVICOMPRESSF_KEYFRAMES;
				opts[0]->lpFormat = 0;
				opts[0]->cbFormat = 0;
				opts[0]->dwInterleaveEvery = 0;
				AVIMakeCompressedStream(&pComStream,ps,&pCompressOption,NULL); //����ѹ��������
				AVIStreamSetFormat(pComStream,0,&bmpInfoHdr,sizeof(BITMAPINFOHEADER));//��������ʽ
			}
			//����һ��������
			BYTE *buffer = new BYTE[bmpInfoHdr.biWidth * bmpInfoHdr.biHeight * 3];
			//��ȡͼ����Ϣ��������
			fread(buffer, 1, bmpInfoHdr.biWidth * bmpInfoHdr.biHeight * 3, pf);
			//������д������
			AVIStreamWrite(pComStream, nFrames,1,(LPBYTE)buffer,bmpInfoHdr.biSizeImage, 
				AVIIF_KEYFRAME, NULL,NULL);
			nFrames ++; 									//д��һ֡
			fclose(pf);										//�ر��ļ�
			delete []buffer;									//�ͷŻ�����
		}
	}
	AVIStreamClose(ps);									//�ر����ļ�
	AVIStreamClose(pComStream);									//�ر����ļ�
	if(pFile != NULL)
		AVIFileRelease(pFile);								//�ͷ�AVI�ļ��ӿ�
	AVIFileExit();											//�˳�AVI������
}

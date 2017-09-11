// BmpAccessDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BmpAccess.h"
#include "BmpAccessDlg.h"

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
// CBmpAccessDlg dialog

CBmpAccessDlg::CBmpAccessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBmpAccessDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBmpAccessDlg)
	m_id = _T("");
	m_name = _T("");
	m_sex = _T("");
	m_knowledge = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBmpAccessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBmpAccessDlg)
	DDX_Control(pDX, IDC_PICTURESHOW, m_pictureshow);
	DDX_Control(pDX, IDC_LIST1, m_grid);
	DDX_Control(pDX, IDC_PICTURE, m_picture);
	DDX_Text(pDX, IDC_EDIT1, m_id);
	DDX_Text(pDX, IDC_EDIT2, m_name);
	DDX_Text(pDX, IDC_EDIT3, m_sex);
	DDX_Text(pDX, IDC_EDIT4, m_knowledge);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBmpAccessDlg, CDialog)
	//{{AFX_MSG_MAP(CBmpAccessDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTLIULAN, OnButliulan)
	ON_BN_CLICKED(IDC_BUTSHOW, OnButshow)
	ON_BN_CLICKED(IDC_BUTSAVE, OnButsave)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBmpAccessDlg message handlers

BOOL CBmpAccessDlg::OnInitDialog()
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
	::CoInitialize(NULL);
	try
	{
       m_pConnection.CreateInstance("ADODB.Connection");
	   CString strConnect="Provider=Microsoft.Jet.OLEDB.4.0;\
		   Data Source=./shujuku.mdb;Persist Security Info=False";
	   m_pConnection->Open((_bstr_t)strConnect,"","",adModeUnknown);
	}
	catch(_com_error e)
	{
		AfxMessageBox("���ݿ����Ӵ���",0,0);
	}
	m_grid.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);
	m_grid.InsertColumn(0,"���",LVCFMT_LEFT,100,0);
	m_grid.InsertColumn(1,"����",LVCFMT_LEFT,100,1);
	m_grid.InsertColumn(2,"�Ա�",LVCFMT_LEFT,100,2);
	m_grid.InsertColumn(3,"ѧ��",LVCFMT_LEFT,100,3);
	AddToGrid();
	m_bExpand=FALSE;
	CRect rcDlg, rcMarker;
	GetWindowRect(rcDlg);
	m_nExpandedHeight = rcDlg.Height();
	GetDlgItem(IDC_COMPART)->GetWindowRect(rcMarker);
	m_nNormalHeight = (rcMarker.top - rcDlg.top);
	Display();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBmpAccessDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBmpAccessDlg::OnPaint() 
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
	if (m_hbitmap != NULL)
	{
		CDC* pDC = m_picture.GetDC();
		CRect r;
		m_picture.GetClientRect(&r);
		//��λͼѡ���豸������
		CDC memdc;	
		memdc.CreateCompatibleDC( pDC );
		memdc.SelectObject(m_hbitmap);
		BITMAP bmp;
		GetObject(m_hbitmap,sizeof(bmp),&bmp);
		pDC->StretchBlt(r.left,r.top,r.Width(),r.Height(),&memdc,0,0,
				bmp.bmWidth,bmp.bmHeight,SRCCOPY);	
		memdc.DeleteDC();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBmpAccessDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBmpAccessDlg::OnButliulan() 
{
	// TODO: Add your control notification handler code here
	CFileDialog m_dialog (true,"bmp",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"λͼ�ļ�(*.bmp)|*.bmp",this);
	if (m_dialog.DoModal()==IDOK)
	{
		//ȡ��ͼƬ������·��
		strText = m_dialog.GetPathName();
	//	HBITMAP m_hBitmap;
		m_hbitmap=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),strText,IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_DEFAULTCOLOR|LR_DEFAULTSIZE);
		if (m_hbitmap != NULL)
		{
			//ʹ�ÿؼ���ʾͼƬ
		//	m_picture.SetBitmap(m_hBitmap);
			CDC* pDC = m_picture.GetDC();
			CRect r;
			m_picture.GetClientRect(&r);
			//��λͼѡ���豸������
			CDC memdc;	
			memdc.CreateCompatibleDC( pDC );
			memdc.SelectObject(m_hbitmap);
			BITMAP bmp;
			GetObject(m_hbitmap,sizeof(bmp),&bmp);
			pDC->StretchBlt(r.left,r.top,r.Width(),r.Height(),&memdc,0,0,
					bmp.bmWidth,bmp.bmHeight,SRCCOPY);	
			memdc.DeleteDC();
		}
	}
}

void CBmpAccessDlg::Display()
{
	CRect rcDlg;
	GetWindowRect(rcDlg);
	if (m_bExpand)
	{
		rcDlg.SetRect( rcDlg.left, rcDlg.top, 
		rcDlg.left + rcDlg.Width(),
		rcDlg.top + m_nExpandedHeight);
	}
	else
	{
		rcDlg.SetRect(rcDlg.left, rcDlg.top, 
		rcDlg.left + rcDlg.Width(),
		rcDlg.top + m_nNormalHeight);
	}
	MoveWindow(rcDlg, TRUE);
}

void CBmpAccessDlg::OnButshow() 
{
	// TODO: Add your control notification handler code here
	m_bExpand = !m_bExpand;
	Display();
}

void CBmpAccessDlg::OnButsave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if ((m_id.IsEmpty() || m_name.IsEmpty() || m_sex.IsEmpty() || m_knowledge.IsEmpty()))
	{
		MessageBox("������Ϣ����Ϊ��.","��ʾ");
		return;
	}
	HBITMAP m_hbitmap;
	if (m_hbitmap == NULL)
	{
		MessageBox("��Ӵ����м���ͼƬ��Ϣ.","��ʾ");
		return;
	}
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	m_pRecordset->Open("select * from picture",m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	try
	{
		m_pRecordset->AddNew();//�������
		VARIANT	 m_bitdata;
		CFile m_file (strText,CFile::modeRead);
		DWORD m_filelen = m_file.GetLength()+1;
		char * m_bitbuffer = new char[m_filelen];
		m_file.ReadHuge(m_bitbuffer,m_filelen);
		m_file.Close();
		m_bitdata.vt= VT_ARRAY|VT_UI1;
		SAFEARRAY * m_psafe;
		SAFEARRAYBOUND m_band;
		m_band.cElements = m_filelen;
		m_band.lLbound = 0;
		m_psafe = SafeArrayCreate(VT_UI1,1,&m_band);
		for(long i=0; i < m_filelen ; i++)
		{
			SafeArrayPutElement(m_psafe,&i,m_bitbuffer++);
		}	
		m_bitdata.parray = m_psafe;
			
		m_pRecordset->GetFields()->GetItem("���")->Value = (_bstr_t)m_id;
		m_pRecordset->GetFields()->GetItem("����")->Value = (_bstr_t)m_name;
		m_pRecordset->GetFields()->GetItem("�Ա�")->Value = (_bstr_t)m_sex;
		m_pRecordset->GetFields()->GetItem("ѧ��")->Value = (_bstr_t)m_knowledge;
		m_pRecordset->GetFields()->GetItem("��Ƭ")->AppendChunk(&m_bitdata);
		m_pRecordset->Update();
	}
	catch(...)
	{
		MessageBox("����ʧ��");
		return;
	}
	MessageBox("�����ɹ�.");
	m_grid.DeleteAllItems();
	AddToGrid();
}

void CBmpAccessDlg::AddToGrid()
{
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	m_pRecordset->Open("select* from picture order by ��� desc",m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	while(!m_pRecordset->adoEOF)
	{
		m_grid.InsertItem(0,"");
		m_grid.SetItemText(0,0,(char*)(_bstr_t)m_pRecordset->GetCollect("���"));
		m_grid.SetItemText(0,1,(char*)(_bstr_t)m_pRecordset->GetCollect("����"));
		m_grid.SetItemText(0,2,(char*)(_bstr_t)m_pRecordset->GetCollect("�Ա�"));
		m_grid.SetItemText(0,3,(char*)(_bstr_t)m_pRecordset->GetCollect("ѧ��"));
		m_pRecordset->MoveNext();
	}
}

void CBmpAccessDlg::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int pos;
	pos=m_grid.GetSelectionMark();
	m_id=m_grid.GetItemText(pos,0);
	CString sql;
	sql.Format("select*from picture where ���='%s'",m_id);
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	m_pRecordset->Open((_bstr_t)sql,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	HBITMAP m_hBitmap;
	//��ȡͼ���ֶε�ʵ�ʴ�С
	long lDataSize = m_pRecordset->GetFields()->GetItem("��Ƭ")->ActualSize;
	char *m_pBuffer;  //���建�����
	if(lDataSize > 0)
	{
		//��ͼ���ֶ��ж�ȡ���ݵ�varBLOB��
		_variant_t varBLOB;
		varBLOB = m_pRecordset->GetFields()->GetItem("��Ƭ")->GetChunk(lDataSize);
		if(varBLOB.vt == (VT_ARRAY | VT_UI1))
		{
			if(m_pBuffer = new char[lDataSize+1])	//�����Ҫ�Ĵ洢�ռ�
			{	
				char *pBuf = NULL;
				SafeArrayAccessData(varBLOB.parray,(void **)&pBuf);
				memcpy(m_pBuffer,pBuf,lDataSize); ///�������ݵ�������m_pBuffer
				SafeArrayUnaccessData (varBLOB.parray);
			
				//������ת��ΪHBITMAP��ʽ
				LPSTR hDIB;
				LPVOID lpDIBBits;
				BITMAPFILEHEADER bmfHeader;  //���ڱ���BMP�ļ�ͷ��Ϣ���������͡���С��λ������
				DWORD bmfHeaderLen;  //�����ļ�ͷ�ĳ���
				bmfHeaderLen = sizeof(bmfHeader);  //��ȡ�ļ�ͷ�ĳ���
				//��m_pBuffer���ļ�ͷ���Ƶ�bmfHeader��
				strncpy((LPSTR)&bmfHeader, (LPSTR)m_pBuffer, bmfHeaderLen); 	
				if (bmfHeader.bfType != (*(WORD*)"BM"))   //����ļ����Ͳ��ԣ��򷵻�
				{
					MessageBox("BMP�ļ���ʽ��׼ȷ");
					return;
				}
				hDIB = m_pBuffer + bmfHeaderLen;  //��ָ�������ļ�ͷ����
				//��ȡBMP�ļ���ͼ�����ݣ��������꼰��ɫ��ʽ����Ϣ��BITMAPINFOHEADER����
				BITMAPINFOHEADER &bmiHeader = *(LPBITMAPINFOHEADER)hDIB;
				//��ȡBMP�ļ���ͼ�����ݣ��������꼰��ɫ��ʽ����Ϣ��BITMAPINFO����
				BITMAPINFO &bmInfo = *(LPBITMAPINFO)hDIB ;
				//����bfOffBits���Խ�ָ�������ļ�ͷ��
				lpDIBBits = (m_pBuffer) + ((BITMAPFILEHEADER *)m_pBuffer)->bfOffBits;
				CClientDC dc(this);  //����һ���뵱ǰ������ص�CClientDC�����ڹ����������
				//����DIBitmap����
				m_hBitmap = CreateDIBitmap(dc.m_hDC,&bmiHeader,CBM_INIT,lpDIBBits,&bmInfo,DIB_RGB_COLORS);
			}
		}
	}
	if(m_hBitmap != NULL)
	{
		CDC* pDC = m_pictureshow.GetDC();
		CRect r;
		m_pictureshow.GetClientRect(&r);
		//��λͼѡ���豸������
		CDC memdc;	
		memdc.CreateCompatibleDC( pDC );
		memdc.SelectObject(m_hBitmap);
		BITMAP bmp;
		GetObject(m_hBitmap,sizeof(bmp),&bmp);
		pDC->StretchBlt(r.left,r.top,r.Width(),r.Height(),&memdc,0,0,
				bmp.bmWidth,bmp.bmHeight,SRCCOPY);	
		memdc.DeleteDC();
	}
	*pResult = 0;
}

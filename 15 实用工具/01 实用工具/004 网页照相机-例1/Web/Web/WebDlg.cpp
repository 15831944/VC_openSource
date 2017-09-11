// WebDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Web.h"
#include "WebDlg.h"
#include "Mshtml.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CWebDlg �Ի���




CWebDlg::CWebDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWebDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWebDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_Web);
	DDX_Control(pDX, IDC_URL, m_Url);
}

BEGIN_MESSAGE_MAP(CWebDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CWebDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_LOCATE, &CWebDlg::OnBnClickedLocate)
END_MESSAGE_MAP()


// CWebDlg ��Ϣ�������

BOOL CWebDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	m_Web.MoveWindow(0, 0, 1, 1);	//���ش���
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CWebDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CWebDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}


//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CWebDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL __stdcall Draw (DWORD dwParam)
{

	return TRUE;
}
void CWebDlg::OnBnClickedOk()
{
	IViewObject* pViewObject = NULL;
	LPDISPATCH pDocument = m_Web.get_Document();
	if (pDocument != NULL)
	{
		pDocument->QueryInterface(IID_IViewObject, (void**)&pViewObject);
		if (pViewObject != NULL)
		{
			IHTMLDocument2* pDocument2 = NULL;
			m_Web.get_Document()->QueryInterface(IID_IHTMLDocument2, (void**)&pDocument2);
			IHTMLElement* pElement = NULL;
			

			pDocument2->get_body(&pElement);
			IHTMLElement2 * pScroll = NULL;

			pElement->QueryInterface(IID_IHTMLElement2, (void**)&pScroll);
			//��ȡҳ��ĸ߶ȺͿ��
			long nHeight, nWidth;
			pScroll->get_scrollHeight(&nHeight);
			pScroll->get_scrollWidth(&nWidth);
			//��ȡ�ؼ��ͻ�����
			CRect clientRC;
			m_Web.GetClientRect(clientRC);

		
			int nBarWidth = GetSystemMetrics(SM_CYHSCROLL) + 5;
			CRect wndRC;
			GetClientRect(wndRC);	
			m_Web.MoveWindow(wndRC.right, 0, nWidth + nBarWidth, nHeight+ nBarWidth);

			BOOL bVerBar = FALSE;
			BOOL bHorBar = FALSE;
		
			pScroll->get_scrollHeight(&nHeight);
			pScroll->get_scrollWidth(&nWidth);

			//����λͼ��Ⱥ͸߶�
			int nBmpWidth = nWidth;
			int nBmpHeight = nHeight;
		
			RECTL rect;
			rect.left = 0;
			rect.right = nWidth + nBarWidth;
			rect.top = 0;
			rect.bottom = nHeight + nBarWidth;


			CDC* pDC = GetDC();
			CDC srcDC, memDC;
			memDC.CreateCompatibleDC(pDC);
			srcDC.CreateCompatibleDC(pDC);

			CBitmap srcBmp, bmp;
			bmp.CreateCompatibleBitmap(pDC, nWidth, nHeight);

			srcBmp.CreateCompatibleBitmap(pDC, nWidth + nBarWidth, nHeight + nBarWidth);
			
			srcDC.SelectObject(&srcBmp);
			memDC.SelectObject(&bmp);

			pViewObject->Draw(DVASPECT_CONTENT, 1, 0, NULL, 
								0, srcDC.m_hDC, &rect, 0, NULL, 0);
			
			memDC.BitBlt(0, 0, nWidth, nHeight, &srcDC,
							1, 1, SRCCOPY);

			
			//����λͼ�ļ�
			int nAlign = 0;
			nAlign = nBmpWidth % 4;
			if (nAlign != 0)
				nAlign = 4 - nAlign;
			//����λͼ�ļ�ͷ
			BITMAPFILEHEADER bmpFileHeader;
			bmpFileHeader.bfReserved1 = 0;
			bmpFileHeader.bfReserved2 = 0;
			bmpFileHeader.bfSize = sizeof(BITMAPFILEHEADER);
			bmpFileHeader.bfType = 0x4d42;
			bmpFileHeader.bfOffBits = 54;
			//����λͼ��Ϣͷ
			BITMAPINFOHEADER bmpInfoHeader;
			memset(&bmpInfoHeader, 0, sizeof(BITMAPINFOHEADER));
			bmpInfoHeader.biHeight = nBmpHeight;
			bmpInfoHeader.biWidth = nBmpWidth;
			bmpInfoHeader.biPlanes = 1;
			bmpInfoHeader.biBitCount = 24;	//���ɫλͼ
			bmpInfoHeader.biSizeImage = (nBmpHeight)*(nBmpWidth*3 + nAlign);
			bmpInfoHeader.biCompression = 0;
			bmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);

			int nImageSize = nBmpHeight*(nBmpWidth*3 + nAlign);
			BYTE* pBmpData = new BYTE[nImageSize];
			memset(pBmpData, 255, nImageSize);
			
			GetDIBits(memDC.m_hDC, bmp, 0, nBmpHeight, pBmpData, (BITMAPINFO*)&bmpInfoHeader, DIB_RGB_COLORS);

			CFileDialog flDlg(FALSE, L"bmp", L"web.bmp", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT);
			if (flDlg.DoModal() == IDOK)
			{
				CString szFileName = flDlg.GetPathName();
				CFile file;
				file.Open(szFileName, CFile::modeCreate|CFile::modeReadWrite);
				file.Write(&bmpFileHeader, sizeof(BITMAPFILEHEADER));
				file.Write(&bmpInfoHeader, sizeof(BITMAPINFOHEADER));
				file.Write(pBmpData, nImageSize);
				file.Close();
			}
			delete [] pBmpData;
			bmp.DeleteObject();
			srcDC.DeleteDC();
			memDC.DeleteDC();
		}
	}
}


void CWebDlg::OnBnClickedLocate()
{
	CString szUrl;
	m_Url.GetWindowText(szUrl);
	if (!szUrl.IsEmpty())
	{
		m_Web.Navigate(szUrl,NULL, NULL, NULL, NULL);
		m_Web.MoveWindow(0, 0, 1, 1);
	}
}
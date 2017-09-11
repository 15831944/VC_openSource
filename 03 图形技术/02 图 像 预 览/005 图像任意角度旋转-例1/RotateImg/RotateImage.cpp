// RotateImage.cpp : implementation file
//

#include "stdafx.h"
#include "RotateImg.h"
#include "RotateImage.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRotateImage dialog


CRotateImage::CRotateImage(CWnd* pParent /*=NULL*/)
	: CDialog(CRotateImage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRotateImage)
	m_nDegree = 0;
	//}}AFX_DATA_INIT
	m_hBmp = NULL;
	m_bLoaded = FALSE;
	m_pBmpData = NULL;

}


void CRotateImage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRotateImage)
	DDX_Control(pDX, IDC_SETDEGREE, m_SetDegree);
	DDX_Control(pDX, IDC_PANEL, m_Panel);
	DDX_Control(pDX, IDC_IMAGE, m_Image);
	DDX_Control(pDX, IDC_BMPNAME, m_BmpName);
	DDX_Text(pDX, IDC_DEGREE, m_nDegree);
	DDV_MinMaxUInt(pDX, m_nDegree, 0, 360);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRotateImage, CDialog)
	//{{AFX_MSG_MAP(CRotateImage)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_BN_CLICKED(IDC_BT_LOAD, OnBtLoad)
	ON_BN_CLICKED(IDC_BT_SAVE, OnBtSave)
	ON_BN_CLICKED(IDC_BT_ROTATE, OnBtRotate)
	ON_EN_CHANGE(IDC_DEGREE, OnChangeDegree)
	ON_BN_CLICKED(IDC_FIXDEGREE, OnFixdegree)
	ON_BN_CLICKED(IDC_RANDDEGREE, OnRanddegree)
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(IDC_ROTATE45,IDC_ROTATE270,OnLBtnRadio)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRotateImage message handlers

void CRotateImage::OnCancel() 
{
	//�ڶԻ���ر�ʱ�ͷ�λͼ����
	if (m_pBmpData != NULL)
	{
		delete []m_pBmpData;
		m_pBmpData = NULL;
	}
	CDialog::OnCancel();
}

void CRotateImage::OnOK() 
{

}

BOOL CRotateImage::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//������ʾͼƬ����������
	m_ImagePanel.Create(IDD_IMAGEPANEL_DIALOG,this);
	
	CRect rcClient,rcFrame;
	//��ȡ�������ڵĿͻ�����
	m_ImagePanel.GetClientRect(rcClient);
	
	//��������������ʾ������
	m_Panel.GetClientRect(rcFrame);
	m_Panel.MapWindowPoints(this,rcFrame);
	m_ImagePanel.MoveWindow(rcFrame);
	m_ImagePanel.ShowWindow(SW_SHOW);
	//����ͼƬ�ؼ��ĸ�����Ϊ��������
	m_Image.SetParent(&m_ImagePanel);
	CRect rcBmp;
	//��ͼƬ�ؼ���ʾ���������ڵ����Ͻ�
	m_Image.GetClientRect(rcBmp);
	m_Image.MoveWindow(0,0,rcBmp.Width(),rcBmp.Height());	
	//��ĳһ����ѡ��ť����Ϊѡ�д�̨
	CButton* pButton =  (CButton*)GetDlgItem(IDC_ROTATE45);
	if (pButton != NULL)
	{
		pButton->SetCheck(TRUE);
	}
	//��Ԥ���Ƕȵĵ�ѡ��ť����Ϊѡ��״̬
	pButton =  (CButton*)GetDlgItem(IDC_FIXDEGREE);
	if (pButton != NULL)
	{
		pButton->SetCheck(TRUE);
	}
	//���û���Ļ�����Χ
	m_SetDegree.SetRange(0,360);

	return TRUE;  
}

void CRotateImage::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	//�ڴ��ڵ�WM_VSCROLL��Ϣ����ʱ�����������ڵ�OnVScroll����
	m_ImagePanel.OnVScroll(nSBCode, nPos, pScrollBar);			
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CRotateImage::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	//����ǻ���ؼ�������WM_HSCROLL��Ϣ
	if (pScrollBar != NULL && pScrollBar->m_hWnd == m_SetDegree.m_hWnd)
	{
		m_nDegree = m_SetDegree.GetPos();
		UpdateData(FALSE);
	}
	else	//�����ؼ�������WM_HSCROLL��Ϣ
	{
		m_ImagePanel.OnHScroll(nSBCode, nPos, pScrollBar);	
	}
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

BOOL CRotateImage::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	//�������ֵ���Ϣ����ʱִ���������ڵ�OnMouseWheel����
	m_ImagePanel.OnMouseWheel(nFlags, zDelta, pt);			
	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}


void CRotateImage::OnBtLoad() 
{
	//����һ���ļ��򿪶Ի���
	CFileDialog flDlg(TRUE, "", "",
			OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "λͼ�ļ�|*.bmp||", this);
	if (flDlg.DoModal()==IDOK)	//ģʽ��ʾ�ļ��򿪶Ի���
	{
		//��ȡ�ļ�����
		CString csFileName = flDlg.GetPathName();
		m_SrcFile = flDlg.GetPathName();
		//���ñ༭���ı�
		m_BmpName.SetWindowText(csFileName);
		//�ж�֮ǰ�Ƿ������λͼ
		if (m_hBmp != NULL)
		{
			//�ͷ�λͼ
			DeleteObject(m_hBmp);
			m_hBmp = NULL;
		}
		//����λͼ
		m_hBmp = (HBITMAP)LoadImage(NULL,csFileName,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
		if (m_hBmp)
		{
			//��ʾλͼ
			m_Image.SetBitmap(m_hBmp);
			m_bLoaded = TRUE;	//���ü��ر��
		}
		CFile file;		//�����ļ�����
		//���ļ�
		file.Open(csFileName,CFile::modeRead);
		//��ȡλͼ�ļ�ͷ
		file.Read(&m_bmFileHeader,sizeof(BITMAPFILEHEADER));
		//��ȡλͼ��Ϣͷ
		file.Read(&m_bmInfoHeader,sizeof(BITMAPINFOHEADER));
		int szPalette = 0;	//�����ɫ���С
		//�ж��Ƿ�Ϊ���ɫλͼ
		if (m_bmInfoHeader.biBitCount != 24)
		{
			file.Close();
			MessageBox("��ѡ�����ɫλͼ!","��ʾ");
			return;
		}
		//��ȡλͼʵ�����ݴ�С
		int nBmpData = m_bmInfoHeader.biSizeImage;
		//���֮ǰ������λͼ���ݣ���ɾ��λͼ����
		if (m_pBmpData != NULL)
		{
			delete []m_pBmpData;
			m_pBmpData = NULL;
		}
		//����λͼ���ݴ�СΪλͼ���ݷ���ռ�
		m_pBmpData = new BYTE[nBmpData];
		//��ȡλͼ���ݵ��ѿռ���
		file.ReadHuge(m_pBmpData,nBmpData);
		//�ر��ļ�
		file.Close();

		//�޸�λͼ���ݣ���λͼÿһ������ռ��4���ֽڣ�����ÿһ��λͼ���ݽ���4��������
		//�����޸ĺ�λͼ���ݵĴ�С
		int sizeofbuffer = m_bmInfoHeader.biWidth * m_bmInfoHeader.biHeight * 4;
		int externWidth;
		//����Դλͼÿ��ʹ�õ��ֽ���
		externWidth = m_bmInfoHeader.biWidth * 3;
		if(externWidth % 4 != 0)
			externWidth = 4 - externWidth % 4;
		else
			externWidth = 0;
		int k = 0;
		//������λͼ���ݵĻ�����
		BYTE* m_pImageTempBuffer = new BYTE[sizeofbuffer];

		//���ɫλͼͨ���ǵ���ģ���ˣ��ӵײ����Ϸ���λͼ����
		for (int n = m_bmInfoHeader.biHeight - 1; n >= 0; n--) 
		{
			//����ÿһ��λͼ����
			for (UINT m = 0; m < m_bmInfoHeader.biWidth * 3; m += 3) 
			{
				//��ȡԴλͼ�����е�������ɫֵ(RGBֵ)
				m_pImageTempBuffer[k]   = m_pBmpData[n*(m_bmInfoHeader.biWidth*3+externWidth)+m];	//blue
				m_pImageTempBuffer[k+1] = m_pBmpData[n*(m_bmInfoHeader.biWidth*3+externWidth)+m+1];//green
				m_pImageTempBuffer[k+2] = m_pBmpData[n*(m_bmInfoHeader.biWidth*3+externWidth)+m+2];//red
				m_pImageTempBuffer[k+3] = 255;
				k += 4;	//������һ��������ɫֵ
			}
		}
		//�ͷ�Դλͼ����
		delete []m_pBmpData;
		//�����µ�λͼ����
		m_pBmpData = new BYTE[sizeofbuffer];
		memcpy(m_pBmpData, m_pImageTempBuffer, sizeofbuffer);
		//�ͷ�m_pImageTempBuffer����
		delete []m_pImageTempBuffer;

		//���ù�����Χ
		CRect bmpRC,wndRC;
		m_ImagePanel.GetClientRect(wndRC);
		m_Image.GetClientRect(bmpRC); 

		m_ImagePanel.OnHScroll(SB_LEFT, 1, NULL); 
		m_ImagePanel.OnVScroll(SB_LEFT, 1, NULL); 

		//���������ؼ�������Χ
		m_ImagePanel.SetScrollRange(SB_VERT,0,bmpRC.Height()-wndRC.Height());
		m_ImagePanel.SetScrollRange(SB_HORZ,0,bmpRC.Width()-wndRC.Width());
	}	
}

void CRotateImage::OnBtSave() 
{
	//�Ѿ�����ͼ��
	if (m_bLoaded)
	{
		//�����ļ�����Ի���
		CFileDialog flDlg(FALSE, "bmp", "Demo.bmp", 
						OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "λͼ�ļ�|*.bmp||");
		if (flDlg.DoModal()==IDOK)	//���ļ�����Ի���
		{
			try
			{
				//��ȡ������ļ�����
				CString csSaveName = flDlg.GetPathName();
				CFile file;	//�����ļ�����
				file.Open(csSaveName,CFile::modeCreate|CFile::modeReadWrite);
				//д��λͼ�ļ���Ϣͷ
				file.Write(&m_bmFileHeader,sizeof(m_bmFileHeader));
				//д��λͼ��Ϣͷ
				file.Write(&m_bmInfoHeader,sizeof(m_bmInfoHeader));
				//д��λͼʵ������

				BYTE byByteAlign;
				//ȷ��ת�����λͼ�Ŀ�Ⱥ͸߶�
				UINT outHeight = m_bmInfoHeader.biHeight;
				UINT outWidth = m_bmInfoHeader.biWidth;

				//����һ��ָ�룬ָ�����һ��λͼ����
				BYTE * pListData = m_pBmpData+((DWORD)outHeight-1)*outWidth*4;

				//�����ֽڶ��룬���ÿ��λͼ�����ֽ�������4������������Ҫ���в���
				if (outWidth % 4 != 0) 
					byByteAlign = 4-((outWidth * 3L) % 4);
				else
					byByteAlign = 0; 

				BYTE byZeroData = 0; 
				//���к��б���λͼ����
				for (int y=0; y<outHeight; y++)
				{
					for (int x=0; x<outWidth; x++)
					{
						//���ļ���д��һ�����ص�λͼ����
						file.Write(pListData, 3);
						pListData += 4;	//ָ����һ������
					}
					//�����Ҫ�ֽڲ��룬��ÿһ�н�β��Ҫ����ʵ����ֽ�����
					for (int i=0; i<byByteAlign; i++)
					{
						file.Write(&byZeroData,1);
					}
					//ָ����һ������
					pListData -= 2L*outWidth*4;
				}	
				file.Close();	//�ر��ļ�
			}
			catch(...)
			{
				MessageBox("�ļ�����ʧ��!","��ʾ");
			}
		}	
	}		
}

//RotationImage�������ڸ���ָ���ĽǶ�ת��λͼ����
void CRotateImage::RotationImage(BITMAPINFOHEADER *pBmInfo, int nDegree)
{
	//Դͼ���Ⱥ͸߶�
	UINT srcWidth = pBmInfo->biWidth;
	UINT srcHeight = pBmInfo->biHeight;

	double pi = 3.1415926535;
	//���Ƕ�ת��Ϊ����
	double dRadian =nDegree* (pi/180.0);
	//����Ŀ��ͼ���Ⱥ͸߶�
	UINT desWidth = (abs)(srcHeight*sin(dRadian)) + (abs)(srcWidth*cos(dRadian))+1;
	UINT desHeight = (abs)(srcHeight*cos(dRadian)) + (abs)(srcWidth*sin(dRadian))+1;

	//ÿ���ֽ���
	UINT desLineBytes = desWidth * pBmInfo->biBitCount / 8;
	int mod = desLineBytes % 4;
	if (mod != 0)
		desLineBytes += 4 - mod;
	//��ȡԴͼ������
	BYTE* psrcData = m_pBmpData;
	BYTE* psrcPixData  = NULL;
	BYTE* pdesPixData = NULL;
	//�ڶ���Ϊ��ת���λͼ����ռ�
	m_hGlobal = GlobalAlloc(GMEM_MOVEABLE,desHeight*desLineBytes);
	//�����ѿռ�
	m_RotData = (BYTE*)GlobalLock(m_hGlobal);
	//��ʼ���ѿռ�
	memset(m_RotData,0,desHeight*desLineBytes);
	//������ת���λͼ��Ϣ
	desBmInfo.biBitCount = pBmInfo->biBitCount;
	desBmInfo.biClrImportant = pBmInfo->biClrImportant;
	desBmInfo.biClrUsed = pBmInfo->biClrUsed;
	desBmInfo.biCompression = pBmInfo->biCompression;
	desBmInfo.biPlanes = pBmInfo->biPlanes;
	desBmInfo.biSize = sizeof(BITMAPINFOHEADER);
	desBmInfo.biXPelsPerMeter = pBmInfo->biXPelsPerMeter;
	desBmInfo.biYPelsPerMeter = pBmInfo->biYPelsPerMeter;

	BYTE* pTemp = NULL;
	//����RotateBmp������תλͼ����
	RotateBmp(psrcData,pTemp,srcWidth,srcHeight,desWidth,desHeight,dRadian);
	
	//����Ŀ��ͼ���Ⱥ͸߶�
	desBmInfo.biHeight = desHeight;
	desBmInfo.biWidth = desWidth;

	desLineBytes = desWidth * pBmInfo->biBitCount / 8;
	mod = desLineBytes % 4;
	if (mod != 0)
		desLineBytes += 4 - mod;
	//����ͼ�����ݴ�С
	desBmInfo.biSizeImage = desHeight*desLineBytes;

	m_bmInfoHeader = desBmInfo;

	//���m_pBmpData����λͼ���ݣ������ͷ�λͼ����
	if (m_pBmpData != NULL)
	{
		delete []m_pBmpData;
		m_pBmpData = NULL;
	}
	//���¸�����ת֮���λͼ����
	m_pBmpData = new BYTE[desHeight*desWidth*4];
	memset(m_pBmpData,255,desHeight*desWidth*4);
	memcpy(m_pBmpData,pTemp,desHeight*desWidth*4);
	//�ͷ���ʱ����
	delete [] pTemp;
	pTemp = NULL;
}

void CRotateImage::OnBtRotate() 
{
	if (m_bLoaded)
	{
		//ȷ����ת��ʽ
		CButton* pButton =  (CButton*)GetDlgItem(IDC_FIXDEGREE);
		int nState = 0;
		int nDegree = 0;
		if (pButton != NULL)
		{
			nState = pButton->GetCheck();
		}
		if (nState)		//Ԥ���Ƕ�
		{
			for (int nID = IDC_ROTATE45; nID <= IDC_ROTATE270; nID++)
			{
				pButton = (CButton*)GetDlgItem(nID);
				if (pButton != NULL)
				{
					nState = pButton->GetCheck();
					if (nState)
					{
						CString csText;
						pButton->GetWindowText(csText);
						int nPos = csText.Find("��");
						nDegree = atoi(csText.Left(nPos));
						break;
					}
				}
			}	
		}
		else			//�̶��Ƕ�
		{
			UpdateData(FALSE);
			nDegree = m_nDegree;
		}
		//ȷ����ת�Ƕȣ�����RotationImage��������ͼ����ת
		RotationImage(&m_bmInfoHeader,nDegree);

		BYTE byByteAlign ;	//λͼ���ֽڶ���
		//��ȡ��ת���λͼ��С
		UINT outHeight = m_bmInfoHeader.biHeight;
		UINT outWidth = m_bmInfoHeader.biWidth;
		//Ϊ��λͼ����ѿռ�
		BYTE* pBmpData  = new BYTE [m_bmInfoHeader.biSizeImage];
		//��ʼ���ѿռ�
		memset(pBmpData,0,m_bmInfoHeader.biSizeImage);
		//��ȡλͼ�����е������������
		BYTE * pListData =m_pBmpData+((DWORD)outHeight-1)*outWidth*4;
		
		//����λͼ����ÿ�в�����ֽ���
		if (outWidth %4 != 0) 
			byByteAlign = 4- ((outWidth*3L) % 4);
		else
			byByteAlign = 0;

		BYTE byZeroData = 0;
		BYTE* pTmpData = pBmpData;
		//����ת���λͼ���ݽ����޸ģ�ʹ��ʹ��3���ֽڱ�ʾһ����������
		for (int y=0 ;y<outHeight;y++)
		{
			for (int x=0;x<outWidth;x++)
			{
				memcpy(pTmpData,pListData,3);
				pTmpData += 3;
				pListData += 4;
			}
			for (int i=0; i<byByteAlign; i++)
			{
				memcpy(pTmpData,&byZeroData,1);
				pTmpData =pTmpData + 1;
			}
			pListData -= 2L*outWidth*4;
		}

		CDC *pDC = m_Image.GetDC();

		BITMAPINFO bInfo;
		bInfo.bmiHeader = m_bmInfoHeader;
		//��ͼ��ؼ�����ʾ��ת���λͼ
		HBITMAP hBmp = m_Image.SetBitmap(CreateDIBitmap(pDC->m_hDC,
				&m_bmInfoHeader, CBM_INIT, pBmpData, &bInfo, DIB_RGB_COLORS));
		if (hBmp != NULL)
		{
			::DeleteObject(hBmp);
		}
		delete [] pBmpData;

		//���ù�����Χ
		CRect bmpRC,wndRC;
		m_ImagePanel.GetClientRect(wndRC);
		m_Image.GetClientRect(bmpRC);

		m_ImagePanel.OnHScroll(SB_LEFT, 1, NULL); 
		m_ImagePanel.OnVScroll(SB_LEFT, 1, NULL); 

		m_ImagePanel.SetScrollRange(SB_VERT,0,bmpRC.Height()-wndRC.Height());
		m_ImagePanel.SetScrollRange(SB_HORZ,0,bmpRC.Width()-wndRC.Width());
	}
}

void CRotateImage::OnChangeDegree() 
{
	UpdateData(TRUE);
	m_SetDegree.SetPos(m_nDegree);
	
}

//����RotateBmp���ڰ�ָ���Ƕ���תλͼ����
void CRotateImage::RotateBmp(BYTE *pBmpData, BYTE *&pDesData, int nWidth, int nHeight, 
							 int nDesWidth, int nDesHeight, double dAngle)
{
	// �������Һ�����ֵ
	double dSin = sin(dAngle);
	double dCos = cos(dAngle);
	//�ڶ��з���һ���ռ䣬���ڴ洢��ת���λͼ����
	pDesData = new BYTE[nDesWidth * nDesHeight * 4];
	//��ʼ�ѿռ��е�����
	memset(pDesData, 255, nDesWidth * nDesHeight * 4);

	//����dx��dy
	double dX = -0.5*nDesWidth*dCos - 0.5*nDesHeight*dSin + 0.5*nWidth;
	double dY = 0.5*nDesWidth*dSin - 0.5*nDesHeight*dCos + 0.5*nHeight;

	BYTE* pSrc = NULL;	
	BYTE* pDes = NULL;	
	int x = 0;				
	int	y = 0;				
	for (int h = 0; h < nDesHeight; h++)
	{
		for (int w = 0; w < nDesWidth; w++) 
		{
			//��0.5��Ϊ������ȡ��
			//x,y��ʾĿ������w,h������Ӧ��Դͼ���е�����
			x = (int)(w * dCos + h * dSin + dX + 0.5);
			y = (int)(-w * dSin + h * dCos + dY + 0.5);
			if (x == nWidth)
			{
				x--;
			}
			if (y == nHeight)
			{
				y--;
			}

			pSrc = pBmpData + y * nWidth * 4 + x * 4;
			pDes = pDesData + h * nDesWidth * 4 + w * 4;
			//�ж�Ŀ�������е���������Դλͼ�д�������㣬ͨ��Ŀ��������Դλͼ�����
			//��ˣ���ЩĿ�������е���Щ������Դλͼ����û�ж�Ӧ������㣬������˵���Щ�����
			if (x >= 0 && x < nWidth && y >= 0 && y < nHeight)
			{
				memcpy(pDes, pSrc, 4);
			}
		}
	}
}

void CRotateImage::OnFixdegree() 
{
	CButton *pButton = (CButton*)GetDlgItem(IDC_FIXDEGREE);	
	if (pButton!=NULL)
	{
		pButton->SetCheck(TRUE);
		pButton = (CButton*)GetDlgItem(IDC_RANDDEGREE);	
		pButton->SetCheck(FALSE);
	}	
}

void CRotateImage::OnRanddegree() 
{
	CButton *pButton = (CButton*)GetDlgItem(IDC_RANDDEGREE);	
	if (pButton!=NULL)
	{
		pButton->SetCheck(TRUE);
		pButton = (CButton*)GetDlgItem(IDC_FIXDEGREE);	
		pButton->SetCheck(FALSE);
	}	
}

void CRotateImage::OnLBtnRadio(UINT nID)
{
	for (UINT i = IDC_ROTATE45; i<IDC_ROTATE270+1 ; i++)
	{
		CButton* pButton = (CButton*)GetDlgItem(i);
		if (i==nID)	
		{
			pButton->SetCheck(TRUE);
		}
		else
		{
			pButton->SetCheck(FALSE);
		}
	}
}

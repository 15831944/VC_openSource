// NumberCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ElectronClock.h"
#include "NumberCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNumberCtrl

CNumberCtrl::CNumberCtrl()
{
	m_csText = "";
	m_nNumberWidth = 26;
	m_nNumberHeight = 34;
	m_nNumberLen = 8;
}

CNumberCtrl::~CNumberCtrl()
{

}


BEGIN_MESSAGE_MAP(CNumberCtrl, CStatic)
	//{{AFX_MSG_MAP(CNumberCtrl)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNumberCtrl message handlers

void CNumberCtrl::OnPaint() 
{
	CPaintDC dc(this); 
	SetRedraw(FALSE);								//��ֹ���ڻ���
	CRect clientRC;
	GetClientRect(clientRC);							//��ȡ���ڿͻ�����
	CMemDC memDC(&dc, clientRC);					//�����ڴ滭��
	SetWindowText("");
	CBitmap bmp;
	bmp.LoadBitmap(IDB_NUMBERBMP);					//����λͼ
	CDC tmpDC;
	tmpDC.CreateCompatibleDC(&dc);					//����һ�����ݵ��豸������
	tmpDC.SelectObject(&bmp);							//ѡ��λͼ����
	BITMAP bInfo;									//����λͼ��Ϣ
	bmp.GetBitmap(&bInfo);							//��ȡλͼ��Ϣ
	int nbmpWidth = bInfo.bmWidth;						//��ȡλͼ���
	int nbmpHeight = bInfo.bmHeight;						//��ȡλͼ�߶�
	int nLen = m_csText.GetLength();						//��ȡ�ı�����
	for (int i=0; i<m_nNumberLen; i++)					//���Ʊ���
	{
		memDC.BitBlt((i)*m_nNumberWidth, 0, m_nNumberWidth, nbmpHeight, 
			&tmpDC, 10*m_nNumberWidth, 0, SRCCOPY);
	}
	if (nLen>0 && nLen<=m_nNumberLen)					//�ж������Ƿ�Ϸ�
	{
		for (int n=0; n<nLen; n++)
		{
			char ch = m_csText[nLen-n-1];
			if (ch == ':' )
			{
				memDC.BitBlt((m_nNumberLen-10)*m_nNumberWidth, 0, m_nNumberWidth,
						nbmpHeight, &tmpDC, m_nNumberWidth, 0, SRCCOPY);
			}
			else
			{
				int nCh = atoi(&ch);
				//��������λͼ
				memDC.BitBlt((m_nNumberLen-n-1)*m_nNumberWidth, 0, m_nNumberWidth,
						nbmpHeight, &tmpDC, (nCh)*m_nNumberWidth, 0, SRCCOPY);
			}
		}
	}
	bmp.DeleteObject();								//ɾ��λͼ����
	tmpDC.DeleteDC();
	SetRedraw();									//����ڻ���
}

void CNumberCtrl::SetText(LPCTSTR text)
{
	m_csText = text;
	RedrawWindow();
}

LPTSTR CNumberCtrl::GetText()
{
	return m_csText.GetBuffer(0);
}

void CNumberCtrl::SubClassCtrl(UINT uID, CWnd *pParent)
{
	SubclassDlgItem(uID, pParent);						//���໯����
	CRect winRC;
	GetWindowRect(winRC);							//��ȡ��������
	ScreenToClient(winRC);
	MapWindowPoints(pParent,winRC);					//����������ӳ�䵽��������
	winRC.right = winRC.left+m_nNumberLen*m_nNumberWidth;//���ô��ڿ��
	winRC.bottom = winRC.top+m_nNumberHeight;			//���ô��ڸ߶�
	MoveWindow(winRC);								//���ÿؼ���ʾ��λ��
}


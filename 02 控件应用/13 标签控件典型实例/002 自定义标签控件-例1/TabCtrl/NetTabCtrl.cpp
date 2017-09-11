// NetTabCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "TabCtrl.h"
#include "NetTabCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetTabCtrl

CNetTabCtrl::CNetTabCtrl()
{
}

CNetTabCtrl::~CNetTabCtrl()
{
}



BEGIN_MESSAGE_MAP(CNetTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CNetTabCtrl)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetTabCtrl message handlers

void CNetTabCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	ASSERT(lpDrawItemStruct->CtlType == ODT_TAB);
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);
	CRect itemRC(lpDrawItemStruct->rcItem);			//��ȡ��Ŀ����
	int nIndex = lpDrawItemStruct->itemID;			//��ȡ��Ŀ����
	int nState = lpDrawItemStruct->itemState;		//��ȡ��Ŀ״̬
	static COLORREF clrBK = RGB(229, 229, 215);		//����Ĭ�ϱ�����ɫ
	static COLORREF clrSelBK = RGB(252, 252, 254);	//����ѡ�еı�����ɫ 
	COLORREF clrText = RGB(113, 111, 100);
	if (nState & ODS_SELECTED)						//����ѡ��״̬
	{
		dc.FillSolidRect((CRect)lpDrawItemStruct->rcItem, clrSelBK);
		clrText = RGB(0, 0, 0);
	}
	else											//��ѡ��״̬
	{
		if (nIndex == 0)
		{
			CRect itemRC = lpDrawItemStruct->rcItem;
			itemRC.OffsetRect(-1, 0);
			dc.FillSolidRect(itemRC, clrBK);
		}
		else
		{
			dc.FillSolidRect((CRect)lpDrawItemStruct->rcItem, clrBK);
		}
	}
	//������Ŀ�ı���ͼ��
	char szText[MAX_PATH] = {0};
	TC_ITEM tcItem;
	tcItem.mask        = TCIF_TEXT | TCIF_IMAGE;
	tcItem.pszText     = szText;
	tcItem.cchTextMax  = MAX_PATH;
	GetItem(nIndex, &tcItem);
	CImageList* pImages = GetImageList();			//��ȡ�ؼ�������ͼ���б�
	if (pImages != NULL)
	{
		CPoint iconPT;
		iconPT.x = itemRC.left;
		iconPT.y = itemRC.top;
		pImages->Draw(&dc, tcItem.iImage, iconPT, ILD_NORMAL);
	}
	//����ı�
	itemRC.left += 40;
	//�����ı���ɫ
	dc.SetTextColor(clrText);
	dc.SetBkMode(TRANSPARENT);
	CFont* pFont = GetFont();
	dc.SelectObject(pFont);
	dc.DrawText(szText, strlen(szText), itemRC, DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	dc.Detach();
}


void CNetTabCtrl::OnPaint() 
{
	CPaintDC dc(this); 
	DRAWITEMSTRUCT drawItem;
	drawItem.CtlType = ODT_TAB;
	drawItem.CtlID = GetDlgCtrlID();
	drawItem.hwndItem = GetSafeHwnd();
	drawItem.hDC = dc.GetSafeHdc();
	drawItem.itemAction = ODA_DRAWENTIRE;
	GetClientRect(&drawItem.rcItem);
	CRect clientRC;
	CRect pageRC;
	pageRC = drawItem.rcItem;
	AdjustRect(FALSE, pageRC);
	drawItem.rcItem.top = pageRC.top - 2;
	//���Ʊ�ǩҳ�ı߿�
	DrawTabBorder(&dc, (CRect)drawItem.rcItem);
	int nItemCount = GetItemCount();
	int nCurSel = GetCurSel();
	if (nItemCount < 1)
		return;
	for(int i=0; i<nItemCount; i++)
	{
		drawItem.itemID = i;
		if (i == nCurSel)
			drawItem.itemState = ODS_SELECTED;
		else
			drawItem.itemState = 0;
		GetItemRect(i, &drawItem.rcItem);
		DrawItem(&drawItem);
		//������Ŀ�߿�
		DrawItemFrame(&drawItem);
	}
}



//���Ʊ�ǩ�ؼ��ı߿�
void CNetTabCtrl::DrawTabBorder(CDC *pDC, CRect &TabRC)
{	
	pDC->Draw3dRect(&TabRC, RGB(255, 255, 255), RGB(177, 174, 162));
}

//������Ŀ�߿�
void CNetTabCtrl::DrawItemFrame(DRAWITEMSTRUCT *lpDrawItem)
{
	int nCurSel = GetCurSel();
	int nIndex = lpDrawItem->itemID;
	BOOL bSelected = (nCurSel==nIndex);
	CDC dc;
	CRect itemRC = lpDrawItem->rcItem;
	dc.Attach(lpDrawItem->hDC);
	if (bSelected)	//��Ŀ����ѡ��״̬
	{
		itemRC.OffsetRect(-1, 0);
		dc.FrameRect(&itemRC, &CBrush(RGB(172, 168, 153)));
	}
	else			//��Ŀ���ڷ�ѡ��״̬
	{
		//�����������˵ķָ���
		if (nIndex == 0)
			dc.FillSolidRect(itemRC.left, itemRC.top + 2, 1, itemRC.Height() - 4, RGB(172, 168, 153));
		dc.FillSolidRect(itemRC.right - 1, itemRC.top + 2, 1, itemRC.Height() - 4, RGB(172, 168, 153));
	}
	dc.Detach();
}

BOOL CNetTabCtrl::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}

void CNetTabCtrl::PreSubclassWindow() 
{
	SetMinTabWidth(100);			//������Сѡ��Ŀ��
	SetItemSize(CSize(120, 32));	//����ѡ��Ŀ�Ⱥ͸߶�	
	CTabCtrl::PreSubclassWindow();
}

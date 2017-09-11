// ImageButton.cpp : implementation file
//

#include "stdafx.h"
#include "ImageText.h"
#include "ImageButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ImageButton

ImageButton::ImageButton()
{
	IsPressed = FALSE;
}

ImageButton::~ImageButton()
{
}


BEGIN_MESSAGE_MAP(ImageButton, CButton)
	//{{AFX_MSG_MAP(ImageButton)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ImageButton message handlers

void ImageButton::SetImageIndex(UINT index)
{
	m_ImageIndex = index;
}

void ImageButton::SetImageList(CImageList *pImage)
{
	m_pImagelist = pImage;
}

void ImageButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC dc ;
	dc.Attach(lpDrawItemStruct->hDC);	
	if (m_pImagelist)
	{
		UINT state = lpDrawItemStruct->itemState; //��ȡ״̬
		UINT action = lpDrawItemStruct->itemAction;
		//��ȡͼ������ͼ���С
		IMAGEINFO imageinfo;
		m_pImagelist->GetImageInfo(m_ImageIndex,&imageinfo);
		CSize imagesize;
		imagesize.cx = imageinfo.rcImage.right-imageinfo.rcImage.left;
		imagesize.cy = imageinfo.rcImage.bottom - imageinfo.rcImage.top;
		//�ڰ�ť��ֱ���������ʾλͼ
		CRect rect;
		GetClientRect(rect);
		CPoint point;
		point.x = 5;
		point.y = (rect.Height() - imagesize.cy)/2;
		m_pImagelist->Draw(&dc,m_ImageIndex,point,ILD_NORMAL|ILD_TRANSPARENT);
		//��ť��ѡ�л��߻�ý���ʱ
		if ((state&ODS_SELECTED)||(state&ODS_FOCUS))
		{		
			CRect focusRect (rect); //�������
			focusRect.DeflateRect(4,4,4,4);
			CPen pen(PS_DASHDOTDOT,1,RGB(0,0,0));
			CBrush brush;
			brush.CreateStockObject(NULL_BRUSH);
			dc.SelectObject(&brush);
			dc.SelectObject(&pen);
			//���ƽ������
			dc.DrawFocusRect(focusRect);
			//��������Ч��
			dc.DrawEdge(rect,BDR_RAISEDINNER|BDR_RAISEDOUTER,BF_BOTTOMLEFT|BF_TOPRIGHT);			
			//��ý���ʱ���ƺ�ɫ�߿�
			dc.Draw3dRect(rect,RGB(51,51,51),RGB(0,0,0));
		}
		else  //Ĭ�������
		{	
			CRect focusRect (rect);
			focusRect.DeflateRect(4,4,4,4);		
			CPen pen(PS_DOT,1,RGB(192,192,192));
			CBrush brush;
			brush.CreateStockObject(NULL_BRUSH);
			dc.SelectObject(&brush);
			dc.SelectObject(&pen);
			dc.Rectangle(focusRect);			
			dc.DrawEdge(rect,BDR_RAISEDINNER|BDR_RAISEDOUTER,BF_BOTTOMLEFT|BF_TOPRIGHT);	
		}
		if (IsPressed) //�ڰ�ť������ʱ���ư���Ч��
		{

			CRect focusRect1(rect);
			focusRect1.DeflateRect(4,4,4,4);
			dc.DrawFocusRect(focusRect1);			
			dc.DrawEdge(rect,BDR_SUNKENINNER |BDR_SUNKENOUTER ,BF_BOTTOMLEFT|BF_TOPRIGHT);

			dc.Draw3dRect(rect,RGB(51,51,51),RGB(0,0,0));	
			//dc.DrawFocusRect(focusRect1);
		}
		//���ư�ť�ı�
		CString text;
		GetWindowText(text);
		rect.DeflateRect(point.x+imagesize.cx+2,0,0,0);
		dc.SetBkMode(TRANSPARENT);
		dc.DrawText(text,rect,DT_LEFT|DT_SINGLELINE|DT_VCENTER);
	}
}

void ImageButton::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CButton::PreSubclassWindow();
	ModifyStyle(0,BS_OWNERDRAW);
}

void ImageButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
/*	CRect rect;
	GetClientRect(rect);

	if (!rect.PtInRect(point)) //�жϵ�ǰ�����Ƿ��ڰ�ť������
	{
		if (IsPressed) //�����겻�ڰ�ť��������,���Ұ�ť���ڰ���״̬,����ť����Ϊ����״̬
			IsPressed = FALSE;
	}*/
	CButton::OnMouseMove(nFlags, point);
}

void ImageButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	IsPressed = TRUE; //��ť������
	CButton::OnLButtonDown(nFlags, point);
}

void ImageButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	IsPressed = FALSE;	//�ͷ���갴ť
	CButton::OnLButtonUp(nFlags, point);
}

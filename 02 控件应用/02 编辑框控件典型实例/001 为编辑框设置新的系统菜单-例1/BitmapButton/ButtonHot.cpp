// ButtonHot.cpp : implementation file
//

#include "stdafx.h"
#include "BitmapButton.h"
#include "ButtonHot.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CButtonHot

CButtonHot::CButtonHot()
{
	m_DownPic   = IDB_BUTTONDOWN;		//��갴��ʱ��ʾ��ͼƬ
	m_NomalPic  = IDB_BUTTONUP;			//�����������ʾ��ͼƬ
	m_EnablePic = IDB_BUTTONENABLE;		//��ťʧЧʱ��ʾ��ͼƬ
	m_MovePic   = IDB_BUTTONMOVE;		//��꾭����ťʱ��ʾ��ͼƬ
	m_IsInRect  = FALSE;
}

CButtonHot::~CButtonHot()
{
}


BEGIN_MESSAGE_MAP(CButtonHot, CButton)
	//{{AFX_MSG_MAP(CButtonHot)
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CButtonHot message handlers

void CButtonHot::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	CDC dc;														//�����豸������
	dc.Attach(lpDrawItemStruct->hDC);									//��û��ư�ť�豸������
	UINT state = lpDrawItemStruct->itemState; 							//��ȡ״̬
	CRect rect;													//�����������
	GetClientRect(rect);										//��ñ༭��ͻ�����
	CString text;
	GetWindowText(text);
	
	if(state & ODS_DISABLED)
	{
		DrawBK(&dc,m_EnablePic);
		dc.SetTextColor(RGB(0,0,0));
	}
	else if(state&ODS_SELECTED)
	{
		DrawBK(&dc,m_DownPic);
		dc.SetTextColor(RGB(0,0,255));
	}
	else if(m_IsInRect==TRUE)
	{
		DrawBK(&dc,m_MovePic);
		dc.SetTextColor(RGB(255,0,0));
	}
	else 													//Ĭ�������
	{
		DrawBK(&dc,m_NomalPic);
		dc.SetTextColor(RGB(0,0,0));
	}
	if(state&ODS_FOCUS)
	{
		CRect FocTect(rect);
		FocTect.DeflateRect(2,2,2,2);
		dc.DrawFocusRect(&FocTect);
		lpDrawItemStruct->itemAction = ODA_FOCUS ;
	}
	dc.SetBkMode(TRANSPARENT);
	dc.DrawText(text,&rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
}

void CButtonHot::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CPoint point;						//����Cpoint����
	GetCursorPos(&point); 				//������λ��
	CRect rcWnd;						//�����������
	GetWindowRect(&rcWnd); 			//��ð�ť����
	if(rcWnd.PtInRect(point)) 				//�ж�����Ƿ��ڰ�ť��
	{
		if(m_IsInRect == TRUE) 			//�ж�����Ƿ�һֱ�ڰ�ť��
			goto END;					//��ת�����
		else							//����ƶ�����ť��
		{
			m_IsInRect = TRUE;			//����m_IsInRect����ֵ
			Invalidate(); 				//�ػ水ť
		}
	}
	else															//���ڰ�ť������
	{
		if(m_IsInRect == FALSE)										//�ж����һֱ�ڰ�ť��
			goto END;												//��ת�����
		else														//����ƶ�����ť��
		{
			Invalidate(); 											//�ػ水ť
			m_IsInRect = FALSE;										//����m_IsInRect����ֵ
		}
	}
END:	CButton::OnTimer(nIDEvent);									//���ñ�ǣ����û��෽��
}

void CButtonHot::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	SetTimer(1,10,NULL); 				//���ö�ʱ��
	CButton::PreSubclassWindow();
}

BOOL CButtonHot::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return true;//CButton::OnEraseBkgnd(pDC);
}

void CButtonHot::DrawBK(CDC *pDC, UINT ResID)
{
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CRect rect;													//�����������
	GetClientRect(rect);										//��ñ༭��ͻ�����
	CBitmap bitmap;
	BITMAP bitStruct;
	bitmap.LoadBitmap(ResID);
	bitmap.GetBitmap(&bitStruct);
	memDC.SelectObject(&bitmap);
	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&memDC,0,0,bitStruct.bmWidth
		,bitStruct.bmHeight,SRCCOPY);
	memDC.DeleteDC();
	bitmap.DeleteObject();
}

BOOL CButtonHot::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->hwnd==this->GetSafeHwnd()&&pMsg->message==WM_KEYDOWN && pMsg->wParam==13)
	{
		pMsg->lParam  = 0;
		pMsg->message = WM_LBUTTONDOWN;
	}
	if(pMsg->hwnd==this->GetSafeHwnd()&&pMsg->message==WM_KEYUP && pMsg->wParam==13)
	{
		pMsg->lParam  = 0;
		pMsg->message = WM_LBUTTONUP;
	}
	return CButton::PreTranslateMessage(pMsg);
}
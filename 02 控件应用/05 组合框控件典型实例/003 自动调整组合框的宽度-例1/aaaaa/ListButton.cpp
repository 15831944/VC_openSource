// ListButton.cpp : implementation file
//

#include "stdafx.h"
#include "aaaaa.h"
#include "ListButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListButton

CListButton::CListButton()
{
}

CListButton::~CListButton()
{
}


BEGIN_MESSAGE_MAP(CListButton, CButton)
	//{{AFX_MSG_MAP(CListButton)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListButton message handlers

void CListButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	CRect rect;												//�����������
	GetClientRect(rect);											//��ð�ť�Ŀͻ�����
	CDC dc;													//�����豸������
	dc.Attach(lpDrawItemStruct->hDC);								//�����豸������
	dc.SetBkMode(TRANSPARENT);								//���ñ���͸��
	CBrush m_Brush(RGB(100,140,200));						//������ˢ
	dc.SelectObject(&m_Brush);									//����ˢѡ���豸������
	dc.DrawEdge(rect,BDR_RAISEDINNER|BDR_RAISEDOUTER
		,BF_BOTTOMLEFT|BF_TOPRIGHT);						//��������Ч��
	dc.Draw3dRect(rect,RGB(51,51,51),RGB(0,0,0));			//��ý���ʱ���ƺ�ɫ�߿�
	CRect rc(rect);
	rc.DeflateRect(2,2,2,2);
	dc.FillRect(rc,&m_Brush);							//�û�ˢ��䰴ť
	CString str;
	GetWindowText(str);								//��ð�ť�ı�
	dc.SetTextColor(RGB(255,255,255));					//���ð�ť��ɫ
	dc.DrawText(str,CRect(0,0,rect.right,rect.bottom),
		DT_CENTER|DT_VCENTER|DT_SINGLELINE);		//���ư�ť�ı�
}

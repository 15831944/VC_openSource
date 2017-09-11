// ColourEdit.cpp : implementation file
//

#include "stdafx.h"
#include "ColourFrame.h"
#include "ColourEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColourEdit

CColourEdit::CColourEdit()
{
}

CColourEdit::~CColourEdit()
{
}


BEGIN_MESSAGE_MAP(CColourEdit, CEdit)
	//{{AFX_MSG_MAP(CColourEdit)
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColourEdit message handlers

HBRUSH CColourEdit::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
	CDC* dc = GetDC(); //��ȡ��������
	CRect rect;
	GetClientRect(rect); //��ȡ�ͻ�����
	rect.InflateRect(1,1,1,1);//���ͻ���������һ������
	CBrush brush (m_Colour);//������ˢ
	dc->FrameRect(rect,&brush);//���Ʊ߿�
	// TODO: Return a non-NULL brush if the parent's handler should not be called
	return NULL;
}

void CColourEdit::SetColour(COLORREF Colour)
{
	m_Colour = Colour;
}

// CustomButton.cpp : implementation file
//

#include "stdafx.h"
#include "NotRule.h"
#include "CustomButton.h"
#include <cmath>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define PI 2.0*asin(1.0)
/////////////////////////////////////////////////////////////////////////////
// CCustomButton

CCustomButton::CCustomButton()
{
	IsPressed = false; 
}

CCustomButton::~CCustomButton()
{
}


BEGIN_MESSAGE_MAP(CCustomButton, CButton)
//{{AFX_MSG_MAP(CCustomButton)
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomButton message handlers
void CCustomButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{ 
	CRect rect;
	GetClientRect(rect);								//��ð�ť�ͻ�����
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);					//����豸������
	int x,y,r;
	x = rect.Width()/2;
	y = rect.top;
	r = rect.Height()/2;
	double lpi=0;
	arrays[0] = CPoint(x,y);							//���ö���ε�һ����������
	if(m_result)
	{
		for(int i=1;i<m_num;i++)						//���ݶ���ζ�����ѭ��
		{
			lpi+=(2*PI/m_num);							//���ÿ���������ԽǶ�
			if(lpi<=2*PI/4)								//С�ڵ���90��ʱ
			{
				arrays[i] = CPoint(x+r*sin(2*i*PI/m_num),r-r*cos(2*i*PI/m_num));
			}
			if(lpi>2*PI/4 && lpi<=2*PI/2)					//����90��С�ڵ���180��
			{
				arrays[i] = CPoint(x+r*sin(PI-2*i*PI/m_num),r+r*cos(PI-2*i*PI/m_num));
			}
			if(lpi>2*PI/2 && lpi<=2*PI*3/4)					//����180��С�ڵ���270��
			{
				arrays[i] = CPoint(x-r*sin(2*i*PI/m_num-2*PI/2),r+r*cos(2*i*PI/m_num-2*PI/2));
			}
			if(lpi>2*PI*3/4 && lpi<=2*PI)					//����270��С�ڵ���360��
			{
				arrays[i] = CPoint(x-r*sin(2*PI-2*i*PI/m_num),r-r*cos(2*PI-2*i*PI/m_num));
			}
		}
	}
	dc.SetBkMode(TRANSPARENT);  					//���ñ���͸��
	CBrush brush(m_color);  							//����һ��λͼ��ˢ
	dc.SelectObject(&brush);
	CPen pen(PS_NULL,1,m_color);					//��������
	dc.SelectObject(&pen);
	if(m_result)
		dc.Polygon(arrays,m_num);							//���ƶ����
	else
		dc.Ellipse(0,0,rect.Width(),rect.Height());					//����Բ��
	if(IsPressed) 										//�ж�����Ƿ���
	{
		CPen pen(PS_DASHDOTDOT,2,RGB(0,0,0));				//��������
		dc.SelectObject(&pen);
		if(m_result)
		{
			dc.MoveTo(arrays[0]);							//�������
			for(int i=1;i<m_num;i++)
			{
				dc.LineTo(arrays[i]);							//����
			}
			dc.LineTo(arrays[0]);
		}
		else
			dc.Ellipse(0,0,rect.Width(),rect.Height());				//����Բ��
	}
	else
	{
		CPen pen(PS_DASHDOTDOT,2,m_color);				//���û���
		dc.SelectObject(&pen);
		if(m_result)
		{
			dc.MoveTo(arrays[0]);							//���ö���
			for(int i=1;i<m_num;i++)
			{
				dc.LineTo(arrays[i]);							//������α���
			}
			dc.LineTo(arrays[0]);
		}
		else
			dc.Ellipse(0,0,rect.Width(),rect.Height());				//����Բ��
	}
	
	CString str;
	GetWindowText(str);									//��ð�ť�ı�
	dc.SetTextColor(RGB(0,0,0));							//�����ı���ɫ
	dc.DrawText(str,CRect(0,0,rect.right,rect.bottom),DT_CENTER|DT_VCENTER|DT_SINGLELINE);	//���ư�ť�ı�
}


void CCustomButton::SetPolygon(int num)
{
	m_num = num;
}

void CCustomButton::SetResult(BOOL result,COLORREF color)
{
	m_result = result;
	m_color = color;   
}

void CCustomButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	IsPressed = true; 
	CButton::OnLButtonDown(nFlags, point);
}

void CCustomButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	IsPressed = false; 
	CButton::OnLButtonUp(nFlags, point);
}

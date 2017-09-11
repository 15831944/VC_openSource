// CustomButton.cpp : implementation file
//

#include "stdafx.h"
#include "XPStyleButton.h"
#include "CustomButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomButton

CCustomButton::CCustomButton()
{
	m_State   = bsNormal;
}

CCustomButton::~CCustomButton()
{
	m_State   = bsNormal;
}


BEGIN_MESSAGE_MAP(CCustomButton, CButton)
	//{{AFX_MSG_MAP(CCustomButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomButton message handlers


void CCustomButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_State = bsDown;					//���ð�ť����״̬
	InvalidateRect(NULL,TRUE);		//���°�ť
}

void CCustomButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	HRGN hRgn = CreateRectRgn(0, 0, 0, 0);
	GetWindowRgn(hRgn);
	BOOL ret = PtInRegion(hRgn, point.x, point.y);//����Ƿ��ڰ�ť��
	if(ret)							//�ڰ�ť��
	{
		if(m_State == bsDown) 		//�жϰ�ť�Ƿ�Ϊ����״̬
			return ;
		if(m_State != bsHot) 			//�жϰ�ť�Ƿ����ȵ�״̬
		{
			m_State = bsHot;			//����Ϊ�ȵ�״̬
			InvalidateRect(NULL,TRUE);	//���°�ť
			SetCapture();				//�������
		}
	} 
	else								//���ڰ�ť��
	{
		m_State = bsNormal;				//���ð�ť״̬
		InvalidateRect(NULL,TRUE);		//���°�ť
		ReleaseCapture();				//�ͷ����
	}	
	DeleteObject( hRgn );	

	CButton::OnMouseMove(nFlags, point);
}

void CCustomButton::OnPaint() 
{
	CPaintDC dc(this); 					//��ȡ��ť���豸������
	CString		Text;					//����һ���ַ�������
	CRect		RC;						//����һ���������
	CFont		Font;					//����һ���������
	CFont		*pOldFont;				//����һ���������ָ�룬���ڴ洢֮ǰ������
	CBrush		Brush;					//����һ����ˢ����
	CBrush		*pOldBrush;				//����һ����ˢ����ָ�룬���ڴ洢֮ǰ�Ļ�ˢ����
	CPoint		PT(2,2);					//����һ�������
	dc.SetBkMode(TRANSPARENT);		//���豸�����ı���ģʽ����Ϊ͸��
	Font.CreateFont(12, 0, 0, 0, FW_HEAVY, 0, 0, 0, ANSI_CHARSET, 
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		VARIABLE_PITCH | FF_SWISS, "����");		//��������
	pOldFont = dc.SelectObject(&Font);						//ѡ���µ�����
	if(m_State == bsNormal)				//�жϰ�ť�Ƿ�Ϊ����״̬
	{
		Brush.CreateSolidBrush( RGB(230, 230, 230)); 	//����ָ����ɫ�Ļ�ˢ
		dc.SetTextColor(RGB(0, 0, 0));		//�����ı���ɫ
	}
	else if(m_State == bsDown)			//�жϰ�ť�Ƿ�Ϊ����״̬
	{
		Brush.CreateSolidBrush(RGB(100, 100, 180));	//����ָ����ɫ�Ļ�ˢ
		dc.SetTextColor(RGB(250, 250, 0));		//�����ı���ɫ
	}
	else if(m_State == bsHot)			//�жϰ�ť�Ƿ�Ϊ�ȵ�״̬
	{
		Brush.CreateSolidBrush(RGB(230, 230, 130));	//����ָ����ɫ�Ļ�ˢ
		dc.SetTextColor(RGB(50, 50, 250));		//�����ı���ɫ
	}
	pOldBrush = dc.SelectObject(&Brush);					//ѡ�л�ˢ
	GetClientRect(&RC);							//��ȡ��ť�Ŀͻ�����
	dc.RoundRect(&RC, PT);								//���õ�ǰѡ�еĻ�ˢ�ͻ��ʻ��ư�ť����
	HRGN hRgn = CreateRectRgn(RC.left, RC.top, RC.right, RC.bottom);		//����һ��ѡ��
	SetWindowRgn(hRgn, TRUE);								//���ð�ť��������
	DeleteObject(hRgn);												//ɾ��ѡ��
	GetWindowText(Text);										//��ȡ��ť�ı�
	dc.DrawText(Text, &RC, DT_CENTER | DT_VCENTER | DT_SINGLELINE);	//���ư�ť�ı�
	Font.DeleteObject();												//ɾ���������
	Brush.DeleteObject();												//ɾ����ˢ����
	dc.SelectObject(pOldFont);											//�ָ�ԭ��ѡ�е�����
	dc.SelectObject(pOldBrush);										//�ָ�ԭ��ѡ�еĻ�ˢ
}

void CCustomButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(m_State != bsNormal)			//�жϰ�ť״̬
	{
		m_State = bsNormal;			//���ð�ť״̬
		ReleaseCapture();				//�ͷ���겶׽
		InvalidateRect(NULL,TRUE);	//���°�ť
	}	
	//�򸸴��ڷ���������Ϣ
	::SendMessage(GetParent()->m_hWnd,WM_COMMAND, GetDlgCtrlID(), (LPARAM) m_hWnd);
}

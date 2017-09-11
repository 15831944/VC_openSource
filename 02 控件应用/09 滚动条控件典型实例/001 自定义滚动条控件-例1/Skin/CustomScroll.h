#if !defined(AFX_CUSTOMSCROLL_H__783E2CD7_18AF_4F83_B4DC_D38723370FCE__INCLUDED_)
#define AFX_CUSTOMSCROLL_H__783E2CD7_18AF_4F83_B4DC_D38723370FCE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomScroll.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustomScroll window


class CMemDC : public CDC 
{
private:
	CBitmap*	m_bmp;
	CBitmap*	m_oldbmp;
	CDC*		m_pDC;
	CRect		m_Rect;
public:
	CMemDC(CDC* pDC, const CRect& rect) : CDC()
	{
		CreateCompatibleDC(pDC);
		m_bmp = new CBitmap;
		m_bmp->CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
		m_oldbmp = SelectObject(m_bmp);
		m_pDC = pDC;
		m_Rect = rect;
	}
	~CMemDC() 
	{
		m_pDC->BitBlt(m_Rect.left, m_Rect.top, m_Rect.Width(), m_Rect.Height(), 
				this, m_Rect.left, m_Rect.top, SRCCOPY);
		SelectObject(m_oldbmp);
		if (m_bmp != NULL) 
			delete m_bmp;
	}
};


class CCustomScroll : public CStatic
{
// Construction
public:
	CCustomScroll();
	UINT       m_ThumbWidth;  //������ͼ�ͷ���
	UINT       m_ThumbHeight; //������ͼ�ͷ�߶�
	CWnd*      m_pParent;     //������
	CRect      m_ClientRect;  //���ڿͻ�����

	CRect      m_ThumbRect;   //����������

	BOOL       m_ButtonDown;  //����Ƿ񵥻�������
	CPoint     m_Startpt;     //��갴��ʱ�����
	BOOL       m_IsLeft;      //�������Ƿ񳬹����ͷ
	BOOL       m_IsLeftArrow; //�Ƿ񵥻����������ť
	BOOL       m_IsRightArrow;//�Ƿ񵥻��ҹ�������ť  
	BOOL       m_IsLeftRange; //�Ƿ񵥻������������
	BOOL       m_IsRightRange;//�Ƿ񵥻����ҹ�������

	UINT       m_MinRange;    //��С������Χ
	UINT       m_MaxRange;    //��������Χ
	UINT       m_CurPos;      //��ǰ��λ��(�߼���λ)
	double     m_Rate;        //�����������߼���λ�ı���

	UINT       m_LeftArrow;   //���ͷλͼID
	UINT       m_RightArrow;  //�Ҽ�ͷλͼID
	UINT       m_ChanelBK;    //����λͼID
	UINT       m_ThumbBK;     //������λͼID

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomScroll)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetScrollRange(int minRange,int maxRange);
	void DrawHorScroll();
	void DrawControl();
	BOOL CreateStatic(CWnd* pParent,DWORD dwStyle,UINT nIDStatic,UINT nID);
	virtual ~CCustomScroll();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCustomScroll)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMSCROLL_H__783E2CD7_18AF_4F83_B4DC_D38723370FCE__INCLUDED_)

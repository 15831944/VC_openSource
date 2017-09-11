#if !defined(AFX_MYSTATIC_H__98E2D694_E860_4674_8F5F_4A8EF383B9E4__INCLUDED_)
#define AFX_MYSTATIC_H__98E2D694_E860_4674_8F5F_4A8EF383B9E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyStatic window

class CMyStatic : public CStatic
{
// Construction
public:
	CMyStatic();
	BOOL islined;  //�Ƿ����»���
	BOOL isframed; //�Ƿ��б߿�

	BOOL isLeft;   //�Ƿ��������
	BOOL isRight;  //�Ƿ����ұ���
	BOOL isTop;    //�Ƿ����ϱ���
	BOOL isBottom; //�Ƿ����±���

	COLORREF m_color;      //�ı���ɫ
	COLORREF m_framecolor; //�߿���ɫ
	UINT     m_lindwidth;  //���߿��
	UINT     align;        //�ı����뷽ʽ

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyStatic)
	afx_msg void OnPaint();
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSTATIC_H__98E2D694_E860_4674_8F5F_4A8EF383B9E4__INCLUDED_)

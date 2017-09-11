#if !defined(AFX_BUTTONHOT_H__D030DAFB_7E8F_4CDB_BDA2_078140A9E3FB__INCLUDED_)
#define AFX_BUTTONHOT_H__D030DAFB_7E8F_4CDB_BDA2_078140A9E3FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ButtonHot.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CButtonHot window

class CButtonHot : public CButton
{
// Construction
public:
	CButtonHot();
	UINT	m_DownPic;		//��갴��ʱ��ʾ��ͼƬ
	UINT	m_NomalPic;		//�����������ʾ��ͼƬ
	UINT	m_EnablePic;    //��ťʧЧʱ��ʾ��ͼƬ
	UINT	m_MovePic;		//��꾭����ťʱ��ʾ��ͼƬ
	BOOL	m_IsInRect;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CButtonHot)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawBK(CDC *pDC, UINT ResID);
	virtual ~CButtonHot();

	// Generated message map functions
protected:
	//{{AFX_MSG(CButtonHot)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUTTONHOT_H__D030DAFB_7E8F_4CDB_BDA2_078140A9E3FB__INCLUDED_)

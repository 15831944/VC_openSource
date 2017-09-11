// DocViewPrintView.h : interface of the CDocViewPrintView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOCVIEWPRINTVIEW_H__85FB5FCA_4D7E_44F0_BC53_2831E0CB82DB__INCLUDED_)
#define AFX_DOCVIEWPRINTVIEW_H__85FB5FCA_4D7E_44F0_BC53_2831E0CB82DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DocViewPrintDoc.h"

class CDocViewPrintView : public CView
{
protected: // create from serialization only
	CDocViewPrintView();
	DECLARE_DYNCREATE(CDocViewPrintView)
	
	CFont m_titlefont; //��������
	CFont m_bodyfont;  //��������



	int screenx,screeny; //��ȡ����ÿӢ��������
	int printx,printy; //��ȡ��ӡ��ÿӢ��������
	double xrate,yrate; //��ӡ������Ļ�����ر���

	int pageheight; //��ӡֽ�߶�
	int pagewidth; //��ӡֽ���

	int leftmargin,rightmargin; //��ӡֽ���ұ߾�
	BOOL isPreview; //�Ƿ���Ԥ��״̬
// Attributes
public:
	CDocViewPrintDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDocViewPrintView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDocViewPrintView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDocViewPrintView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DocViewPrintView.cpp
inline CDocViewPrintDoc* CDocViewPrintView::GetDocument()
   { return (CDocViewPrintDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOCVIEWPRINTVIEW_H__85FB5FCA_4D7E_44F0_BC53_2831E0CB82DB__INCLUDED_)

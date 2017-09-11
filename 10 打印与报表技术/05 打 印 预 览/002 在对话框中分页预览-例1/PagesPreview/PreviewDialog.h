#if !defined(AFX_PREVIEWDIALOG_H__B5017560_3294_4F9A_8CB2_49DC1F2DE410__INCLUDED_)
#define AFX_PREVIEWDIALOG_H__B5017560_3294_4F9A_8CB2_49DC1F2DE410__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PreviewDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPreviewDialog dialog

class CPreviewDialog : public CDialog
{
// Construction
protected:

	CPrintDialog *printsetup;//��ӡ����
	CPageSetupDialog *pagesetup;//ҳ����
	int Orientation;//���� default 1
	CRect Margin;//ҳ�߾�
	CPoint StartPoint;//�������
	CRect FrameMargin;//ҳ����߿����
	CSize PageSize;//ҳ��С
	int PageCount;//ҳ��
	int CurrentPage;//��ǰҳ
	int Zoom;//���Ŵ�С
	CSize hp,vp;

	void InitPreview(HDC hDC,DEVMODE dev);
	virtual void DrawPreview(CDC *DrawDC,CRect *DrawRect);
	void UpdateScroll();
public:
	CStatusBar * StatusBar;

	CPreviewDialog(CWnd* pParent = NULL);   // standard constructor
	void OnNext();
	void OnPrevi();
	void OnPrintsetup();
	void OnPagesetup();
	void OnZoomOut();
	void OnZoomIn();
	void UpdateStatusBar();
// Dialog Data
	//{{AFX_DATA(CPreviewDialog)
	enum { IDD = IDD_PREVIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPreviewDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPreviewDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREVIEWDIALOG_H__B5017560_3294_4F9A_8CB2_49DC1F2DE410__INCLUDED_)

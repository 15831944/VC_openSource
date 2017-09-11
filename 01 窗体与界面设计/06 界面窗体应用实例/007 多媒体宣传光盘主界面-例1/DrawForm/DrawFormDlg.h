// DrawFormDlg.h : header file
//

#if !defined(AFX_DRAWFORMDLG_H__12660E6B_91CD_419E_9FBF_33AE11C5F2FC__INCLUDED_)
#define AFX_DRAWFORMDLG_H__12660E6B_91CD_419E_9FBF_33AE11C5F2FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MyStatic.h"

/////////////////////////////////////////////////////////////////////////////
// CDrawFormDlg dialog

//��ť״̬
enum CButtonState{bsNone,bsIni,bsMin,bsMax,bsRes,bsClose};

class CDrawFormDlg : public CDialog
{
// Construction
public:
	void DrawFormCaption();
	void DrawForm();
	CDrawFormDlg(CWnd* pParent = NULL);	// standard constructor

	BOOL m_IsMax;         //�Ƿ������״̬
	int  m_BorderWidth;   //�߿���
	int  m_BorderHeight;  //�߿�߶�
	int  m_CaptionHeight; //�������ĸ߶�
	CString  m_Caption;      //���ڱ���
	COLORREF m_CapitonColor; //����������ɫ
	CFont    m_CaptionFont;  //��������

	int m_ButtonWidth;  //��ťλͼ���
	int m_ButtonHeight; //��ťλͼ�߶�
	
	BOOL  m_FirstShow; //�����״α���ʾ

	CRect m_OrigonRect;//ԭʼ��������

	CRect m_IniRect,m_MinRect,m_MaxRect,m_CloseRect;//��������ť����ʾ����
	
	CButtonState m_ButtonState; //��ť״̬

	BOOL m_IsDrawForm;//�Ƿ���Ҫ���ƴ���

// Dialog Data
	//{{AFX_DATA(CDrawFormDlg)
	enum { IDD = IDD_DRAWFORM_DIALOG };
	CMyStatic	m_label2;
	CMyStatic	m_label1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawFormDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDrawFormDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnNcPaint();
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void OnButton2();
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWFORMDLG_H__12660E6B_91CD_419E_9FBF_33AE11C5F2FC__INCLUDED_)

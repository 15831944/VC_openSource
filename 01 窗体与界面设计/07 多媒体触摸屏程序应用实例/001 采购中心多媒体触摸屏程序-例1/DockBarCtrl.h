#if !defined(AFX_DOCKBARCTRL_H__52BCC555_E091_4BCA_9991_2B2A36F655AB__INCLUDED_)
#define AFX_DOCKBARCTRL_H__52BCC555_E091_4BCA_9991_2B2A36F655AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DockBarCtrl.h : header file
//
#include "afxpriv.h"
/////////////////////////////////////////////////////////////////////////////
// CDockBarCtrl window

class CDockBarCtrl : public CControlBar
{
// Construction
public:
	CDockBarCtrl();

// Attributes
public:
	UINT m_DockBarID;
	
	CDialog *m_pDlg;      //�����ĶԻ���
	CBrush m_bkBrush;     //������ˢ
	CString m_Caption;    //���ڱ���

	CRect m_FloatRect;    //����ʱ�Ĵ�������
	CRect m_VerRect;      //����ʱ,����\����ʾʱ������
	CRect m_HorRect;      //����ʱ,����\����ʾʱ������

	//ȷ���������ķǿͻ����򲿷�
	int m_ncTBandHeight;  //�ǿͻ������ϱ����߶�
	int m_ncRBandWidth;   //�ұ����Ŀ��
	int m_ncLBandWidth ;  //ȷ��������Ŀ��
	int m_ncBBandHeight;  // ȷ���ױ����Ŀ��

	//�����������ť����ʾ����
	
	CRect m_closeRC; //�رհ�ť����ʾ����
	CRect m_maxRc;   //��󻯰�ť����ʾ����

	int m_ncLeftWidth ; //��¼��ֱ��ʾʱ�ķǿͻ�������������
	int m_ncTopHeight;  // ��¼ˮƽ��ʾʱ�ķǿͻ������ϱ����Ŀ��

	COLORREF m_TopBandColor,m_BottomBandColor; //������������ɫ

	BOOL  m_IsTraking; //�Ƿ��ڵ�����������С״̬
	BOOL  m_IsInRect;  //�жϿ������Ƿ���ͣ��״̬
	
	CPoint m_OldPos;  //��갴��ʱԭʼ��λ��
	CRect m_Bandrc;   //�϶��ı�������

	CRect m_temprc;   //��ʱ������
	int m_TopInterval,m_LeftInterval; //��������Ը����ڵ�λ��

	int m_HitTest;
	CSize m_Min; //�����������ڸ���״̬ʱ,�����û��ı����С����С����

	 
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDockBarCtrl)
	public:
	virtual BOOL Create(CWnd* pParentWnd, CDialog* pDialog, UINT nID, DWORD dwStyle= WS_CHILD | WS_VISIBLE | CBRS_LEFT, CCreateContext* pContext = NULL);
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
	virtual CSize CalcDynamicLayout(int nLength, DWORD nMode);
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawDashLine(CRect rect);
	void EndTracking();
	void BeginTracking();
	void DrowTitleLine(CDC* pDC);
	virtual ~CDockBarCtrl();
	
	//ʵ�ָ���ĳ��󷽷�
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	// Generated message map functions
protected:
	//{{AFX_MSG(CDockBarCtrl)
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	afx_msg void OnNcPaint();
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOCKBARCTRL_H__52BCC555_E091_4BCA_9991_2B2A36F655AB__INCLUDED_)

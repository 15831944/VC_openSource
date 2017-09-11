// FingerExerciseDlg.h : header file
//

#if !defined(AFX_FINGEREXERCISEDLG_H__F01575A7_3C13_49B5_90CD_D4A90D5C45A6__INCLUDED_)
#define AFX_FINGEREXERCISEDLG_H__F01575A7_3C13_49B5_90CD_D4A90D5C45A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFingerExerciseDlg dialog

class CFingerExerciseDlg : public CDialog
{
// Construction
public:
	void Initialization();
	void SetBitmap(int num);
	void RandLetter();
	CFingerExerciseDlg(CWnd* pParent = NULL);	// standard constructor
	UINT	   m_Num[10];       //��ʾ��ĸ
	CStatic   m_Static[10];//��̬�ؼ�
	int m_Error;			//������
	int m_Sum;				//������
	int m_Lose;				//©����
	int m_Time;				//��ʱ
	BOOL m_IsStart;			//��ʼ
	int m_iTime;			//��ʱ
	int m_aTime;			//���ʱ��

// Dialog Data
	//{{AFX_DATA(CFingerExerciseDlg)
	enum { IDD = IDD_FINGEREXERCISE_DIALOG };
	CButton	m_Cancel;
	CButton	m_Exit;
	CButton	m_Start;
	CEdit	m_Alternation;
	CEdit	m_Timing;
	CEdit	m_sNum;
	CEdit	m_Veracity;
	CEdit	m_uTime;
	CEdit	m_Rate;
	CEdit	m_lNum;
	CEdit	m_eNum;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFingerExerciseDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFingerExerciseDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButstart();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnButexit();
	afx_msg void OnButcancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINGEREXERCISEDLG_H__F01575A7_3C13_49B5_90CD_D4A90D5C45A6__INCLUDED_)

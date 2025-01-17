// WriteIniDlg.h : header file
//

#if !defined(AFX_WRITEINIDLG_H__007E00E5_1D57_4E29_89AA_1A57B2D935D5__INCLUDED_)
#define AFX_WRITEINIDLG_H__007E00E5_1D57_4E29_89AA_1A57B2D935D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWriteIniDlg dialog
typedef struct _Record{
	int ID;
	char Name[255];
}Record;
class CWriteIniDlg : public CDialog
{
// Construction
public:
	CWriteIniDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWriteIniDlg)
	enum { IDD = IDD_WRITEINI_DIALOG };
	CEdit	m_edit8;
	CEdit	m_edit7;
	CEdit	m_edit6;
	CEdit	m_edit5;
	CEdit	m_edit4;
	CEdit	m_edit3;
	CEdit	m_edit2;
	CEdit	m_filename;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWriteIniDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWriteIniDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WRITEINIDLG_H__007E00E5_1D57_4E29_89AA_1A57B2D935D5__INCLUDED_)

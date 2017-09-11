// WebDlg.h : ͷ�ļ�
//

#pragma once
#include "explorer1.h"
#include "afxwin.h"


// CWebDlg �Ի���
class CWebDlg : public CDialog
{
// ����
public:
	CWebDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_WEB_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CExplorer1 m_Web;
public:
	afx_msg void OnBnClickedOk();
public:
	CEdit m_Url;
public:
	afx_msg void OnBnClickedLocate();
};

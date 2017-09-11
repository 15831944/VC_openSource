// ServerDlg.h : header file
//

#if !defined(AFX_SERVERDLG_H__EFCCE8FE_0A0C_4191_B7E7_D980FDFC82CC__INCLUDED_)
#define AFX_SERVERDLG_H__EFCCE8FE_0A0C_4191_B7E7_D980FDFC82CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CServerDlg dialog
#include "ServerSock.h"


//�������ݰ����ͣ��ı����ļ�
enum PackageType  {PTTEXT, PTFILE};

//�ļ����ͱ�ǣ���ʼ���ͣ����͹����У� ��������, �����ļ����ͣ��ܾ������ļ���ȡ���ļ����ͻ����
enum SendFlag {SFBEGIN, SFSENDING, SFEND, SFACCEPT, SFDENY, SFCANCEL};

//�Է��Է����ļ��Ļش𣬽��գ��ܾ���ȡ��(���͹�����)
enum RequestInfo {RIACCEPT, RIDENY, RICANCEL, RIUNKNOWN};

//����Ӧ�ò����ݰ��ṹ
//���ļ���ʼ����ʱ�����ݻ�������ǰ128���ֽ����ڴ洢�ļ�����������ļ�����, 
//�����ļ����͹����У����ݻ������о����ļ�����

class  CPackage
{
public:
	PackageType m_Type;						//���ݰ�����
	SendFlag	m_Flag;						//�ļ����ͱ��
	DWORD		m_dwSize;					//���ݱ��ṹ��С
	DWORD		m_dwFileSize;				//�����ļ���С
	DWORD		m_dwData;					//m_Data�Ĵ�С
	BYTE		m_Data[];					//���ݻ�����
};


class CServerDlg : public CDialog
{
// Construction
public:
	void ReveiveData();
	void AcceptConnect();
	CServerDlg(CWnd* pParent = NULL);	// standard constructor

	CServerSock	m_ServerSock;
	CServerSock m_ClientSock;
	BOOL		m_bSending;				//�ļ����ͽ�����
	HANDLE		m_hSendThread;			//�����ļ����߳̾��
	RequestInfo	m_RequestInfo;
	CString		m_szFileName;			//���͵��ļ�����
// Dialog Data
	//{{AFX_DATA(CServerDlg)
	enum { IDD = IDD_SERVER_DIALOG };
	CProgressCtrl	m_Progress;
	CEdit	m_FileName;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBrowse();
	afx_msg void OnSendFile();
	afx_msg void OnSendCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERDLG_H__EFCCE8FE_0A0C_4191_B7E7_D980FDFC82CC__INCLUDED_)

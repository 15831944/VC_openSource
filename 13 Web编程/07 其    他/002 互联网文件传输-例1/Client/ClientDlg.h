// ClientDlg.h : header file
//

#if !defined(AFX_CLIENTDLG_H__FF35012F_F82A_4839_8EF4_C8AB8F60516F__INCLUDED_)
#define AFX_CLIENTDLG_H__FF35012F_F82A_4839_8EF4_C8AB8F60516F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// CClientDlg dialog
#include "ClientSock.h"

//�������ݰ����ͣ��ı����ļ�
enum PackageType  {PTTEXT, PTFILE};

//�ļ����ͱ�ǣ���ʼ���ͣ����͹����У� ��������, �����ļ����ͣ��ܾ������ļ���ȡ���ļ����ͻ����
enum SendFlag {SFBEGIN, SFSENDING, SFEND, SFACCEPT, SFDENY, SFCANCEL};



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



class CClientDlg : public CDialog
{
// Construction
public:
	void HandleRecData(CPackage* pPackage);
	void ReceiveData();
	CClientDlg(CWnd* pParent = NULL);	// standard constructor

	CClientSock m_ClientSock;
	HGLOBAL		m_hGlobal;				//ȫ�ֶѾ��
	BOOL		m_bSending;				//�ļ��Ƿ��ڷ��͹�����

// Dialog Data
	//{{AFX_DATA(CClientDlg)
	enum { IDD = IDD_CLIENT_DIALOG };
	CEdit	m_ServerIP;
	CEdit	m_Port;
	CProgressCtrl	m_Progress;
	CButton	m_Cancel;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnExit();
	afx_msg void OnCancelRec();
	afx_msg void OnConnect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTDLG_H__FF35012F_F82A_4839_8EF4_C8AB8F60516F__INCLUDED_)

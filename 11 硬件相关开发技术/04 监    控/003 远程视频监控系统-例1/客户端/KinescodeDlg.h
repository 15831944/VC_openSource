// KinescodeDlg.h : header file
//

#if !defined(AFX_KINESCODEDLG_H__B73CC7D3_0F5C_4891_947A_3985421EA530__INCLUDED_)
#define AFX_KINESCODEDLG_H__B73CC7D3_0F5C_4891_947A_3985421EA530__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "vfw.h"
#pragma comment (lib,"vfw32.lib")
#include <afxmt.h>

#include "ClientSocket.h"
#include "Login.h"
//class CClientSocket;
/////////////////////////////////////////////////////////////////////////////
// CKinescodeDlg dialog
class CKinescodeDlg : public CDialog
{
// Construction
public:
	void ReceiveData(CClientSocket* sock);
	void SendData();
	virtual void OnCancel();
	CKinescodeDlg(CWnd* pParent = NULL);	// standard constructor

	HWND            m_hVideoWnd;   //��Ƶ��׽����
	CWinThread*     m_pThread;     //�̶߳���ָ��
	CEvent          m_Event;       //�¼�����,�����߳�ͬ��
	BOOL            m_IsKindscode; //�Ƿ�¼��
	CClientSocket*  m_pSock;       //�ͻ����׽���
	BOOL            m_IsSend;      //�Ƿ���
	BOOL            m_IsReceived;  //�������˽��������Ƿ����


	static UINT ThreadFun( LPVOID wParam );


// Dialog Data
	//{{AFX_DATA(CKinescodeDlg)
	enum { IDD = IDD_KINESCODE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKinescodeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CKinescodeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnExit();
	afx_msg void OnKinescode();
	afx_msg void OnStopkinescode();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLinkserver();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KINESCODEDLG_H__B73CC7D3_0F5C_4891_947A_3985421EA530__INCLUDED_)

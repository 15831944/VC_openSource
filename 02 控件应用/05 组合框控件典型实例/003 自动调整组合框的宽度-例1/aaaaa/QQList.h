#if !defined(AFX_QQLIST_H__C1D981D1_5FDD_4E18_9307_5E54DABF9E5C__INCLUDED_)
#define AFX_QQLIST_H__C1D981D1_5FDD_4E18_9307_5E54DABF9E5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QQList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQQList window
//����˫���б���ͼ��Ļص�����
typedef void(ItemDlbFun)(const CListCtrl* pListCtrl,int nItemIndex);
class CQQList : public CListCtrl
{
// Construction
public:
	CQQList();
	CPtrArray	m_pButton;				//��ť����
	UINT		m_ButtonCount ;			//��ť����
	UINT		m_ButtonHeight;			//��ť�߶�
	UINT		m_LeftMargin;			//ͼ���б���ʾ����߾�
	CListCtrl	m_ClientList;			//�ڿͻ�������ʾ��ͼ��
	ItemDlbFun* m_pItemDlbFun;			//��ͼ���˫���¼�
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQQList)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetImageLists(CImageList *pImagelist);
	void ShowButtonItems(UINT nIndex);//��ʾָ����ť�������б���ͼ��
	void AddButtonItems(UINT nIndex, CString &strItem, int nImageIndex);
	CRect GetListClientRect();
	UINT GetBtmTopIndex();//��ȡ�·���ť�Ķ�������
	UINT GetBtmBtnHeight();
	UINT GetTopButtonHeight();//���ض��㰴ť�ĸ߶�
	UINT CommandToIndex(UINT nID);//���ݰ�ť���������
	void OnButtonDown(UINT bIndex, UINT nID);//��ť�ĵ�������
	CRect GetAddButtonRect();//��ȡ��Ҫ��Ӱ�ť�Ŀͻ�����
	void AddButton(LPCSTR Btntext,UINT uID);
	virtual ~CQQList();

	// Generated message map functions
protected:
	//{{AFX_MSG(CQQList)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QQLIST_H__C1D981D1_5FDD_4E18_9307_5E54DABF9E5C__INCLUDED_)

// QQList.cpp : implementation file
//

#include "stdafx.h"
#include "aaaaa.h"
#include "QQList.h"
#include "ListButton.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQQList

CQQList::CQQList()
{
	m_ButtonHeight = 25;
	m_ButtonCount  = 0;
	m_pItemDlbFun  = NULL;
}

CQQList::~CQQList()
{
	int m = m_pButton.GetSize();
	for (int i = 0; i<m_pButton.GetSize();i++)
	{
		((CListButton*)m_pButton[i])->DestroyWindow();
		delete ((CListButton*)m_pButton[i]);
	}
}


BEGIN_MESSAGE_MAP(CQQList, CListCtrl)
	//{{AFX_MSG_MAP(CQQList)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQQList message handlers

void CQQList::AddButton(LPCSTR Btext, UINT uID)
{
	int index = m_pButton.Add(new CListButton);
	((CListButton*)m_pButton[m_pButton.GetSize()-1])->Create(
		Btext,WS_CHILD| BS_OWNERDRAW,GetAddButtonRect(),this,uID);		//������ť�ؼ�
	((CListButton*)m_pButton[m_pButton.GetSize()-1])->m_Index = index;	//���ð�ť����
	((CListButton*)m_pButton[m_pButton.GetSize()-1])->ShowWindow(SW_SHOW);	//��ʾ�ؼ�
	m_ButtonCount+=1;												//���㰴ť����
}

CRect CQQList::GetAddButtonRect()
{
	int count = m_pButton.GetSize();					//��ð�ť����
	int sumheight = 0;
	CRect rect;
	GetClientRect(rect);									//����б�����
	if(count>1)
	{
		CRect rc;
		for(int m=0; m<count-1;m++)
		{
			((CListButton*)m_pButton[m])->GetClientRect(rc);//��ð�ť�ͻ�����
			sumheight += rc.Height();							//��ø߶�
		}
		return CRect(0,sumheight,rect.Width(),sumheight+m_ButtonHeight);	//������ʾ��ť������	
	}
	else
		return CRect(0,0,rect.Width(),m_ButtonHeight);
}

void CQQList::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_ClientList.Create(LVS_ICON,CRect(0,0,0,0),this,101);		//�����б�
	m_ClientList.ShowWindow(SW_SHOW);							//��ʾ�б�
	m_ClientList.SetExtendedStyle(LVS_EX_FLATSB);				//�����б���
	m_ClientList.SetBkColor(RGB(255,255,255));					//�����б�����ɫ
	m_ClientList.SetTextBkColor(RGB(255,255,255));				//�������ֱ�����ɫ
	m_ClientList.SetTextColor(RGB(0,0,255));					//����������ɫ
	m_ClientList.Arrange(LVA_ALIGNLEFT);						//����������ʾλ��
	CListCtrl::PreSubclassWindow();
}

BOOL CQQList::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if((pMsg->hwnd==m_ClientList.m_hWnd)&&(pMsg->message==WM_LBUTTONDBLCLK))
	{
		int index;
		index = m_ClientList.GetSelectionMark();
		if (m_pItemDlbFun != NULL)
			m_pItemDlbFun(&m_ClientList,index);
	}
	return CListCtrl::PreTranslateMessage(pMsg);
}

BOOL CQQList::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	int index =  CommandToIndex(nID);
	if(index != -1)
	{
		OnButtonDown(index,nID);
	}
	m_ClientList.OnCmdMsg(nID,nCode,pExtra,pHandlerInfo);
	return CListCtrl::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CQQList::OnButtonDown(UINT bIndex, UINT nID)
{
	CRect listrect,buttonrect;
	int height = 0;	
	CListButton* temp;
	GetClientRect(listrect);
	if(m_ButtonCount!=1)
	{	
		temp = (CListButton*)m_pButton[bIndex];
		if(temp->m_Toped) //�û��������㰴ť
		{
			for(int i= m_ButtonCount-1; i>bIndex;i--)
			{
				temp = (CListButton*)m_pButton[i];
				temp->GetClientRect(buttonrect);			
				CRect rect(0,listrect.bottom-buttonrect.Height()-height,
					buttonrect.Width(),listrect.bottom-height);				
				height+= buttonrect.Height();
				temp->MoveWindow(rect);
				temp->m_Toped = FALSE;
			}			
		}
		else //���ڵ����ײ㰴ť
		{
			int bottomindex = GetBtmTopIndex();
			for(int i = bottomindex; i <=bIndex;i++)
			{
				int topheight = GetTopButtonHeight();//��ȡ���㰴ť�߶�
				temp          = (CListButton*)m_pButton[i];
				temp->GetClientRect(buttonrect);
				CRect rect(0,topheight,buttonrect.Width(),topheight+buttonrect.Height());
				temp->MoveWindow(rect);
				temp->m_Toped = TRUE;			
			}
		}
		CRect rectclt = GetListClientRect();
		m_ClientList.MoveWindow(rectclt);
		ShowButtonItems(bIndex);
	}
}
//���ݰ�ť���������
UINT CQQList::CommandToIndex(UINT nID)
{
	for(int i = 0;i< m_pButton.GetSize();i++)
	{
		if(((CListButton*)m_pButton[i])->GetDlgCtrlID()==nID)
		{
			return ((CListButton*)m_pButton[i])->m_Index;
		}
	}
	return -1;
}

UINT CQQList::GetTopButtonHeight()
{
	UINT result = 0;
	CListButton* temp;
	CRect rect;
	for(int i = 0; i< m_ButtonCount;i++)
	{
		temp = (CListButton*)m_pButton[i];
		if(temp->m_Toped)
		{
			temp->GetClientRect(rect);
			result += rect.Height();
		}
	}
	return result;
}

UINT CQQList::GetBtmBtnHeight()
{
	UINT result = 0;
	CListButton* temp;
	CRect rect;
	for(int i = 0; i< m_ButtonCount;i++)
	{
		temp = (CListButton*)m_pButton[i];
		if (temp->m_Toped==FALSE)
		{
			temp->GetClientRect(rect);
			result += rect.Height();
		}
	}
	return result;
}

UINT CQQList::GetBtmTopIndex()
{
	CListButton* temp;
	for(int i = 0; i<m_ButtonCount;i++)
	{
		temp = (CListButton*)m_pButton[i];		
		if (temp->m_Toped==FALSE)
			return i;
	}
	return -1;
}

CRect CQQList::GetListClientRect()
{
	int TopHeight = GetTopButtonHeight(); //��ȡ�Ϸ���ť�ĸ߶�
	int BtmHeight = GetBtmBtnHeight();	//��ȡ�·���ť�ĸ߶�
	CRect rect;
	GetClientRect(rect); //��ȡ�б��ܵĿͻ�����
	CRect ClientRect(0,TopHeight,rect.Width(),rect.Height()-BtmHeight);
	return ClientRect;
}

void CQQList::AddButtonItems(UINT nIndex, CString &strItem, int nImageIdex)
{
	CString strIndex;
	strIndex.Format("%d",nImageIdex);
	CListButton* temp;
	temp = (CListButton*)m_pButton[nIndex];
	temp->m_ButtonItems.AddTail(strItem);
	temp->m_ButtonIndex.AddTail(strIndex);
}

void CQQList::ShowButtonItems(UINT nIndex)
{
	CListButton* temp;
	temp = (CListButton*)m_pButton[nIndex];
	m_ClientList.DeleteAllItems();
	CRect showrect = GetListClientRect();
	if(temp->m_ButtonItems.GetCount()>0)
	{
		POSITION pos,index;
		index = temp->m_ButtonIndex.GetHeadPosition();
		pos = temp->m_ButtonItems.GetHeadPosition();
		CString str = temp->m_ButtonItems.GetHead();
		CRect ClientRect;
		ClientRect = GetListClientRect();
		int m = 0,n;
		n = atoi(temp->m_ButtonIndex.GetHead());
		m_LeftMargin = showrect.Width()/2-20;
		m_ClientList.InsertItem(m,str,n);
		m_ClientList.SetItemPosition(m,CPoint(m_LeftMargin,m*(48+5)));
		while (pos != temp->m_ButtonItems.GetTailPosition() 
			&& index != temp->m_ButtonIndex.GetTailPosition())
		{
			n = atoi(temp->m_ButtonIndex.GetNext(index));
			str = temp->m_ButtonItems.GetNext(pos);
			m_ClientList.InsertItem(m,str,n);
			m_ClientList.SetItemPosition(m,CPoint(m_LeftMargin,m*(48+5)));
			m+=1;
		}
		n = atoi(temp->m_ButtonIndex.GetAt(index));
		str = temp->m_ButtonItems.GetAt(pos);
		m_ClientList.InsertItem(m,str,n);
		m_ClientList.SetItemPosition(m,CPoint(m_LeftMargin,m*(48+5)));
	}
}

void CQQList::SetImageLists(CImageList *pImagelist)
{
	if(pImagelist)
		m_ClientList.SetImageList(pImagelist,LVSIL_NORMAL);
}

void CQQList::OnSize(UINT nType, int cx, int cy) 
{
	CListCtrl::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	for (int i = 0; i<m_pButton.GetSize();i++)
	{
		CRect rect;
		((CListButton*)m_pButton[i])->GetClientRect(&rect);
		rect.right = cx;
		if (((CListButton*)m_pButton[i])->m_Toped)
		{
			((CListButton*)m_pButton[i])->MoveWindow(rect.left, rect.top+i*m_ButtonHeight
				, rect.right, m_ButtonHeight);
		}
		else
		{
			((CListButton*)m_pButton[i])->MoveWindow(rect.left, (cy-GetBtmBtnHeight())
				+(i-GetBtmTopIndex())*m_ButtonHeight, rect.right,m_ButtonHeight);
		}
	}
	m_ClientList.MoveWindow(GetListClientRect());
	ShowButtonItems(GetBtmTopIndex()-1);
}

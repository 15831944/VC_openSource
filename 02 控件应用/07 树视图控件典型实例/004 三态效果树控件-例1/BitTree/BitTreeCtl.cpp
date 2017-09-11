// BitTreeCtl.cpp : implementation file
//

#include "stdafx.h"
#include "BitTree.h"
#include "BitTreeCtl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBitTreeCtl

CBitTreeCtl::CBitTreeCtl()
{
	m_Flags = 0;
}

CBitTreeCtl::~CBitTreeCtl()
{

}


BEGIN_MESSAGE_MAP(CBitTreeCtl, CTreeCtrl)
	//{{AFX_MSG_MAP(CBitTreeCtl)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBitTreeCtl message handlers

void CBitTreeCtl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	HTREEITEM hItemInfo =HitTest(point, &m_Flags);
	nFlags = m_Flags;
	//TVHT_ONITEMSTATEICON��ʾ�û��������ͼ���ͼ��״̬
	if ( m_Flags &TVHT_ONITEMSTATEICON )
	{
		//State: 0��״̬ 1û��ѡ�� 2����ѡ�� 3ȫ��ѡ��
		//12��15λ��ʾ��ͼ���ͼ��״̬����
		UINT State = GetItemState( hItemInfo, TVIS_STATEIMAGEMASK ) >> 12;
		State=(State==3)?1:3;
		SetItemState( hItemInfo, INDEXTOSTATEIMAGEMASK(State), TVIS_STATEIMAGEMASK );
	}
	else
		CTreeCtrl::OnLButtonDown(nFlags, point);
}

BOOL CBitTreeCtl::SetItemState(HTREEITEM hItem, UINT State, UINT StateMask, BOOL IsSearch)
{
	BOOL ret=CTreeCtrl::SetItemState( hItem, State, StateMask );

	UINT nState =State >> 12;
	if(nState!=0)
	{
		if(IsSearch) 
			RansackChild(hItem, nState);
		RansackParentAndChild(hItem,nState);
	}
	return ret;
}

//�����ӽڵ�
void CBitTreeCtl::RansackChild(HTREEITEM hItem, UINT State)
{
	HTREEITEM hChildItem,hBrotherItem;
	//�����ӽڵ�
	hChildItem=GetChildItem(hItem);
	if(hChildItem!=NULL)
	{
		//�������ӽڵ��״̬�����븸�ڵ���ͬ
		CTreeCtrl::SetItemState( hChildItem, INDEXTOSTATEIMAGEMASK(State), TVIS_STATEIMAGEMASK );
		//�ٵݹ鴦���ӽڵ���ӽڵ�
		RansackChild(hChildItem, State);
		
		//�����ӽڵ���ֵܽڵ�
		hBrotherItem=GetNextSiblingItem(hChildItem);
		while (hBrotherItem)
		{
			//�����ӽڵ���ֵܽڵ�״̬�뵱ǰ�ڵ��״̬һ��
			int nState = GetItemState( hBrotherItem, TVIS_STATEIMAGEMASK ) >> 12;
			if(nState!=0)
			{
				CTreeCtrl::SetItemState( hBrotherItem, INDEXTOSTATEIMAGEMASK(State), TVIS_STATEIMAGEMASK );
			}
			//�ٵݹ鴦���ֵܽڵ�
			RansackChild(hBrotherItem, State);
			hBrotherItem=GetNextSiblingItem(hBrotherItem);
		}
	}
}

void CBitTreeCtl::RansackParentAndChild(HTREEITEM hItem, UINT State)
{
	HTREEITEM hNextItem,hPrevItem,hParentItem;
	
	//���Ҹ��ڵ㣬û�оͽ���
	hParentItem=GetParentItem(hItem);
	if(hParentItem!=NULL)
	{
		UINT nState1=State;//���ʼֵ����ֹû���ֵܽڵ�ʱ����
		
		//���ҵ�ǰ�ڵ�������ֵܽڵ�,��������ֵܽڵ�״̬����ͬ,
		//���ø��ڵ��״̬

		//���ҵ�ǰ�ڵ�������ֵܽڵ��״̬
		hNextItem=GetNextSiblingItem(hItem);
		while(hNextItem!=NULL)
		{
			nState1 = GetItemState( hNextItem, TVIS_STATEIMAGEMASK ) >> 12;
			if(nState1!=State && nState1!=0) break;
			else hNextItem=GetNextSiblingItem(hNextItem);
		}
		
		if(nState1==State)
		{
			//���ҵ�ǰ�ڵ�������ֵܽڵ��״̬
			hPrevItem=GetPrevSiblingItem(hItem);
			while(hPrevItem!=NULL)
			{
				nState1 = GetItemState( hPrevItem, TVIS_STATEIMAGEMASK ) >> 12;
				if(nState1!=State && nState1!=0) break;
				else hPrevItem=GetPrevSiblingItem
					(hPrevItem);
			}
		}	
		if(nState1==State || nState1==0)
		{
			nState1 = GetItemState( hParentItem, TVIS_STATEIMAGEMASK ) >> 12;
			if(nState1!=0)
			{
				//���״̬һ�£��򸸽ڵ��״̬�뵱ǰ�ڵ��״̬һ��
				CTreeCtrl::SetItemState( hParentItem, INDEXTOSTATEIMAGEMASK(State), TVIS_STATEIMAGEMASK );
			}
			//�ٵݹ鴦���ڵ���ֵܽڵ���丸�ڵ�
			RansackParentAndChild(hParentItem,State);
		}
		else
		{
			//״̬��һ�£���ǰ�ڵ�ĸ��ڵ㡢���ڵ�ĸ��ڵ㡭��״̬��Ϊ����̬
			hParentItem=GetParentItem(hItem);
			while(hParentItem!=NULL)
			{
				nState1 = GetItemState( hParentItem, TVIS_STATEIMAGEMASK ) >> 12;
				if(nState1!=0)
				{
					CTreeCtrl::SetItemState( hParentItem, INDEXTOSTATEIMAGEMASK(2), TVIS_STATEIMAGEMASK );
				}
				hParentItem=GetParentItem(hParentItem);
			}
		}
	}
}

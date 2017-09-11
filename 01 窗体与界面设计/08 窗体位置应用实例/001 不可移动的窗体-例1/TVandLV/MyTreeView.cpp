// MyTreeView.cpp : implementation file
//

#include "stdafx.h"
#include "TVandLV.h"
#include "MyTreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyTreeView

IMPLEMENT_DYNCREATE(CMyTreeView, CTreeView)

CMyTreeView::CMyTreeView()
{
	imlst.Create(16,16,ILC_COLOR32|ILC_MASK,0,0);
}

CMyTreeView::~CMyTreeView()
{
}


BEGIN_MESSAGE_MAP(CMyTreeView, CTreeView)
	//{{AFX_MSG_MAP(CMyTreeView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTreeView drawing

void CMyTreeView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CMyTreeView diagnostics

#ifdef _DEBUG
void CMyTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CMyTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyTreeView message handlers

void CMyTreeView::OnInitialUpdate() 
{
	CTreeView::OnInitialUpdate();
	

	GetTreeCtrl().SetImageList(&imlst,TVSIL_NORMAL);
	GetTreeCtrl().ModifyStyle(0L,TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS);
	for(int i=0;i<11;i++)
	imlst.Add(AfxGetApp()->LoadIcon(IDI_ICON1+i));

	CTreeCtrl *pTreeCtl=&GetTreeCtrl();
	HTREEITEM item;
	pTreeCtl->DeleteAllItems();
	item=pTreeCtl->InsertItem("������Ϣ",0,0,TVI_ROOT);
	pTreeCtl->InsertItem("Ա����Ϣ",1,1,item);
	pTreeCtl->InsertItem("�̶��ʲ�",2,2,item);
	pTreeCtl->InsertItem("��ҵ�ṹ",3,3,item);
	item=pTreeCtl->InsertItem("��ѯ",4,4,TVI_ROOT);
	pTreeCtl->InsertItem("�򵥲�ѯ",5,5,item);
	pTreeCtl->InsertItem("���ϲ�ѯ",6,6,item);
	item=pTreeCtl->InsertItem("��ӡ",7,7,TVI_ROOT);
	pTreeCtl->InsertItem("��ӡ������",8,8,item);
	pTreeCtl->InsertItem("��ӡ����",9,9,item);
	pTreeCtl->InsertItem("��ӡ��ѯ���",10,10,item);
	
}


// MyListView.cpp : implementation file
//

#include "stdafx.h"
#include "TVandLV.h"
#include "MyListView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyListView

IMPLEMENT_DYNCREATE(CMyListView, CListView)

CMyListView::CMyListView()
{

}

CMyListView::~CMyListView()
{
}


BEGIN_MESSAGE_MAP(CMyListView, CListView)
	//{{AFX_MSG_MAP(CMyListView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListView drawing

void CMyListView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CMyListView diagnostics

#ifdef _DEBUG
void CMyListView::AssertValid() const
{
	CListView::AssertValid();
}

void CMyListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG
CString strdata[4][4]={"1","ƽƽ","����","����",
"2","����","ְԱ","����",
"3","��ĳ","����","����",
"4","��ĳ","ְԱ","����"
};
/////////////////////////////////////////////////////////////////////////////
// CMyListView message handlers

void CMyListView::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();

	CListCtrl *pListCtl=&GetListCtrl();
	pListCtl->DeleteAllItems();
	pListCtl->ModifyStyle(0L,LVS_REPORT);
	pListCtl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	pListCtl->InsertColumn(0,"ͼ��",LVCFMT_LEFT,100);
	pListCtl->InsertColumn(1,"Ա����Ϣ",LVCFMT_LEFT,150);
	pListCtl->InsertColumn(2,"��ҵ��Ϣ",LVCFMT_LEFT,150);
	pListCtl->InsertColumn(3,"��˾�ṹ",LVCFMT_LEFT,150);
	for(int p=0;p<4;p++)
	{

		pListCtl->InsertItem(p,"");
		pListCtl->SetItemText(p,0,strdata[p][0]);
		pListCtl->SetItemText(p,1,strdata[p][1]);
		pListCtl->SetItemText(p,2,strdata[p][2]);
		pListCtl->SetItemText(p,3,strdata[p][3]);
	}
}

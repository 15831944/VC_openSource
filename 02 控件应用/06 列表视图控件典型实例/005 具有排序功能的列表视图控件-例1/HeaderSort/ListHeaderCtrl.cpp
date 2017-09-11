// ListHeaderCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "HeaderSort.h"
#include "ListHeaderCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListHeaderCtrl
class CItemData
{
public:
	CItemData()
	{
		m_ColumnTexts = NULL;
		m_dwData = 0;
	}
	LPTSTR* m_ColumnTexts;	//��¼��ǰ���������ı�
	DWORD	m_dwData;		//��ͼ������

private:
	CItemData( const CItemData& );
	//��ֹ����
	CItemData& operator=( const CItemData& );
};

//�ж��ı��Ƿ�Ϊ����
bool IsNumber( LPCTSTR pszText )
{
	for( int i = 0; i < lstrlen( pszText ); i++ )
		if( !_istdigit( pszText[ i ] ) )
			return false;
	return true;
}


int CompareDataAsNumber( LPCTSTR pszParam1, LPCTSTR pszParam2 )
{
	int nNumber1 = atoi( pszParam1 );
	int nNumber2 = atoi( pszParam2 );
	return nNumber1 - nNumber2;
}

CListHeaderCtrl::CListHeaderCtrl()
{
	m_nNumColumns = 0;
	m_nSortColumn = -1;
	m_bAscend = FALSE;
}

CListHeaderCtrl::~CListHeaderCtrl()
{
}


BEGIN_MESSAGE_MAP(CListHeaderCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CListHeaderCtrl)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListHeaderCtrl message handlers

void CListHeaderCtrl::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	ASSERT( GetStyle() & LVS_REPORT );							//�ж��б���ͼ�ķ���Ƿ��Ǳ����ʽ
	CListCtrl::PreSubclassWindow();
	VERIFY( m_ctlHeader.SubclassWindow( GetHeaderCtrl()->GetSafeHwnd() ) );//ʵ�ֱ�ͷ�ؼ������໯
}

void CListHeaderCtrl::Sort(int iColumn, BOOL bAscending)
{
	m_nSortColumn = iColumn;
	m_bAscend = bAscending;
	m_ctlHeader.SetSortColomn(m_nSortColumn, m_bAscend);
	SortItems(SortFunction, (DWORD)this);
}

void CListHeaderCtrl::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	int nColumn = pNMListView->iSubItem;
	Sort(nColumn, nColumn == m_nSortColumn ? !m_bAscend : TRUE);
	*pResult = 0;
}

int CALLBACK CListHeaderCtrl::SortFunction(LPARAM lParam1, LPARAM lParam2, LPARAM lParamData)
{
	CListHeaderCtrl* pListCtrl = (CListHeaderCtrl*)(lParamData);
	CItemData* pParam1 = (CItemData*)(lParam1);						//��ȡ��ͼ�����������
	CItemData* pParam2 = (CItemData*)(lParam2); 
	LPCTSTR pszText1 = pParam1->m_ColumnTexts[pListCtrl->m_nSortColumn];	//��ȡ�����е��ı�
	LPCTSTR pszText2 = pParam2->m_ColumnTexts[pListCtrl->m_nSortColumn];
	if(IsNumber(pszText1))											//����ֵ�Ƚ�
		return pListCtrl->m_bAscend ? CompareDataAsNumber(pszText1, pszText2)
			: CompareDataAsNumber(pszText2, pszText1);
	else														//���ı��Ƚ�
		return pListCtrl->m_bAscend ? lstrcmp(pszText1, pszText2)
			: lstrcmp(pszText2, pszText1);
}

int CListHeaderCtrl::AddItem(LPCTSTR pszText, ... )
{
	int nIndex = InsertItem( GetItemCount(), pszText );				//����У�����������
	LPTSTR* pszColumnTexts = new LPTSTR[ m_nNumColumns ];		//��¼�����ı�
	pszColumnTexts[ 0 ] = new TCHAR[ lstrlen( pszText ) + 1 ];
	lstrcpy( pszColumnTexts[ 0 ], pszText );							//���Ƶ�һ���ı���pszColumnTexts��
 	va_list list;
	va_start( list, pszText );
	//�������ı�
	for( int nColumn = 1; nColumn < m_nNumColumns; nColumn++ )		//�������ı����Ƶ�pszColumnTexts��
	{
		pszText = va_arg( list, LPCTSTR );
		CListCtrl::SetItem( nIndex, nColumn, LVIF_TEXT, pszText, 0, 0, 0, 0 );
		pszColumnTexts[ nColumn ] = new TCHAR[ lstrlen( pszText ) + 1 ];
		lstrcpy( pszColumnTexts[ nColumn ], pszText );
	}
	va_end(list);
	SetItemDataList(nIndex, pszColumnTexts );						//������ͼ������
	return nIndex;
}

BOOL CListHeaderCtrl::SetItemDataList(int iItem, LPTSTR *pchTexts)
{
	if (CListCtrl::GetItemData(iItem) == NULL)
	{
		CItemData* pItemData = new CItemData();					//����һ��CItemData����
		pItemData->m_ColumnTexts = pchTexts;						//�������ı�
		return CListCtrl::SetItemData(iItem, (DWORD)pItemData);		//������Ŀ����

	}
}

void CListHeaderCtrl::SetColumnNum(int num)
{
	m_nNumColumns = num;
}

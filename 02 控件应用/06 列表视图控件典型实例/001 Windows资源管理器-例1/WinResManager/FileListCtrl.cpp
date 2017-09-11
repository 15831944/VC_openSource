// FileListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "WinResManager.h"
#include "FileListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileListCtrl
LPCTSTR g_pszSection = _T("ListCtrls");

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


CFileListCtrl::CFileListCtrl()
{
	m_BaseDir = m_CurDir = "";
	m_nNumColumns = 0;
	m_nSortColumn = -1;
	m_bAscend = FALSE;
}

CFileListCtrl::~CFileListCtrl()
{

}


BEGIN_MESSAGE_MAP(CFileListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CFileListCtrl)
	ON_WM_DESTROY()
	ON_NOTIFY_REFLECT(LVN_KEYDOWN, OnKeydown)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileListCtrl message handlers

BOOL CFileListCtrl::SetColumns(const CString &strHeadings)
{
	int nStart = 0;
	for( ;; )
	{
		int nComma = strHeadings.Find( _T(','), nStart );	
		if( nComma == -1 )
			break;
		//��ȡ�ı�
		CString strHeading = strHeadings.Mid( nStart, nComma - nStart );
		nStart = nComma + 1;	//�ӹ�","
		int nSemiColon = strHeadings.Find( _T(';'), nStart );
		if( nSemiColon == -1 )
			nSemiColon = strHeadings.GetLength();
		int nWidth = atoi( strHeadings.Mid( nStart, nSemiColon - nStart ) );	//��ȡ���
		nStart = nSemiColon + 1;			//ָ����һ����Ϣ
		if( InsertColumn( m_nNumColumns++, strHeading, LVCFMT_LEFT, nWidth ) == -1 )
			return FALSE;					//������
	}
	return TRUE;
}

int CFileListCtrl::AddItem(LPCTSTR pszText, ... )
{
	//����У�����������
	int nIndex = InsertItem( GetItemCount(), pszText );
	//��¼�����ı�
	LPTSTR* pszColumnTexts = new LPTSTR[ m_nNumColumns ];
	pszColumnTexts[ 0 ] = new TCHAR[ lstrlen( pszText ) + 1 ];
	lstrcpy( pszColumnTexts[ 0 ], pszText );
 	va_list list;
	va_start( list, pszText );
	//�������ı�
	for( int nColumn = 1; nColumn < m_nNumColumns; nColumn++ )
	{
		pszText = va_arg( list, LPCTSTR );
		CListCtrl::SetItem( nIndex, nColumn, LVIF_TEXT, pszText, 0, 0, 0, 0 );

		pszColumnTexts[ nColumn ] = new TCHAR[ lstrlen( pszText ) + 1 ];
		lstrcpy( pszColumnTexts[ nColumn ], pszText );
	}
	va_end(list);
	SetItemDataList(nIndex, pszColumnTexts );
	return nIndex;
}

BOOL CFileListCtrl::DeleteItem(int iItem)
{
	FreeData(iItem);
	return CListCtrl::DeleteItem(iItem);
}

BOOL CFileListCtrl::DeleteAllItems()
{
	for(int iItem = 0; iItem < GetItemCount(); iItem ++ )
		FreeData(iItem);
	return CListCtrl::DeleteAllItems();
}

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

//�ж��Ƿ�Ϊ����
bool IsDate( LPCTSTR pszText )
{
	//��ʽΪ0000-00-00
	if( lstrlen( pszText ) < 10 )
		return false;
	return _istdigit( pszText[ 0 ] )
		&& _istdigit( pszText[ 1 ] )
		&& _istdigit( pszText[ 2 ] )
		&& _istdigit( pszText[ 3 ] )
		&& pszText[ 4 ] == _T('-')
		&& _istdigit( pszText[ 5 ] )
		&& _istdigit( pszText[ 6 ] )
		&& pszText[ 7 ] == _T('-')
		&& _istdigit( pszText[ 8 ] )
		&& _istdigit( pszText[ 9 ] );
}

//�����ڱȽ�����
int CompareDataAsDate( const CString& strDate1, const CString& strDate2 )
{
	//�ȱȽ���
	int nYear1 = atoi( strDate1.Mid(0, 4 ) );
	int nYear2 = atoi( strDate2.Mid(0, 4 ) );
	if (nYear1 != nYear2)
	{
		return nYear1 - nYear2;
	}
	//�Ƚ���
	int nMonth1 = atoi( strDate1.Mid( 5, 2 ) );
	int nMonth2 = atoi( strDate2.Mid( 5, 2 ) );
	if( nMonth1 != nMonth2 )
	{
		return nMonth1 = nMonth2;	
	}
	//�Ƚ���
	int nDay1 = atoi( strDate1.Mid( 8, 2 ) );
	int nDay2 = atoi( strDate2.Mid( 8, 2 ) );
	
	if( nDay1 !=  nDay2 )
	{
		return nDay1 - nDay2;
	}
	return 0;		//������ȣ�����0
}

BOOL CFileListCtrl::SetItemText(int nItem, int nSubItem, LPCTSTR lpszText)
{
	if( !CListCtrl::SetItemText(nItem, nSubItem, lpszText))
		return FALSE;
	//��ȡ�и����ı�
	LPTSTR *pszTexts = GetItemDataList(nItem);
	LPTSTR pszText = pszTexts[nSubItem];
	delete[] pszText;
	pszText = new TCHAR[lstrlen(lpszText) + 1];
	lstrcpy(pszText, lpszText);
	pszTexts[nSubItem] = pszText;
	return TRUE;
}

void CFileListCtrl::Sort(int iColumn, BOOL bAscending)
{
	m_nSortColumn = iColumn;
	m_bAscend = bAscending;
	m_ctlHeader.SetSortColomn(m_nSortColumn, m_bAscend);
	SortItems(SortFunction, (DWORD)this);
}

BOOL CFileListCtrl::SetItemData(int nItem, DWORD dwData)
{
	if(nItem >= GetItemCount())
		return FALSE;
	CItemData* pItem = (CItemData*)CListCtrl::GetItemData(nItem) ;
	pItem->m_dwData = dwData;
	return TRUE;
}

DWORD CFileListCtrl::GetItemData(int nItem) const
{
	ASSERT(nItem < GetItemCount());
	CItemData* pItem = (CItemData*)(CListCtrl::GetItemData(nItem));
	return pItem->m_dwData;
}

void CFileListCtrl::FreeData(const int nItem)
{
	CItemData* pItemData = ( CItemData* )CListCtrl::GetItemData( nItem  );
	LPTSTR* pcsTexts = pItemData->m_ColumnTexts;

	for( int i = 0; i < m_nNumColumns; i++ )
		delete[] pcsTexts[ i ];

	delete[] pcsTexts;
	delete pItemData;

	VERIFY( CListCtrl::SetItemData( nItem , NULL ) );
}

BOOL CFileListCtrl::SetItemDataList(int iItem, LPTSTR *pchTexts)
{
	if (CListCtrl::GetItemData(iItem) == NULL)
	{
		CItemData* pItemData = new CItemData();
		pItemData->m_ColumnTexts = pchTexts;
		//������Ŀ����
		return CListCtrl::SetItemData(iItem, (DWORD)pItemData);
	}
}

LPTSTR *CFileListCtrl::GetItemDataList(int iItem) const
{
	ASSERT(iItem < GetItemCount());
	CItemData* pItemData = (CItemData*)CListCtrl::GetItemData(iItem) ;
	return pItemData->m_ColumnTexts;
}

void CFileListCtrl::PreSubclassWindow() 
{
	ASSERT( GetStyle() & LVS_REPORT );
	CListCtrl::PreSubclassWindow();
	VERIFY( m_ctlHeader.SubclassWindow( GetHeaderCtrl()->GetSafeHwnd() ) );	
	LoadSysFileIcon();
}

int CALLBACK CFileListCtrl::SortFunction( LPARAM lParam1, LPARAM lParam2, LPARAM lParamData )
{
	CFileListCtrl* pListCtrl = (CFileListCtrl*)(lParamData);
	CItemData* pParam1 = (CItemData*)(lParam1);
	CItemData* pParam2 = (CItemData*)(lParam2); 
	//��ȡ�����е��ı�
	LPCTSTR pszText1 = pParam1->m_ColumnTexts[pListCtrl->m_nSortColumn];
	LPCTSTR pszText2 = pParam2->m_ColumnTexts[pListCtrl->m_nSortColumn];

	if(IsNumber(pszText1))	//����ֵ�Ƚ�
		return pListCtrl->m_bAscend ? CompareDataAsNumber(pszText1, pszText2)
			: CompareDataAsNumber(pszText2, pszText1);
	else if(IsDate(pszText1))	//�����ڱȽ�
		return pListCtrl->m_bAscend ? CompareDataAsDate(pszText1, pszText2)
			: CompareDataAsDate(pszText2, pszText1);
	else						//���ı��Ƚ�
		return pListCtrl->m_bAscend ? lstrcmp(pszText1, pszText2)
			: lstrcmp(pszText2, pszText1);
}

void CFileListCtrl::DisplayPath(LPCTSTR lpPath)
{
	DeleteAllItems();
	BOOL bFind;
	CFileFind flFind;
	CString csPath = lpPath;
	m_CurDir = lpPath;
	if ( csPath.Right(1) != "\\" )
	{  
		csPath += "\\";
		m_CurDir +="\\";
	}
	csPath += "*.*";
	bFind = flFind.FindFile(csPath);
	CString csText,csFileSize,csDataTime;
	//�����б�ǰ��ʾ��Ŀ¼
	while ( bFind )
	{
		bFind = flFind.FindNextFile();
		if ( !flFind.IsDots() && !flFind.IsHidden())
		{		
			__int64 lFileLen = flFind.GetLength64();
			
			if (flFind.IsDirectory())
			{
				csFileSize = "�ļ���";
			}
			else
			{
				double fGB = lFileLen /(double)(1024*1024*1024);
				if (fGB < 1)
				{
					double fMB = lFileLen / (double)(1024*1024);
					if (fMB < 1)
					{
						double fBK = lFileLen / (double)(1024);
						if (fBK >1)
						{
							csFileSize.Format("%2.2f KB",fBK);
						}
						else
						{
							csFileSize.Format("%i B",lFileLen);
						}
					}
					else
					{
						csFileSize.Format("%2.2f MB",fMB);
					}
				}
				else
				{
					csFileSize.Format("%2.2f GB",fGB);
				}
			}
			
			csText = flFind.GetFileName();
			CTime time;
			flFind.GetCreationTime(time);
			csDataTime = time.Format("%Y-%m-%d %H:%M");
			int nItem = AddItem(csText,csFileSize,csDataTime);
			//�����ļ���ʾ��ͼ��
			SHFILEINFO shInfo;
			int nIcon = 0;
			SHGetFileInfo(flFind.GetFilePath(),0,&shInfo,sizeof(shInfo),SHGFI_ICON | SHGFI_SMALLICON );
			DestroyIcon(shInfo.hIcon);
			nIcon = shInfo.iIcon;
			SetItem(nItem,0,LVIF_IMAGE,"",nIcon,0,0,0);
			 //������Ŀ���,0��ʾ�ļ���1��ʾĿ¼
			if (flFind.IsDirectory())
			{
				SetItemData(nItem, 1);
			}
			else
			{
				SetItemData(nItem, 0);
			}
			nItem++;
		}
	}
}

void CFileListCtrl::OnDestroy() 
{	
	for(int nItem=0; nItem<GetItemCount(); nItem++)
	{
		FreeData(nItem);
	}
	CListCtrl::OnDestroy();
}


void CFileListCtrl::OnKeydown(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	if (pLVKeyDow->wVKey==VK_BACK)	//������һ��Ŀ¼
	{
		if (m_BaseDir != m_CurDir && m_BaseDir != "")
		{
			if ( m_CurDir.Right(1) == "\\" )
			{
				//ȥ��"\\"
				m_CurDir = m_CurDir.Left(m_CurDir.GetLength()-1);
			}
			int nPos = m_CurDir.ReverseFind('\\');
			m_CurDir = m_CurDir.Left(nPos);
		}
		DisplayPath(m_CurDir);
	}
	*pResult = 0;
}

void CFileListCtrl::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nColumn = pNMListView->iSubItem;
	Sort(nColumn, nColumn == m_nSortColumn ? !m_bAscend : TRUE);
	*pResult = 0;
}

void CFileListCtrl::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int nItem = GetSelectionMark();
	if (nItem != -1)
	{
		
		int nFlag = GetItemData(nItem);
		if (nFlag==1)	//�ж��Ƿ�ΪĿ¼	
		{
			//��ȡ������Ŀ¼��Ϣ
			CString csFoder = GetItemText(nItem,0);
			csFoder += "\\";
			//��ȡĿ¼
			m_CurDir += csFoder;
			DisplayPath(m_CurDir);
		}
		else			//������ļ�������ļ�
		{
			CString csFileName = m_CurDir + GetItemText(nItem, 0);
			ShellExecute(NULL, "open", csFileName, 0, 0, SW_SHOWNORMAL);
		}
	}
	*pResult = 0;
}

void CFileListCtrl::LoadSysFileIcon()
{
	SHFILEINFO shInfo;
	memset(&shInfo,0,sizeof(SHFILEINFO));
	HIMAGELIST hImage = (HIMAGELIST)SHGetFileInfo("C:\\",0,&shInfo, sizeof( SHFILEINFO ),
		SHGFI_SYSICONINDEX | SHGFI_SMALLICON );
	m_ImageList.Attach(hImage); 
	SetImageList(&m_ImageList, LVSIL_SMALL);
}



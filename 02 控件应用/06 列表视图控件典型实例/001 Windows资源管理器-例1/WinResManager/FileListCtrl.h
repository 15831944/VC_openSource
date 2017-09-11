#if !defined(AFX_FILELISTCTRL_H__4F8A4E4C_7D7A_47F2_8215_7125EAE2C1CF__INCLUDED_)
#define AFX_FILELISTCTRL_H__4F8A4E4C_7D7A_47F2_8215_7125EAE2C1CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileListCtrl window
#include "FileHeaderCtrl.h"

#ifdef _DEBUG
	#define ASSERT_VALID_STRING( str ) ASSERT( !IsBadStringPtr( str, 0xfffff ) )
#else	//	_DEBUG
	#define ASSERT_VALID_STRING( str ) ( (void)0 )
#endif	//	_DEBUG

#include <afxinet.h>

class CFileListCtrl : public CListCtrl
{
// Construction
public:
	CFileListCtrl();
	CString			m_BaseDir;					//��Ŀ¼
	CString			m_CurDir;					//��¼��ǰ�б����ļ���Ŀ¼
	CFileHeaderCtrl m_ctlHeader;				//��ͷ
	int				m_nNumColumns;				//����
	int				m_nSortColumn;				//������
	BOOL			m_bAscend;					//�Ƿ���������
	CImageList		m_ImageList;				//����ͼ���б�

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileListCtrl)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void LoadSysFileIcon();
	void DisplayPath(LPCTSTR lpPath);
	static int CALLBACK SortFunction( LPARAM lParam1, LPARAM lParam2, LPARAM lParamData );
	LPTSTR *GetItemDataList( int iItem ) const;
	BOOL SetItemDataList( int iItem, LPTSTR* pchTexts );
	void FreeData( const int nItem );
	DWORD GetItemData(int nItem) const;
	BOOL SetItemData(int nItem, DWORD dwData);
	void Sort( int iColumn, BOOL bAscending );
	BOOL SetItemText( int nItem, int nSubItem, LPCTSTR lpszText );
	BOOL DeleteAllItems();
	BOOL DeleteItem( int iItem );
	int AddItem( LPCTSTR pszText, ... );
	BOOL SetColumns( const CString& strHeadings );
	virtual ~CFileListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFileListCtrl)
	afx_msg void OnDestroy();
	afx_msg void OnKeydown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILELISTCTRL_H__4F8A4E4C_7D7A_47F2_8215_7125EAE2C1CF__INCLUDED_)

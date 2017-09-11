// ListHeader.cpp : implementation file
//

#include "stdafx.h"
#include "HeaderSort.h"
#include "ListHeader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListHeader

CListHeader::CListHeader()
{
	m_nSortColumn = -1;
	m_bAscend = TRUE;
}

CListHeader::~CListHeader()
{
}


BEGIN_MESSAGE_MAP(CListHeader, CHeaderCtrl)
	//{{AFX_MSG_MAP(CListHeader)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListHeader message handlers

void CListHeader::SetSortColomn(int nColumn, BOOL bAscend)
{
	m_nSortColumn = nColumn;							//��¼������
	m_bAscend = bAscend;							//��¼����ʽ������(TRUE)���ǽ���(FALSE)
	HD_ITEM hItem;
	hItem.mask = HDI_FORMAT;
	GetItem( nColumn, &hItem ) ;						//��ȡ����Ϣ
	hItem.fmt |= HDF_OWNERDRAW;					//�����Ի���
	SetItem( nColumn, &hItem );							//��������Ϣ
	Invalidate();									//���±�ͷ
}

void CListHeader::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC dc;			//�����豸������
	dc.Attach( lpDrawItemStruct->hDC );		//�����豸�����ľ��
	const int nSavedIndex = dc.SaveDC();	//�����豸������
	CRect rc( lpDrawItemStruct->rcItem );	//��ȡ��ǰ������
	CBrush brush( GetSysColor( COLOR_3DFACE ) );	//���屳����ˢ
	dc.FillRect( rc, &brush );				//��仭ˢ
	TCHAR szText[ 256 ];					
	HD_ITEM hditem;
	hditem.mask = HDI_TEXT | HDI_FORMAT;
	hditem.pszText = szText;
	hditem.cchTextMax = 255;
	GetItem( lpDrawItemStruct->itemID, &hditem );	//��ȡ��ǰ����Ŀ��Ϣ
	//���û��Ƶ��ı���ʽ
	UINT uFormat = DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER | DT_END_ELLIPSIS ;
	if( hditem.fmt & HDF_CENTER)
		uFormat |= DT_CENTER;
	else if( hditem.fmt & HDF_RIGHT)
		uFormat |= DT_RIGHT;
	else
		uFormat |= DT_LEFT;
	if( lpDrawItemStruct->itemState == ODS_SELECTED )
	{
		rc.left++;
		rc.top += 2;
		rc.right++;
	}
	CRect rcIcon( lpDrawItemStruct->rcItem );
	const int iOffset = ( rcIcon.bottom - rcIcon.top ) / 4;
	if( lpDrawItemStruct->itemID == (UINT) m_nSortColumn )
		rc.right -= 3 * iOffset;
	rc.left += iOffset;
	rc.right -= iOffset;
	//�������ı�
	if( rc.left < rc.right )
		dc.DrawText( szText, -1, rc, uFormat );
	//���Ƽ�ͷ
	if( lpDrawItemStruct->itemID == (UINT) m_nSortColumn )
	{
		//���廭��
		CPen penLight( PS_SOLID, 1, GetSysColor( COLOR_3DHILIGHT ) );
		CPen penShadow( PS_SOLID, 1, GetSysColor( COLOR_3DSHADOW ) );
		CPen* pOldPen = dc.SelectObject( &penLight );	//ѡ�л���
		if( m_bAscend )
		{
			//�������ϵļ�ͷ
			dc.MoveTo( rcIcon.right - 2 * iOffset, iOffset);
			dc.LineTo( rcIcon.right - iOffset, rcIcon.bottom - iOffset - 1 );
			dc.LineTo( rcIcon.right - 3 * iOffset - 2, rcIcon.bottom - iOffset - 1 );
			dc.SelectObject( &penShadow );
			dc.MoveTo( rcIcon.right - 3 * iOffset - 1, rcIcon.bottom - iOffset - 1 );
			dc.LineTo( rcIcon.right - 2 * iOffset, iOffset - 1);		
		}
		else
		{
			//�������µļ�ͷ
			dc.MoveTo( rcIcon.right - iOffset - 1, iOffset );
			dc.LineTo( rcIcon.right - 2 * iOffset - 1, rcIcon.bottom - iOffset );
			dc.SelectObject( &penShadow );
			dc.MoveTo( rcIcon.right - 2 * iOffset - 2, rcIcon.bottom - iOffset );
			dc.LineTo( rcIcon.right - 3 * iOffset - 1, iOffset );
			dc.LineTo( rcIcon.right - iOffset - 1, iOffset );		
		}
		dc.SelectObject( pOldPen );		//�ָ�ԭ��ѡ��Ļ���
	}
	dc.RestoreDC( nSavedIndex );		//�ָ�֮ǰ���豸������
	dc.Detach();//���豸�������з����豸�����ľ��
}

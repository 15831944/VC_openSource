// ImagePanel.cpp : implementation file
//

#include "stdafx.h"
#include "RotateImg.h"
#include "ImagePanel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImagePanel dialog


CImagePanel::CImagePanel(CWnd* pParent /*=NULL*/)
	: CDialog(CImagePanel::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImagePanel)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CImagePanel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImagePanel)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImagePanel, CDialog)
	//{{AFX_MSG_MAP(CImagePanel)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImagePanel message handlers

void CImagePanel::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int nCurpos,nMin,nMax,nThumbWidth;
	//���������Ϣ
	SCROLLINFO siInfo;
	//��ȡˮƽ�������Ĺ�����Ϣ
	GetScrollInfo(SB_HORZ,&siInfo);
	//��ȡ��ǰ�Ĺ���λ��
	nCurpos = siInfo.nPos;
	//��ȡ������Χ
	nMin = siInfo.nMin;
	nMax = siInfo.nMax;
	//��ȡ�������С
	nThumbWidth = siInfo.nPage;
	switch (nSBCode)
	{
	break;
	case SB_THUMBTRACK:		//�϶�������
		//�������ڵ�ָ����λ��
		ScrollWindow(-(nPos-nCurpos),0);
		//���ù������µ�λ��
		SetScrollPos(SB_HORZ,nPos);	
	break;
	case SB_LINELEFT : //�������ͷ
		SetScrollPos(SB_HORZ,nCurpos-1);
		if (nCurpos != 0)
			ScrollWindow(1,0);
	break;
	case SB_LINERIGHT: //�����Ҽ�ͷ
		SetScrollPos(SB_HORZ,nCurpos+1);
		if (nCurpos+nThumbWidth < nMax)
			ScrollWindow(-1,0);	
	break;
	case SB_PAGELEFT: //�ڹ�������󷽿հ׹������򵥻�,����Ϊ6
		SetScrollPos(SB_HORZ,nCurpos-6);
		if (nCurpos+nThumbWidth >0)
			ScrollWindow(6,0);
	break;
	case SB_PAGERIGHT: //�ڹ�������ҷ��հ׹������򵥻�,����Ϊ6
		SetScrollPos(SB_HORZ,nCurpos+6);
		if (nCurpos+nThumbWidth <nMax)
			ScrollWindow(-6,0);
	break;
	case SB_LEFT:	
		SetScrollPos(SB_HORZ,0);
		ScrollWindow(nCurpos,0);
	break;
	}	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);	

}

void CImagePanel::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int nCurpos,nMin,nMax,nThumbWidth;
	SCROLLINFO siInfo;
	GetScrollInfo(SB_VERT,&siInfo);
	nCurpos = siInfo.nPos;
	nMin = siInfo.nMin;
	nMax = siInfo.nMax;
	nThumbWidth = siInfo.nPage;
	switch (nSBCode)
	{
	case SB_THUMBTRACK:
		nCurpos = GetScrollPos(SB_VERT);
		ScrollWindow(0,-(nPos-nCurpos));
		SetScrollPos(SB_VERT,nPos);	
	break;

	case SB_LINELEFT:
		nCurpos = GetScrollPos(SB_VERT);
		SetScrollPos(SB_VERT,nCurpos-1);
		if (nCurpos !=0)
			ScrollWindow(0,1);
	break;
	case SB_LINERIGHT:
		nCurpos = GetScrollPos(SB_VERT);
		SetScrollPos(SB_VERT,nCurpos+1);
		if (nCurpos+nThumbWidth < nMax)
			ScrollWindow(0,-1);	
	break;
	case SB_PAGELEFT: //�ڹ�������Ϸ��հ׹������򵥻�,����Ϊ6
		SetScrollPos(SB_VERT,nCurpos-6);
		if (nCurpos+nThumbWidth >0)
			ScrollWindow(0,6);
	break;
	case SB_PAGERIGHT: //�ڹ�������·��հ׹������򵥻�,����Ϊ6
		SetScrollPos(SB_VERT,nCurpos+6);
		if (nCurpos+nThumbWidth < nMax)
			ScrollWindow(0,-6);
	break;
	case SB_LEFT:	
		SetScrollPos(SB_VERT,0);
		ScrollWindow(0,nCurpos);
	break;
	}	
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

//�������ֶ�����Ϣ
BOOL CImagePanel::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	SCROLLINFO siInfo;
	//��ȡ��ֱ�������Ĺ�����Ϣ
	GetScrollInfo(SB_VERT,&siInfo);
	int nMin,nMax,nThumbWidth;
	//��ȡ��ֱ�������Ĺ�����Χ
	nMin = siInfo.nMin;
	nMax = siInfo.nMax;
	//��ȡ�������С
	nThumbWidth = siInfo.nPage;
	//��ȡ��ֱ��������ǰ����λ��
	int nPos = GetScrollPos(SB_VERT);
	if (zDelta > 0)	//�ж������ֵĹ������룬�������ʾ��ǰ������С�����ʾ������
	{
		if (nPos == 0)
			return TRUE;
		//���ô�ֱ�������Ĺ���λ��
		SetScrollPos(SB_VERT,nPos-6);
		//��������
		ScrollWindow(0,6);
	}
	else		//������
	{
		if ((nPos+nThumbWidth >= nMax))
			return TRUE;
		//���ô�ֱ�������Ĺ���λ��
		SetScrollPos(SB_VERT,nPos+6);
		//��������
		ScrollWindow(0,-6);
	}
	return TRUE;//CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

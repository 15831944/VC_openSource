// DockBarCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "�����ںϼ���.h"
#include "DockBarCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDockBarCtrl

CDockBarCtrl::CDockBarCtrl()
{
	m_bkBrush.CreateSolidBrush(::GetSysColor(COLOR_BTNFACE));
	m_Caption = "�����ںϼ���";

	m_ncTBandHeight = 20;
	m_ncLBandWidth = 3;
	m_ncRBandWidth = 6;
	m_ncBBandHeight = 3;
	m_TopBandColor = GetSysColor(COLOR_BTNHILIGHT);
	m_BottomBandColor = GetSysColor(COLOR_BTNSHADOW);
	m_IsTraking = FALSE;
	m_IsInRect = FALSE;
	m_Min = CSize(32,32);
}

CDockBarCtrl::~CDockBarCtrl()
{

}

BEGIN_MESSAGE_MAP(CDockBarCtrl,  CControlBar)
	//{{AFX_MSG_MAP(CDockBarCtrl)
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_NCCALCSIZE()
	ON_WM_NCPAINT()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCHITTEST()
	ON_WM_NCLBUTTONDBLCLK()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_NCLBUTTONUP()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CDockBarCtrl message handlers
void CDockBarCtrl::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{	
	CWnd::UpdateDialogControls(pTarget, bDisableIfNoHndler);
}

BOOL CDockBarCtrl::Create(CWnd* pParentWnd, CDialog* pDialog, UINT nID, DWORD dwStyle,  CCreateContext* pContext) 
{
	ASSERT_VALID(pParentWnd);

	ASSERT(!((dwStyle& CBRS_SIZE_DYNAMIC)&&(dwStyle&CBRS_SIZE_FIXED )));

	m_dwStyle = dwStyle & CBRS_ALL;
	//ע�ᴰ����
	CString classname;
	classname = AfxRegisterWndClass(CS_DBLCLKS,LoadCursor(NULL,IDC_ARROW),m_bkBrush,0);

	//����������
	CWnd::Create(classname,m_Caption,dwStyle,CRect(0,0,0,0),pParentWnd,0);
	
	m_pDlg = pDialog;
	m_pDlg->Create(nID,this);
	
	m_pDlg->GetWindowRect(m_FloatRect);

	m_HorRect.CopyRect(m_FloatRect);
	m_VerRect.CopyRect(m_FloatRect);

	return true;
}


CSize CDockBarCtrl::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	int dockwidth,dockheight;
	CRect rc,clientrc;
	m_pDockSite->GetClientRect(clientrc);

	//�����ǰ���ڸ���״̬	
	if (IsFloating())
		return CSize(m_FloatRect.Width(),m_FloatRect.Height());
	else  //���ڹ̶�״̬
	{
		if (bHorz) //ˮƽ������ʾ
		{
			m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_TOP)->GetWindowRect(rc);
			dockwidth = bStretch? 1200:rc.Width()+4;
			return CSize(dockwidth,m_HorRect.Height());
		}
		else  //��ֱ������ʾ
		{		
			m_pDockSite->GetControlBar(AFX_IDW_DOCKBAR_LEFT)->GetWindowRect(rc);
			dockheight= bStretch?1200:rc.Height()+4;
			return CSize(m_VerRect.Width(),dockheight);
		}		
	}
}

CSize CDockBarCtrl::CalcDynamicLayout(int nLength, DWORD nMode)
{

	if (IsFloating())
	{
		//�޸�CMiniDockFrameWnd�ķ��
		//����ͬʱ�������ڵĿ�Ⱥ͸߶�
		CFrameWnd* pDockFrame =  GetDockingFrame();
		pDockFrame->ModifyStyle(MFS_4THICKFRAME,0);
	}

	if (nMode&(LM_HORZDOCK|LM_VERTDOCK))
		return CControlBar::CalcDynamicLayout(nLength,nMode);

	if (nMode&LM_COMMIT)
		return CSize(nLength,m_FloatRect.Height());

	if (nMode & LM_MRUWIDTH)
		return CSize(m_FloatRect.Width(),m_FloatRect.Height());

	//��ȡCMiniDockFrameWnd�Ĵ�������
	CRect rect;
	GetParent()->GetParent()->GetWindowRect(rect);

	//��ȡCMiniDockFrameWnd�ı������߶�
	int CaptionHeight = GetSystemMetrics(SM_CYCAPTION);

	if (IsFloating())
	{
		CPoint pt;
		//��ȡ��굱ǰλ��
		GetCursorPos(&pt);
		
		m_FloatRect.left = 0;
		m_FloatRect.top = 0;

		//�ж��û��ڴ�����ĸ��Ƕ���ʼ������С,ʵ����m_pDockContext->m_nHitTest��ֵ
		//����CMiniDockFrameWnd��OnNcLButtonDown�����е���m_pDockContext��StartResize�������õ�
		
		switch (m_pDockContext->m_nHitTest)
		{
		case HTTOPLEFT: //��������Ͻ�
			{
				m_FloatRect.left = 0;
				m_FloatRect.top = 0;
				m_FloatRect.right =  (m_Min.cx > rect.right - pt.x)?m_Min.cx: (rect.right - pt.x);//�������

				int temp = rect.bottom - CaptionHeight - pt.y - 1;
				m_FloatRect.bottom =  (m_Min.cy>temp)? m_Min.cy : temp;

				//����CMiniDockFrameWnd�����Ͻ�����Ϊ��ǰ�ƶ����������
				m_pDockContext->m_rectFrameDragHorz.top = pt.y;	
				m_pDockContext->m_rectFrameDragHorz.left =pt.x;
				return CSize(m_FloatRect.Width(),m_FloatRect.Height());
			}
			
		case HTTOPRIGHT: //��������Ͻ�
			{
				m_FloatRect.left = 0;
				m_FloatRect.top = 0;

				m_FloatRect.right= (m_Min.cx >pt.x-rect.left)?m_Min.cx: pt.x-rect.left;

				int temp = rect.bottom - CaptionHeight - pt.y - 1;
				m_FloatRect.bottom =  (m_Min.cy>temp)? m_Min.cy : temp;
				
				m_pDockContext->m_rectFrameDragHorz.top = pt.y;

				return CSize(m_FloatRect.Width(),m_FloatRect.Height());
			}
			
		case HTBOTTOMLEFT://��������½�
			{
				
				m_FloatRect.right = max(m_Min.cx, rect.right-pt.x);
				m_FloatRect.bottom = max(m_Min.cy,pt.y-rect.top-CaptionHeight);

				m_pDockContext->m_rectFrameDragHorz.left =max(m_Min.cx,pt.x);
					
				return CSize(m_FloatRect.Width(),m_FloatRect.Height());
			}
			
		case HTBOTTOMRIGHT: //��������½�
			{
				m_FloatRect.right = max(m_Min.cx, pt.x-rect.left);
				m_FloatRect.bottom = max(m_Min.cy,pt.y-rect.top-CaptionHeight);

				m_pDockContext->m_rectFrameDragHorz.right =pt.x;
					
				return CSize(m_FloatRect.Width(),m_FloatRect.Height());
			}
		}
	
	}  
	if (nMode&LM_LENGTHY)//�����������ĸ߶�
	{
		m_FloatRect.top=0;
		m_FloatRect.bottom= max(m_Min.cy, nLength);
		return CSize(m_FloatRect.Width(),max(m_Min.cy, nLength));
	}
	else if (nMode&LM_HORZ)//�����������Ŀ��
	{		
		//m_FloatRect.OffsetRect(-m_FloatRect.Width(),-m_FloatRect.Height());
		m_FloatRect.top = 0;
		m_FloatRect.left = 0;
		m_FloatRect.right = max(m_Min.cx,nLength);
		m_FloatRect.bottom = max(m_Min.cy,rect.Height()-CaptionHeight);
		return CSize(max(nLength,m_Min.cx),m_FloatRect.Height());
	}
}

void CDockBarCtrl::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
	CControlBar::OnWindowPosChanged(lpwndpos);

	//��ȡCDockBar��ID
	m_DockBarID =  GetParent()->GetDlgCtrlID();
	if (m_IsInRect)
	{
		CRect rc;
		GetClientRect(rc);
		m_pDlg->MoveWindow(rc);
		return;
	}
	m_pDockSite->RecalcLayout();
	m_IsInRect = TRUE;
	SetWindowPos(NULL, 0,0,0,0,
        SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
	m_IsInRect = FALSE;
//	m_temprc = m_Bandrc;
}
//�ǿͻ�����ļ���
void CDockBarCtrl::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{	
	//����ÿһ�����з�ʽ������ǿͻ�����
	switch (m_DockBarID)
	{
	case AFX_IDW_DOCKBAR_TOP://������ͣ�����Ϸ�
		lpncsp->rgrc[0].left += m_ncTBandHeight;
		lpncsp->rgrc[0].bottom-=m_ncRBandWidth; 
		lpncsp->rgrc[0].top += m_ncLBandWidth;
		lpncsp->rgrc[0].right-= m_ncBBandHeight;
		m_ncTopHeight = m_ncRBandWidth;
		break;
	case AFX_IDW_DOCKBAR_LEFT: //������ͣ������
		lpncsp->rgrc[0].left +=m_ncLBandWidth;
		lpncsp->rgrc[0].bottom -=m_ncBBandHeight;
		lpncsp->rgrc[0].top +=m_ncTBandHeight;
		lpncsp->rgrc[0].right-=m_ncRBandWidth;
		m_ncLeftWidth = m_ncLBandWidth;
		break;
	case AFX_IDW_DOCKBAR_RIGHT: ////������ͣ�����ҷ�
		lpncsp->rgrc[0].left +=m_ncRBandWidth;
		lpncsp->rgrc[0].bottom -=m_ncBBandHeight;
		lpncsp->rgrc[0].top +=m_ncTBandHeight;
		lpncsp->rgrc[0].right-=m_ncLBandWidth;
		m_ncLeftWidth = m_ncLBandWidth;

		break;
	case AFX_IDW_DOCKBAR_BOTTOM: ////������ͣ�����·�
		lpncsp->rgrc[0].left +=m_ncTBandHeight;
		lpncsp->rgrc[0].bottom -= m_ncLBandWidth;
		lpncsp->rgrc[0].top += m_ncRBandWidth;
		lpncsp->rgrc[0].right-=m_ncBBandHeight;
		m_ncTopHeight = m_ncRBandWidth;
		break;	
	}
}

//���Ʊ�������˫��
void CDockBarCtrl::DrowTitleLine(CDC *pDC)
{
	if (IsFloating()) //������ڸ���״̬�˳�
		return;

	m_pDockSite->RecalcLayout();

	CRect m_clientRC,m_windowRC;
	GetClientRect(m_clientRC);
	GetWindowRect(m_windowRC);
	
	if( m_dwStyle & CBRS_ORIENT_HORZ ) 
	{
		int rtop = m_ncTopHeight;
		int rbottom = m_ncTopHeight+14;
		m_closeRC.CopyRect(CRect(4,rtop,18,rbottom));
		//���ƹرհ�ť
		pDC->DrawFrameControl(m_closeRC ,DFC_CAPTION,DFCS_CAPTIONCLOSE);		
		
		m_maxRc.top = m_closeRC.bottom+4;
		m_maxRc.bottom = m_maxRc.top+ m_closeRC.Height();
		m_maxRc.left=m_closeRC.left;
		m_maxRc.right= m_closeRC.right;
		//������󻯰�ť
		pDC->DrawFrameControl(m_maxRc,DFC_CAPTION, DFCS_CAPTIONMAX);

		//��������
		CRect lineRC;
		lineRC.top= m_maxRc.bottom+2;
		lineRC.bottom = m_windowRC.Height()-m_ncLBandWidth;
		lineRC.left= m_maxRc.left+2;
		lineRC.right = m_maxRc.left+5;
		pDC->Draw3dRect(lineRC, m_TopBandColor,m_BottomBandColor);
		
		lineRC.left = lineRC.right+2;
		lineRC.right = lineRC.left+3;  
		//lineRC.InflateRect(8,0,5,0);
		pDC->Draw3dRect(lineRC, m_TopBandColor,m_BottomBandColor);
	}
	
	else 
	{
		int rpos =m_clientRC.Width()+m_ncLeftWidth;
		int lpos = rpos-16;

		m_closeRC.CopyRect(CRect(lpos,4,rpos,18)); //ȷ���رհ�ť����
		//���ƹرհ�ť
		pDC->DrawFrameControl(m_closeRC, DFC_CAPTION, DFCS_CAPTIONCLOSE);

		m_maxRc.top = m_closeRC.top;
		m_maxRc.bottom = m_closeRC.bottom;
		m_maxRc.left = m_closeRC.left-m_closeRC.Width()-4; //4��������ť�ļ��
		m_maxRc.right = m_maxRc.left+ m_closeRC.Width();
		//������󻯰�ť
		pDC->DrawFrameControl(m_maxRc, DFC_CAPTION, DFCS_CAPTIONMAX);

		//��������
		CRect lineRC;//������������
		lineRC.top= m_closeRC.top+3;
		lineRC.left = m_ncLeftWidth+2;
		lineRC.right = m_maxRc.left-2;
		lineRC.bottom=lineRC.top+3;
		
		pDC->Draw3dRect(lineRC, m_TopBandColor,m_BottomBandColor);
		lineRC.DeflateRect(0,4,0,-4);
		pDC->Draw3dRect(lineRC, m_TopBandColor,m_BottomBandColor);
	}
}

void CDockBarCtrl::OnNcPaint() 
{
    EraseNonClient();
	
	CDC* pDC = GetWindowDC();
	DrowTitleLine(pDC);	
	// Do not call CControlBar::OnNcPaint() for painting messages
}

void CDockBarCtrl::OnNcLButtonDown(UINT nHitTest, CPoint point) 
{	
	//CDockContext
	switch( nHitTest)
	{
	case HTSYSMENU://������¹رհ�ť,���ؿ�����
		m_pDockSite->ShowControlBar(this,FALSE,FALSE);
		break;
	case HTMAXBUTTON:
		m_pDockContext->ToggleDocking();
		break;
	case HTCAPTION :
		if (!IsFloating())
			m_pDockContext->StartDrag(point);
		break;
	case HTSIZE:
		{
			m_OldPos = point;
			if (!IsFloating())
				BeginTracking(); //��ʼ�����������Ĵ�С
		}
		break;
	}
}

UINT CDockBarCtrl::OnNcHitTest(CPoint point) 
{
	CRect rc,ncrc;//��������ͷǿͻ�����


	m_pDockSite->RecalcLayout();
	GetWindowRect(rc);
	
	if (m_dwStyle&CBRS_ORIENT_VERT ) 
	{	//��ֱ��ʾʱ�������������
		ncrc.CopyRect(CRect(0,0,rc.Width()-m_maxRc.Width(),m_ncTBandHeight));
		//��ֱ��ʾʱ����������
		if (m_DockBarID==AFX_IDW_DOCKBAR_LEFT ) //�����ͣ��
			m_Bandrc.CopyRect(CRect(rc.Width()-m_ncLeftWidth,0,rc.Width(),rc.Height()));
		else //���ұ�ͣ��
			m_Bandrc.CopyRect(CRect(0,0,m_ncLeftWidth,rc.Height()));
		m_Bandrc.InflateRect(2,0,2,0);
	}
	else 
	{
		//ˮƽ��ʾʱ�������������
		ncrc.CopyRect(CRect(0,0,m_ncTBandHeight,rc.Width()-m_maxRc.Width()));

		if (m_DockBarID==AFX_IDW_DOCKBAR_TOP ) //���Ϸ�ͣ��
			//bandrc.CopyRect(CRect(0,0,rc.Width(),m_ncTopHeight));
			m_Bandrc.CopyRect(CRect(0,rc.Height()-m_ncTopHeight,rc.Width(),rc.Height()));
		else  //���·�ͣ��
			m_Bandrc.CopyRect(CRect(0,0,rc.Width(),m_ncTopHeight));
		m_Bandrc.InflateRect(0,2,0,2);
	}
	point.Offset(-rc.left,-rc.top);
	if (m_closeRC.PtInRect(point))
		return HTSYSMENU;
	if (m_maxRc.PtInRect(point))
		return HTMAXBUTTON;
	if (ncrc.PtInRect(point))
		return HTCAPTION ;
	if (m_Bandrc.PtInRect(point))
		return HTSIZE;
	 
		m_HitTest = CControlBar::OnNcHitTest(point);
	return  m_HitTest;
}

void CDockBarCtrl::OnNcLButtonDblClk(UINT nHitTest, CPoint point) 
{
	//CDockContext
	if ((m_pDockBar != NULL) && (nHitTest == HTCAPTION))
	{
	//	m_pDockSite->RecalcLayout();
		m_pDockContext->ToggleDocking();

	}
	else
		CWnd::OnNcLButtonDblClk(nHitTest, point);
}

void CDockBarCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	
	//CControlBar::OnLButtonDblClk(nFlags, point);
}

BOOL CDockBarCtrl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if (nHitTest==HTSIZE)
		if (m_dwStyle&(CBRS_ORIENT_HORZ))
			SetCursor(LoadCursor(NULL,IDC_SIZENS));
		else
			SetCursor(LoadCursor(NULL,IDC_SIZEWE));
	else
		return CControlBar::OnSetCursor(pWnd, nHitTest, message);
	return TRUE;
}

void CDockBarCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (! m_IsTraking)
	{
		CControlBar::OnMouseMove(nFlags, point);
		return;
	}
	if (m_IsTraking)
	{
		
		CRect rc;
		GetWindowRect(rc);

		CPoint pot;
		pot = m_temprc.CenterPoint();

		if (m_dwStyle&(CBRS_ORIENT_HORZ))
		{
			DrawDashLine(m_temprc);	

			point.y +=m_TopInterval;
			m_temprc.OffsetRect(0,point.y-pot.y);
			DrawDashLine(m_temprc);
		}
		else
		{		
			DrawDashLine(m_temprc);	
			if (m_DockBarID==AFX_IDW_DOCKBAR_RIGHT)
				point.x +=m_LeftInterval+ m_ncLeftWidth;
			point.y +=m_TopInterval;
			m_temprc.OffsetRect(point.x-pot.x,0);
			DrawDashLine(m_temprc);
		}
	}
}


void CDockBarCtrl::BeginTracking()
{
	SetCapture();	
	m_IsTraking = TRUE;	

    RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_UPDATENOW);	
	m_pDockSite->LockWindowUpdate();
	
	
	m_temprc = m_Bandrc;

	CRect rc,rect;
	GetWindowRect(rc);
	m_pDockSite->GetWindowRect(rect);

	m_LeftInterval  = rc.left-rect.left;
	m_TopInterval = rc.top-rect.top-4;

	if (m_DockBarID==AFX_IDW_DOCKBAR_LEFT)
	{
		m_temprc.DeflateRect(0,4,0,0);

		m_temprc.OffsetRect(0,m_TopInterval);
	}
	if (m_DockBarID==AFX_IDW_DOCKBAR_RIGHT)
	{
		m_temprc.DeflateRect(0,4,0,0);
		m_temprc.OffsetRect(0,m_TopInterval);
	}
	if (m_DockBarID==AFX_IDW_DOCKBAR_BOTTOM)
	{
		m_temprc.DeflateRect(4,0,4,0);
		m_temprc.OffsetRect(m_LeftInterval,0);
	}
	if (m_DockBarID==AFX_IDW_DOCKBAR_TOP)
	{
		m_temprc.DeflateRect(4,0,4,0);
		m_temprc.OffsetRect(m_LeftInterval,0);
	}

	DrawDashLine(m_temprc);
}

void CDockBarCtrl::EndTracking()
{
	ReleaseCapture();
	m_IsTraking = FALSE;
	m_pDockSite->UnlockWindowUpdate();

    RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_UPDATENOW);	
	m_pDlg->Invalidate();

	CPoint pos;
	GetCursorPos(&pos);
	
	CRect rc;
	m_pDockSite->GetWindowRect(rc);
	if (m_DockBarID==AFX_IDW_DOCKBAR_TOP)
	{
		m_pDlg->GetWindowRect(&m_HorRect);
		m_HorRect.bottom= pos.y;

	}
	else if (m_DockBarID==AFX_IDW_DOCKBAR_LEFT)
	{
		int temp = pos.x-m_OldPos.x;
		m_pDlg->GetWindowRect(&m_VerRect);
		m_VerRect.right= pos.x;
	}
	else if (m_DockBarID== AFX_IDW_DOCKBAR_RIGHT)
	{
		int temp = pos.x-m_OldPos.x;
		m_VerRect.left +=temp;
	}
	else if (m_DockBarID==AFX_IDW_DOCKBAR_BOTTOM)
	{
		m_pDlg->GetWindowRect(&m_HorRect);
		int temp = pos.y-m_OldPos.y;
		m_HorRect.top += temp;	
	}

	m_pDockSite->RecalcLayout();
}

void CDockBarCtrl::OnNcLButtonUp(UINT nHitTest, CPoint point) 
{
	CControlBar::OnNcLButtonUp(nHitTest, point);
}

void CDockBarCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_IsTraking)
		EndTracking();
	else
		CControlBar::OnLButtonUp(nFlags, point);
}

void CDockBarCtrl::DrawDashLine(CRect rect)
{
	CDC *pDC =m_pDockSite->GetDCEx(NULL,DCX_WINDOW|DCX_CACHE|DCX_LOCKWINDOWUPDATE);

    CBrush* pBrush = CDC::GetHalftoneBrush();//��ȡһ��ǰ��ɫ�ͱ���ɫ��ϵĻ�ˢ
    HBRUSH hOldBrush = NULL;

    if (pBrush != NULL)
        hOldBrush = (HBRUSH)SelectObject(pDC->m_hDC, pBrush->m_hObject);
	if (m_dwStyle&(CBRS_ORIENT_HORZ))
		pDC->PatBlt(rect.left,rect.top+8,rect.Width(),rect.Height(),PATINVERT);

	else
		pDC->PatBlt(rect.left+m_ncLeftWidth,rect.top,rect.Width(),rect.Height(),PATINVERT);

    if (hOldBrush != NULL)
        SelectObject(pDC->m_hDC, hOldBrush);

	m_pDockSite->ReleaseDC(pDC);
}

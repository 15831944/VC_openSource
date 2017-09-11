// PictureOverturnView.cpp : implementation of the CPictureOverturnView class
//

#include "stdafx.h"
#include "PictureOverturn.h"

#include "PictureOverturnDoc.h"
#include "PictureOverturnView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPictureOverturnView

IMPLEMENT_DYNCREATE(CPictureOverturnView, CView)

BEGIN_MESSAGE_MAP(CPictureOverturnView, CView)
	//{{AFX_MSG_MAP(CPictureOverturnView)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPictureOverturnView construction/destruction

CPictureOverturnView::CPictureOverturnView()
{
	// TODO: add construction code here

}

CPictureOverturnView::~CPictureOverturnView()
{
}

BOOL CPictureOverturnView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	m_BS_now=IDB_BITMAP1;
	m_ID_now=IDB_BITMAP1;
	m_ID_next=IDB_BITMAP2;

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPictureOverturnView drawing

void CPictureOverturnView::OnDraw(CDC* pDC)
{
	CPictureOverturnDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	//��ֹ�ˣ��ػ�ʱ��������Ļ��˸��ֻ�ڸտ�ʼʱ��ʾһ��ͼƬ��
	DrawPicture(m_BS_now);	//����m_BS_now�洢��λͼID���л���λͼ
}

/////////////////////////////////////////////////////////////////////////////
// CPictureOverturnView printing

BOOL CPictureOverturnView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPictureOverturnView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPictureOverturnView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPictureOverturnView diagnostics

#ifdef _DEBUG
void CPictureOverturnView::AssertValid() const
{
	CView::AssertValid();
}

void CPictureOverturnView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPictureOverturnDoc* CPictureOverturnView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPictureOverturnDoc)));
	return (CPictureOverturnDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPictureOverturnView message handlers

BOOL CPictureOverturnView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
//	
	return true;
//	return CView::OnEraseBkgnd(pDC);
}



void CPictureOverturnView::DrawPicture(int ID_PICTURE)
{
	CDC *pDC= GetDC();		//�õ��ͻ������豸����
	CBitmap bitmap;			//����һ��λͼ����
	bitmap.LoadBitmap(ID_PICTURE);	//��λͼ���ص�λͼ������

	BITMAP bmp;			//����λͼ�ṹ
	bitmap.GetBitmap(&bmp);		//��λͼ��Ϣ���λͼ�ṹ

	CDC dcCompatible;		//�����豸�����Ķ���
	dcCompatible.CreateCompatibleDC(pDC);//�����ڴ��豸��������pDC�豸��������ƥ��
	dcCompatible.SelectObject(&bitmap);//��λͼѡ���ڴ��豸������

	CRect rect;
	GetClientRect(rect);		//�õ��ͻ����Ĵ�С

	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,
			0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);//��λͼ������ָ��������
	ReleaseDC(pDC);
}

void CPictureOverturnView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	static int i=IDB_BITMAP1;
	//�ж�����λ��
	CRect ClientRect;
	GetClientRect(ClientRect);
	int Clientwidth=ClientRect.Width();
	Clientwidth /=2;
	CString str;
	if(point.x>Clientwidth)
	{		
		
		if(i==IDB_BITMAP1+16)
		{
			i=IDB_BITMAP1+16;
		}
		else
		{
			int picture_pos=i;
			//����ͼƬ��ID���������ڲ�����SetTimer����
			DrawLToR(picture_pos,picture_pos+1);
			i++;//ҳ���һ
			m_BS_now++;//���浱ǰ��ҳ�棬�Ŵ���Сʱʹ�á�
		}
		
	}
	else
	{
		
		if(i==IDB_BITMAP1)
		{	
			i=IDB_BITMAP1;
		}
		else
		{
			int picture_pos=i;
			DrawRToL(picture_pos,picture_pos-1);
			i--;
			m_BS_now--;
		}

	}
	CView::OnLButtonDown(nFlags, point);
}

void CPictureOverturnView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{
	case 1 :	//ͼƬ�������ҷ�����ҳ�ķ�ת(��һ��)
		{
			OverPicture_LToR();
			break;
		}

	case 2:		//ͼƬ�������ҷ�����ҳ�ķ�ת���ڶ�����
		{
			OverPicture_LToR2();
			break;
		}
	case 3:
		{
			OverPicture_RToL();
			break;
		}
	case 4:
		{
			OverPicture_RToL2();
			break;
		}
	default:
		{
			break;
		}

	}
	CView::OnTimer(nIDEvent);
}



////////////////////////
//�������ҵķ�ҳ
void CPictureOverturnView::OverPicture_LToR()
{

	static int page_step=0;
	
	CDC *pDC= GetDC();
	//bitmapnow�ǵ�ǰ��λͼ��bitmap����һ��λͼ
	CBitmap bitmapnow,bitmapnext;
	bitmapnow.LoadBitmap(m_ID_now);
	bitmapnext.LoadBitmap(m_ID_next);

	//����bitmapnowλͼ�Ľṹ
	BITMAP bmpnow ,bmpnext;
	bitmapnow.GetBitmap(&bmpnow);//��ǰ��λͼ�ṹ
	bitmapnow.GetBitmap(&bmpnext);//��һ�ŵ�λͼ�ṹ

	//����ǰͼƬѡ���豸��������
	CDC dcnow;
	dcnow.CreateCompatibleDC(pDC);
	dcnow.SelectObject(&bitmapnow);
	//����һ��ͼƬѡ���豸��������
	CDC dcnext;
	dcnext.CreateCompatibleDC(pDC);
	dcnext.SelectObject(&bitmapnext);


	CRect rect;
	GetClientRect(rect);
	//��λͼ������ʾ��һ�������У�������Σ�
	//������ε����ϵ㣬���ߣ� �豸������
	//ѡ��λͼ�����ϵ㣬���ߣ� ���Ƶķ�ʽ
	//�Ȼ�����߲����ĵ�ǰλͼ��
	pDC->StretchBlt(0,0,rect.Width()/2,rect.Height(),&dcnow,
			0,0,bmpnow.bmWidth/2,bmpnow.bmHeight,SRCCOPY);
	//�����ұ���һ�ŵ�λͼ
	pDC->StretchBlt(rect.Width()-rect.Width()/12*page_step,//������ε�x��
			0,				//������ε�y��
			rect.Width()/12*page_step,	//������εĿ��
			rect.Height(),			//������εĸ߶�
			&dcnext,			//���λͼ���豸������
			bmpnext.bmWidth/2+bmpnext.bmWidth/2-bmpnext.bmWidth/12*page_step,//λͼ����ʼx��
			0,				//λͼ����ʼy��
			bmpnext.bmWidth/12*page_step,	//λͼ�Ŀ��
			bmpnext.bmHeight,		//λͼ�ĸ߶�
			SRCCOPY);			//���Ƶķ�ʽ
	//�����ұߵ�ǰ���ε�λͼ����������һ��λͼ��
	pDC->StretchBlt(rect.Width()/2,0,rect.Width()/2-rect.Width()/12*page_step,rect.Height(),&dcnow,
			bmpnow.bmWidth/2,0,bmpnow.bmWidth/2,bmpnow.bmHeight,SRCCOPY);

	page_step++;
	if(page_step>6)
	{
		page_step=0;
		KillTimer(1);		//ȡ��1�Ŷ�ʱ���ĵ���	
		ReleaseDC(&dcnow);//�ͷ��ڴ��豸������
		ReleaseDC(&dcnext);
		ReleaseDC(pDC);
		SetTimer(2,150,NULL);	//����2�Ŷ�ʱ��
	}
	ReleaseDC(&dcnow);
	ReleaseDC(&dcnext);
	ReleaseDC(pDC);

	
}


//����ͼƬ��ID�����ö�ʱ����1�Ŷ�ʱ��
void CPictureOverturnView::DrawLToR(int IDNOW, int IDNEXT)
{
	m_ID_now=IDNOW;
	m_ID_next= IDNEXT;
	SetTimer(1,150,NULL);
}

void CPictureOverturnView::OverPicture_LToR2()
{
	static int page_step=0;
	
	//bitmapnow�ǵ�ǰ��λͼ��bitmap����һ��λͼ
	CDC *pDC = GetDC();
	CBitmap bitmapnow,bitmapnext;
	bitmapnow.LoadBitmap(m_ID_now);
	bitmapnext.LoadBitmap(m_ID_next);
	
	//����bitmapnowλͼ�Ľṹ
	BITMAP bmpnow ,bmpnext;
	bitmapnow.GetBitmap(&bmpnow);//��ǰ��λͼ�ṹ
	bitmapnow.GetBitmap(&bmpnext);//��һ�ŵ�λͼ�ṹ
	
	//����ǰͼƬѡ���豸��������
	CDC dcnow;
	dcnow.CreateCompatibleDC(pDC);
	dcnow.SelectObject(&bitmapnow);
	//����һ��ͼƬѡ���豸��������
	CDC dcnext;
	dcnext.CreateCompatibleDC(pDC);
	dcnext.SelectObject(&bitmapnext);
	
	
	CRect rect;
	GetClientRect(rect);
	//��λͼ������ʾ��һ�������У�������Σ�
	//������ε����ϵ㣬���ߣ� �豸������
	//ѡ��λͼ�����ϵ㣬���ߣ� ���Ƶķ�ʽ
	//�Ȼ����ұ߲�������һ��λͼ��
	pDC->StretchBlt(rect.Width()/2,0,rect.Width()/2,rect.Height(),&dcnext,
		bmpnext.bmWidth/2,0,bmpnext.bmWidth/2,bmpnext.bmHeight,SRCCOPY);
	//������ߵ�ǰ��λͼ
	pDC->StretchBlt(
		0,				//������ε�x��
		0,				//������ε�y��
		rect.Width()/2-rect.Width()/12*page_step,	//������εĿ��
		rect.Height(),			//������εĸ߶�
		&dcnow,			//���λͼ���豸������
		0,//λͼ����ʼx��
		0,				//λͼ����ʼy��
		bmpnow.bmWidth/2-bmpnow.bmWidth/12*page_step,	//λͼ�Ŀ��
		bmpnow.bmHeight,		//λͼ�ĸ߶�
		SRCCOPY);			//���Ƶķ�ʽ
	//���������һ�ű��ε�λͼ�������˵�ǰλͼ��
	pDC->StretchBlt(rect.Width()/2-rect.Width()/12*page_step,//���ε�x��
		0,			//���ε�y��
		rect.Width()/12*page_step,//���εĿ��
		rect.Height(),
		&dcnext,
		0,			//λͼ��x��
		0,			//λͼ��y��
		bmpnext.bmWidth/2,
		bmpnext.bmHeight,
		SRCCOPY);
	
	page_step++;
	if(page_step>6)
	{
		page_step=0;
		KillTimer(2);
		ReleaseDC(&dcnow);
		ReleaseDC(&dcnext);
		ReleaseDC(pDC);
		//�ٻ�һ�鵱ǰ��ͼƬ������Ч�����һЩ
		DrawPicture(m_BS_now);
	}
	ReleaseDC(&dcnow);
	ReleaseDC(&dcnext);
	ReleaseDC(pDC);
	
}



void CPictureOverturnView::OverPicture_RToL()
{
	static int page_step=0;
	
	CDC *pDC= GetDC();
	//bitmapnow�ǵ�ǰ��λͼ��bitmapnext����һ��λͼ
	CBitmap bitmapnow,bitmapnext;
	bitmapnow.LoadBitmap(m_ID_now);//��ǰҳ
	bitmapnext.LoadBitmap(m_ID_next);//ǰһҳ
	
	//����bitmapnowλͼ�Ľṹ
	BITMAP bmpnow ,bmpnext;
	bitmapnow.GetBitmap(&bmpnow);//��ǰ��λͼ�ṹ
	bitmapnow.GetBitmap(&bmpnext);//��һ�ŵ�λͼ�ṹ
	
	//����ǰͼƬѡ���豸��������
	CDC dcnow;
	dcnow.CreateCompatibleDC(pDC);
	dcnow.SelectObject(&bitmapnow);
	//����һ��ͼƬѡ���豸��������
	CDC dcnext;
	dcnext.CreateCompatibleDC(pDC);
	dcnext.SelectObject(&bitmapnext);
	
	
	CRect rect;
	GetClientRect(rect);
	//��λͼ������ʾ��һ�������У�������Σ�
	//������ε����ϵ㣬���ߣ� �豸������
	//ѡ��λͼ�����ϵ㣬���ߣ� ���Ƶķ�ʽ
	//�Ȼ����ұ߲����ĵ�ǰλͼ��
	pDC->StretchBlt(rect.Width()/2,0,rect.Width()/2,rect.Height(),&dcnow,
		bmpnow.bmWidth/2,0,bmpnow.bmWidth/2,bmpnow.bmHeight,SRCCOPY);
	//�����ұ���һ�ŵ�λͼ
	pDC->StretchBlt(0,			//������ε�x��
		0,				//������ε�y��
		rect.Width()/12*page_step,	//������εĿ��
		rect.Height(),			//������εĸ߶�
		&dcnext,			//���λͼ���豸������
		0,//λͼ����ʼx��
		0,				//λͼ����ʼy��
		bmpnext.bmWidth/12*page_step,	//λͼ�Ŀ��
		bmpnext.bmHeight,		//λͼ�ĸ߶�
		SRCCOPY);			//���Ƶķ�ʽ
	//�����ұߵ�ǰ���ε�λͼ����������һ��λͼ��
	pDC->StretchBlt(rect.Width()/12*page_step,0,rect.Width()/2-rect.Width()/12*page_step,rect.Height(),&dcnow,
		0,0,bmpnow.bmWidth/2,bmpnow.bmHeight,SRCCOPY);					
	page_step++;
	if(page_step>6)
	{
		page_step=0;
		KillTimer(3);
		ReleaseDC(&dcnow);
		ReleaseDC(&dcnext);
		ReleaseDC(pDC);
		SetTimer(4,150,NULL);//����4�Ŷ�ʱ��
	}
	ReleaseDC(&dcnow);
	ReleaseDC(&dcnext);
	ReleaseDC(pDC);
	
	
}



void CPictureOverturnView::DrawRToL(int IDNOW, int IDNEXT)
{
	m_ID_now=IDNOW;
	m_ID_next= IDNEXT;
	SetTimer(3,150,NULL);
}

void CPictureOverturnView::OverPicture_RToL2()
{
	static int page_step=0;
	
	CDC *pDC= GetDC();
	//bitmapnow�ǵ�ǰ��λͼ��bitmapnext����һ��λͼ
	CBitmap bitmapnow,bitmapnext;
	bitmapnow.LoadBitmap(m_ID_now);//���
	bitmapnext.LoadBitmap(m_ID_next);//С��
	
	//����bitmapnowλͼ�Ľṹ
	BITMAP bmpnow ,bmpnext;
	bitmapnow.GetBitmap(&bmpnow);//��ǰ��λͼ�ṹ
	bitmapnow.GetBitmap(&bmpnext);//��һ�ŵ�λͼ�ṹ
	
	//����ǰͼƬѡ���豸��������
	CDC dcnow;
	dcnow.CreateCompatibleDC(pDC);
	dcnow.SelectObject(&bitmapnow);
	//����һ��ͼƬѡ���豸��������
	CDC dcnext;
	dcnext.CreateCompatibleDC(pDC);
	dcnext.SelectObject(&bitmapnext);
	
	
	CRect rect;
	GetClientRect(rect);
	//��λͼ������ʾ��һ�������У�������Σ�
	//������ε����ϵ㣬���ߣ� �豸������
	//ѡ��λͼ�����ϵ㣬���ߣ� ���Ƶķ�ʽ
	//�Ȼ�����߲����ĵ�ǰλͼ��
	pDC->StretchBlt(0,0,rect.Width()/2,rect.Height(),&dcnext,
		0,0,bmpnext.bmWidth/2,bmpnext.bmHeight,SRCCOPY);
	//�����ұ���һ�ŵ�λͼ
	pDC->StretchBlt(
		rect.Width()/2+rect.Width()/12*page_step,			//������ε�x��
		0,				//������ε�y��
		rect.Width()/2-rect.Width()/12*page_step,	//������εĿ��
		rect.Height(),			//������εĸ߶�
		&dcnow,			//���λͼ���豸������
		bmpnow.bmWidth/2+bmpnow.bmWidth/12*page_step,//λͼ����ʼx��
		0,				//λͼ����ʼy��
		bmpnow.bmWidth/2-bmpnow.bmWidth/12*page_step,	//λͼ�Ŀ��
		bmpnow.bmHeight,		//λͼ�ĸ߶�
		SRCCOPY);			//���Ƶķ�ʽ
	//�����ұߵ�ǰ���ε�λͼ����������һ��λͼ��
	pDC->StretchBlt(rect.Width()/2,			//������ε�x��
		0,				//������ε�y��
		rect.Width()/12*page_step,	//������εĿ��
		rect.Height(),			//������εĸ߶�
		&dcnext,			//���λͼ���豸������
		bmpnext.bmWidth/2,//λͼ����ʼx��
		0,				//λͼ����ʼy��
		bmpnext.bmWidth/2,	//λͼ�Ŀ��
		bmpnext.bmHeight,		//λͼ�ĸ߶�
		SRCCOPY);			//���Ƶķ�ʽ					
	page_step++;
	if(page_step>6)
	{
		page_step=0;
		KillTimer(4);
		ReleaseDC(&dcnow);
		ReleaseDC(&dcnext);
		ReleaseDC(pDC);
		//�ٻ�һ�鵱ǰ��ͼƬ������Ч�����һЩ
		DrawPicture(m_BS_now);
	}
	ReleaseDC(&dcnow);
	ReleaseDC(&dcnext);
	ReleaseDC(pDC);
}

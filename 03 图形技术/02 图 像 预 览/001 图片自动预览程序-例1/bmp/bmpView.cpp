// bmpView.cpp : implementation of the CBmpView class
//

#include "stdafx.h"
#include "bmp.h"

#include "bmpDoc.h"
#include "bmpView.h"
#include <direct.h>
#include "io.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBmpView

IMPLEMENT_DYNCREATE(CBmpView, CView)

BEGIN_MESSAGE_MAP(CBmpView, CView)
	//{{AFX_MSG_MAP(CBmpView)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBmpView construction/destruction

CBmpView::CBmpView()
{
	// TODO: add construction code here
	
}

CBmpView::~CBmpView()
{
}

BOOL CBmpView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBmpView drawing

void CBmpView::OnDraw(CDC* pDC)
{
	CBmpDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	BITMAP BitMap;
	CDC DCMem;
	if (!pDoc->GetHandle())
		return;
	//�����ڴ��豸����
	if (!DCMem.CreateCompatibleDC(pDC))
		TRACE0("DCMem.CreateCompatibleDC failed\n");
	pDoc->SelectBitmap(&DCMem);
	pDoc->GetBitmap(&BitMap);
	//��λͼ��������ʾ�豸�����У�������ʾ
	if (!pDC->BitBlt(0, 0, BitMap.bmWidth, BitMap.bmHeight, &DCMem, 0, 0, SRCCOPY))
		TRACE0("BitBlt failed\n");
	pDoc->SelectOldBitmap(&DCMem);
	DCMem.DeleteDC();

}

/////////////////////////////////////////////////////////////////////////////
// CBmpView printing

BOOL CBmpView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBmpView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBmpView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CBmpView diagnostics

#ifdef _DEBUG
void CBmpView::AssertValid() const
{
	CView::AssertValid();
}

void CBmpView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBmpDoc* CBmpView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBmpDoc)));
	SetTimer(1,2000,NULL);
	return (CBmpDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBmpView message handlers
void CBmpView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CString str=Search(GetDocument()->GetPathName());
	if(str=="")
		return;
	AfxGetApp()->OpenDocumentFile(str);
	CView::OnTimer(nIDEvent);
}

CString CBmpView::Search(CString curstr)
{
	long handle;
	if(curstr.IsEmpty())
		return "";
	if(_getcwd( buffer, 1000)==NULL)
	{
		AfxMessageBox("û�е�ǰ·��,���һ��ͼ���ļ�!");
		return "";
	}

	CString m_sPartname;
	int len = curstr.GetLength();
	int i;
	for(i = len-1;curstr[i] != '\\';i--)
		m_sPartname.Insert(0,curstr[i]);
	i++;
	while(i--<0)
		buffer[i]=curstr[i];
	if (_chdir(buffer) != 0)
		return "";
	
	bool b_notfinde=false;
	struct _finddata_t filestruct;
	// ��ʼ���ҹ���, �ҵ���ǰĿ¼�µĵ�һ��ʵ��(�ļ�����Ŀ¼)�� 
	// ��*���ʾ�����κε��ļ�����Ŀ¼, filestructΪ���ҽ�� 
	handle = _findfirst("*", &filestruct);
	do{
		if((handle ==-1)) // ��handleΪ��1, ��ʾ��ǰĿ¼Ϊ��, ��������Ҷ�����
			break; 
		// ����ҵ��ĵ�һ��ʵ���Ƿ���һ��Ŀ¼ 
		if( ::GetFileAttributes(filestruct.name) & FILE_ATTRIBUTE_DIRECTORY )
		{
			continue ;
		}
		CString Filename=filestruct.name;
		{
			CString tailstr;
			//��ȡ�ļ���չ��
			tailstr = Filename.Mid(Filename.GetLength()-3);
			tailstr.MakeUpper();
			Filename.MakeUpper();
			m_sPartname.MakeUpper();
			if(tailstr=="BMP")
			{
				if(b_notfinde==false)
				{
					if(m_sPartname==Filename)
						b_notfinde=true;
				}
				else
				{
					_findclose(handle);
					return Filename;
				}		
			}									
		}				
	} while(_findnext(handle, &filestruct)==0);
	_findclose(handle);
	this->KillTimer(1);
	AfxMessageBox("�Ѿ��������һ��ͼ���ļ�!");	
	return "";
}

char szFilter[] = "BMP Files(*.BMP)|*.BMP";




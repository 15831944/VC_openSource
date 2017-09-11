// ColorProgress.cpp : implementation file
//

#include "stdafx.h"
#include "Progress.h"
#include "ColorProgress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorProgress

CColorProgress::CColorProgress()
{
}

CColorProgress::~CColorProgress()
{
}


BEGIN_MESSAGE_MAP(CColorProgress, CProgressCtrl)
	//{{AFX_MSG_MAP(CColorProgress)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorProgress message handlers

void CColorProgress::OnPaint() 
{
//	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	PAINTSTRUCT ps;
	CDC* pDC = BeginPaint(&ps);						//��ʼ����
	int nPos = GetPos();							//��ȡ��ǰ��������λ��
	CRect clientRC;
	GetClientRect(clientRC);						//��ȡ�ͻ�����
	pDC->SetBkMode(TRANSPARENT);					//���豸�����ĵı���ģʽ����Ϊ͸��
	int nMin, nMax;
	GetRange(nMin, nMax);							//��ȡ����������ʾ��Χ
	//��ȡ��λ�̶�
	double dFraction = (double)clientRC.Width() / (nMax-nMin);
	int nLeft = nPos * dFraction;					//������߾�
	CRect leftRC  = clientRC;
	leftRC.right  = nLeft;
	CRect rightRC = clientRC;
	rightRC.left  = nLeft;
	for(int m=255;m>0;m--)
	{
		int x,y;
		x = leftRC.Width() * m / 255;
		pDC->FillRect(CRect(0,0,x,leftRC.Height()),&CBrush(RGB(255,m,0)));
	}
	pDC->FillRect(rightRC, &CBrush(RGB(255, 255, 255)));		//ʹ�ð�ɫ��ʶʣ��Ĳ���
	ReleaseDC(pDC);									//�ͷ��豸������
	EndPaint(&ps);									//�������ڻ���
	// Do not call CProgressCtrl::OnPaint() for painting messages
}

// TextProgress1.cpp : implementation file
//

#include "stdafx.h"
#include "TextProgress.h"
#include "TextProgress1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextProgress

CTextProgress::CTextProgress()
{
	m_crText	 = RGB(0, 255, 0);
	m_crBlank	 = RGB(255, 255, 255);
	m_crProgress = RGB(0, 0, 255);
}

CTextProgress::~CTextProgress()
{
}


BEGIN_MESSAGE_MAP(CTextProgress, CProgressCtrl)
	//{{AFX_MSG_MAP(CTextProgress)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextProgress message handlers

void CTextProgress::OnPaint() 
{
	PAINTSTRUCT ps;
	CDC* pDC = BeginPaint(&ps);						//��ʼ����
	int nPos = GetPos();							//��ȡ��ǰ��������λ��
	CString csPos;
	csPos.Format("%d%%", nPos);						//��ʽ���ַ���
	CRect clientRC;
	GetClientRect(clientRC);						//��ȡ�ͻ�����
	CSize sztext = pDC->GetTextExtent(csPos);		//��ȡ�ַ����ĸ߶ȺͿ��
	int nX = (clientRC.Width() - sztext.cx) / 2;	//��������λ��
	int nY = (clientRC.Height() - sztext.cy) / 2;
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
	pDC->FillRect(leftRC, &CBrush(m_crProgress));	//ʹ����ɫ��ʶ��ǰ�Ľ���
	pDC->FillRect(rightRC, &CBrush(m_crBlank));		//ʹ�ð�ɫ��ʶʣ��Ĳ���
	pDC->SetTextColor(m_crText);					//�����ı���ɫ
	pDC->TextOut(nX, nY, csPos);					//�����ǰ�Ľ���
	ReleaseDC(pDC);									//�ͷ��豸������
	EndPaint(&ps);									//�������ڻ���	
}



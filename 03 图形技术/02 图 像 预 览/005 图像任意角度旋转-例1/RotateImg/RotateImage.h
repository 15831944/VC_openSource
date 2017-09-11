#if !defined(AFX_ROTATEIMAGE_H__EA81F65C_16B5_42D0_BB1D_9F8ADB0AA1BB__INCLUDED_)
#define AFX_ROTATEIMAGE_H__EA81F65C_16B5_42D0_BB1D_9F8ADB0AA1BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RotateImage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRotateImage dialog
#include "ImagePanel.h"

class CRotateImage : public CDialog
{
// Construction
public:
	void OnLBtnRadio(UINT nID);
	void RotateBmp(BYTE* pBmpData, BYTE*& pDesData, int nWidth, int nHeight,
			int nDesWidth, int nDesHeight,double dAngle);
	void RotationImage(BITMAPINFOHEADER *pBmInfo,int nDegree);
	CRotateImage(CWnd* pParent = NULL);   // standard constructor

	CImagePanel m_ImagePanel;		//ͼƬ��ʾ������
	HBITMAP m_hBmp;					//����λͼ���
	BOOL m_bLoaded;					//��ʾ�Ƿ������λͼ
	BITMAPINFOHEADER desBmInfo;		//����λͼʱʹ�õ�λͼ��Ϣͷ
	BYTE *m_pBmpData;				//����һ��ָ�룬���ڼ�¼λͼ����

	BITMAPFILEHEADER m_bmFileHeader;	//λͼ�ļ�ͷ
	BITMAPINFOHEADER m_bmInfoHeader;	//λͼ��Ϣͷ

	HGLOBAL  m_hGlobal;					//����һ��ȫ�ֶ���
	BYTE* m_RotData;					//����һ��ָ�룬��ʾ��ת���ͼ��
	CString m_SrcFile;					//��¼���ص�λͼ�ļ���

// Dialog Data
	//{{AFX_DATA(CRotateImage)
	enum { IDD = IDD_ROTATEIMAGE_DIALOG };
	CSliderCtrl	m_SetDegree;
	CStatic	m_Panel;
	CStatic	m_Image;
	CEdit	m_BmpName;
	UINT	m_nDegree;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRotateImage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRotateImage)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnBtLoad();
	afx_msg void OnBtSave();
	afx_msg void OnBtRotate();
	afx_msg void OnChangeDegree();
	afx_msg void OnFixdegree();
	afx_msg void OnRanddegree();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROTATEIMAGE_H__EA81F65C_16B5_42D0_BB1D_9F8ADB0AA1BB__INCLUDED_)

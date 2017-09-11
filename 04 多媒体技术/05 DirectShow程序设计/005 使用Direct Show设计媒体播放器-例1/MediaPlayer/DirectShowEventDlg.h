// DirectShowEventDlg.h : header file
//

#if !defined(AFX_DIRECTSHOWEVENTDLG_H__71A12478_E511_4AC1_BC2D_ECCEA434FB9D__INCLUDED_)
#define AFX_DIRECTSHOWEVENTDLG_H__71A12478_E511_4AC1_BC2D_ECCEA434FB9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dshow.h"
#include "D3d9.h"
#include "vmr9.h"
#include "Objbase.h"

#include "CustomSlider.h" 
#include "NumLabel.h"
#include "DisplayWnd.h"
#include "CustomGroup.h"
/////////////////////////////////////////////////////////////////////////////
// CDirectShowEventDlg dialog


#pragma comment (lib,"Strmiids")
#pragma comment (lib,"quartz")



#define VOLUMN_CLIENCE -10000L
#define CM_POSCHANGE WM_USER+1001
#define  CM_COMPLETE WM_USER+1


class CDirectShowEventDlg : public CDialog
{
// Construction
public:
	void PlayFile(LPCTSTR lpFileName);
	void OnPosChange();
	void SetViewInfo(int nFlag,float fValue);
	void Done(WPARAM wParam, LPARAM lParam);
	void OnCancel();
	CDirectShowEventDlg(CWnd* pParent = NULL);	// standard constructor
	IMediaControl     *pMediaControl ;         //ý�����
	IGraphBuilder     *pGraph;                 //����ͼ��
	ICaptureGraphBuilder2 * pBuilder;
	IGraphBuilder			*pGraphBuilder;
	IBaseFilter       *pSrc,*pBase;				//������
	IMoniker          *pMoniker;               //������
	BOOL              m_Previewed;             //�Ƿ����Ԥ��
	IMediaEventEx     *pEvent;                 //�¼�
	IVideoWindow *    pViewWnd;                //��ƵԤ������
	BOOL              m_Completed;             //Ԥ���Ƿ����
	HANDLE            m_hThread;               //�߳̾��
	BOOL              m_bFullScreen;			//�Ƿ�Ϊȫ��
	long              m_lVolumn;				//��¼��ǰ����
	BOOL              m_bMute;					//�Ƿ�Ϊ����
	BOOL              m_bSpeed;					//�Ƿ���
	BOOL              m_bBack;					//�Ƿ�Ϊ����
	IBasicVideo       *pBaseVideo;
	IBaseFilter *pMixing ,*pRender;
	BOOL              m_bGrayImage;				//�Ƿ�Ϊ�ڰ�ͼ��  
	float               m_fSaturation,m_fHue,m_fContrast,m_fBright;		
	VMR9ProcAmpControlRange m_HueRange;			//ɫ����Χ
	VMR9ProcAmpControlRange m_SatRange;			//���Ͷȷ�Χ
	VMR9ProcAmpControlRange m_ConRange;			//�Աȶȷ�Χ
	VMR9ProcAmpControlRange m_BrightRange;		//������Χ
	BOOL              m_bPause;					//�Ƿ�Ϊ��ͣ
	BOOL              m_bStop;					//�Ƿ�ֹͣ
	CString           m_FileName;

	BOOL              m_ThreadStop;
	CDisplayWnd       m_DisplayWnd;
	BOOL              m_bViewPlay;				//��Ƶ�ļ��Ƿ����ڲ���
	IPin* FindPin(IBaseFilter *pFilter, PIN_DIRECTION dir);
	CRect m_OriginRC;							//��Ƶ����ԭʼ��С
	BOOL              m_bInvalidFile;			//ý���ļ��Ƿ�Ϸ�

// Dialog Data
	//{{AFX_DATA(CDirectShowEventDlg)
	enum { IDD = IDD_DIRECTSHOWEVENT_DIALOG };
	CCustomGroup	m_CtlList;
	CCustomGroup	m_GroupPos;
	CNumLabel	m_CurPos;
	CNumLabel	m_Progress;
	CButton	m_Stop;
	CButton	m_Pause;
	CButton	m_GrayBtn;
	CCustomSlider	m_ProgressCtrl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirectShowEventDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDirectShowEventDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnSetFile();
	afx_msg void OnSnap();
	afx_msg void OnFullScreen();
	afx_msg void OnMute();
	afx_msg void OnVolumnmax();
	afx_msg void OnVolumnmin();
	afx_msg void OnAddSpeed();
	afx_msg void OnAddBack();
	afx_msg void OnGray();
	afx_msg void OnTimer(UINT nIDEvent);

	afx_msg void OnVideoset();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnTbPause();
	afx_msg void OnTbStop();
	afx_msg void OnShowwnd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRECTSHOWEVENTDLG_H__71A12478_E511_4AC1_BC2D_ECCEA434FB9D__INCLUDED_)

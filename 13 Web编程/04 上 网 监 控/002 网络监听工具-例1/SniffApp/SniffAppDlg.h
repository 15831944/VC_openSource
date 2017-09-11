// SniffAppDlg.h : header file
//

#if !defined(AFX_SNIFFAPPDLG_H__C51CBD1D_BCF8_4E20_8508_FE4538057903__INCLUDED_)
#define AFX_SNIFFAPPDLG_H__C51CBD1D_BCF8_4E20_8508_FE4538057903__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSniffAppDlg dialog
#define SIO_RCVALL            _WSAIOW(IOC_VENDOR,1)
#define SIO_RCVALL_MCAST      _WSAIOW(IOC_VENDOR,2)
#define SIO_RCVALL_IGMPMCAST  _WSAIOW(IOC_VENDOR,3)
#define SIO_KEEPALIVE_VALS    _WSAIOW(IOC_VENDOR,4)
#define SIO_ABSORB_RTRALERT   _WSAIOW(IOC_VENDOR,5)
#define SIO_UCAST_IF          _WSAIOW(IOC_VENDOR,6)
#define SIO_LIMIT_BROADCASTS  _WSAIOW(IOC_VENDOR,7)
#define SIO_INDEX_BIND        _WSAIOW(IOC_VENDOR,8)
#define SIO_INDEX_MCASTIF     _WSAIOW(IOC_VENDOR,9)
#define SIO_INDEX_ADD_MCAST   _WSAIOW(IOC_VENDOR,10)
#define SIO_INDEX_DEL_MCAST   _WSAIOW(IOC_VENDOR,11)


//����Ip���ݱ�ͷ�ṹ,20���ֽ�
typedef struct HeadIP {
		unsigned char  headerlen:4;  //�ײ�����,ռ4λ
        unsigned char  version:4;    //�汾,ռ4λ 

        unsigned char  servertype;   //��������,ռ8λ,��1���ֽ�
        unsigned short totallen;     //�ܳ���,ռ16λ
        unsigned short id;           //��idoff���ɱ�ʶ ,��ռ16λ,ǰ3λ�Ǳ�ʶ,��13λ��Ƭƫ��
        unsigned short idoff;        
        unsigned char  ttl;          //����ʱ�� ,ռ8λ         
        unsigned char  proto;        //Э��,ռ8λ   
        unsigned short checksum;     //�ײ������,ռ16λ  
        unsigned int   sourceIP;     //ԴIP��ַ,ռ32λ
        unsigned int   destIP;       //Ŀ��IP��ַ,ռ32λ

}HEADIP;

//����TCP���ݱ��ײ�
typedef struct HeadTCP {
		WORD   SourcePort;    //16λԴ�˿ں�
		WORD   DePort;        //16λĿ�Ķ˿�
		DWORD  SequenceNo;    //32λ���
		DWORD  ConfirmNo;     //32λȷ�����
		BYTE   HeadLen;       //��FlagΪһ����ɲ���, �ײ�����,ռ4λ,����6λ,6λ��ʶ,��16λ   
		BYTE   Flag;
		WORD   WndSize;       //16λ���ڴ�С
		WORD   CheckSum;      //16λУ���
		WORD   UrgPtr;        //16λ����ָ��
} HEADTCP;

//����UDP���ݱ��ײ�
typedef struct HeadUDP {
		WORD SourcePort;  //16λԴ�˿ں�
		WORD DePort;      //16λĿ�Ķ˿�
		WORD Len;         //16ΪUDP����
		WORD ChkSum;      //16λUDPУ���
} HEADUDP;


//����ICMP���ݱ��ײ�
typedef struct HeadICMP {
		BYTE Type;    //8λ����
		BYTE Code;    //8λ����
		WORD ChkSum;  //16λУ���
} HEADICMP;

//����Э������
struct  PROTONAME{
	int  value;
	char* protoname;  
};


class CSniffAppDlg : public CDialog
{
// Construction
public:
	void OnCancel();
	CSniffAppDlg(CWnd* pParent = NULL);	// standard constructor

	SOCKET       m_Sock ;
	CWinThread*  m_pThread;
// Dialog Data
	//{{AFX_DATA(CSniffAppDlg)
	enum { IDD = IDD_SNIFFAPP_DIALOG };
	CListCtrl	m_List;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSniffAppDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSniffAppDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnBeginlisten();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SNIFFAPPDLG_H__C51CBD1D_BCF8_4E20_8508_FE4538057903__INCLUDED_)

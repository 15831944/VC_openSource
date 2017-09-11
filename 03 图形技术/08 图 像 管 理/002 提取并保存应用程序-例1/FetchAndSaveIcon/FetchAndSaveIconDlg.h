// FetchAndSaveIconDlg.h : header file
//

#if !defined(AFX_FETCHANDSAVEICONDLG_H__9BEB090E_C135_447C_85FF_6FC8ED6F0853__INCLUDED_)
#define AFX_FETCHANDSAVEICONDLG_H__9BEB090E_C135_447C_85FF_6FC8ED6F0853__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFetchAndSaveIconDlg dialog
#pragma pack( push )
#pragma pack( 2 )
typedef struct
{
	BYTE	bWidth;               
	BYTE	bHeight;      
	BYTE	bColorCount;  
	BYTE	bReserved;    
	WORD	wPlanes;      
	WORD	wBitCount;    
	DWORD	dwBytesInRes; 
	WORD	nID;          
} MEMICONDIRENTRY, *LPMEMICONDIRENTRY;

typedef struct 
{
	WORD			idReserved;   
	WORD			idType;       
	WORD			idCount;      
	MEMICONDIRENTRY	idEntries[1]; 
} MEMICONDIR, *LPMEMICONDIR;

#pragma pack( pop)
//����ͼ������
typedef struct
{

	LPBITMAPINFO   icheader;  // λͼ��Ϣͷ���ɲ����Ͻڵ�λͼͷ��Ϣ�ṹ
	RGBQUAD         iccolors; //ɫ�ʱ�ͬλͼ��ɫ�ʱ�
	LPBYTE			lpXOR;    
	LPBYTE			lpAND;  
 
      // AND����
} iconimage, *lpiconimage;

//����ͼ����Դ����Ŀ¼
typedef struct
{
	byte        bwidth;          // ͼ���ȣ�������Ϊ��λ
	byte        bheight;         // ͼ��߶ȣ�������Ϊ��λ
	byte        bcolorcount;     //ͼ���е���ɫ��������Ǵ��ڣ���λͼ����ֵΪ��
	byte        breserved;       //����������Ϊ��
	WORD        wplanes;         //λ������һ��Ϊ��
	WORD        wbitcount;       //ÿ������ռλ��
	DWORD       dwbytesinres;    // ��Դ���ֽ���
	DWORD       dwimageoffset;   //ͼ�����ݾ�����Դ��ʼ��ƫ��λ��
} icondirentry, *lpicondirentry;

//����ͼ���ļ�ͷ
typedef struct
{
WORD           idreserved;   // ����������Ϊ��
WORD           idtype;       // ��Դ���ͣ�����ͼ�꣬���ǹ��
WORD          idcount;       // ͼ�����
icondirentry   identries[1]; // ÿ��ͼ�����ڶ���
} icondir, *lpicondir;


class CFetchAndSaveIconDlg : public CDialog
{
// Construction
public:
	DWORD GetImageOffset(HMODULE hmodule ,UINT index,DWORD& cursize ,LPBYTE pbitinfo =NULL);
	CFetchAndSaveIconDlg(CWnd* pParent = NULL);	// standard constructor

	lpicondirentry m_lpdirentry;
	lpicondir m_lpdir;
	lpiconimage m_lpicondata;

	LPMEMICONDIRENTRY m_lpMemEntry;
	LPMEMICONDIR m_lpMemDir;
	LPBYTE m_lpData;

// Dialog Data
	//{{AFX_DATA(CFetchAndSaveIconDlg)
	enum { IDD = IDD_FETCHANDSAVEICON_DIALOG };
	CStatic	m_demoicon;
	CEdit	m_filename;

	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFetchAndSaveIconDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFetchAndSaveIconDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnBrown();
	afx_msg void OnFetch();
	afx_msg void OnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FETCHANDSAVEICONDLG_H__9BEB090E_C135_447C_85FF_6FC8ED6F0853__INCLUDED_)

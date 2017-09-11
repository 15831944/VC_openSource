// ForceDeleteDlg.h : header file
//

#if !defined(AFX_FORCEDELETEDLG_H__AC2CB5C0_A1F1_4BC9_993E_CDCF03F10746__INCLUDED_)
#define AFX_FORCEDELETEDLG_H__AC2CB5C0_A1F1_4BC9_993E_CDCF03F10746__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "afxtempl.h"
/////////////////////////////////////////////////////////////////////////////
// CForceDeleteDlg dialog
//���庯��ָ������
typedef DWORD( WINAPI *funGetModuleFileNameExA)( HANDLE hProcess, HMODULE hModule, LPSTR lpFilename, DWORD nSize);

typedef DWORD (WINAPI *PNtQueryObject)( HANDLE, DWORD, VOID*, DWORD, VOID* );
typedef DWORD (WINAPI *PNtQuerySystemInformation)( DWORD, VOID*, DWORD, ULONG* );
typedef DWORD (WINAPI *PNtQueryInformationThread)(HANDLE, ULONG, PVOID,	DWORD, DWORD* );
typedef DWORD (WINAPI *PNtQueryInformationFile)(HANDLE, PVOID,	PVOID, DWORD, DWORD );
typedef DWORD (WINAPI *PNtQueryInformationProcess)(HANDLE, DWORD, PVOID, DWORD, PVOID );

typedef struct _UNICODE_STRING
{
	WORD  Length;
	WORD  MaximumLength;
	PWSTR Buffer;
} UNICODE_STRING;


//����ϵͳ����ṹ
typedef struct _SYSTEM_HANDLE
{
	DWORD	ProcessID;
	WORD	HandleType;
	WORD	HandleNumber;
	DWORD	KernelAddress;
	DWORD	Flags;
} SYSTEM_HANDLE;

typedef struct _SYSTEM_HANDLE_INFORMATION
{
	DWORD			Count;
	SYSTEM_HANDLE	Handles[1];
} SYSTEM_HANDLE_INFORMATION;

//���������Ϣ�ṹ
	typedef LARGE_INTEGER   QWORD;

	typedef struct _PROCESS_BASIC_INFORMATION {
			DWORD ExitStatus;
			PVOID PebBaseAddress;
			DWORD AffinityMask;
			DWORD BasePriority;
			DWORD UniqueProcessId;
			DWORD InheritedFromUniqueProcessId;
		} PROCESS_BASIC_INFORMATION;

	typedef struct _VM_COUNTERS
		{
		DWORD PeakVirtualSize;
		DWORD VirtualSize;
		DWORD PageFaultCount;
		DWORD PeakWorkingSetSize;
		DWORD WorkingSetSize;
		DWORD QuotaPeakPagedPoolUsage;
		DWORD QuotaPagedPoolUsage;
		DWORD QuotaPeakNonPagedPoolUsage;
		DWORD QuotaNonPagedPoolUsage;
		DWORD PagefileUsage;
		DWORD PeakPagefileUsage;
		} VM_COUNTERS;

	typedef struct _SYSTEM_THREAD
		{
		DWORD        u1;
		DWORD        u2;
		DWORD        u3;
		DWORD        u4;
		DWORD        ProcessId;
		DWORD        ThreadId;
		DWORD        dPriority;
		DWORD        dBasePriority;
		DWORD        dContextSwitches;
		DWORD        dThreadState;      // 2=running, 5=waiting
		DWORD        WaitReason;
		DWORD        u5;
		DWORD        u6;
		DWORD        u7;
		DWORD        u8;
		DWORD        u9;
		} SYSTEM_THREAD;

	typedef struct _SYSTEM_PROCESS_INFORMATION
		{
		DWORD          dNext;
		DWORD          dThreadCount;
		DWORD          dReserved01;
		DWORD          dReserved02;
		DWORD          dReserved03;
		DWORD          dReserved04;
		DWORD          dReserved05;
		DWORD          dReserved06;
		QWORD          qCreateTime;
		QWORD          qUserTime;
		QWORD          qKernelTime;
		UNICODE_STRING usName;
		DWORD	       BasePriority;
		DWORD          dUniqueProcessId;
		DWORD          dInheritedFromUniqueProcessId;
		DWORD          dHandleCount;
		DWORD          dReserved07;
		DWORD          dReserved08;
		VM_COUNTERS    VmCounters;
		DWORD          dCommitCharge;
		SYSTEM_THREAD  Threads[1];
		} SYSTEM_PROCESS_INFORMATION;



#define MAX_FILENAME 0x1000

class CForceDeleteDlg : public CDialog
{
// Construction
public:
	BOOL GetDiviceName(LPCTSTR lpDosName, CString& szDiviceName);
	void OnCancel();
	void EnumRunningProc();
	void LoadFileHanle();
	void EnumProcessOpenedFile();
	BOOL CloseFileHandle(DWORD dwProcessID, HANDLE hFile);
	BOOL AdjustPrivilege();
	CForceDeleteDlg(CWnd* pParent = NULL);	// standard constructor
	//���庯��ָ�����
	PNtQueryObject				NtQueryObject;
	PNtQuerySystemInformation	NtQuerySystemInformation;
	
	//��¼�ļ����
	CList<SYSTEM_HANDLE, SYSTEM_HANDLE&> m_FileHandles;
	//��¼ϵͳ��ǰ���еĽ�����Ϣ
	CMap< DWORD, DWORD&, SYSTEM_PROCESS_INFORMATION*, SYSTEM_PROCESS_INFORMATION*> m_SysProcesses;

	funGetModuleFileNameExA		GetModuleFileNameEx;	

	UCHAR*						m_pProcInfo;	//������Ϣ������
	DWORD						m_dwProcSize;	//������Ϣ��������С
	UCHAR						m_FileNames[MAX_FILENAME];
	HANDLE						m_hFile;		//�ļ����
	BOOL						m_bFindFile;	//�Ƿ����ļ�
	HMODULE hMod;
// Dialog Data
	//{{AFX_DATA(CForceDeleteDlg)
	enum { IDD = IDD_FORCEDELETE_DIALOG };
	CEdit	m_FileName;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CForceDeleteDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CForceDeleteDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnClear();
	afx_msg void OnBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORCEDELETEDLG_H__AC2CB5C0_A1F1_4BC9_993E_CDCF03F10746__INCLUDED_)

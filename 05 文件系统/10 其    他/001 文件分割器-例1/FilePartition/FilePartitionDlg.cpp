// FilePartitionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FilePartition.h"
#include "FilePartitionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFilePartitionDlg dialog

CFilePartitionDlg::CFilePartitionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFilePartitionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFilePartitionDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFilePartitionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFilePartitionDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFilePartitionDlg, CDialog)
	//{{AFX_MSG_MAP(CFilePartitionDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTADD, OnAdd)
	ON_BN_CLICKED(IDC_BTDIR, OnAddDir)
	ON_BN_CLICKED(IDC_BTPatition, OnPartition)
	ON_BN_CLICKED(IDC_BTSELPART, OnSelectPart)
	ON_BN_CLICKED(IDC_BTOMBIN, OnOmbin)
	ON_EN_CHANGE(IDC_EDFILEPATH, OnChangeEdfilepath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFilePartitionDlg message handlers

BOOL CFilePartitionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFilePartitionDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CFilePartitionDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFilePartitionDlg::OnAdd() 
{
	CFileDialog log(TRUE,NULL,NULL,OFN_HIDEREADONLY,"FILE(*.*)|*.*||",NULL);
	if(log.DoModal()==IDOK)
	{
		CString pathname;
		pathname=log.GetPathName();
		filename=log.GetFileName();
		filenamenoext=log.GetFileTitle();
		filenameext=log.GetFileExt();
		GetDlgItem(IDC_EDFILEPATH)->SetWindowText(pathname);
		CFileStatus status;
		CFile::GetStatus(pathname,status);
		CString strsize;
		strsize.Format("�ļ���СΪ��%dBytes",status.m_size);
		GetDlgItem(IDC_FILESIZE)->SetWindowText(strsize);
	}	
}

void CFilePartitionDlg::OnAddDir() 
{
	BROWSEINFO bi;   
	char buffer[MAX_PATH];   
	ZeroMemory(buffer,MAX_PATH);   
	bi.hwndOwner=GetSafeHwnd();   
	bi.pidlRoot=NULL;   
	bi.pszDisplayName=buffer;   
	bi.lpszTitle="ѡ��һ���ļ���";   
	bi.ulFlags=BIF_EDITBOX;   
	bi.lpfn=NULL;   
	bi.lParam=0;   
	bi.iImage=0; 
	LPITEMIDLIST pList=NULL;   
	if((pList=SHBrowseForFolder(&bi))!=NULL)   
	{   
		char path[MAX_PATH];
		ZeroMemory(path,MAX_PATH);
		SHGetPathFromIDList(pList,path);
		GetDlgItem(IDC_EDSAVEPATH)->SetWindowText(path);
	}
}

void CFilePartitionDlg::OnPartition() 
{
	CFile *readfile,*writefile;
	DWORD filelen,readlen,poslen;
	CString name,path,desname;
	//��ý�Ҫ�ָ���ļ���ȫ·��
	GetDlgItem(IDC_EDFILEPATH)->GetWindowText(name);
	//��÷ָ���ļ��Ĵ��·��
	GetDlgItem(IDC_EDSAVEPATH)->GetWindowText(path);
	CString strsize;
	//����ļ��ָ��Ĵ�С
	GetDlgItem(IDC_EDSIZE)->GetWindowText(strsize);
	if(strsize.IsEmpty())return;

	DWORD partsize=atoi(strsize)*1024;
	BYTE *b=new BYTE[partsize];
	readfile=new CFile(name,CFile::modeRead);
	filelen=readfile->GetLength();
	int i=1;
	//��ѭ���и����ļ��Ĵ�С���û��趨�Ĵ�С���������ļ��������ļ���д������
	while(1)
	{
		ZeroMemory(b,partsize);
		desname.Format("%s\\%spart%d_%s.dat",path,filenamenoext,i,filenameext);
		//�����ļ���
		HANDLE hfile=::CreateFile(desname,GENERIC_WRITE|GENERIC_WRITE,
			0,0,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,0);
		CloseHandle(hfile);
		writefile=new CFile(desname,CFile::modeWrite);
		readlen=readfile->Read(b,partsize);
		poslen=readfile->GetPosition();
		writefile->Write(b,readlen);
		writefile->Close();
		i++;
		if(poslen==filelen)break;
	}
	readfile->Close();
	delete writefile;
	delete readfile;
	//����INI�ļ���·��
	//char buf[128];
	//::GetCurrentDirectory(128,buf);
	CString inifile,pageend,size;
	inifile.Format("%s\\%s.ini",path,filenamenoext);
	size.Format("%d",filelen);
	pageend.Format("%d",i);
	//��ԭ���ļ�����Ϣ���ָ����ļ���д�뵽INI�ļ���
	::WritePrivateProfileString("FilePartition","name",filenamenoext,inifile);
	::WritePrivateProfileString("FilePartition","ext",filenameext,inifile);
	::WritePrivateProfileString("FilePartition","pageend",pageend,inifile);
	::WritePrivateProfileString("FilePartition","size",size,inifile);
	AfxMessageBox("�ָ�ɹ�");
}

void CFilePartitionDlg::OnSelectPart() 
{
	CFileDialog log(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|
		OFN_ALLOWMULTISELECT,"INI�ļ�(*.ini)|*.ini||",NULL);
	if(log.DoModal()==IDOK)
	{
		CString ininame=log.GetPathName();
		GetDlgItem(IDC_EDINI)->SetWindowText(ininame);
	}	
}

void CFilePartitionDlg::OnOmbin() 
{
	CFile *readfile,*writefile;
	CString ininame,inidir;
	//��÷ָ��ļ�ʱ���ɵ�INI�ļ�
	GetDlgItem(IDC_EDINI)->GetWindowText(ininame);
	//���INI�ļ�����Ŀ¼
	inidir=FindPath(ininame);
	//��÷ָ�ǰ�ļ���Ϣ����������ţ��ļ���������չ��������չ�������С
	char pagenum[128],pagename[128],pageext[128],size[128];
	::GetPrivateProfileString("FilePartition","name","",pagename,128,ininame);
	::GetPrivateProfileString("FilePartition","ext","",pageext,128,ininame);
	::GetPrivateProfileString("FilePartition","pageend","",pagenum,128,ininame);
	::GetPrivateProfileString("FilePartition","size","",size,128,ininame);
	int pagecount=atoi(pagenum);
	CString desname; //�ϲ����ļ�����·��
	CString srcname; //�ϲ����ļ���·��
	desname.Format("%s\\%s.%s",inidir,pagename,pageext);
	HANDLE hfile=::CreateFile(desname,GENERIC_WRITE|GENERIC_WRITE,
			0,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
	CloseHandle(hfile);
	writefile=new CFile(desname,CFile::modeWrite);
	for(int i=1;i<pagecount;i++)
	{
		srcname.Format("%s\\%spart%d_%s.dat",inidir,pagename,i,pageext);
		readfile=new CFile(srcname,CFile::modeRead);
		DWORD filelen=readfile->GetLength();
		BYTE *b=new BYTE[filelen];
		readfile->Read(b,filelen);
		writefile->Write(b,filelen);
		readfile->Close();
		delete b;
	}
	writefile->Close();
	delete writefile;
	delete readfile;
	AfxMessageBox("�ϲ����");
}

void CFilePartitionDlg::OnChangeEdfilepath() 
{
	CString desdirname,temp;
	GetDlgItem(IDC_EDFILEPATH)->GetWindowText(desdirname);
	int pos=desdirname.Find(filename);
	desdirname=desdirname.Left(pos-1);
	GetDlgItem(IDC_EDSAVEPATH)->SetWindowText(desdirname);
}

CString CFilePartitionDlg::FindPath(CString path)
{
	CString strpathname; //�ļ����ڵ�·��
	CString strtemp;     //����ȫ·��
	strtemp=path;
	int pos;
	int leftpos=0; 
	pos=strtemp.Find("\\");
	while(pos!=-1)
	{
		leftpos+=pos;
		leftpos++;
		strtemp=strtemp.Right(strtemp.GetLength()-pos-1);
		pos=strtemp.Find("\\");
	}
	strpathname=path.Left(leftpos);
	return strpathname;

}
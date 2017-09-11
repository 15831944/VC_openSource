// CartSet.cpp : implementation file
//

#include "stdafx.h"
#include "CheckAttendance.h"
#include "CartSet.h"

#include "CheckAttendanceDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCartSet dialog
extern _ConnectionPtr m_pCon;
extern	_RecordsetPtr m_pRecord;

CCartSet::CCartSet(CWnd* pParent /*=NULL*/)
	: CDialog(CCartSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCartSet)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_IsWrite = FALSE;
}


void CCartSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCartSet)
	DDX_Control(pDX, IDC_WRITE, m_Write);
	DDX_Control(pDX, IDC_CARDID, m_Card);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCartSet, CDialog)
	//{{AFX_MSG_MAP(CCartSet)
	ON_BN_CLICKED(IDC_GENERATEID, OnGenerateid)
	ON_BN_CLICKED(IDC_WRITE, OnWrite)
	ON_BN_CLICKED(IDC_REFRESHCARD, OnRefreshcard)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCartSet message handlers

void CCartSet::OnGenerateid() 
{
	if (m_IsWrite==TRUE)
	{
		CString sql = "select max(ICID) as ID from ICID";
		
		m_pRecord = m_pCon->Execute((_bstr_t)sql,NULL,-1);
		CString sID = "";
		BOOL isNULL = FALSE;
		try
		{
			sID = (char*)(_bstr_t)m_pRecord->GetFields()->GetItem("ID")->Value;
			
		}
		catch(_com_error &e)
		{
			isNULL = TRUE;
		
		}
		if (isNULL)
				sID = "IC-001";
		else
		{
   			CString sTemp =sID;
			int pos = sID.Find("-",0);
			CString sInt = sID.Right(pos+1);
			int ID = atoi(sInt);
			ID+=1;
			sTemp.Format("%i",ID);
			switch (sTemp.GetLength())
			{
			case 1:{
						sID = "IC-00"+sTemp;
						break;
				   }
			case 2:{
						sID = "IC-0"+sTemp;
						break;
				 }
			default:
				{
						sID = "IC-"+sTemp;
						break;
				}
			}
		}
		m_Card.SetWindowText(sID);
		m_Write.EnableWindow();
	}
	else
	{
		MessageBox("��ǰIC������û����֤���룬IC������д��");
	}
}

BOOL CCartSet::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	

	CCheckAttendanceDlg* pDlg = (CCheckAttendanceDlg*)AfxGetMainWnd();
	m_icdev  = pDlg->icdev;	
	OnRefreshcard() ;	
	return TRUE; 
}

void CCartSet::OnWrite() 
{
	if (MessageBox("ȷʵҪд��������","��ʾ",MB_YESNO)==IDYES)
	{
		CString str;
		m_Card.GetWindowText(str);
		if (str.IsEmpty())
		{
			MessageBox("����������");
			return;
		}
		if (str.GetLength()>224)
		{
			MessageBox("д�����ݲ��ܳ���224���ַ�","��ʾ",64);
			return;
		}

		__int16 result;
		//�����ݿ��в�������
		m_pCon->BeginTrans();
		
		CString sql;
		sql.Format("insert into ICID values ('%s')",str);
		try
		{
			m_pCon->Execute((_bstr_t)sql,NULL,-1);

			//��IC����Ӧ������д������
			result =swr_4442(m_icdev,33,str.GetLength(),(unsigned char*)str.GetBuffer(0));
				
			if (result==0)
			{
				m_pCon->CommitTrans();
				MessageBox("����д��ɹ�.","��ʾ",64);
			}
			else
			{
				m_pCon->RollbackTrans();
				MessageBox("����д��ʧ��.","��ʾ",64);
			}
		}
		catch(...)
		{
			m_pCon->RollbackTrans();
			MessageBox("����ʧ��");
			return;
		
		}
		m_Write.EnableWindow(FALSE);
		m_Card.SetWindowText("");
	}
}

void CCartSet::OnRefreshcard() 
{
	m_IsWrite = TRUE;	
	//��ȡID��״̬
	__int16 status = -1;
	
	__int16 result =get_status(m_icdev,&status);

	if (result<0)
	{
		MessageBox("��ȡIC��״̬����");
		m_IsWrite = FALSE;
	}
	else if ((result==0)&&(status==0))
	{
		MessageBox("�����ID��");
		m_IsWrite = FALSE;
	}
	//������4442IC����������Ϊffffff
	unsigned char pass[3]={0xff,0xff,0xff};
	//��֤����
	__int16 rpass =csc_4442(m_icdev,3,pass);
	if (rpass<0)
	{
		MessageBox("IC������˶Դ���,ֻ�ܶ�ȡ����");
		m_IsWrite = FALSE;
	}	
	
}

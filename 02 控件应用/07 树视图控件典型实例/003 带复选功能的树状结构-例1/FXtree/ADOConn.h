// ADOConn.h: interface for the ADOConn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADOCONN_H__A22F5A67_CEF8_49E8_8E84_61E23D66B409__INCLUDED_)
#define AFX_ADOCONN_H__A22F5A67_CEF8_49E8_8E84_61E23D66B409__INCLUDED_
#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","adoEOF")rename("BOF","adoBOF")

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ADOConn  
{
public:
	//���һ��ָ��Connection�����ָ��
    _ConnectionPtr m_pConnection;
	//���һ��ָ��Recordset�����ָ��
	_RecordsetPtr m_pRecordset;
public:
	ADOConn();
	virtual ~ADOConn();

	//��ʼ��--�������ݿ�
    void OnInitADOConn();
	//ִ�в�ѯ
    _RecordsetPtr& GetRecordSet(_bstr_t bstrSQL);
	//ִ��SQL���
    BOOL ExecuteSQL(_bstr_t bstrSQL);
	//�Ͽ����ݿ�����
	void ExitConnect();
};

#endif // !defined(AFX_ADOCONN_H__A22F5A67_CEF8_49E8_8E84_61E23D66B409__INCLUDED_)

#include "ExportClass.h"
#include "windows.h"//ʹ����MessageBox��������Ҫ�����ͷ�ļ�����
//���Լ��
int CMath::GetMaxCommDiv(int a,int b)
{
	int x=1;//a,b���������Ľ��
	int ires;//����ṹ
    if(a<b)
	{
		MessageBox(NULL,"a����С��b","����",MB_OK);
		return 0;
	}
	if(b==0)
	{
		MessageBox(NULL,"b����Ϊ0","����",MB_OK);
		return 0;
	}
    while(x!=0)
	{
		x=a%b;
        a=b;
		ires=b;
		b=x;
	}
	return ires;
}
//��С������
int CMath::GetMinCommMul(int a,int b)
{
	int x=1;//a,b���������Ľ��
	int ires;//������
	int m,n;//�洢��ʱ��a,bֵ
	m=a;n=b;
    if(a<b)
	{
		MessageBox(NULL,"a����С��b","����",MB_OK);
		return 0;
	}
	if(a==0)
	{
		MessageBox(NULL,"a����Ϊ0","����",MB_OK);
		return 0;
	}
	if(b==0)
	{
		MessageBox(NULL,"b����Ϊ0","����",MB_OK);
		return 0;
	}
	
    while(x!=0)
	{
		x=a%b;
        a=b;
		ires=b;
		b=x;
	}
	ires=(m*n)/(ires);
	return ires;
}
/*class CMath
{
public:
	int GetMaxCommDiv(int a,int b);//���Լ��
	int __declspec(dllexport)GetMinCommMul(int a,int b);//��С������
};*/
class __declspec(dllexport)CMath
{
public:
	int GetMaxCommDiv(int a,int b);//���Լ��
	int GetMinCommMul(int a,int b);//��С������
};
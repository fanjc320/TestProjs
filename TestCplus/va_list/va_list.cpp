// va_list.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <string>
#include <stdarg.h>
#include <iostream>
using namespace std;
//typedef atomic<unsigned long> atomic_ulong;
typedef unsigned __int64 uint64;
typedef unsigned __int32 uint32;
void logString(int level, const char * source, const char * str, va_list args)
{
	char content[1000];
	vsnprintf(content,1000,str,args);
	cout << "\nlogstring " << content << " ARGEND" << endl;

}
void outDebug(int i, const char * source, const char * str, ...)
{
	try
	{
			va_list ap;
			va_start(ap, str);
			logString(1, source, str, ap);
			va_end(ap);
	}
	catch (...)
	{

	}
}


uint32 GetPendings() {
	return 1;
}

uint64 GetProducedCounts() {
	return 2;
}

uint64 GetConsumedCounts() {
	return 3;
}

int main()
{
	//outDebug(0, "logstring ", " :%u %u %u", GetPendings(), GetProducedCounts(), GetConsumedCounts());
	outDebug(0, "logstring1 ", " :%u %u %u", 1, 2, 3);
	//������x64����ȷ����x86�²���ȷ
	outDebug(0, "logstring2 ", " :%u %u %u", (uint32)1, (uint64)2, (uint64)3);
	outDebug(0, "logstring2 ", " :%u %u %u", (uint64)1, (uint64)2, (uint64)3);
	outDebug(0, "logstring2 ", " :%llu %llu %llu", (uint64)1, (uint64)2, (uint64)3);

	getchar();
    return 0;
}

string AppendString(string str1, ...)//һ�������ַ����ĺ����������������Զ�̬�仯
{
	string str = str1;//str��Ϊָ�����ͣ���Ϊva_arg�귵�ص�����Ĳ�����ָ�룬���������Ĳ���Ϊint�ȼ����ͣ��򲻱�Ϊָ�룬��Ϊ������ʵ���ϼ���ָ�롣
	string res;
	va_list marker;     //�����������
	va_start(marker, str1);//��ʼ�����marker����

	while (str != "ListEnd")//ListEnd:�����Ľ�����־��ʮ����Ҫ����ʵ����������ָ��
	{
		res += str;
		str = va_arg(marker, string);//ȡ����һ��ָ��
	}
	va_end(marker);//��������va_start����
	return res;
}

//int main()
//{
//	string    str = AppendString("xu", "zhi", "hong", "ListEnd");
//	cout << str.c_str() << endl;
//	return 0;
//}


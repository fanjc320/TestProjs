// va_list.cpp : 定义控制台应用程序的入口点。
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
	//以下在x64下正确，在x86下不正确
	outDebug(0, "logstring2 ", " :%u %u %u", (uint32)1, (uint64)2, (uint64)3);
	outDebug(0, "logstring2 ", " :%u %u %u", (uint64)1, (uint64)2, (uint64)3);
	outDebug(0, "logstring2 ", " :%llu %llu %llu", (uint64)1, (uint64)2, (uint64)3);

	getchar();
    return 0;
}

string AppendString(string str1, ...)//一个连接字符串的函数，参数个数可以动态变化
{
	string str = str1;//str需为指针类型，因为va_arg宏返回的是你的参数的指针，但是如果你的参数为int等简单类型，则不必为指针，因为变量名实际上即是指针。
	string res;
	va_list marker;     //你的类型链表
	va_start(marker, str1);//初始化你的marker链表

	while (str != "ListEnd")//ListEnd:参数的结束标志，十分重要，在实际中需自行指定
	{
		res += str;
		str = va_arg(marker, string);//取得下一个指针
	}
	va_end(marker);//结束，与va_start合用
	return res;
}

//int main()
//{
//	string    str = AppendString("xu", "zhi", "hong", "ListEnd");
//	cout << str.c_str() << endl;
//	return 0;
//}


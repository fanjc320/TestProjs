// ConsoleApplication4.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


#include <iostream>
#include <windows.h>
#include <sysinfoapi.h>
using namespace std;

typedef unsigned __int64 uint64;

int main()
{
	int i = 0;
	uint64 begin = GetTickCount64();
	while (++i<100)
	{
		uint64 tick = GetTickCount64();
		cout << "tick:"<<tick << endl;
	}
	uint64 end = GetTickCount64();
	cout << "end-begin:" << end - begin << endl;
	getchar();
	return 0;
}


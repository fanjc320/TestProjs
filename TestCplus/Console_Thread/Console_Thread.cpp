// Console_Thread.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using std::cout;

#include <windows.h>
#include "Master.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Master sMaster(_T("Crossgate_GameWorld"));
	if (argc > 1)
	{
		if (_tcscmp(argv[1], _T("PC")) == 0) {//以控制台的方式运行			
			sMaster.Run();
			return 0;
		}
	}
	else
	{
		//以服务的方式运行		
		sMaster.RunAsService();
	}
	return 0;
}

//int main()
//{
//	SetConsoleOutputCP(65001);
//
//	cout << "是否\n\n测试测试";
//	getchar();
//
//	return 0;
//}


// Console_Thread.cpp : �������̨Ӧ�ó������ڵ㡣
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
		if (_tcscmp(argv[1], _T("PC")) == 0) {//�Կ���̨�ķ�ʽ����			
			sMaster.Run();
			return 0;
		}
	}
	else
	{
		//�Է���ķ�ʽ����		
		sMaster.RunAsService();
	}
	return 0;
}

//int main()
//{
//	SetConsoleOutputCP(65001);
//
//	cout << "�Ƿ�\n\n���Բ���";
//	getchar();
//
//	return 0;
//}


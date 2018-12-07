// smartPointer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int main()
{
	//TestSharePtr();
	std::cout << "----------------------------" << endl;
	TestUniquePtr();

	std::cout << "============================" << endl;
	//TestShareFromThis();
	std::cout << "========-----------=========" << endl;
	//TestSharedPtrCrossReference();

	//TestPoint2Add();

	getchar();
    return 0;
}


// lambda.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
using namespace std;

void fcn()
{
	size_t v1 = 42;
	auto f2 = [&v1] {return ++v1; };
	v1 = 0;
	auto j = f2();
	cout << j << endl;//1
}

int main()
{
	fcn();
	getchar();
    return 0;
}


// ConsoleApplication3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <unordered_map>
#include <windows.h>
#include <tchar.h>
#include <algorithm>
#include <stdio.h>
#include <stdarg.h>
#include <string>

using namespace std;

int mon_log(char* format, ...)
{
	char str_tmp[50];
	int i = 0;
	va_list vArgList;                            //定义一个va_list型的变量,这个变量是指向参数的指针.
	va_start(vArgList, format);                 //用va_start宏初始化变量,这个宏的第二个参数是第一个可变参数的前一个参数,是一个固定的参数
	i = _vsnprintf_s(str_tmp, 50, format, vArgList); //注意,不要漏掉前面的_
	va_end(vArgList);                            //用va_end宏结束可变参数的获取
	return i;                                    //返回参数的字符个数中间有逗号间隔
}

int main()
{
	{
		//64位过大，赋值给32位，会被截断
		unsigned long long tick = 50LL * 24L * 3600L * 1000L;
		unsigned long long tick1 = 50 * 24 * 3600 * 1000;
		unsigned int begin = tick;
		tick = tick + 10 * 60 * 1000;
		unsigned int s = (tick - begin) / 1000;
		cout << begin << " " << s << endl;


		int* p = new int;
		delete p;
		cout << "p: " << p << endl;

		float testf = 0.51f;
		float testf1 = 0.51f;
		cout << "floatf " << (unsigned int)testf << testf - testf1 << " " << bool(testf == testf1) << endl;

		unordered_map<int, int> testu;
		for (int i = 1; i < 100; i++)
		{
			testu[i] = 100 + i;
		}

	}
	/*
	string t1 = "你好";
	//MessageBox(NULL, _T(t1.c_str()), _T("哈哈"), MB_OKCANCEL | MB_ICONERROR);
	MessageBox(NULL, _T("好帅"), _T("哈哈"), MB_OKCANCEL | MB_ICONERROR);
	MessageBox(NULL, _T("好帅"), _T("哈哈"), MB_OKCANCEL | MB_ICONERROR);
	*/
	
	{
		//无符号与有符号比较问题
		unsigned int a = 1;
		unsigned int b = 2;
		int c = a - b;
		cout << "c:" << c << endl;

		int d = max(a, c);
		int e = max(b, a - b);
		int f = max(-1, a);
		int g = max(-1, 1);
		//无符号不能和有符号比较
		cout << "d:" << d << " e:" << e << " f:" << f << " g:" << g << endl;

		int i = mon_log("%s,%d,%d,%d", "asd", 2, 3, 4);
		printf("%d\n", i);

		int h = -1;

		cout << "unsigned int h:" << (unsigned int)h << endl;
		printf("pirntf h:%d h:%u \n", h, h);
		unsigned int k = unsigned int(h);
		unsigned int m = h;
		cout << "i:" << k << " " << m << endl;
		//千万注意有符号和无符号的比较问题
		//if (h < 10)
		int n[] = { 1,2,3 };
		if (h < sizeof(a))
			cout << "h<" << endl;
		else
			cout << "h>" << endl;
	}

	{
		//最小整数取相反数溢出
		int a = 0xffffffff;
		if (a < 0)
		{
			printf("1 a = %d\n", a);
			a = -a;
			printf("2 a = %d\n", a);
		}
		else if (a == 0xffffffff)
			printf("3 a = %d\n", a);
		printf("4 a = %d \n",a);

		//分析：有符号的数据类型，有正负之分，如int，double,float...溢出后去反，得到a = 1
		//解决：对int数据类型进行去反处理时候，需要额外处理这种情况，添加以下代码：
	}

	{
		//cin>>和 getline 混用导致的奇怪问题
		//输出：b 的 值无法输入
		//解决：将注释那句激活
		int a;
		string b;
		cout << "Please input a:" << endl;
		std::cin >> a;
		//  cin.ignore();   //默认cin::ignore（1，EOF）

		cout << "Please input b:" << endl;
		std::getline(cin, b);

		cout << "a:" << a << endl;
		cout << "b:" << b << endl;

		return 0;
	}

	getchar();
	return 0;
}


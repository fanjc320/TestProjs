// ConsoleApplication3.cpp : �������̨Ӧ�ó������ڵ㡣
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
	va_list vArgList;                            //����һ��va_list�͵ı���,���������ָ�������ָ��.
	va_start(vArgList, format);                 //��va_start���ʼ������,�����ĵڶ��������ǵ�һ���ɱ������ǰһ������,��һ���̶��Ĳ���
	i = _vsnprintf_s(str_tmp, 50, format, vArgList); //ע��,��Ҫ©��ǰ���_
	va_end(vArgList);                            //��va_end������ɱ�����Ļ�ȡ
	return i;                                    //���ز������ַ������м��ж��ż��
}

int main()
{
	{
		//64λ���󣬸�ֵ��32λ���ᱻ�ض�
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
	string t1 = "���";
	//MessageBox(NULL, _T(t1.c_str()), _T("����"), MB_OKCANCEL | MB_ICONERROR);
	MessageBox(NULL, _T("��˧"), _T("����"), MB_OKCANCEL | MB_ICONERROR);
	MessageBox(NULL, _T("��˧"), _T("����"), MB_OKCANCEL | MB_ICONERROR);
	*/
	
	{
		//�޷������з��űȽ�����
		unsigned int a = 1;
		unsigned int b = 2;
		int c = a - b;
		cout << "c:" << c << endl;

		int d = max(a, c);
		int e = max(b, a - b);
		int f = max(-1, a);
		int g = max(-1, 1);
		//�޷��Ų��ܺ��з��űȽ�
		cout << "d:" << d << " e:" << e << " f:" << f << " g:" << g << endl;

		int i = mon_log("%s,%d,%d,%d", "asd", 2, 3, 4);
		printf("%d\n", i);

		int h = -1;

		cout << "unsigned int h:" << (unsigned int)h << endl;
		printf("pirntf h:%d h:%u \n", h, h);
		unsigned int k = unsigned int(h);
		unsigned int m = h;
		cout << "i:" << k << " " << m << endl;
		//ǧ��ע���з��ź��޷��ŵıȽ�����
		//if (h < 10)
		int n[] = { 1,2,3 };
		if (h < sizeof(a))
			cout << "h<" << endl;
		else
			cout << "h>" << endl;
	}

	{
		//��С����ȡ�෴�����
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

		//�������з��ŵ��������ͣ�������֮�֣���int��double,float...�����ȥ�����õ�a = 1
		//�������int�������ͽ���ȥ������ʱ����Ҫ���⴦�����������������´��룺
	}

	{
		//cin>>�� getline ���õ��µ��������
		//�����b �� ֵ�޷�����
		//�������ע���Ǿ伤��
		int a;
		string b;
		cout << "Please input a:" << endl;
		std::cin >> a;
		//  cin.ignore();   //Ĭ��cin::ignore��1��EOF��

		cout << "Please input b:" << endl;
		std::getline(cin, b);

		cout << "a:" << a << endl;
		cout << "b:" << b << endl;

		return 0;
	}

	getchar();
	return 0;
}


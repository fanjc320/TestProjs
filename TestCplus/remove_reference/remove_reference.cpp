// remove_reference.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
using namespace std;

//int main()
//{
//
//	int a[] = { 1,2,3 };
//	//decltype(*a) b = a[0];
//	decltype(a[1]) b = a[0];
//	a[0] = 4;
//	cout << b; //���4
//	getchar();
//	return 0;
//}
//���Ϊ4, ��Ϊdecltype(*a)����*a������, ʵ������һ��int&, ���Ǿ�����û�а취ȥ���������

//template <typename T>
//class remove_reference
//{
//public:
//	typedef T type;
//};
//
//int main()
//{
//
//	int a[] = { 1,2,3 };
//	remove_reference<decltype(*a)>::type b = a[0];
//	a[0] = 4;
//	cout << b; //���4��,
//	return 0;
//}

//������������remove_reference�����Ƴ�����, �ڱ����ڼ�, �Ƶ���������TΪint&,
//typedef T type��, typeʵ���Ͼ�������int&, ��˽������4


//template <typename T>
//class remove_reference
//{
//public:
//	typedef T type;
//};

//template<typename T>
//class remove_reference<T&>
//{
//public:
//	typedef T type;
//};

int main()
{

	int a[] = { 1,2,3 };
	remove_reference<decltype(*a)>::type b = a[0];
	a[0] = 4;
	cout << b; //���1
	getchar();
	return 0;
}

//���Ƕ�ģ��������ػ�, �ػ�Ϊ����, ��TΪint&ʱ, ������ʵ�ʵ�TΪint, ����������Ƴ��Ĺ���


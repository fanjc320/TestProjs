// remove_reference.cpp : 定义控制台应用程序的入口点。
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
//	cout << b; //输出4
//	getchar();
//	return 0;
//}
//输出为4, 因为decltype(*a)返回*a的类型, 实际上是一个int&, 我们就想有没有办法去掉这个引用

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
//	cout << b; //输出4中,
//	return 0;
//}

//我们引入了类remove_reference用于移除引用, 在编译期间, 推导出了类型T为int&,
//typedef T type中, type实际上就是类型int&, 因此结果还是4


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
	cout << b; //输出1
	getchar();
	return 0;
}

//我们对模版类进行特化, 特化为引用, 当T为int&时, 在类内实际的T为int, 完成了引用移除的功能


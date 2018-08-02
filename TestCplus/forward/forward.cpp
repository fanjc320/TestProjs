// forward.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

template<class T>
void wrapper(T&& arg)
{
	//foo(std::forward<T>(arg)); // Forward a single argument.
}

//If a call to wrapper() passes an rvalue std::string, then T is deduced to std::string(not std::string&, const std::string&, or std::string&&), and std::forward ensures that an rvalue reference is passed to foo.
//If a call to wrapper() passes a const lvalue std::string, then T is deduced to const std::string&, and std::forward ensures that a const lvalue reference is passed to foo.
//If a call to wrapper() passes a non - const lvalue std::string, then T is deduced to std::string&, and std::forward ensures that a non - const lvalue reference is passed to foo.

#include <iostream>
#include <memory>
#include <utility>
#include <array>

struct A {
	A(int&& n) { std::cout << "rvalue overload, n=" << n << "\n"; }
	A(int& n) { std::cout << "lvalue overload, n=" << n << "\n"; }
};

class B {
public:
	template<class T1, class T2, class T3>
	B(T1&& t1, T2&& t2, T3&& t3) :
		a1_{ std::forward<T1>(t1) },
		a2_{ std::forward<T2>(t2) },
		a3_{ std::forward<T3>(t3) }
	{
	}

private:
	A a1_, a2_, a3_;
};

template<class T, class U>
std::unique_ptr<T> make_unique1(U&& u)
{
	return std::unique_ptr<T>(new T(std::forward<U>(u)));
}

template<class T, class... U>
std::unique_ptr<T> make_unique(U&&... u)
{
	return std::unique_ptr<T>(new T(std::forward<U>(u)...));
}

void overloaded(const int& x) { std::cout << "[lvalue]"; }
void overloaded(int&& x) { std::cout << "[rvalue]"; }

// function template taking rvalue reference to deduced type:
template <class T> void fn(T&& x) {
	overloaded(x);                   // always an lvalue
	overloaded(std::forward<T>(x));  // rvalue if argument is rvalue
}

//testR(a) ok
//����T&& ��˵����https://images2015.cnblogs.com/blog/642223/201603/642223-20160316184942881-1173419133.png
//��Ҫ��T&& ��Ϊ��int&&��,�漰�����۵�������
template <class T> void testR(T&& x) {
	//����	C2062	��������͡�int &��
	//std::cout << "testR: type: " << decltype(x) << " " << x << std::endl;
	std::cout << "testR: type: " << x << std::endl;
}


//testR(a) ����	C2664	��void testR(int &&)��: �޷������� 1 �ӡ�int��ת��Ϊ��int &&��	
void testR(int&& x) {
	//������ʹ��������
	//std::cout << "int testR: type: " << decltype(x) << " " << x << std::endl;
	std::cout << "int testR: type: " << x << std::endl;
}

int main()
{
	auto p1 = make_unique1<A>(2); // rvalue
	int i = 1;
	auto p2 = make_unique1<A>(i); // lvalue

	std::cout << "B\n";
	auto t = make_unique<B>(2, i, 3);

	std::cout << "-----------------------------------" << std::endl;

	int a=1;

	std::cout << "calling fn with lvalue: ";
	fn(a);
	std::cout << '\n';

	std::cout << "calling fn with rvalue: ";
	fn(0);
	std::cout << '\n';

	std::cout << "calling testR begin------------ " << std::endl;
	testR(a);
	testR(1);
	std::cout << "calling testR end------------ " << std::endl;


	getchar();
	return 0;
}
//�����
//rvalue overload, n = 2
//lvalue overload, n = 1
//B
//rvalue overload, n = 2
//lvalue overload, n = 1
//rvalue overload, n = 3

//��󣬼�ס��
//������T&&����ֵ���á���ֵ���ã�std::forward���ᰴ��ԭ������������ת��
// Tuple.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <tuple>
#include <type_traits>
#include <utility>
#include <iostream>
//tuple��һ���̶���С�Ĳ�ͬ����ֵ�ļ��ϣ��Ƿ�����std::pair����c#�е�tuple���ƣ�
//���Ǳ�c#�е�tupleǿ��öࡣ����Ҳ���԰�������һ��ͨ�õĽṹ�����ã�����Ҫ�����ṹ���ֻ�ȡ�ṹ���������
//��ĳЩ����¿���ȡ���ṹ��ʹ�������ֱ࣬�ۡ�

//�����÷�
//����һ��tuple
//tuple<const char*, int>tp = make_tuple(sendPack, nSendSize); //����һ��tuple
//���tuple�ȼ���һ���ṹ��
//struct A
//{
//	char* p;
//	int len;
//};
//��tuple<const char*, int>tp�Ϳ��Բ��ô�������ṹ���ˣ���������һ���ģ��ǲ��Ǹ����ֱ���ˡ�

//��������
//(10, Test, 3.14, Foo, bar, 10, Test, 3.14, 10)

//������tuple���÷��������ˣ��ǲ��Ǻܼ򵥣�Ҳ������ʹ�ã�������ʹ����֮����벻�����ˡ�
//��ǰ��˵��tuple�Ǽ�Լ�����򵥡����кܶ�߼����÷���
//����ģ��Ԫ��ϵ����, Ҫ�������ĸ߼��÷���ʱ�򣬶�����Ҫһ����ģ��Ԫ������
//�����ֻ�ǰ�����һ�����͵�pairȥʹ��ʱ���ⲿ�ֿ��Բ�����������������߼��÷���ʱ������¿���������Ҫ�����ҿ�tuple���ص���ɴ��
//tuple�ĸ߼��÷�
//��ȡtuple��ĳ��λ��Ԫ�ص�����
//ͨ��std::tuple_element��ȡԪ�����͡�

template<typename Tuple>
void Fun(Tuple& tp)
{
	std::tuple_element<0, Tuple>::type first = std::get<0>
		(mytuple);
	std::tuple_element<1, Tuple>::type second = std::get<1>
		(mytuple);
}

//��ȡtuple��Ԫ�صĸ�����
//tuple t;
//
//int size = std::tuple_size<decltype(t)) > ::value;

//����tuple�е�ÿ��Ԫ��
//��Ϊtuple�Ĳ����Ǳ䳤�ģ�Ҳû��for_each������������������tuple�е�ÿ��Ԫ�أ���Ҫ�Լ�д����ʵ�֡�������Ҫ��ӡtuple�е�ÿ��Ԫ�ء�

template<class Tuple, std::size_t N>
struct TuplePrinter {
	static void print(const Tuple& t)
	{
		TuplePrinter<Tuple, N - 1>::print(t);
		std::cout << ", " << std::get<N - 1>(t);
	}
};

template<class Tuple>
struct TuplePrinter<Tuple, 1> {
	static void print(const Tuple& t)
	{
		std::cout << std::get<0>(t);
	}
};

template<class... Args>
void PrintTuple(const std::tuple<Args...>& t)
{
	std::cout << "(";
	TuplePrinter<decltype(t), sizeof...(Args)>::print(t);
	std::cout << ")\n";
}

//����tupleԪ��ֵ��ȡ���Ӧ������λ��
namespace detail
{
	template<int I, typename T, typename... Args>
	struct find_index
	{
		static int call(std::tuple<Args...> const& t, T&& val)
		{
			return (std::get<I - 1>(t) == val) ? I - 1 :
				find_index<I - 1, T, Args...>::call(t, std::forward<T>(val));
		}
	};

	template<typename T, typename... Args>
	struct find_index<0, T, Args...>
	{
		static int call(std::tuple<Args...> const& t, T&& val)
		{
			return (std::get<0>(t) == val) ? 0 : -1;
		}
	};
}

template<typename T, typename... Args>
int find_index(std::tuple<Args...> const& t, T&& val)
{
	return detail::find_index<0, sizeof...(Args)-1, T, Args...>::
		call(t, std::forward<T>(val));
}

int main()
{
	std::tuple<int, int, int, int> a(2, 3, 1, 4);
	std::cout << find_index(a, 1) << std::endl; // Prints 2
	std::cout << find_index(a, 2) << std::endl; // Prints 0
	std::cout << find_index(a, 5) << std::endl; // Prints -1 (not found)


}

//չ��tuple������tupleԪ����Ϊ�����Ĳ����������Ϳ��Ը�����Ҫ��tupleԪ�ؽ��д�����



template<size_t N>
struct Apply {
	template<typename F, typename T, typename... A>
	static inline auto apply(F && f, T && t, A &&... a)
		-> decltype(Apply<N - 1>::apply(
			::std::forward<F>(f), ::std::forward<T>(t),
			::std::get<N - 1>(::std::forward<T>(t)),
			::std::forward<A>(a)...
		))
	{
		return Apply<N - 1>::apply(::std::forward<F>(f),
			::std::forward<T>(t),
			::std::get<N - 1>(::std::forward<T>(t)),
			::std::forward<A>(a)...
		);
	}
};

template<>
struct Apply<0> {
	template<typename F, typename T, typename... A>
	static inline auto apply(F && f, T &&, A &&... a)
		-> decltype(::std::forward<F>(f)
		(::std::forward<A>(a)...))
	{
		return ::std::forward<F>(f)(::std::forward<A>
			(a)...);
	}
};

template<typename F, typename T>
inline auto apply(F && f, T && t)
-> decltype(Apply< ::std::tuple_size<
	typename ::std::decay<T>::type
>::value>::apply(::std::forward<F>(f),
	::std::forward<T>(t)))
{
	return Apply< ::std::tuple_size<
		typename ::std::decay<T>::type
	>::value>::apply(::std::forward<F>(f),
		::std::forward<T>(t));
}

void one(int i, double d)
{
	std::cout << "function one(" << i << ", " << d <<
		");\n";
}
int two(int i)
{
	std::cout << "function two(" << i << ");\n";
	return i;
}

//���Դ���
int main()
{
	std::tuple<int, double> tup(23, 4.5);
	apply(one, tup);

	int d = apply(two, std::make_tuple(2));

	return 0;
}

//���������ش�Ҷ�tuple����һ��ȫ�����ʶ�˰ɣ���ô�������Ǽ�Լ�����򵥰ɡ�
//��ģ��Ԫ����Ϥ��ͯЬ���Բ���tuple�߼��÷����֣���ҪΪ��������׽����û�µģ��߼�����һ���ò�����֪�������÷��͹����ˡ�
//tuple��vector�Ƚϣ�
//vectorֻ������ͬһ�����͵����ݣ�tuple���������������͵����ݣ�
//vector��variant�Ƚϣ�
//���߶��������ɲ�ͬ���͵����ݣ�����variant�����͸����ǹ̶��ģ���tuple�����͸������ǹ̶��ģ��Ǳ䳤�ģ���Ϊǿ��


int main()
{
	std::tuple<int, std::string, float> t1(10, "Test",
		3.14);
	int n = 7;
	auto t2 = std::tuple_cat(t1, std::make_pair("Foo",
		"bar"), t1, std::tie(n));
	n = 10;
	print(t2);

	//����һ�ַ���Ҳ���Դ���Ԫ�飬��std::tie�����ᴴ��һ��Ԫ�����ֵ���á�

	auto tp = return std::tie(1, "aa", 2);
	//tp������ʵ���ǣ�
	std::tuple<int&, string&, int&>
		//�ٿ�����λ�ȡ����ֵ��
		const char* data = tp.get<0>(); //��ȡ��һ��ֵ
	int len = tp.get<1>(); //��ȡ�ڶ���ֵ
						   //����һ�ַ���Ҳ���Ի�ȡԪ���ֵ��ͨ��std::tie���tuple
	int x, y;
	string a;
	std::tie(x, a, y) = tp;
	//ͨ��tie�����tp������ֵ���Զ���ֵ������������
	//���ʱ���������ֻ���ĳ��λ�õ�ֵʱ��������std::ignoreռλ������ʾ����ĳ��λ�õ�ֵ����������ֻ��������ֵʱ��
	std::tie(std::ignore, std::ignore, y) = tp; //ֻ�������ֵ��
												//����һ��������ֵ������Ԫ�鷽����forward_as_tuple��
	std::map<int, std::string> m;
	m.emplace(std::forward_as_tuple(10, std::string(20, 'a')));
	//��ʵ���ϴ�����һ��������std::tuple<int&&, std::string&&>���͵�tuple��
	//���ǻ�����ͨ��tuple_cat���Ӷ��tupe
}
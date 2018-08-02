// Args_ellipsis.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <unordered_map>
using namespace std;

//�ݹ���ֹ����
void print() {
	cout << "empty" << endl;
}
//չ������
template <class T, class ...Args>
void print(T head, Args... rest)
{
	cout << "parameter " << head << endl;
	print(rest...);
}

//���������ÿһ��������ֱ��Ϊ��ʱ���empty��չ���������ĺ�����������
//һ���ǵݹ麯��������һ���ǵݹ���ֹ������������Args...��չ���Ĺ����еݹ�����Լ���
//ÿ����һ�β������еĲ����ͻ���һ����ֱ�����еĲ�����չ��Ϊֹ����û�в���ʱ������÷�ģ�庯��print��ֹ�ݹ���̡�
//�ݹ���õĹ����������� :
//
//print(1, 2, 3, 4); print(2, 3, 4); print(3, 4); print(4); print();
//����ĵݹ���ֹ����������д��������
//
//template <class T>void print(T t) { cout << t << endl; }
//�޸ĵݹ���ֹ�����������еĵ��ù����������ģ�
//
//print(1, 2, 3, 4); print(2, 3, 4); print(3, 4); print(4);
//��������չ�������һ������ʱ�ݹ�Ϊֹ��

template<typename T>T
sum(T t) { return t; }
template<typename T, typename ... Types>T
sum(T first, Types ... rest)
{
	return first + sum<T>(rest...);
}

template <class T>void printarg(T t)
{
	cout << t << endl;
}
template <class ...Args>
void expand(Args... args)
{
	int arr[] = {
		(printarg(args), 0)...
	};
}
//expand�����еĶ��ű��ʽ��(printarg(args), 0)��Ҳ�ǰ������ִ��˳��
//��ִ��printarg(args)���ٵõ����ű��ʽ�Ľ��0��ͬʱ���õ���C++11������һ�����ԡ�����ʼ���б�
//ͨ����ʼ���б�����ʼ��һ���䳤����, { (printarg(args), 0)... }
//����չ����((printarg(arg1), 0), (printarg(arg2), 0), (printarg(arg3), 0), etc...)��
//���ջᴴ��һ��Ԫ��ֵ��Ϊ0������int arr[sizeof...(Args)]�������Ƕ��ű��ʽ��
//�ڴ�������Ĺ����л���ִ�ж��ű��ʽǰ��Ĳ���printarg(args)��ӡ��������Ҳ����˵�ڹ���int����Ĺ����оͽ�������չ���ˣ�
//��������Ŀ�Ĵ�����Ϊ�������鹹��Ĺ���չ�������������ǿ��԰�����������ٽ�һ���Ľ�һ�£�
//��������Ϊ�������Ϳ���֧��lambda���ʽ�ˣ��Ӷ�������дһ���ݹ���ֹ�����ˣ�����������£�

template<class F, class... Args>
void expand1(const F& f, Args&&...args)
{  //�����õ�������ת������������ת�������߿��Բο���������һ�ڳ���Ա�е����¡�ͨ��4�д��뿴��ֵ���á�  
	initializer_list<int>
	{
		(f(std::forward< Args>(args)), 0)...
	};
}

int main()
{
	print(1, 2, 3, 4);
	sum(1, 2, 3, 4); //10
	expand(1, 2, 3, 4);

	expand1([](int i) {cout << i << endl; }, 10, 20, 30);
	//��������ӽ���ӡ��ÿ�����������������ʹ��C++14�������Է���lambda���ʽ�Ļ�������д��������lambda���ʽ�ˣ�
	expand1([](auto i) {cout << i << endl; }, 11, 12.0, "test");


	getchar();
    return 0;
}


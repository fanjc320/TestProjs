// lvalue_rvalue.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <vector>

//C++(���� C) �����еı��ʽ�ͱ���Ҫô����ֵ��Ҫô����ֵ��ͨ�׵���ֵ�Ķ�����Ƿ���ʱ������Щ�����ڶ��������ʹ�õĶ���
//���еı���������������壬�ڶ��������ж�����ʹ�ã�������ֵ����ֵ��ָ��ʱ�Ķ�������ֻ�ڵ�ǰ���������Ч���뿴����ʾ�� :
//�򵥵ĸ�ֵ���
//�磺int i = 0;
//����������У�i ����ֵ��0 ����ʱֵ��������ֵ��������Ĵ����У�i ���Ա����ã�0 �Ͳ������ˡ�������������ֵ��
//��ֵҲ���Գ����ڸ�ֵ���ʽ����ߣ����ǲ�����Ϊ��ֵ�Ķ�����Ϊ��ֵֻ�ڵ�ǰ�����Ч����ֵû�����塣
//�磺((i > 0) ? i : j) = 1;
//����������У�0 ��Ϊ��ֵ�������ˡ� = ������ߡ����Ǹ�ֵ������ i ���� j��������ֵ��
//�� C++11 ֮ǰ����ֵ�ǲ��ܱ����õģ�����޶Ⱦ����ó������ð�һ����ֵ���� :
//const int &a = 1;
//����������£���ֵ���ܱ��޸ĵġ�����ʵ������ֵ�ǿ��Ա��޸ĵģ���:
//T().set().get();
//T ��һ���࣬set ��һ������Ϊ T �е�һ��������ֵ��get ����ȡ�����������ֵ��������У�
//T() ����һ����ʱ���󣬾�����ֵ��set() �޸��˱�����ֵ��Ҳ���޸��������ֵ��
//��Ȼ��ֵ���Ա��޸ģ���ô�Ϳ���ʵ����ֵ���á���ֵ�����ܹ�����ؽ��ʵ�ʹ����е����⣬ʵ�ַǳ����������Ľ��������

//����ҲҪʱ�����ѣ���ʱ����ֵ��תΪ��ֵ����ֵ��תΪ��ֵ��
//��Ҳ��ת���������õĲ��Ǻ�׼ȷ��
//
//�������Ҫ��������ת���أ�
//������Ҫһ�ַ����ܰ��ղ���ԭ��������ת������һ�������У�������������ǳ�֮Ϊ����ת����
//
//std::forward�Ϳ��Ա����������ֵ����ֵ���ԡ�

void process_value(int& i) {
	std::cout << "LValue processed: " << i << std::endl;
}

void process_value(int&& i) {
	std::cout << "RValue processed: " << i << std::endl;
}

//��Ȼ���ܵ�����ֵ�������ղ�����i����ֵ,������������ֵ,�����޷�����ֵ��Ҳ�Ͳ��ܽ��ղ���
void forward_value(int&& i) {
	i = 100;
	process_value(i);
}

class MyString {
private:
	char* _data;
	size_t   _len;
	void _init_data(const char *s) {
		_data = new char[_len + 1];
		memcpy(_data, s, _len);
		_data[_len] = '\0';
	}
public:
	MyString() {
		_data = NULL;
		_len = 0;
	}

	MyString(const char* p) {
		_len = strlen(p);
		_init_data(p);
	}

	MyString(const MyString& str) {
		_len = str._len;
		_init_data(str._data);
		std::cout << "Copy Constructor is called! source: " << str._data << std::endl;
	}

	MyString& operator=(const MyString& str) {
		if (this != &str) {
			_len = str._len;
			_init_data(str._data);
		}
		std::cout << "Copy Assignment is called! source: " << str._data << std::endl;
		return *this;
	}

	void printself(){
		std::cout << "string content: " << _data << std::endl;
	}

	MyString& operator=(MyString&& str);

	MyString(MyString&& str);

	virtual ~MyString() {
		if (_data) free(_data);//fjc:Ӧ����delete�ɣ�
	}

};

void ProcessValue(int& i) {
	std::cout << "--LValue processed: " << i << std::endl;
}

void ProcessValue(int&& i) {
	std::cout << "--RValue processed: " << i << std::endl;
}

//fjc:a�Ƿǳ������ã���Ȼ����ֵ
//template <class T>void swap(T& a, T& b)
//{
//	T tmp(a);   // copy a to tmp 
//	a = b;      // copy b to a 
//	b = tmp;    // copy tmp to b 
//}

//ͨ�� std::move��һ���򵥵� swap �����ͱ����� 3 �β���Ҫ�Ŀ���������
//fjc:moveת��������
template <class T>void swap(T& a, T& b)
{
	T tmp(std::move(a)); // move a to tmp 
	a = std::move(b);    // move b to a 
	b = std::move(tmp);  // move tmp to b 
}

//fjc:const ��������
//���� forward_value Ϊÿһ���������������������ͣ�T& �� const T&
template <typename T> void forward_value(const T& val) {
	process_value(val);
}
template <typename T> void forward_value(T& val) {
	process_value(val);
}
//����һ��������Ҫ�������Σ�Ҳ���Ǻ������صĴ����Ͳ����ĸ�����һ�����ȵĹ�ϵ��
//��������Ķ���������ڳ���Ա��˵���Ƿǳ���Ч�ġ����ǿ�����ֵ������ΰ������ǽ���������
//C++11 �ж���� T&& ���Ƶ�����Ϊ��
//��ֵʵ��Ϊ��ֵ���ã���ֵʵ����ȻΪ��ֵ���á�fjc:?��������ʣ���ֵ�������޷��󶨵���ֵʵ�ε�,����ֵ������ֵ���ûᱨ��
//һ�仰�����ǲ��������Բ��䡣����Ҳ��������ʵ���˲�������������
template <typename T> void forward_value(T&& val) {
	process_value(val);
}

//fjc:��ͨ���������ñ�������������ڣ�ǰ���Ը�ֵ�������=�������������������=,�а󶨸��õ�
int main()
{
	int a = 0;
	int b(10);
	process_value(a);
	process_value(1);

	//Process_value ���������أ��ֱ������ֵ����ֵ�������������Կ�������ʱ��������Ϊ��ֵ����ġ�
	//���������ʱ����ͨ��һ��������ֵ�ĺ������ݸ���һ������ʱ���ͻ�����ֵ����Ϊ�����ʱ�����ڴ��ݹ����У��������������
	//��Ȼ 2 ����������ں��� forward_value ����ʱ����ֵ�������� process_value ����ʱ���������ֵ��
	/*LValue processed : 0
	RValue processed : 1
	LValue processed : 100*/
	forward_value(2);
	//forward_value(a);�޷�����ֵ���ð󶨵���ֵ

	ProcessValue(std::move(a));

	/*��� string ���Ѿ���������������ʾ����Ҫ���� main �����У�ʵ���˵��ÿ������캯���Ĳ����Ϳ�����ֵ�������Ĳ�����
	MyString(��Hello��) �� MyString(��World��) ������ʱ����Ҳ������ֵ����Ȼ��������ʱ�ģ���������Ȼ�����˿�������Ϳ�����ֵ��
	�����û���������Դ������ͷŵĲ���������ܹ�ֱ��ʹ����ʱ�����Ѿ��������Դ�����ܽ�ʡ��Դ�����ܽ�ʡ��Դ������ͷŵ�ʱ�䡣
	�����Ƕ���ת�������Ŀ�ġ�*/
	MyString str;
	str = MyString("Hello");
	std::vector<MyString> vec;
	vec.push_back(MyString("World"));


	MyString stra("string a");
	MyString strb("string b");
	swap(stra, strb);
	stra.printself();
	strb.printself();





	getchar();
    return 0;
}

//ת�ƹ��캯��
//�Ϳ������캯�����ƣ��м�����Ҫע�⣺
//1. ��������ֵ���ķ��ű�������ֵ���÷��ţ�����&&����
//2. ��������ֵ���������ǳ�������Ϊ������Ҫ�޸���ֵ��
//3. ��������ֵ������Դ���Ӻͱ�Ǳ����޸ġ�������ֵ�����������ͻ��ͷ���Դ��ת�Ƶ��¶������ԴҲ����Ч�ˡ�
MyString::MyString(MyString&& str) {
	std::cout << "Move Constructor is called! source: " << str._data << std::endl;
	_len = str._len;
	_data = str._data;
	str._len = 0;
	str._data = NULL;
}

//ת�Ƹ�ֵ������
MyString& MyString::operator=(MyString&& str) {
	std::cout << "Move Assignment is called! source: " << str._data << std::endl;
	if (this != &str) {
		_len = str._len;
		_data = str._data;
		str._len = 0;
		str._data = NULL;
	}
	return *this;
}

//������ֵ���ú�ת�����壬��������ƺ�ʵ����ʱ��������Ҫ��̬���������Դ���࣬Ӧ�����ת�ƹ��캯����ת�Ƹ�ֵ�����������Ӧ�ó����Ч�ʡ�

//��Ȼ������ֻ����ֵ���ò��ܵ���ת�ƹ��캯����ת�Ƹ�ֵ��������������������ֻ������ֵ���ã������֪һ�����������ٱ�ʹ�ö����������ת�ƹ��캯����ת�Ƹ�ֵ������
//Ҳ���ǰ�һ����ֵ���õ�����ֵ������ʹ�ã���ô���أ���׼���ṩ�˺��� std::move����������Էǳ��򵥵ķ�ʽ����ֵ����ת��Ϊ��ֵ����
//��ֵ���ã������Ͽ�ֻ��������һ�����÷��ţ������� C++ �����ƺ���������зǳ����Ӱ�졣�����ܼ򻯴��룬������߳�������Ч�ʡ�
//ÿһ�� C++ ������ʦ�ͳ���Ա��Ӧ����Ⲣ�ܹ�Ӧ������������������ʱ������ж�̬�������Դ��ҲӦ�����ת�ƹ��캯����ת�ƿ���������
//��������ʱ����Ӧ�ÿ��� std::move ��ʹ�ó���������ʹ������
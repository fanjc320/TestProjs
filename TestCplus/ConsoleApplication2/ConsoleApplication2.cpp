// ConsoleApplication2.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <list>
#include <string>
#include <iostream>
#include <cstring>
#include <utility>
#include <xstring>
#include <vector>
using namespace std;

struct Material
{
public:
	Material() {
		cout << "shininess " << &shininess << " strpointer: " << endl;
		cout << &str << " str0 " << &str[0] << " str1 " << &str[1] << endl;
		cout << " vipointer: " << &vi << " vi0 " << &vi[0] << endl; 
		setDefaults();
	}
	void setDefaults() { cout << "material size:" << sizeof(*this) << endl; memset(this, 0, sizeof(*this)); }
	std::string str = "abcdefghijk";   // material name //ռ��28���ֽ�,���ݳ��Ȳ�Ӱ��sizeofthis;
	vector<int> vi = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };//�̶�ռ��16���ֽڣ����ݳ��Ȳ�Ӱ��sizeofthis;
	int shininess;  //
	float alpha;    //
	bool test;
};
//��Ĵ��������ڴ�й¶��
//���Զ���C++��std::string��˵��Ҫʹ��C++���ĳ�ʼ����
//�κ��඼������memset, һ���������͵�����ǿ���������ڲ����ݣ����Ѿ�������
//���������麯���ģ�ָ���麯�����ָ��ᱻ��ʼ�����麯�����Ʒ���

class st_Test
{
	int a = 0;
	/*virtual*/ void test() {};//������麯����������4���ֽڵ��ڴ� 
};

class st_Derive :st_Test
{

};

int main()
{

	char buf[10] = { 0 };
	char buf1[10] = {};

	for (int i = 0; i < 10; ++i)
	{
		cout << buf[i] << " buf1i: " << buf1[i] << endl;
	}

	Material mat;

	st_Test st;
	st_Derive drive;
	cout << "st size:" << sizeof(st) << " derive size " << sizeof(drive) << endl;

	getchar();
	return 0;
}

//https://www.cnblogs.com/yyxt/archive/2015/02/02/4268304.html
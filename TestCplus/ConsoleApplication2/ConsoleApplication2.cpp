// ConsoleApplication2.cpp : 定义控制台应用程序的入口点。
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
	std::string str = "abcdefghijk";   // material name //占用28个字节,内容长度不影响sizeofthis;
	vector<int> vi = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };//固定占用16个字节，内容长度不影响sizeofthis;
	int shininess;  //
	float alpha;    //
	bool test;
};
//面的代码会造成内存泄露：
//所以对于C++的std::string来说，要使用C++风格的初始化。
//任何类都不能用memset, 一旦暴力，就等于你强奸了她的内部数据，她已经崩溃了
//尤其是有虚函数的，指向虚函数表的指针会被初始化，虚函数机制费了

class st_Test
{
	int a = 0;
	/*virtual*/ void test() {};//如果是虚函数，会增加4个字节的内存 
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
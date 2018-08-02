// Register.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <map>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <functional>
using namespace std;

map<string, string>map_funcs;

class MyClass
{
public:
	/*MyClass();
	~MyClass();*/
	int TestFunc(int a)
	{
		cout << __FUNCTION__ << endl;
		string ss = __FUNCTION__;
		cout << ss << endl;
		map_funcs[ss] = "hhhhhh";
		return 1;
	}

private:

};

//MyClass::MyClass()
//{
//}
//
//MyClass::~MyClass()
//{
//}

//A functor is pretty much just a class which defines the operator().That lets you create objects which "look like" a function :
// this is a functor
struct add_x {
	add_x(int x) : x(x) {}
	int operator()(int y) const { return x + y; }

private:
	int x;
};

typedef function<int()> FUC;


map<string, FUC> map_s_func;
string g_Func3 = "";
int TestF0() { cout << __FUNCTION__ << endl; return 10; }
int TestF1() { cout << __FUNCTION__ << endl; return 11; }
int TestF2() { cout << __FUNCTION__ << endl; return 12; }
int TestF3() { cout << __FUNCTION__ << endl; g_Func3 = __FUNCTION__; return 13; }
int TestF4() { cout << __FUNCTION__ << endl; return 14; }
int TestF5() { cout << __FUNCTION__ << endl; map_s_func[__FUNCTION__] = TestF4; return 15; }


int g_Minus(int i, int j)
{
	return i - j;
}

int main()
{
	MyClass* obj = new MyClass();
	obj->TestFunc(0);
	for (auto i: map_funcs)
	{
		cout <<"f:"<< i.first <<"	s:"<< i.second << endl;
	}

	{
		// Now you can use it like this:
		//add_x add42(42); // create an instance of the functor class
		//int i = add42(8); // and "call" it
		//assert(i == 50); // and it added 42 to its argument

		//std::vector<int> in; // assume this contains a bunch of values)
		//std::vector<int> out(in.size());
		//// Pass a functor to std::transform, which calls the functor on every element 
		//// in the input sequence, and stores the result to the output sequence
		//std::transform(in.begin(), in.end(), out.begin(), add_x(1));
		//assert(out[i] == in[i] + 1); // for all i
	}

	function<int(int, int)> f = g_Minus;
	cout << f(1, 2) << endl;
	
	string ss = "TestF0";
	map_s_func[ss] = TestF0;
	map_s_func["TestF0"]();


	TestF5();
	if (map_s_func.end()!=map_s_func.find("TestF5"))
	{
		map_s_func["TestF5"]();
	}

	getchar();
    return 0;
}


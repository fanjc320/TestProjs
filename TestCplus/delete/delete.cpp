// delete.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <map>
#include <unordered_map>
using namespace std;

class Test
{
public:
	Test() { cout << "Test cons" << endl; p = new int[10](); }
	~Test() { cout << "Test des" << endl; delete p; }
private:
	int* p = nullptr;
};

int main()
{
#ifdef _DEBUG0
	{

		vector<Test> vec;
		Test* p1 = new Test();
		Test* p2 = new Test();
		//Test* p3 = new Test();
		vec.push_back(*p1);
		vec.push_back(*p2);
		//vec.push_back(*p3);

		//对象如何进行释放，要调用已定义析构函数  
		vec.clear();//vec中只有一个对象时是正确释放了的，一个以上就不行 如果不加Teat里不加p,调用了六次析构！！！  报异常
					//结论：不可以在vector容器中放对象,其他容器可能也这样
					//delete p1;

	}
#endif // _DEBUG0

	Test t1 = Test();
	Test t2 = Test();
#define  _DEBUG1
#ifdef _DEBUG1
	{
		vector<Test> vec1;

		vec1.push_back(t1);
		vec1.push_back(t2);
		vec1.clear();//异常
	}
#endif // _DEBUG1

#ifdef _DEBUG2
	unordered_map<int, Test> um;
	um[1] = t1;
	um[2] = t2;
	um.clear();//无异常
#endif // _DEBUG2

	getchar();
	return 0;
}

//vector中存储了对象的指针，调用clear后，并不会调用这些指针所指对象析构函数，因此要在clear之前调用delete；
//如果vector存储的是对象，调用clear后，自建类型的对象(int之类的)直接删除，若是外部类型，则调用析构函数。
//https://blog.csdn.net/luomoshusheng/article/details/48226517
// move.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Source.h"


//move后，源对象被掏空，例如这里的str "Hello"->""
void TestMove1()
{
	std::string str = "Hello";
	std::vector<std::string> v;
	//调用常规的拷贝构造函数，新建字符数组，拷贝数据
	v.push_back(str);
	std::cout << "After copy, str is \"" << str << "\"\n";
	//调用移动构造函数，掏空str，掏空后，最好不要使用str
	v.push_back(std::move(str));
	std::cout << "After move, str is \"" << str << "\"\n";
	std::cout << "The contents of the vector are \"" << v[0]
		<< "\", \"" << v[1] << "\"\n";
}




int main()
{
	//TestMove1();
	TestMove_Class();

	getchar();
    return 0;
}


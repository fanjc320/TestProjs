// move.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Source.h"


//move��Դ�����Ϳգ����������str "Hello"->""
void TestMove1()
{
	std::string str = "Hello";
	std::vector<std::string> v;
	//���ó���Ŀ������캯�����½��ַ����飬��������
	v.push_back(str);
	std::cout << "After copy, str is \"" << str << "\"\n";
	//�����ƶ����캯�����Ϳ�str���Ϳպ���ò�Ҫʹ��str
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


// TestFile.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <fstream> 
#include <iostream>
using namespace std;
int main()
{
	ofstream out("out.txt", ios::app);
	if (out.is_open())
	{
		out << "This is a line.\n";
		out << "This is another line.\n";
		out.close();
	}

	getchar();
    return 0;
}


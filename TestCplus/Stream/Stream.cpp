// Stream.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

typedef unsigned __int8 uint8;
string gmPrintPetTalent()
{
	ostringstream oss;
	for (uint8 i = 0; i < 10; ++i)
	{
		float propv = 0.5f;
		oss << (int)i << ": " << propv << " | ";
	}
	string ss = oss.str();
	return ss;
}

int main()
{
	string ss =gmPrintPetTalent();
	cout << ss << endl;

	getchar();
    return 0;
}


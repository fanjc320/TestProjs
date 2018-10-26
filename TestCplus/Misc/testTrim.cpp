#include "stdafx.h"


#include <cctype>
#include <iostream>
#include <algorithm>
#include <string> 
#include <functional>

using namespace std;

inline string& ltrim(string &str) {
	string::iterator p = find_if(str.begin(), str.end(), not1(ptr_fun<int, int>(isspace)));
	str.erase(str.begin(), p);
	return str;
}

inline string& rtrim(string &str) {
	string::reverse_iterator p = find_if(str.rbegin(), str.rend(), not1(ptr_fun<int, int>(isspace)));
	str.erase(p.base(), str.end());
	return str;
}

inline string& trim(string &str) {
	ltrim(rtrim(str));
	return str;
}
//
//int main() {
//	string str = "\t\r\n ·¶½õ²ı ACB%&*KU234 \r\n";
//	string str1 = str;
//	string str2 = str;
//
//	cout << "str: ~" << str.c_str() << "~" << endl << endl;
//
//	cout << "ltrim(str): ~" << ltrim(str1).c_str() << "~" << endl;
//	cout << "rtrim(ltrim(str)): ~" << rtrim(str1).c_str() << "~" << endl << endl;
//
//	cout << "rtrim(str): ~" << rtrim(str2).c_str() << "~" << endl;
//	cout << "ltrim(rtrim(str)): ~" << ltrim(str2).c_str() << "~" << endl << endl;
//
//	cout << "trim(str): ~" << trim(str).c_str() << "~" << endl;
//
//	cout << str << endl;
//
//	while (true);
//	return 0;
//}
// FjcTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <cstdlib>



using namespace std;

 
//int main()
//{
//	unordered_set<int> us;
//	//cout << *us.begin() << endl;//崩溃
//
//	unordered_map<int, unordered_set<int> >um;
//	unordered_map<int, unordered_set<int> >um2;
//
//	um[1].insert(1);
//	um[1].insert(2);
//	um[1].insert(3);
//
//	cout << "--begin---" << endl;
//	for (auto i : um)
//	{
//		for (auto j : i.second)
//		{
//			cout << " set " << i.first << " v " << j << endl;
//		}
//	}
//
//	for (auto i : um)
//	{
//		auto j = i.second;
//		for (auto k:j)
//		{
//			cout << "setcontain " << k << endl;
//		}
//		//i.second.erase(1);
//		j.erase(1);
//	}
//
//	um[1].erase(2);
//
//	for (auto i=um.begin();i!=um.end();)
//	{
//		if (i->second.erase(3))
//		{
//
//		}
//		else
//		{
//			++i;
//		}
//	}
//	cout << "---------------------------" << endl;
//	for (auto i : um)
//	{
//		for (auto j : i.second)
//		{
//			cout << " set " << i.first << " v " << j << endl;
//		}
//	}
//
//	cout << "--end---" << endl;
//
//	cout << atoi("999999999999999999") << endl;
//
//	int i;
//	while (cin >> i);
//
//	return 0;
//}


//#include "stdafx.h"





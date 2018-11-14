// Iterator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <set>
using namespace std;

void TestVector() {
	std::vector<char> charVector;

	int x;
	for (x = 0; x < 10; ++x)
		charVector.push_back(65 + x);
	int size = charVector.size();
	for (x = 0; x < size; ++x)
	{
		std::vector<char>::iterator start = charVector.begin();
		charVector.erase(start);
		std::vector<char>::iterator iter;
		for (iter = charVector.begin(); iter != charVector.end(); iter++)
		{
			std::cout << *iter;
		}
		std::cout << std::endl;
	}
	cout << "---------------------TestVector----------------" << endl;
}

void TestDeque() {
	deque<char> charDeque;
	for (int x = 0; x < 10; ++x)
		charDeque.push_front(65 + x);

	//应该先保存charDeque.size()的值,因为chardeque的大小在变,输出不了10次
	for (int x=0;x<charDeque.size();++x)
	{
		cout << "x:" << x << endl;
		deque<char>::iterator start = charDeque.begin();
		charDeque.erase(start);
		for (auto it = charDeque.begin();it!=charDeque.end();++it)
		{
			cout << *it;
		}
		cout << endl;
	}
	cout << "---------------------TestDeque----------------" << endl;
}

void TestList() {
	int x;
	list<char> charList;
	for (x = 0; x < 10; ++x)
		charList.push_front(65 + x);
	cout << "Original list:" << endl;
	list<char>::iterator iter;
	for (iter = charList.begin(); iter != charList.end(); ++iter)
		cout << *iter;
	cout << endl;

	list<char>::iterator start = charList.begin();
	charList.insert(++start, 5, 'X');
	cout << "Resultant list:" << endl;
	for (auto it = charList.begin();it!=charList.end();++it)
	{
		cout << *it;
	}
	cout << "---------------------TestList----------------" << endl;
}

void TestSet() {
	set<char> charSet;
	charSet.insert('E');
	charSet.insert('D');
	charSet.insert('C');
	charSet.insert('B');
	charSet.insert('A');

	cout << "contents of set:" << endl;
	for (auto it=charSet.begin();it!=charSet.end();++it)
	{
		cout << *it << endl;
	}
	auto it = charSet.find('D');
	if (it != charSet.end())
		cout << "element found" << endl;
	cout << "---------------------TestSet----------------" << endl;
}

void TestMultiSet() {
	multiset<char> charMultiSet1;
	charMultiSet1.insert('E');
	charMultiSet1.insert('D');
	charMultiSet1.insert('C');
	charMultiSet1.insert('B');
	charMultiSet1.insert('A');
	charMultiSet1.insert('B');
	charMultiSet1.insert('D');
	for (auto it = charMultiSet1.begin(); it != charMultiSet1.end(); ++it)
		cout << *it << endl;
	cout << endl;
	cout << "---------------------TestMultiSet----------------" << endl;
}

int main()
{
	TestVector();
	TestDeque();
	TestList();
	TestSet();
	TestMultiSet();

	int i;
	cin >> i;
	return 0;
}


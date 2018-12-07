#pragma once

#include <string>
#include <map>
using namespace std;

#define foreach(container,it) \
    for(typeof((container).begin()) it = (container).begin();it!=(container).end();++it)


template<typename T>
void PrintBeginEnd(T begin, T end) {
	int i = 0;
	for (auto it = begin; it != end; ++it) {
		printf("order:%d:",i++,*it);
	}
}

//打印数组
template<typename T>
void printContain(T* begin, int size)
{
	for (int from = 0; from < size; ++from)
	{
		cout << from << ":" << begin[from] << endl;
	}
	cout << "-------------------------" << strlen(begin) << endl; //strlen 以'\0'结尾
}

template<typename T>
void printContain(T begin, T end,string tip="")
{
	static int flag = 0;
	flag++;
	cout << tip << "-------printContain BEGIN---------flag:" << flag << endl; //strlen 以'\0'结尾
	
	for (auto it = begin; it != end; ++it)
	{
		cout << " " << *it;
	}
	cout << endl;
}

template<typename Tkey,typename Tvalue>
void printMap(std::map<Tkey,Tvalue> m)
{
	for_each(m.begin(), m.end(), [](std::map<Tkey, Tvalue>::reference a) {
		cout << a.first << " " << a.second << endl;
	})
}
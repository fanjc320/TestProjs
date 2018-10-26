#pragma once

void TestSum();


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
void printContain(T begin, T end)
{
	static int flag = 0;
	flag++;
	for (auto it = begin; it != end; ++it)
	{
		cout << "::" << *it << endl;
	}
	cout << "-------------+++----------flag:" << flag << endl; //strlen 以'\0'结尾
}

template<typename It>
auto sum(It beg, It end)->decltype(*beg) {
	decltype(*beg) ret = *beg;
	for (It it = beg + 1; it != end; it++)
	{
		ret = ret + *it;
	}
	return ret;
}

template<typename T1,typename T2,typename T3>
T1 sum(T2 v2, T3 v3) {
	return static_cast<T1>(v2 + v3);
}

template<typename T1,typename T2,typename T3>
T3 sum_alternative(T1 v1, T2 v2) {
	return static_cast<T1>(v1 + v2);
}

void TestTemplate();

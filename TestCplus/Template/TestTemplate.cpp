#include "stdafx.h"





void TestSum() {
	vector<int> v = { 1,2,3,4 };
	auto s = sum(v.begin(), v.end());
	cout << __FUNCDNAME__ << " s:" << s << endl;
}

void TestTemplate()
{
	auto ret = sum<long>(1L, 23);//指定T1, T2和T3交由编译器来推断
	//auto ret = sum_alternative<long>(1L, 23);//error，只能从左向右逐一指定
	auto ret1 = sum_alternative<long, int, long>(1L, 23);//ok, 谁叫你把最后一个T3作为返回类型的呢？
}

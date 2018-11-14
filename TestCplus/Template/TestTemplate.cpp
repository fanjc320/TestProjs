#include "stdafx.h"





void TestSum() {
	vector<int> v = { 1,2,3,4 };
	auto s = sum(v.begin(), v.end());
	cout << __FUNCDNAME__ << " s:" << s << endl;
}

void TestTemplate()
{
	auto ret = sum<long>(1L, 23);//ָ��T1, T2��T3���ɱ��������ƶ�
	//auto ret = sum_alternative<long>(1L, 23);//error��ֻ�ܴ���������һָ��
	auto ret1 = sum_alternative<long, int, long>(1L, 23);//ok, ˭��������һ��T3��Ϊ�������͵��أ�
}

// delete.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <map>
#include <unordered_map>
using namespace std;

class Test
{
public:
	Test() { cout << "Test cons" << endl; p = new int[10](); }
	~Test() { cout << "Test des" << endl; delete p; }
private:
	int* p = nullptr;
};

int main()
{
#ifdef _DEBUG0
	{

		vector<Test> vec;
		Test* p1 = new Test();
		Test* p2 = new Test();
		//Test* p3 = new Test();
		vec.push_back(*p1);
		vec.push_back(*p2);
		//vec.push_back(*p3);

		//������ν����ͷţ�Ҫ�����Ѷ�����������  
		vec.clear();//vec��ֻ��һ������ʱ����ȷ�ͷ��˵ģ�һ�����ϾͲ��� �������Teat�ﲻ��p,��������������������  ���쳣
					//���ۣ���������vector�����зŶ���,������������Ҳ����
					//delete p1;

	}
#endif // _DEBUG0

	Test t1 = Test();
	Test t2 = Test();
#define  _DEBUG1
#ifdef _DEBUG1
	{
		vector<Test> vec1;

		vec1.push_back(t1);
		vec1.push_back(t2);
		vec1.clear();//�쳣
	}
#endif // _DEBUG1

#ifdef _DEBUG2
	unordered_map<int, Test> um;
	um[1] = t1;
	um[2] = t2;
	um.clear();//���쳣
#endif // _DEBUG2

	getchar();
	return 0;
}

//vector�д洢�˶����ָ�룬����clear�󣬲����������Щָ����ָ�����������������Ҫ��clear֮ǰ����delete��
//���vector�洢���Ƕ��󣬵���clear���Խ����͵Ķ���(int֮���)ֱ��ɾ���������ⲿ���ͣ����������������
//https://blog.csdn.net/luomoshusheng/article/details/48226517
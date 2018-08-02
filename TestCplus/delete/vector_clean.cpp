//##û�ж���Ŀ�--��ȷ�ͷ�vector���ڴ�
//vector���ڴ�᲻��й¶��
//��ʹ��й¶����ô����С��ռ�ռ��أ�
//
//����֪��vector�и�clear()������
//
//ԭ�� :
//
//#include <vector>
//void clear();
//����clear()ɾ��������vector�е�����Ԫ��.���vector��Ԫ����һЩobject, ������Ϊ��ǰ�����ÿ��Ԫ�ص������Ǹ��Ե���������(destructor).Ȼ��, ���vector�������ָ������ָ��, �˺�����������õ���Ӧ����������.�ڵڶ��������, Ϊ����ȫɾ��vector�е�Ԫ����Ӧʹ��һ���������µ�ѭ��:
//
//std::vector<SomeObject*> aVector;
////The elements of the vector are created with the operand 'new' at some point in the program
//[...]
//for (int i = 0; i < aVector.size(); i++)
//	delete aVector[i];
//aVector.clear();
//����clear֮��, vector�ĳߴ�(size)�����zero.����������(capacity)ȴ���������仯, vector�������ͷ��κ��ڴ�.
//
//�������ͬʱ�������vector��Ԫ�غ��ͷ�vector������, �����ʹ��swap���ɡ�
//�������ᴴ��һ����ʱ�Ŀ�vector, �����滻ϣ����յ�vector��
//
//��vector �� clear ��Ӱ�� capacity, ��Ӧ�� swap һ���յ� vector����
//
//vector<type>(v).swap(v);
////����string��������������� 
//string(s).swap(s);
//
//���ȴ���һ����ʱ������ԭ�ȵ�vectorһ�£�ֵ��ע����ǣ���ʱ�Ŀ��� �������Ǿ�����С�ķ����������ݵġ������Ž��ÿ�����ԭ�ȵ�vector v���� ���������˴�ʱ��ִ�н�������ʱ�����ᱻ���٣��ڴ�õ��ͷš���ʱ��v��Ϊԭ�� ����ʱ�����������������ʱ������Ϊ�����ǳ����vector�������Ѿ������٣�
//
//Ϊ��֤����һ�㣬��д��һ���������£�

#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

vector <string> v;
char ch;


#ifdef TEST_VECTOR_CLEAN
int main()
{

	for (int i = 0; i < 1000000; i++)
		v.push_back("hello vector");
	cin >> ch;

	// ��ʱ����ڴ���� ռ��54M

	v.clear();
	cin >> ch;

	// ��ʱ�ٴμ�飬 ��Ȼռ��54M

	cout << "Vector �� ����Ϊ" << v.capacity() << endl;

	// ��ʱ����Ϊ 1048576

	vector<string>(v).swap(v);

	cout << "Vector �� ����Ϊ" << v.capacity() << endl;

	// ��ʱ����Ϊ0
	cin >> ch;

	// ����ڴ棬�ͷ��� 10M+ ��Ϊ�����ڴ�
	return 0;
}
#endif // TEST_VECTOR_CLEAN
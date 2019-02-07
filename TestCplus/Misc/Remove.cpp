#include "stdafx.h"

void print(vector<int>&);
void print1(vector<int>&);

int TestRemove()
{
	vector<int> array;
	array.push_back(1);
	array.push_back(6);
	array.push_back(6);
	array.push_back(3);

	vector<int> arr(array);
	vector<int> arr1(array); vector<int> arr2(array); vector<int> arr3(array);
	list<int> lst1(array.begin(),array.end()); list<int> lst2(array.begin(), array.end()); list<int> lst3(array.begin(), array.end());
	//ɾ��array�е����е�6
	vector<int>::iterator itor;
	vector<int>::iterator itor2;
	itor = array.begin();

	for (itor = array.begin(); itor != array.end(); itor++)
	{
		if (6 == *itor)
		{
			//vector iterator not decrementable; itor��ɾ�����ʧЧ�ˣ�������������
			/*itor2 = itor;
			array.erase(itor2);
			itor--;*/ 
			itor = array.erase(itor);//������6���һ��Ԫ��
		}
	}

	//��ȷ�汾
	for (itor = arr.begin(); itor != arr.end();)
	{
		if (6 == *itor)
		{
			itor = arr.erase(itor);//������6���һ��Ԫ��
		}
		else
		{
			itor++;
		}
	}
	
	arr2.erase(remove(arr2.begin(), arr2.end(), 6), arr2.end());
	printContain(arr2.begin(), arr2.end(), "erase remove:");
	cout << "-------Test Remove Begin -------" << endl;
	remove(arr1.begin(), arr1.end(), 6);
	printContain(arr1.begin(),arr1.end(),"remove vector:");


	remove(lst1.begin(), lst1.end(), 6);
	printContain(lst1.begin(), lst1.end(),"remove lst:");

	lst2.remove(6);
	printContain(lst2.begin(), lst2.end(), "lst remove:");

	return 0;
}

int TestUnique()
{
	vector<int> array;
	array.push_back(1);
	array.push_back(6);
	array.push_back(6);
	array.push_back(3);
	array.push_back(3);
	array.push_back(6);
	array.push_back(2);

	vector<int> arr(array);
	vector<int> arr1(array);
	list<int> list1(array.begin(),array.end());  list<int> list2(array.begin(), array.end());

	//ȥ������Ԫ�أ�����������ɾ��
	auto it = std::unique(array.begin(),array.end());

	cout << "-----TestUnique Begin ---------" << endl;
	printContain(array.begin(), it);
	printContain(array.begin(),array.end(),"unique vector:");


	auto jt = std::unique(list1.begin(), list1.end());
	printContain(list1.begin(), jt);
	printContain(list1.begin(), list1.end(),"unique list:");
	
	list2.unique();
	printContain(list2.begin(), list2.end(), "list unique:");

	return 0;
}



void print1(vector<int>& v)
{
	/*for(auto& var : v)
	{
		cout << var << endl;
	}*/
	/*for each (auto& var in v)
	{
		cout << var << endl;
	}*/
	for_each(v.begin(), v.end(), [](int e) { cout << e << " " ; });
	cout << endl;
}

//̹�׵�˵���������remove������һ��STL�е�ì�ܡ��ڹ������������Ƶĺ�����erase��list��removeҲ���Խ���erase��
//����û�У��������Ƕ�����ϰ���������������ڵ����粻�����п�������õ����磬��ȴ�����������ġ�
//������һ�㣬����44ָ��������list������remove��Ա������Ӧ��erase - remove���÷�����Ч����
//һ����֪����remove���ܡ���ġ���һ��������ɾ����������erase����ʹ�þͱ��������Ȼ�ˡ���Ҫ��ס��Ψһ�����Ķ�����remove����Ψһ����������㷨��
//���������֡�����remove�����㷨��remove_if��unique��
//remove��remove_if֮��������Ժ�ֱ���˵��������Ҳ���ϸ������unique��ΪҲ��remove��
//��������һ������ɾ���������ڽ����ظ�ֵ�������÷��ʳ�������Ԫ�ص�������
//�������������Ҫ��������ɾ��Ԫ�أ���Ҳ����ɶԵ���unique��erase��unique��list��Ҳ������remove��
//����list::remove���ɾ�����������ұ�erase - remove���÷���Ч�öࣩ��list::uniqueҲ���ɾ���ڽ����ظ�ֵ��Ҳ��erase - unique��Ч����
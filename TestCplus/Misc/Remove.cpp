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
	//删除array中的所有的6
	vector<int>::iterator itor;
	vector<int>::iterator itor2;
	itor = array.begin();

	for (itor = array.begin(); itor != array.end(); itor++)
	{
		if (6 == *itor)
		{
			//vector iterator not decrementable; itor被删除后就失效了，不能再做操作
			/*itor2 = itor;
			array.erase(itor2);
			itor--;*/ 
			itor = array.erase(itor);//跳过了6后的一个元素
		}
	}

	//正确版本
	for (itor = arr.begin(); itor != arr.end();)
	{
		if (6 == *itor)
		{
			itor = arr.erase(itor);//跳过了6后的一个元素
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

	//去掉相邻元素，但并不真正删除
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

//坦白地说，调用这个remove函数是一个STL中的矛盾。在关联容器中类似的函数叫erase，list的remove也可以叫做erase。
//但它没有，所以我们都必须习惯它。我们所处于的世界不是所有可能中最好的世界，但却是我们所处的。
//（附加一点，条款44指出，对于list，调用remove成员函数比应用erase - remove惯用法更高效。）
//一旦你知道了remove不能“真的”从一个容器中删除东西，和erase联合使用就变成理所当然了。你要记住的唯一其他的东西是remove不是唯一这种情况的算法。
//另外有两种“类似remove”的算法：remove_if和unique。
//remove和remove_if之间的相似性很直截了当。所以我不会细讲，但unique行为也像remove。
//它用来从一个区间删除东西（邻近的重复值）而不用访问持有区间元素的容器。
//结果，如果你真的要从容器中删除元素，你也必须成对调用unique和erase，unique在list中也类似于remove。
//正像list::remove真的删除东西（而且比erase - remove惯用法高效得多）。list::unique也真的删除邻近的重复值（也比erase - unique高效）。
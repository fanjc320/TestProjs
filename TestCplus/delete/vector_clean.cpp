//##没有躲过的坑--正确释放vector的内存
//vector的内存会不会泄露？
//即使不泄露，怎么能缩小所占空间呢？
//
//我们知道vector有个clear()方法？
//
//原型 :
//
//#include <vector>
//void clear();
//函数clear()删除储存在vector中的所有元素.如果vector的元素是一些object, 则它将为当前储存的每个元素调用它们各自的析构函数(destructor).然而, 如果vector储存的是指向对象的指针, 此函数并不会调用到对应的析构函数.在第二种情况下, 为了完全删除vector中的元素则应使用一个类似于下的循环:
//
//std::vector<SomeObject*> aVector;
////The elements of the vector are created with the operand 'new' at some point in the program
//[...]
//for (int i = 0; i < aVector.size(); i++)
//	delete aVector[i];
//aVector.clear();
//调用clear之后, vector的尺寸(size)将变成zero.但它的容量(capacity)却并不发生变化, vector本身并不释放任何内存.
//
//如果你想同时做到清空vector的元素和释放vector的容量, 你可以使用swap技巧。
//这样做会创建一个临时的空vector, 它将替换希望清空的vector。
//
//“vector 的 clear 不影响 capacity, 你应该 swap 一个空的 vector。”
//
//vector<type>(v).swap(v);
////对于string则可能像下面这样 
//string(s).swap(s);
//
//即先创建一个临时拷贝与原先的vector一致，值得注意的是，此时的拷贝 其容量是尽可能小的符合所需数据的。紧接着将该拷贝与原先的vector v进行 交换。好了此时，执行交换后，临时变量会被销毁，内存得到释放。此时的v即为原先 的临时拷贝，而交换后的临时拷贝则为容量非常大的vector（不过已经被销毁）
//
//为了证明这一点，我写了一个程序，如下：

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

	// 此时检查内存情况 占用54M

	v.clear();
	cin >> ch;

	// 此时再次检查， 仍然占用54M

	cout << "Vector 的 容量为" << v.capacity() << endl;

	// 此时容量为 1048576

	vector<string>(v).swap(v);

	cout << "Vector 的 容量为" << v.capacity() << endl;

	// 此时容量为0
	cin >> ch;

	// 检查内存，释放了 10M+ 即为数据内存
	return 0;
}
#endif // TEST_VECTOR_CLEAN
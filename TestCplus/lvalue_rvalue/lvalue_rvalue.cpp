// lvalue_rvalue.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>

//C++(包括 C) 中所有的表达式和变量要么是左值，要么是右值。通俗的左值的定义就是非临时对象，那些可以在多条语句中使用的对象。
//所有的变量都满足这个定义，在多条代码中都可以使用，都是左值。右值是指临时的对象，它们只在当前的语句中有效。请看下列示例 :
//简单的赋值语句
//如：int i = 0;
//在这条语句中，i 是左值，0 是临时值，就是右值。在下面的代码中，i 可以被引用，0 就不可以了。立即数都是右值。
//右值也可以出现在赋值表达式的左边，但是不能作为赋值的对象，因为右值只在当前语句有效，赋值没有意义。
//如：((i > 0) ? i : j) = 1;
//在这个例子中，0 作为右值出现在了” = ”的左边。但是赋值对象是 i 或者 j，都是左值。
//在 C++11 之前，右值是不能被引用的，最大限度就是用常量引用绑定一个右值，如 :
//const int &a = 1;
//在这种情况下，右值不能被修改的。但是实际上右值是可以被修改的，如:
//T().set().get();
//T 是一个类，set 是一个函数为 T 中的一个变量赋值，get 用来取出这个变量的值。在这句中，
//T() 生成一个临时对象，就是右值，set() 修改了变量的值，也就修改了这个右值。
//既然右值可以被修改，那么就可以实现右值引用。右值引用能够方便地解决实际工程中的问题，实现非常有吸引力的解决方案。

//我们也要时刻清醒，有时候右值会转为左值，左值会转为右值。
//（也许“转换”二字用的不是很准确）
//
//如果我们要避免这种转换呢？
//我们需要一种方法能按照参数原来的类型转发到另一个函数中，这才完美，我们称之为完美转发。
//
//std::forward就可以保存参数的左值或右值特性。

void process_value(int& i) {
	std::cout << "LValue processed: " << i << std::endl;
}

void process_value(int&& i) {
	std::cout << "RValue processed: " << i << std::endl;
}

//虽然接受的是右值，但接收参数的i是左值,函数参数是左值,否则无法被赋值，也就不能接收参数
void forward_value(int&& i) {
	i = 100;
	process_value(i);
}

class MyString {
private:
	char* _data;
	size_t   _len;
	void _init_data(const char *s) {
		_data = new char[_len + 1];
		memcpy(_data, s, _len);
		_data[_len] = '\0';
	}
public:
	MyString() {
		_data = NULL;
		_len = 0;
	}

	MyString(const char* p) {
		_len = strlen(p);
		_init_data(p);
	}

	MyString(const MyString& str) {
		_len = str._len;
		_init_data(str._data);
		std::cout << "Copy Constructor is called! source: " << str._data << std::endl;
	}

	MyString& operator=(const MyString& str) {
		if (this != &str) {
			_len = str._len;
			_init_data(str._data);
		}
		std::cout << "Copy Assignment is called! source: " << str._data << std::endl;
		return *this;
	}

	void printself(){
		std::cout << "string content: " << _data << std::endl;
	}

	MyString& operator=(MyString&& str);

	MyString(MyString&& str);

	virtual ~MyString() {
		if (_data) free(_data);//fjc:应该是delete吧？
	}

};

void ProcessValue(int& i) {
	std::cout << "--LValue processed: " << i << std::endl;
}

void ProcessValue(int&& i) {
	std::cout << "--RValue processed: " << i << std::endl;
}

//fjc:a是非常量引用，必然是左值
//template <class T>void swap(T& a, T& b)
//{
//	T tmp(a);   // copy a to tmp 
//	a = b;      // copy b to a 
//	b = tmp;    // copy tmp to b 
//}

//通过 std::move，一个简单的 swap 函数就避免了 3 次不必要的拷贝操作。
//fjc:move转移了引用
template <class T>void swap(T& a, T& b)
{
	T tmp(std::move(a)); // move a to tmp 
	a = std::move(b);    // move b to a 
	b = std::move(tmp);  // move tmp to b 
}

//fjc:const 参与重载
//函数 forward_value 为每一个参数必须重载两种类型，T& 和 const T&
template <typename T> void forward_value(const T& val) {
	process_value(val);
}
template <typename T> void forward_value(T& val) {
	process_value(val);
}
//对于一个参数就要重载两次，也就是函数重载的次数和参数的个数是一个正比的关系。
//这个函数的定义次数对于程序员来说，是非常低效的。我们看看右值引用如何帮助我们解决这个问题
//C++11 中定义的 T&& 的推导规则为：
//右值实参为右值引用，左值实参仍然为左值引用。fjc:?这句有疑问：右值引用是无法绑定到左值实参的,把左值传给右值引用会报错
//一句话，就是参数的属性不变。这样也就完美的实现了参数的完整传递
template <typename T> void forward_value(T&& val) {
	process_value(val);
}

//fjc:普通变量和引用变量的区别就在于，前者以赋值语义接收=，后者以引用语义接收=,叫绑定更好点
int main()
{
	int a = 0;
	int b(10);
	process_value(a);
	process_value(1);

	//Process_value 函数被重载，分别接受左值和右值。由输出结果可以看出，临时对象是作为右值处理的。
	//但是如果临时对象通过一个接受右值的函数传递给另一个函数时，就会变成左值，因为这个临时对象在传递过程中，变成了命名对象
	//虽然 2 这个立即数在函数 forward_value 接收时是右值，但到了 process_value 接收时，变成了左值。
	/*LValue processed : 0
	RValue processed : 1
	LValue processed : 100*/
	forward_value(2);
	//forward_value(a);无法将右值引用绑定到左值

	ProcessValue(std::move(a));

	/*这个 string 类已经基本满足我们演示的需要。在 main 函数中，实现了调用拷贝构造函数的操作和拷贝赋值操作符的操作。
	MyString(“Hello”) 和 MyString(“World”) 都是临时对象，也就是右值。虽然它们是临时的，但程序仍然调用了拷贝构造和拷贝赋值，
	造成了没有意义的资源申请和释放的操作。如果能够直接使用临时对象已经申请的资源，既能节省资源，有能节省资源申请和释放的时间。
	这正是定义转移语义的目的。*/
	MyString str;
	str = MyString("Hello");
	std::vector<MyString> vec;
	vec.push_back(MyString("World"));


	MyString stra("string a");
	MyString strb("string b");
	swap(stra, strb);
	stra.printself();
	strb.printself();





	getchar();
    return 0;
}

//转移构造函数
//和拷贝构造函数类似，有几点需要注意：
//1. 参数（右值）的符号必须是右值引用符号，即“&&”。
//2. 参数（右值）不可以是常量，因为我们需要修改右值。
//3. 参数（右值）的资源链接和标记必须修改。否则，右值的析构函数就会释放资源。转移到新对象的资源也就无效了。
MyString::MyString(MyString&& str) {
	std::cout << "Move Constructor is called! source: " << str._data << std::endl;
	_len = str._len;
	_data = str._data;
	str._len = 0;
	str._data = NULL;
}

//转移赋值操作符
MyString& MyString::operator=(MyString&& str) {
	std::cout << "Move Assignment is called! source: " << str._data << std::endl;
	if (this != &str) {
		_len = str._len;
		_data = str._data;
		str._len = 0;
		str._data = NULL;
	}
	return *this;
}

//有了右值引用和转移语义，我们在设计和实现类时，对于需要动态申请大量资源的类，应该设计转移构造函数和转移赋值函数，以提高应用程序的效率。

//既然编译器只对右值引用才能调用转移构造函数和转移赋值函数，而所有命名对象都只能是左值引用，如果已知一个命名对象不再被使用而想对它调用转移构造函数和转移赋值函数，
//也就是把一个左值引用当做右值引用来使用，怎么做呢？标准库提供了函数 std::move，这个函数以非常简单的方式将左值引用转换为右值引用
//右值引用，表面上看只是增加了一个引用符号，但它对 C++ 软件设计和类库的设计有非常大的影响。它既能简化代码，又能提高程序运行效率。
//每一个 C++ 软件设计师和程序员都应该理解并能够应用它。我们在设计类的时候如果有动态申请的资源，也应该设计转移构造函数和转移拷贝函数。
//在设计类库时，还应该考虑 std::move 的使用场景并积极使用它。
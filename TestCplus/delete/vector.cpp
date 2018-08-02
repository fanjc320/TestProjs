#include "stdafx.h"
#include <iostream>

#include <string>

#include <memory>

#include <cstddef>

#include <stdexcept>

using namespace std;



// vector的模拟实现 – Vector

template<typename T>

class Vector

{

private:

	T *elements;              // 指向第一个元素的指针

	T *first_free;               // 指向最后有效元素后面紧接着位置的指针

	T *end;                        // 指向数组末尾后面紧接着位置的指针



private:

	// 用于获取为构造内存(unconstructed memory)的对象。在此，它必须是static的，因为：

	// 创建对象之前，必须要为其提供内存。如果非static，那么alloc对象必须是在Vector

	// 对象创建之后才可以使用，而alloc的初衷却是为即将要创建的对象分配内存。因此非

	// static是断然不行的。

	// static成员是类级别的，而非类之对象级别的。也就是说，static成员早于对象存在，

	// 因此，下面的alloc可以为即将要创建的对象分配内存。

	static std::allocator<T> alloc;



	// 当元素数量超过容量时，该函数用来分配更多的内存，并复制已有元素到新空间。

	void reallocate();



public:

	Vector() : elements(0), first_free(0), end(0)        // 全部初始化为空指针

	{}



	void push_back(const T&);                          // 增加一个元素

	void reserve(const size_t);                           // 保留内存大小

	void resize(const size_t);                              // 调整Vector大小

	T& operator[](const size_t);                          // 下标操作符

	size_t size();                                                    // 获取Vector中元素的个数

	size_t capacity();                                             // 获取Vector的容量

	T& erase(const size_t);                                 // 删除指定元素

};



// 初始化静态变量。注意，即使是私有成员，静态变量也可以用如下方式初始化

template<typename T>

allocator<T> Vector<T>::alloc;



template<typename T>

void Vector<T>::reallocate()

{

	// 计算现有元素数量

	ptrdiff_t size = first_free - elements;



	// 分配现有元素大小两倍的空间

	ptrdiff_t new_capacity = 2 * max(size, 1);  //(size == 0) ? 2 : 2 * size;

	T *new_elements = alloc.allocate(new_capacity);



	// 在新空间中构造现有元素的副本

	uninitialized_copy(elements, first_free, new_elements);



	// 逆序销毁原有元素

	for (T *p = first_free; p != elements; )

	{

		alloc.destroy(--p);

	}



	// 释放原有元素所占内存

	if (elements)

	{

		alloc.deallocate(elements, end - elements);

	}



	// 更新个重要的数据成员

	elements = new_elements;

	first_free = elements + size;

	end = elements + new_capacity;

}



template<typename T>

void Vector<T>::push_back(const T &t)

{

	if (first_free == end)                      // 如果没有剩余的空间

	{

		reallocate();                         // 分配更多空间，并复制已有元素

	}

	alloc.construct(first_free, t);       // 将t复制到first_free指定的位置

	first_free++;                                  // 将first_free加

}



template<typename T>

void Vector<T>::reserve(const size_t n)

{

	// 计算当前Vector的大小

	size_t size = first_free - elements;

	// 如果新分配空间小于当前Vector的大小

	if (n < size)

	{

		throw custom_exception("所保留的空间不应少于容器中原有元素的个数");

	}



	// 分配可以存储n个T类型元素的空间

	T *newelements = alloc.allocate(n);

	// 在新分配的空间中，构造现有元素的副本

	uninitialized_copy(elements, first_free, newelements);



	// 逆序销毁原有元素，但此时并未将原有元素占用的空间交还给系统

	for (T *p = first_free; p != elements;)

	{

		alloc.destroy(--p);

	}



	// 释放原有元素所占用的内存

	if (elements)

	{

		alloc.deallocate(elements, end - elements);

	}



	// 更新个重要的数据成员

	elements = newelements;

	first_free = elements + size;

	end = first_free + n;

}



template<typename T>

void Vector<T>::resize(const size_t n)                          // 调整Vector大小

{

	// 计算当前Vector大小以及容量

	size_t size = first_free - elements;

	size_t capacity = end - elements;



	if (n > capacity)  // 如果新空间的大小大于原来的容量

	{

		reallocate();

		T temp;

		uninitialized_fill(elements + size, elements + n, temp);

		end = elements + n;

	}

	else if (n > size)          // 如果新空间的大小大于原来Vector的大小

	{

		uninitialized_fill(elements + size, elements + n, temp);

	}

	else // 如果新空间的大小小于或等于原来Vector的大小

	{

		// 逆序销毁多余元素

		for (T *p = first_free; p != elements + n;)

		{

			alloc.destroy(--p);

		}

	}



	// 更新相关数据成员

	// elements没有改变，无需更新

	first_free = elements + n;

	// end在上面n > capacity时，已经被更改

}

template<typename T>

T& Vector<T>::operator[](const size_t index)               // 下标操作符

{

	size_t size = first_free - elements;

	// 如果接受的参数不在有效的范围内，则抛出异常

	if (index < 0 || index > size)

	{

		throw custom_exception("给定的索引参数错误");

	}

	return elements[index];

}



template<typename T>

size_t Vector<T>::size()                                                   // 获取Vector中元素的个数

{

	size_t temp = first_free - elements;

	return temp;

}



template<typename T>

size_t Vector<T>::capacity()                                            // 获取Vector的容量

{

	size_t temp = end - elements;

	return temp;

}



//在Vector中用到的自定义异常类以及Student类分别定义如下：

// 自定义异常类，从std::runtime_error继承而来

// 注意，可以在此基础上，增加更复杂的内容。本例为了方便，使用了最简单的形式。

class custom_exception : public runtime_error

{

public:

	// 定义一个explicit的构造函数，并将参数传递给基类

	explicit custom_exception(const string& s) : runtime_error(s)

	{

	}



	// An empty specification list says that the function does not throw any exception

	// 析构函数不抛出任何异常

	virtual ~custom_exception() throw()

	{

	}

};



// 这个类将作为Vector中元素的类型

class Student

{

public:

	Student(const string name = "Andrew", const int age = 7) : name(name), age(age)

	{}



	~Student()

	{

		cout << name << "\tdeleted." << endl;

	}



	const string get_name() const

	{

		return name;

	}



	const int get_age() const

	{

		return age;

	}



private:

	string name;

	int age;

};

//我们可以看到前面几乎没有析构函数被调用，最后析构函数被调用了9次，是因为测试代码中的9个Student对象在其作用域结束时，自动被销毁的结果。关于这点，可以参考：http://patmusing.blog.163.com/blog/static/13583496020101824142699/
//在Vector中，并没有实现erase，这是因为erase要用到Iterator，限于篇幅就不在此列出相关代码了，因为其原理和上面的代码是一样的，而上面的代码已经足以解释博文http://patmusing.blog.163.com/blog/static/13583496020101831514657/ 中提到的关于析构函数被多次调用的问题。
//最后再次强调一下：显式调用析构函数，可以销毁对象，但不会释放对象所占的内存。
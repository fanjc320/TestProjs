#include "stdafx.h"
#include <iostream>

#include <string>

#include <memory>

#include <cstddef>

#include <stdexcept>

using namespace std;



// vector��ģ��ʵ�� �C Vector

template<typename T>

class Vector

{

private:

	T *elements;              // ָ���һ��Ԫ�ص�ָ��

	T *first_free;               // ָ�������ЧԪ�غ��������λ�õ�ָ��

	T *end;                        // ָ������ĩβ���������λ�õ�ָ��



private:

	// ���ڻ�ȡΪ�����ڴ�(unconstructed memory)�Ķ����ڴˣ���������static�ģ���Ϊ��

	// ��������֮ǰ������ҪΪ���ṩ�ڴ档�����static����ôalloc�����������Vector

	// ���󴴽�֮��ſ���ʹ�ã���alloc�ĳ���ȴ��Ϊ����Ҫ�����Ķ�������ڴ档��˷�

	// static�Ƕ�Ȼ���еġ�

	// static��Ա���༶��ģ�������֮���󼶱�ġ�Ҳ����˵��static��Ա���ڶ�����ڣ�

	// ��ˣ������alloc����Ϊ����Ҫ�����Ķ�������ڴ档

	static std::allocator<T> alloc;



	// ��Ԫ��������������ʱ���ú����������������ڴ棬����������Ԫ�ص��¿ռ䡣

	void reallocate();



public:

	Vector() : elements(0), first_free(0), end(0)        // ȫ����ʼ��Ϊ��ָ��

	{}



	void push_back(const T&);                          // ����һ��Ԫ��

	void reserve(const size_t);                           // �����ڴ��С

	void resize(const size_t);                              // ����Vector��С

	T& operator[](const size_t);                          // �±������

	size_t size();                                                    // ��ȡVector��Ԫ�صĸ���

	size_t capacity();                                             // ��ȡVector������

	T& erase(const size_t);                                 // ɾ��ָ��Ԫ��

};



// ��ʼ����̬������ע�⣬��ʹ��˽�г�Ա����̬����Ҳ���������·�ʽ��ʼ��

template<typename T>

allocator<T> Vector<T>::alloc;



template<typename T>

void Vector<T>::reallocate()

{

	// ��������Ԫ������

	ptrdiff_t size = first_free - elements;



	// ��������Ԫ�ش�С�����Ŀռ�

	ptrdiff_t new_capacity = 2 * max(size, 1);  //(size == 0) ? 2 : 2 * size;

	T *new_elements = alloc.allocate(new_capacity);



	// ���¿ռ��й�������Ԫ�صĸ���

	uninitialized_copy(elements, first_free, new_elements);



	// ��������ԭ��Ԫ��

	for (T *p = first_free; p != elements; )

	{

		alloc.destroy(--p);

	}



	// �ͷ�ԭ��Ԫ����ռ�ڴ�

	if (elements)

	{

		alloc.deallocate(elements, end - elements);

	}



	// ���¸���Ҫ�����ݳ�Ա

	elements = new_elements;

	first_free = elements + size;

	end = elements + new_capacity;

}



template<typename T>

void Vector<T>::push_back(const T &t)

{

	if (first_free == end)                      // ���û��ʣ��Ŀռ�

	{

		reallocate();                         // �������ռ䣬����������Ԫ��

	}

	alloc.construct(first_free, t);       // ��t���Ƶ�first_freeָ����λ��

	first_free++;                                  // ��first_free��

}



template<typename T>

void Vector<T>::reserve(const size_t n)

{

	// ���㵱ǰVector�Ĵ�С

	size_t size = first_free - elements;

	// ����·���ռ�С�ڵ�ǰVector�Ĵ�С

	if (n < size)

	{

		throw custom_exception("�������Ŀռ䲻Ӧ����������ԭ��Ԫ�صĸ���");

	}



	// ������Դ洢n��T����Ԫ�صĿռ�

	T *newelements = alloc.allocate(n);

	// ���·���Ŀռ��У���������Ԫ�صĸ���

	uninitialized_copy(elements, first_free, newelements);



	// ��������ԭ��Ԫ�أ�����ʱ��δ��ԭ��Ԫ��ռ�õĿռ佻����ϵͳ

	for (T *p = first_free; p != elements;)

	{

		alloc.destroy(--p);

	}



	// �ͷ�ԭ��Ԫ����ռ�õ��ڴ�

	if (elements)

	{

		alloc.deallocate(elements, end - elements);

	}



	// ���¸���Ҫ�����ݳ�Ա

	elements = newelements;

	first_free = elements + size;

	end = first_free + n;

}



template<typename T>

void Vector<T>::resize(const size_t n)                          // ����Vector��С

{

	// ���㵱ǰVector��С�Լ�����

	size_t size = first_free - elements;

	size_t capacity = end - elements;



	if (n > capacity)  // ����¿ռ�Ĵ�С����ԭ��������

	{

		reallocate();

		T temp;

		uninitialized_fill(elements + size, elements + n, temp);

		end = elements + n;

	}

	else if (n > size)          // ����¿ռ�Ĵ�С����ԭ��Vector�Ĵ�С

	{

		uninitialized_fill(elements + size, elements + n, temp);

	}

	else // ����¿ռ�Ĵ�СС�ڻ����ԭ��Vector�Ĵ�С

	{

		// �������ٶ���Ԫ��

		for (T *p = first_free; p != elements + n;)

		{

			alloc.destroy(--p);

		}

	}



	// ����������ݳ�Ա

	// elementsû�иı䣬�������

	first_free = elements + n;

	// end������n > capacityʱ���Ѿ�������

}

template<typename T>

T& Vector<T>::operator[](const size_t index)               // �±������

{

	size_t size = first_free - elements;

	// ������ܵĲ���������Ч�ķ�Χ�ڣ����׳��쳣

	if (index < 0 || index > size)

	{

		throw custom_exception("������������������");

	}

	return elements[index];

}



template<typename T>

size_t Vector<T>::size()                                                   // ��ȡVector��Ԫ�صĸ���

{

	size_t temp = first_free - elements;

	return temp;

}



template<typename T>

size_t Vector<T>::capacity()                                            // ��ȡVector������

{

	size_t temp = end - elements;

	return temp;

}



//��Vector���õ����Զ����쳣���Լ�Student��ֱ������£�

// �Զ����쳣�࣬��std::runtime_error�̳ж���

// ע�⣬�����ڴ˻����ϣ����Ӹ����ӵ����ݡ�����Ϊ�˷��㣬ʹ������򵥵���ʽ��

class custom_exception : public runtime_error

{

public:

	// ����һ��explicit�Ĺ��캯���������������ݸ�����

	explicit custom_exception(const string& s) : runtime_error(s)

	{

	}



	// An empty specification list says that the function does not throw any exception

	// �����������׳��κ��쳣

	virtual ~custom_exception() throw()

	{

	}

};



// ����ཫ��ΪVector��Ԫ�ص�����

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

//���ǿ��Կ���ǰ�漸��û���������������ã��������������������9�Σ�����Ϊ���Դ����е�9��Student�����������������ʱ���Զ������ٵĽ����������㣬���Բο���http://patmusing.blog.163.com/blog/static/13583496020101824142699/
//��Vector�У���û��ʵ��erase��������ΪeraseҪ�õ�Iterator������ƪ���Ͳ��ڴ��г���ش����ˣ���Ϊ��ԭ�������Ĵ�����һ���ģ�������Ĵ����Ѿ����Խ��Ͳ���http://patmusing.blog.163.com/blog/static/13583496020101831514657/ ���ᵽ�Ĺ���������������ε��õ����⡣
//����ٴ�ǿ��һ�£���ʽ���������������������ٶ��󣬵������ͷŶ�����ռ���ڴ档
// TestSharePtr.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <memory>
#include <iostream>
#include <assert.h>
#include <vector>
using namespace std;

struct Good : std::enable_shared_from_this<Good> // note: public inheritance
{
	std::shared_ptr<Good> getptr() {
		return shared_from_this();
	}
};

struct Bad
{
	std::shared_ptr<Bad> getptr() {
		return std::shared_ptr<Bad>(this);
	}
	~Bad() { std::cout << "Bad::~Bad() called\n"; }
};

class shared                                    //一个拥有shared_ptr的类    
{
private:
	shared_ptr<int> p;                          //shared_ptr成员变量    
public:
	shared(shared_ptr<int> p_) :p(p_) {}          //构造函数初始化shared_ptr        
	void print()                                //输出shared_ptr的引用计数和指向的值        
	{
		cout << "count:" << p.use_count()
			<< "v =" << *p << endl;
	}
};
void print_func(shared_ptr<int> p)                //使用shared_ptr作为函数参数    
{
	//同样输出shared_ptr的引用计数和指向的值        
	cout << "count:" << p.use_count()
		<< " v=" << *p << endl;
}

int TestSharePtr()
{
	//// Good: the two shared_ptr's share the same object
	//std::shared_ptr<Good> gp1 = std::make_shared<Good>();
	//std::shared_ptr<Good> gp2 = gp1->getptr();
	//std::cout << "gp2.use_count() = " << gp2.use_count() << '\n';

	//// Bad: shared_from_this is called without having std::shared_ptr owning the caller 
	//try {
	//	Good not_so_good;
	//	std::shared_ptr<Good> gp1 = not_so_good.getptr();
	//}
	//catch (std::bad_weak_ptr& e) {
	//	// undefined behavior (until C++17) and std::bad_weak_ptr thrown (since C++17)
	//	std::cout << e.what() << '\n';
	//}

	//// Bad, each shared_ptr thinks it's the only owner of the object
	//std::shared_ptr<Bad> bp1 = std::make_shared<Bad>();
	//std::shared_ptr<Bad> bp2 = bp1->getptr();
	//std::cout << "bp2.use_count() = " << bp2.use_count() << '\n';


	shared_ptr<int> sp(new int(10));                //一个指向整数的shared_ptr    
	assert(sp.unique());                            //现在shared_ptr是指针的唯一持有者     
	shared_ptr<int> sp2 = sp;                       //第二个shared_ptr,拷贝构造函数     
	assert(sp == sp2 && sp.use_count() == 2 && sp2.use_count()==2);       //两个shared_ptr相等,指向同一个对象,引用计数为2  

	*sp2 = 100;                                     //使用解引用操作符修改被指对象    
	assert(*sp == 100);                             //另一个shared_ptr也同时被修改     
	sp.reset();                                     //停止shared_ptr的使用    
	assert(!sp);

	assert(sp.use_count() == 0);


	shared_ptr<int> p(new int(100));
	shared s1(p), s2(p);                        //构造两个自定义类         
	s1.print();
	s2.print();
	*p = 20;                                    //修改shared_ptr所指的值        
	print_func(p);
	s1.print();


	typedef vector<shared_ptr<int> > vs;    //一个持有shared_ptr的标准容器类型        
	vs v(10);                               //声明一个拥有10个元素的容器，元素被初始化为空指针         
	int i = 0;
	for (vs::iterator pos = v.begin(); pos != v.end(); ++pos)
	{
		(*pos) = make_shared<int>(++i);     //使用工厂函数赋值            
		cout << *(*pos) << ", ";            //输出值        
	}
	cout << endl;
	shared_ptr<int> p1 = v[9];
	*p1 = 100;
	cout << *v[9] << endl;

	return 0;
}

//.为何会出现这种使用场合
//
//因为在异步调用中，存在一个保活机制，异步函数执行的时间点我们是无法确定的，然而异步函数可能会使用到异步调用之前就存在的变量。
//为了保证该变量在异步函数执期间一直有效，我们可以传递一个指向自身的share_ptr给异步函数，这样在异步函数执行期间share_ptr所管理的对象就不会析构，
//所使用的变量也会一直有效了（保活）。
//在智能指针的使用过程中我们会遇到这样一种情况，我们在类的成员函数调用某一个函数，而该函数需要传递一个当前对象的智能指针作为参数时，
//我们需要能够在成员函数中获得自己的智能指针。在多线程编程中也存在这样的应用，如果我们的线程函数绑定的是一个类成员函数，
//我们通过可以把该对象的智能指针作为参数传递到线程函数中，这种做法是人为的增加了对象的引用计数，延长对象的生命周期，
//防止线程函数在执行的时候对象被释放而引发内存错误。总之就是我们在实际的编码中会存在各种各样的应用。
//我们不能人为地通过this来构造一个当前对象的shared_ptr指针，如下错误的做法

//class TestClass : public std::enable_shared_from_this<TestClass>
//{
//public:
//	TestClass()
//	{
//	}
//	~TestClass()
//	{
//		//TestClassPtr tt = shared_from_this();
//	}
//	void TestPtr()
//	{
//		std::shared_ptr<TestClass> tt = shared_from_this();
//		Test(tt);
//	}
//}
//
//
//int main()
//{
//	TestClass t;
//	t.TestPtr(); //shared_from_this()错误
//
//	TestClass* t1(new TestClass());
//	t1->TestPtr();//shared_from_this()错误
//
//	std::shared_ptr<TestClass> t2(new TestClass());
//	t2->TestPtr(); //正确，已提前创建了shared_ptr
//}

//不能在构造函数\析构函数调用shared_from_this() 

struct Good1 : std::enable_shared_from_this<Good1> // 注意：继承
{
public:
	std::shared_ptr<Good1> getptr() {
		return shared_from_this();
	}
	~Good1() { std::cout << "Good::~Good() called" << std::endl; }

};
void TestShareFromThis()
{
	std::shared_ptr<Good1> gp1(new Good1());
	std::shared_ptr<Good1> gp2 = gp1->getptr();

	std::cout << "pg1.use_count:" << gp1.use_count() << std::endl;
	std::cout << "gp2.use_count:" << gp2.use_count() << std::endl;
}



class CLeader;
class CMember;

class CLeader
{
public:
	CLeader() { cout << "CLeader::CLeader()" << endl; }
	~CLeader() { cout << "CLeader:;~CLeader() " << endl; }

	std::shared_ptr<CMember> member;
};

class CMember
{
public:
	CMember() { cout << "CMember::CMember()" << endl; }
	~CMember() { cout << "CMember::~CMember() " << endl; }

	std::shared_ptr<CLeader> leader;
};



void TestSharedPtrCrossReference()
{
	cout << "TestCrossReference<<<" << endl;
	shared_ptr<CLeader> ptrleader(new CLeader);
	shared_ptr<CMember> ptrmember(new CMember);

	ptrleader->member = ptrmember;
	ptrmember->leader = ptrleader;

	cout << "  ptrleader.use_count: " << ptrleader.use_count() << endl;
	cout << "  ptrmember.use_count: " << ptrmember.use_count() << endl;

}
//从运行输出来看，两个对象的析构函数都没有调用，也就是出现了内存泄漏——原因在于：
//TestSharedPtrCrossReference（）函数退出时，两个shared_ptr对象的引用计数都是2，所以不会释放对象；
//这里出现了常见的交叉引用问题，这个问题，即使用原生指针互相记录时也需要格外小心；shared_ptr在这里也跌了跟头，ptrleader和ptrmember在离开作用域的时候，
//由于引用计数不为1，所以最后一次的release操作（shared_ptr析构函数里面调用）也无法destroy掉所托管的资源。
//为了解决这种问题，可以采用weak_ptr来隔断交叉引用中的回路。所谓的weak_ptr，是一种弱引用，表示只是对某个对象的一个引用和使用，而不做管理工作；


class Point2
{
public:
	Point2() : X(0), Y(0) { cout << "Point2::Point2(), (" << X << "," << Y << ")" << endl; }
	Point2(int x, int y) : X(x), Y(y) { cout << "Point2::Point2(int x, int y), (" << X << "," << Y << ")" << endl; }
	~Point2() { cout << "Point2::~Point2(), (" << X << "," << Y << ")" << endl; }

public:
	shared_ptr<Point2> Add(const Point2* rhs) { X += rhs->X; Y += rhs->Y; return shared_ptr<Point2>(this); }

private:
	int X;
	int Y;
};

void TestPoint2Add()
{
	cout << endl << "TestPoint2Add() >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
	shared_ptr<Point2> p1(new Point2(2, 2));
	shared_ptr<Point2> p2(new Point2(3, 3));

	//会崩掉：把一个指针赋值给了俩不共享的智能指针
	//p1->Add(p2.get());
	//p2.swap(p1->Add(p2.get()));
}

//输出为：
//TestPoint2Add() >> >> >> >> >> >> >> >> >> >> >> >> >> >> >> >>
//Point2::Point2(int x, int y), (2, 2)
//Point2::Point2(int x, int y), (3, 3)
//Point2::~Point2(), (3, 3)
//Point2::~Point2(), (5, 5)
//Point2::~Point2(), (3379952, 3211460)

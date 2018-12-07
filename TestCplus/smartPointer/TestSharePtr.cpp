// TestSharePtr.cpp : �������̨Ӧ�ó������ڵ㡣
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

class shared                                    //һ��ӵ��shared_ptr����    
{
private:
	shared_ptr<int> p;                          //shared_ptr��Ա����    
public:
	shared(shared_ptr<int> p_) :p(p_) {}          //���캯����ʼ��shared_ptr        
	void print()                                //���shared_ptr�����ü�����ָ���ֵ        
	{
		cout << "count:" << p.use_count()
			<< "v =" << *p << endl;
	}
};
void print_func(shared_ptr<int> p)                //ʹ��shared_ptr��Ϊ��������    
{
	//ͬ�����shared_ptr�����ü�����ָ���ֵ        
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


	shared_ptr<int> sp(new int(10));                //һ��ָ��������shared_ptr    
	assert(sp.unique());                            //����shared_ptr��ָ���Ψһ������     
	shared_ptr<int> sp2 = sp;                       //�ڶ���shared_ptr,�������캯��     
	assert(sp == sp2 && sp.use_count() == 2 && sp2.use_count()==2);       //����shared_ptr���,ָ��ͬһ������,���ü���Ϊ2  

	*sp2 = 100;                                     //ʹ�ý����ò������޸ı�ָ����    
	assert(*sp == 100);                             //��һ��shared_ptrҲͬʱ���޸�     
	sp.reset();                                     //ֹͣshared_ptr��ʹ��    
	assert(!sp);

	assert(sp.use_count() == 0);


	shared_ptr<int> p(new int(100));
	shared s1(p), s2(p);                        //���������Զ�����         
	s1.print();
	s2.print();
	*p = 20;                                    //�޸�shared_ptr��ָ��ֵ        
	print_func(p);
	s1.print();


	typedef vector<shared_ptr<int> > vs;    //һ������shared_ptr�ı�׼��������        
	vs v(10);                               //����һ��ӵ��10��Ԫ�ص�������Ԫ�ر���ʼ��Ϊ��ָ��         
	int i = 0;
	for (vs::iterator pos = v.begin(); pos != v.end(); ++pos)
	{
		(*pos) = make_shared<int>(++i);     //ʹ�ù���������ֵ            
		cout << *(*pos) << ", ";            //���ֵ        
	}
	cout << endl;
	shared_ptr<int> p1 = v[9];
	*p1 = 100;
	cout << *v[9] << endl;

	return 0;
}

//.Ϊ�λ��������ʹ�ó���
//
//��Ϊ���첽�����У�����һ��������ƣ��첽����ִ�е�ʱ����������޷�ȷ���ģ�Ȼ���첽�������ܻ�ʹ�õ��첽����֮ǰ�ʹ��ڵı�����
//Ϊ�˱�֤�ñ������첽����ִ�ڼ�һֱ��Ч�����ǿ��Դ���һ��ָ�������share_ptr���첽�������������첽����ִ���ڼ�share_ptr������Ķ���Ͳ���������
//��ʹ�õı���Ҳ��һֱ��Ч�ˣ������
//������ָ���ʹ�ù��������ǻ���������һ���������������ĳ�Ա��������ĳһ�����������ú�����Ҫ����һ����ǰ���������ָ����Ϊ����ʱ��
//������Ҫ�ܹ��ڳ�Ա�����л���Լ�������ָ�롣�ڶ��̱߳����Ҳ����������Ӧ�ã�������ǵ��̺߳����󶨵���һ�����Ա������
//����ͨ�����԰Ѹö��������ָ����Ϊ�������ݵ��̺߳����У�������������Ϊ�������˶�������ü������ӳ�������������ڣ�
//��ֹ�̺߳�����ִ�е�ʱ������ͷŶ������ڴ������֮����������ʵ�ʵı����л���ڸ��ָ�����Ӧ�á�
//���ǲ�����Ϊ��ͨ��this������һ����ǰ�����shared_ptrָ�룬���´��������

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
//	t.TestPtr(); //shared_from_this()����
//
//	TestClass* t1(new TestClass());
//	t1->TestPtr();//shared_from_this()����
//
//	std::shared_ptr<TestClass> t2(new TestClass());
//	t2->TestPtr(); //��ȷ������ǰ������shared_ptr
//}

//�����ڹ��캯��\������������shared_from_this() 

struct Good1 : std::enable_shared_from_this<Good1> // ע�⣺�̳�
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
//����������������������������������û�е��ã�Ҳ���ǳ������ڴ�й©����ԭ�����ڣ�
//TestSharedPtrCrossReference���������˳�ʱ������shared_ptr��������ü�������2�����Բ����ͷŶ���
//��������˳����Ľ����������⣬������⣬��ʹ��ԭ��ָ�뻥���¼ʱҲ��Ҫ����С�ģ�shared_ptr������Ҳ���˸�ͷ��ptrleader��ptrmember���뿪�������ʱ��
//�������ü�����Ϊ1���������һ�ε�release������shared_ptr��������������ã�Ҳ�޷�destroy�����йܵ���Դ��
//Ϊ�˽���������⣬���Բ���weak_ptr�����Ͻ��������еĻ�·����ν��weak_ptr����һ�������ã���ʾֻ�Ƕ�ĳ�������һ�����ú�ʹ�ã���������������


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

	//���������һ��ָ�븳ֵ�����������������ָ��
	//p1->Add(p2.get());
	//p2.swap(p1->Add(p2.get()));
}

//���Ϊ��
//TestPoint2Add() >> >> >> >> >> >> >> >> >> >> >> >> >> >> >> >>
//Point2::Point2(int x, int y), (2, 2)
//Point2::Point2(int x, int y), (3, 3)
//Point2::~Point2(), (3, 3)
//Point2::~Point2(), (5, 5)
//Point2::~Point2(), (3379952, 3211460)

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

int main()
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

	
	getchar();
	return 0;
}


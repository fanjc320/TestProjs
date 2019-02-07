#pragma once
using namespace std;

class B
{
public:
	B();
	B(const B & b){cout << "B copy constructor" << endl; }
	~B();

private:

};

B::B()
{
}

B::~B()
{
}

class A
{
public:
	A() :m_b(new B()) {
		cout << " A constructor " << endl;
	};
	A(const A& src) :m_b(new B(*(src.m_b))) { cout << "A copy constructor" << endl; }
	//A(const A& src) { new B(*(src.m_b)); cout << "A copy constructor" << endl; }
	//A(const A& src):m_b(src.m_b) {   cout << "A copy constructor" << endl; }
	A(A&& src) :m_b(src.m_b) { src.m_b = nullptr; cout << " A move constructor" << endl; }
	A& operator= (const A& src)
	{
		if (this==&src)//!!!
		{
			return *this;
		}
		delete m_b;//!!!
		m_b = new B(*src.m_b);
		cout << "A& operator= (const A& src)" << endl;
		return *this;
	}
	A& operator= (A&& src) noexcept
	{
		if (this==&src)
		{
			return *this;
		}
		delete m_b;
		m_b = src.m_b;
		src.m_b = nullptr;
		cout << "A& operator= (A&& src) " << endl;
		return *this;
	}
	~A() {
		//delete m_b; cout << " ~A " << endl;
	}
private:
	B* m_b;
public:
	void checkB() {
		if (m_b==nullptr)
		{
			cout <<" m-b == null "<< endl;
		}
	}
};

static A getA()
{
	A a;
	return a;
}

void TestMove_Class()
{
	A a;
	A a1=a;//= A a1(a);
	std::cout << "================================================" << std::endl;
	a = a1;
	std::cout << "================================================" << std::endl;
	A a2(std::move(a1));//move ֮��õ���ֵ
	//a1.checkB();//!!�� a1��m_b�ѱ���Ϊnull,a1���ٰ���new ��������Դ���ѱ�ת�Ƶ�a2��
	//cout << "---" << endl;
	//a2.checkB();
	std::cout << "================================================" << std::endl;

	a2 = getA();//!!! a2 �����ƺ�a2ԭ���Ķ����ͷ�
	std::cout << "================================================" << std::endl;
	A a3(getA());
}
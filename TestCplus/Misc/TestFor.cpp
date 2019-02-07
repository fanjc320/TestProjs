#include "stdafx.h"

void myfunction(int i) {  // function:
	std::cout << ' ' << i;
}

struct myclass {           // function object type:
	void operator() (int i) { std::cout << ' ' << i; }
} myobject;

struct State
{
	State(int state) : m_state(state) {}
	~State() { std::cout << "~State(), m_state=" << m_state << std::endl; }

	void setState(int state) { m_state = state; }
	int getState() const { return m_state; }

	void print() const { std::cout << "State::print: " << m_state << std::endl; }

private:
	int m_state;
};


int TestFor() {
	std::vector<int> myvector;
	myvector.push_back(10);
	myvector.push_back(20);
	myvector.push_back(30);

	std::cout << "myvector contains:";
	for_each(myvector.begin(), myvector.end(), myfunction);
	std::cout << '\n';

	// or:
	std::cout << "myvector contains:";
	for_each(myvector.begin(), myvector.end(), myobject);
	std::cout << '\n';


	std::vector<State*> vect;

	vect.push_back(new State(0));
	vect.push_back(new State(1));
	vect.push_back(new State(2));
	vect.push_back(new State(3));

	//mem_fun_ref的作用和用法跟mem_fun一样，唯一的不同就是：当容器中存放的是对象实体的时候用mem_fun_ref，当容器中存放的是对象的指针的时候用mem_fun。
	std::for_each(vect.begin(), vect.end(), std::mem_fun(&State::print));

	return 0;
}
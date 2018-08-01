// TestUniquePtr.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <memory>
#include <cstdio>
#include <fstream>
#include <cassert>
#include <functional>
using namespace  std;
struct B {
	virtual void bar() { std::cout << "B::bar\n"; }
	virtual ~B() = default;
};
struct D : B
{
	D() { std::cout << "D::D\n"; }
	~D() { std::cout << "D::~D\n"; }
	void bar() override { std::cout << "D::bar\n"; }
};

// ���� unique_ptr �ĺ�������ֵ������ֵ���ý�����
std::unique_ptr<D> pass_through(std::unique_ptr<D> p)
{
	p->bar();
	return p;
}

int main()
{
	std::cout << "unique ownership semantics demo\n";
	{
		auto p = std::make_unique<D>(); // p ��ռ�� D �� unique_ptr
		auto q = pass_through(std::move(p));
		assert(!p); // ���� p ��ռ���κ����ݲ����п�ָ��
		q->bar();   // �� q ռ�� D ����
	} // ~D �����ڴ�

	auto p1 = std::make_unique<D>();
	//auto p2 = p1;,error


	std::cout << "Runtime polymorphism demo\n";
	{
		std::unique_ptr<B> p = std::make_unique<D>(); // p ��ռ�� D �� unique_ptr
													  // ��Ϊָ������ָ��
		p->bar(); // ���ɷ�

		std::vector<std::unique_ptr<B>> v;  // unique_ptr �ܴ洢������
		v.push_back(std::make_unique<D>());
		v.push_back(std::move(p));
		assert(!p);
		v.emplace_back(new D);
		//v.push_back(new D);//����
		for (auto& p : v) p->bar(); // ���ɷ�
	} // ~D called 3 times

	std::cout << "initialized with new";
	{
		//unique_ptr<D> p = new D;
	}

	std::cout << "Custom deleter demo\n";
	std::ofstream("demo.txt") << 'x'; // ׼��Ҫ�����ļ�
	{
		std::unique_ptr<std::FILE, decltype(&std::fclose)> fp(std::fopen("demo.txt", "r"),
			&std::fclose);
		if (fp) // fopen ���Դ�ʧ�ܣ�������� fp ���п�ָ��
			std::cout << (char)std::fgetc(fp.get()) << '\n';
	} // fclose() �����ڴˣ������� FILE* ���ǿ�ָ��
	  // ���� fopen �ɹ���

	std::cout << "Custom lambda-expression deleter demo\n";
	{
		std::unique_ptr<D, std::function<void(D*)>> p(new D, [](D* ptr)
		{
			std::cout << "destroying from a custom deleter...\n";
			delete ptr;
		});  // p ռ�� D
		p->bar();
	} // �������� lambda ������ D

	std::cout << "Array form of unique_ptr demo\n";
	{
		std::unique_ptr<D[]> p{ new D[3] };
	} // ���� ~D 3 ��

	getchar();
}


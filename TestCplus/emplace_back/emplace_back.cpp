// emplace_back.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include<string>
using namespace std;

struct President
{
	std::string name;
	std::string country;
	int year;

	President(std::string p_name, std::string p_country, int p_year)
		: name(std::move(p_name)), country(std::move(p_country)), year(p_year)
	{
		std::cout << "I am being constructed.\n";
	}
	President(const President& other)
		: name(std::move(other.name)), country(std::move(other.country)), year(other.year)
	{
		std::cout << "I am being copy constructed.\n";
	}
	//�򿪺͹رտ���ͬЧ��
	/*President(President&& other)
		: name(std::move(other.name)), country(std::move(other.country)), year(other.year)
	{
		std::cout << "I am being moved.\n";
	}*/
	//President& operator=(const President& other) = default;
	~President(){ std::cout << "I am being detructed.\n"; }
};


//����ȥ��President(President&& other)�鿴������

int main()
{
	//This new element is constructed in place using args as the arguments for its constructor.
	//A similar member function exists, push_back, which either copies or moves an existing object into the container.

	//�к�û��reserve()���ܴ�!!!!!
	std::vector<President> elections;
	elections.reserve(10);
	std::cout << "emplace_back:\n";
	elections.emplace_back("Nelson Mandela", "South Africa", 1994); //û����Ĵ���  
	cout << "--------emplace president---------"<<endl;
	elections.emplace_back(President("fanjinchang", "South Kerea", 2030)); //û����Ĵ��� 
	cout << "--------emplace original pre---------" << endl;
	President pre("pre","precountry",1026);
	cout << "--------emplace original president---------" << endl;
	elections.emplace_back(pre);


	std::vector<President> reElections;
	reElections.reserve(10);
	cout << "--------push_back president---------" << endl;
	//elections.push_back("fjc", "China", 2020); // no overloaded function takes 3 arguments
	reElections.push_back(President("Franklin Delano Roosevelt", "the USA", 1936));
	cout << "--------pushback original president---------" << endl;
	reElections.push_back(pre);

	std::cout << "\nContents:\n";
	for (President const& president : elections) {
		std::cout << president.name << " was elected president of "
			<< president.country << " in " << president.year << ".\n";
	}
	for (President const& president : reElections) {
		std::cout << president.name << " was re-elected president of "
			<< president.country << " in " << president.year << ".\n";
	}


	getchar();
	return 0;
}


// list.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <list>
#include <iostream>
using namespace  std;


class MapObject
{
public:
	MapObject();
	~MapObject();

private:

};

MapObject::MapObject()
{
}

MapObject::~MapObject()
{
	cout << "~MapObject" << endl;
}

typedef std::list<MapObject*> ObjectList;

int main()
{
	MapObject* pObj = new MapObject();
	ObjectList m_objectsInRange;
	m_objectsInRange.push_back(pObj);

	m_objectsInRange.erase(m_objectsInRange.begin());
	m_objectsInRange.remove(pObj);//据说调用析构

	delete pObj;
	delete pObj;
	getchar();
    return 0;
}


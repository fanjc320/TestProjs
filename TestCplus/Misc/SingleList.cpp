#include "stdafx.h"

int TestSingleList() {
	ListNode<int>* pNode1 = new ListNode<int>(1);
	AddToTail(pNode1, 2);
	AddToTail(pNode1, 3);
	AddToTail(pNode1, 4);
	AddToTail(pNode1, 5);
	AddToTail(pNode1, 6);
	cout << "��תǰ��" << endl;
	Print(pNode1);

	ListNode<int>* pNode = ReverseList(pNode1);
	cout << "��ת��" << endl;
	Print(pNode);

	return 0;
}
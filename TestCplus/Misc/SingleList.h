#pragma once

template<typename T>
struct ListNode
{
	T m_Value;
	ListNode* m_pNext;
	ListNode(){}
	ListNode(T v):m_Value(v),m_pNext(nullptr){}
};

template<typename T>
void AddToTail(ListNode<T>* pHead, T value) {
	ListNode<T>* pNew = new ListNode<T>();
	pNew->m_Value = value;
	pNew->m_pNext = nullptr;

	if (pHead == nullptr) {
		pHead = pNew;
	}
	else
	{
		ListNode<T>* pNode = pHead;
		while (pNode->m_pNext!=nullptr)
		{
			pNode = pNode->m_pNext;
		}
		pNode->m_pNext = pNew;
	}
}

template<typename T>
void Print(ListNode<T>* head) {
	ListNode<T>* pNode = head;
	while (pNode!=nullptr)
	{
		cout << pNode->m_Value << endl;
		pNode = pNode->m_pNext;
	}
}

template<typename T>
ListNode<T>* ReverseList(ListNode<T>* head) {
	ListNode<T>* pNode = head;
	ListNode<T>* pPrev = nullptr;
	while (pNode!=nullptr)
	{
		ListNode<T>* pNext = pNode->m_pNext;
		pNode->m_pNext = pPrev;
		pPrev = pNode;
		pNode = pNext;
		//error:À¿—≠ª∑
		/*ListNode<T>* pNext = pNode->m_pNext;
		pPrev = pNode;
		pNext->m_pNext = pPrev;
		pNode = pNext;*/
	}
	return pPrev;
}

int TestSingleList();
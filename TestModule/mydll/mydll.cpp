// mydll.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "mydll.h"


// ���ǵ���������һ��ʾ��
MYDLL_API int nmydll=10;

// ���ǵ���������һ��ʾ����
MYDLL_API int fnmydll(void)
{
    return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� mydll.h
Cmydll::Cmydll()
{
    return;
}

int Cmydll::dllAdd(int plus1, int plus2)
{
	return plus1 + plus2;
}

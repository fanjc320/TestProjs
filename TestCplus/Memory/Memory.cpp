// Memory.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <assert.h>
#include <iostream>

using namespace std;

struct C {
	C() {}
	C(const C&) { std::cout << "A copy was made.\n"; }
};

C f() {
	return C();
}

int main()
{
	#ifdef TEST1
FILE *fp = fopen("Memory.cpp", "rb");
	/*FILE * fp, *stream2;
	errno_t err;
	err = fopen_s(&fp,"Memory.cpp","r");*/

	char a;
	char *buf = &a;
	int N = 99;

	fread(buf,1,1024,fp); //�����еı��������쳣���е��ƻ���ջ���������assert���쳣
	assert(N==99);
	fclose(fp);
#endif

	C obj = f();

	getchar();
	return 0;

}

//linux��
//#include<netdb.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
//char *rm_lang(const char *str)
//{
//	int len = strlen(str) + 1;
//	char *tmp = malloc(len);
//	memcpy(tmp, str, len);
//	while (1)
//	{
//		char *tmp_1 = strstr(tmp, "LANG");
//		if (tmp_1 == NULL)
//			break;
//		char *tmp_2 = strstr(tmp_1 + 1, "|");
//		memmove(tmp_1, tmp_2 + 1, strlen(tmp_2) + 1);
//		memmove(tmp_1-1, tmp_2 + 1, strlen(tmp_2) + 1);//�ᱨ��
//	}
//	return tmp;
//}
//void  main()
//{
//	char *str = "LANG3044| admin| IP:192.168.124.218";
//	char *tmp = rm_lang(str);
//	printf("%s\n", tmp);
//	free(tmp);
//}



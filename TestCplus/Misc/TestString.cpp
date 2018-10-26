#include "stdafx.h"

//strc一定要以'\0'结尾，且长度不大于strDest
char* strcpy_My(char* strDest, const char* strSrc)
{
	assert((strDest != nullptr) && (strSrc != nullptr));
	char* strDestBegin = strDest;
	//如果 strSrc 不以strSrc结尾
	while ((*strDest++ = *strSrc++) != '\0')
	{
		int cnt = 0;
		++cnt;
		//cout << cnt << endl;
	}
	//*strDest = '\0';//Run-Time Check Failure #2  Stack around the variable 'a' was corrupted 
	return strDestBegin;
}

//std::string eraseNumber(string strIn)
//{
//
//}

//// 去掉字符串中的数字
//string eraseNumber(string strIn) {
//	auto it = strIn.begin();
//	for (; it != strIn.end();) {
//		if (*it >= '0'&&*it <= '9') {
//			cout << *it << endl;
//			it = strIn.erase(it);
//		}
//		else
//		{
//			++it;
//		}
//	}
//	return strIn;
//}



void TestStrErase() {
	/*string testStr = "abc23d5j9oln7";
	string newStr = eraseNumber(testStr);
	printf("TestStrErase old:%s,new:%s \n", testStr.c_str(), newStr.c_str());*/
}
 
void TestStrCp() {
	char a[2] = { 'a','b' };
	printContain<char>(a, sizeof(a));
	char b[2] = { 'z','\0' };
	printContain<char>(b, sizeof(b));

	strcpy_My(a, b);
	printContain(a, sizeof(a));
	char* pa = a;
	char* pa1 = a + 2;
	printContain(pa, ++pa);
	printContain(pa, pa1);
	//printContain<char>(a, sizeof(a)); 
	//离开时汇报：Run-Time Check Failure #2  Stack around the variable 'a' was corrupted //https://blog.csdn.net/chenyujing1234/article/details/8261914 无用
}
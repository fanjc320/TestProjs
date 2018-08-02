// time.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <time.h>
#include <iostream>
using namespace std;
typedef  unsigned int uint32;
 
string GetPayOrder()
{
	static uint32 ids = 0;
	ids++;
	if (ids > 10000)  ids = 1;
	char buf[128];
	time_t t = time(NULL);
	tm* local = localtime(&t);
	strftime(buf, 128, "%y%m%d%H%M%S", local);
	//strftime(buf, 128, "%y-%m-%d-%H-%M-%S", local);
	string backstr = buf;
	char buf2[128];
	sprintf(buf2, "%.5d", ids);
	backstr = backstr + string(buf2);
	return backstr;
}

int main()
{
	time_t now = time(NULL);
	struct tm * timeinfo = localtime(&now);
	int aYear = timeinfo->tm_year;
	int amonth = timeinfo->tm_mon + 1;
	int date = timeinfo->tm_mday;
	int hour = timeinfo->tm_hour;
	int minute = timeinfo->tm_min;
	int sec = timeinfo->tm_sec;

	int time = (aYear % 100) * 100000000 + amonth * 1000000 + date*10000+minute*100+ sec;
	std::cout <<aYear<<" "<< time <<" now: "<<now<< endl;

	char szNumbers[] = "250068492 7b06af00 1100011011110101010001100000 0x6fffff";
	char * pEnd;
	unsigned long long int ulli1, ulli2, ulli3, ulli4;
	ulli1 = strtoull(szNumbers, &pEnd, 10);
	ulli2 = strtoull(pEnd, &pEnd, 16);
	ulli3 = strtoull(pEnd, &pEnd, 2);
	ulli4 = strtoull(pEnd, NULL, 0);
	printf("The decimal equivalents are: %llu, %llu, %llu and %llu.\n", ulli1, ulli2, ulli3, ulli4);

	string tt = GetPayOrder();
	cout << tt.c_str() << endl;
	unsigned long long ll = strtoull(tt.c_str(),0,0);
	cout << ll << endl;

	char buf[128];
	snprintf(buf,sizeof(buf),"%.4u %4u",912345,912345);
	cout << "buf:" << buf << endl;

	getchar();
    return 0;
}


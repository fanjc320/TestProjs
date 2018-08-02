// multithread.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#include <iostream>  
#include <thread>  
#include <Windows.h>  

using namespace std;

void thread01()
{
	for (int i = 0; i < 5; i++)
	{
		cout << "Thread 01 is working ！" << endl;
		Sleep(100);
	}
}
void thread02()
{
	for (int i = 0; i < 5; i++)
	{
		cout << "Thread 02 is working ！" << endl;
		Sleep(200);
	}
}

int main()
{
	thread task01(thread01);
	thread task02(thread02);
	//当我们调用某个线程的这个方法时，这个方法会挂起调用线程，直到被调用线程结束执行，调用线程才会继续执行。
	task01.join();
	task02.join();

	for (int i = 0; i < 5; i++)
	{
		cout << "Main thread is working ！" << endl;
		Sleep(200);
	}
	system("pause");
}

//https://www.cnblogs.com/bokeyuan-dlam/articles/6185121.html
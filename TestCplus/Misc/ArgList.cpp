#include "stdafx.h"

// Build with VS2008withSP1, /W4 
#include <cstdio> 
#include <cstdarg> 

#include <iostream>

void foo(char arg, char* arg2, ...)
{
	printf_s("sizeof(double)        = %d\n", sizeof(double));
	printf_s("sizeof(unsigned char) = %d\n", sizeof(unsigned char));
	printf_s("sizeof(int)           = %d\n", sizeof(int));
	printf_s("sizeof(short)         = %d\n", sizeof(short));
	printf_s("sizeof(long long)     = %d\n", sizeof(long long));

	printf_s("\n");

	printf_s("arg  = %c\n", arg);
	printf_s("arg2 = %s\n", arg2);

	va_list arg_ptr;                   // ! 
	va_start(arg_ptr, arg2);           // ! 
									   // arg_ptr: 0x003ffba0 

	double arg3 = va_arg(arg_ptr, double);
	printf_s("arg3 = %f\n", arg3);   // arg_ptr: 0x003ffba8 == 0x003ffba0 + sizeof(double) 

	unsigned char arg4 = va_arg(arg_ptr, unsigned char);
	printf_s("arg4 = %c\n", arg4);   // arg_ptr: 0x003ffbac != 0x003ffba8 + sizeof(unsigned char) 
									   //          0x003ffbac == 0x003ffba8 + 4 

	int arg5 = va_arg(arg_ptr, int);
	printf_s("arg5 = %d\n", arg5);   // arg_ptr: 0x003ffbb0 != 0x003ffbac + sizeof(int) 

	short arg6 = va_arg(arg_ptr, short);
	printf_s("arg6 = %hd\n", arg6);  // arg_ptr: 0x003ffbb4 != 0x003ffbb0 + sizeof(short) 
									   //          0x003ffbb4 == 0x003ffbb0 + 4 

	long long arg7 = va_arg(arg_ptr, long long);
	printf_s("arg7 = %lld\n", arg7); // arg_ptr: 0x003ffbbc == 0x003ffbb4 + sizeof(long long) 

	va_end(arg_ptr);                   // ! 
									   // arg_ptr: 0x00000000 
}

//int main()
//{
//	foo('A', "ABCDEF", 3.14, 'B', 2147483647, 32767, 9223372036854775807);
//
//	int i;
//	while (std::cin >> i);
//
//	return 0;
//}
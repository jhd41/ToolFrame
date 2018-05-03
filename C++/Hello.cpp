// Hello.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>

int AtoI(const char* sz);


int AtoI( char* sz) {


	int number = 0;
	for(int i=0;sz[i];i++)
	{
		number = number*10+ (sz[i]- '0');
		
	}
		return number;
}
int main()

{
	char str[] = "34";
	int a = AtoI(str);
	printf("%d", a);
	return 0;
}


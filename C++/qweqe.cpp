// qweqe.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>

int AtoI(const char* szString)  //空
{
	int nNumber = 0;

	for (int nIndex = 0; szString[nIndex] != '\0'; nIndex++)    //通过循环遍历字符串的每个字符

		if (szString[nIndex] >= '0' && szString[nIndex] <= '9') //判断是否属于0-9
		{
			nNumber = szString[nIndex] - '0' + 10 * nNumber;    //成立则转化
		}
     return nNumber;	
}
int main()
{
	char szString[] = "1234";
	int nInt = AtoI(szString);
	std::cout << nInt << std::endl;
    return 0;
}


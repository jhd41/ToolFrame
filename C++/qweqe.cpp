// qweqe.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>

int AtoI(const char* szString)  //��
{
	int nNumber = 0;

	for (int nIndex = 0; szString[nIndex] != '\0'; nIndex++)    //ͨ��ѭ�������ַ�����ÿ���ַ�

		if (szString[nIndex] >= '0' && szString[nIndex] <= '9') //�ж��Ƿ�����0-9
		{
			nNumber = szString[nIndex] - '0' + 10 * nNumber;    //������ת��
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


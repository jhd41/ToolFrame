// iterator.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
#include<list>


int main()
{
	std::list<int>vInt;              //����һ������Ϊint������list
	vInt.push_back(1);               //��β������Ԫ��1
	vInt.push_back(8);               //��β������Ԫ��8
	vInt.push_back(6);               //��β������Ԫ��6
	vInt.push_back(7);               //��β������Ԫ��7
	vInt.push_back(9);               //��β������Ԫ��9

	//�������
	for (std::list<int>::iterator iter = vInt.begin(); iter != vInt.end(); iter++)
          std::cout << *iter << std::endl;

	std::cout << "����������" << std::endl;

	//��ʼ���в�������
	for (std::list<int>::iterator iter = vInt.begin(); iter != vInt.end(); )
	{
		if (*iter==6||*iter==7)
		{
			vInt.erase(iter++);      //�ӣ�������ʱ��iterator��ʧЧ            
		}
		else
		{
			iter++;
		}
	}

	//�����������
	for (std::list<int>::iterator iter = vInt.begin(); iter != vInt.end(); iter++)
		std::cout << *iter << std::endl;                                            
     return 0;
}


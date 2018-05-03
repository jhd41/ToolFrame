// iterator.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<list>


int main()
{
	std::list<int>vInt;              //创建一个类型为int的容器list
	vInt.push_back(1);               //从尾部插入元素1
	vInt.push_back(8);               //从尾部插入元素8
	vInt.push_back(6);               //从尾部插入元素6
	vInt.push_back(7);               //从尾部插入元素7
	vInt.push_back(9);               //从尾部插入元素9

	//遍历输出
	for (std::list<int>::iterator iter = vInt.begin(); iter != vInt.end(); iter++)
          std::cout << *iter << std::endl;

	std::cout << "擦除进行中" << std::endl;

	//开始进行擦除步骤
	for (std::list<int>::iterator iter = vInt.begin(); iter != vInt.end(); )
	{
		if (*iter==6||*iter==7)
		{
			vInt.erase(iter++);      //坑，当擦除时，iterator会失效            
		}
		else
		{
			iter++;
		}
	}

	//容器遍历输出
	for (std::list<int>::iterator iter = vInt.begin(); iter != vInt.end(); iter++)
		std::cout << *iter << std::endl;                                            
     return 0;
}


// map.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<map>
#include<string>
using std::string;

int main()
{
	std::map<string, int>M;
	M["a"] = 1;
	M["b"] = 2;
	M["c"] = 3;
    std::map<string, int>::iterator it;
	for (it = M.begin(); it != M.end(); ++it)
		std::cout << "key:" << it->first << "   value:" << it->second << std::endl;
	return 0;
}

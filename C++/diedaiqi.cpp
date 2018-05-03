studio// diedaiqi.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<vector>
using namespace std;



int main()
{
	vector<int>vecInt;                                 //定义一个Int类型的容器vecInt


	//把需要插入的元素用push_back从尾巴部分放进去
	vecInt.push_back(1);                               
	vecInt.push_back(8);
	vecInt.push_back(6);
	vecInt.push_back(7);
	vecInt.push_back(9);

	//用迭代器遍历vector
	for (vector<int>::iterator iter = vecInt.begin(); iter != vecInt.end(); ++iter)
    cout << *iter << endl;

	//擦除3，4位
	printf("兄弟们把三四位干掉！！\n");
	vecInt.erase(vecInt.begin() + 2,vecInt.end()-1);  //用erase方法进行擦除

	//再次使用迭代器遍历vector
	for (vector<int>::iterator iter = vecInt.begin(); iter != vecInt.end(); ++iter)
    cout << *iter << endl;
    return 0;
}



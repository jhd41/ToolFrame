studio// diedaiqi.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
#include<vector>
using namespace std;



int main()
{
	vector<int>vecInt;                                 //����һ��Int���͵�����vecInt


	//����Ҫ�����Ԫ����push_back��β�Ͳ��ַŽ�ȥ
	vecInt.push_back(1);                               
	vecInt.push_back(8);
	vecInt.push_back(6);
	vecInt.push_back(7);
	vecInt.push_back(9);

	//�õ���������vector
	for (vector<int>::iterator iter = vecInt.begin(); iter != vecInt.end(); ++iter)
    cout << *iter << endl;

	//����3��4λ
	printf("�ֵ��ǰ�����λ�ɵ�����\n");
	vecInt.erase(vecInt.begin() + 2,vecInt.end()-1);  //��erase�������в���

	//�ٴ�ʹ�õ���������vector
	for (vector<int>::iterator iter = vecInt.begin(); iter != vecInt.end(); ++iter)
    cout << *iter << endl;
    return 0;
}



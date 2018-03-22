// variety_sort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "Constant.h"
#include "SingletonFactory.h"

using namespace std;

//获取数字
int* get_num(int n)
{
	int *p = new int[n];
	for(int i = 0; i < n; i++)
	{
		cin>>p[i];
	}
	return p;
}



//输出数字
void show_num(int *L, int n)
{
	for(int i = 0; i < n; i++)
		cout<<L[i]<<' ';

	cout<<endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int *num_array = NULL;
	int n;
	cout<<"how many numbers do you want to input?"<<endl;
	cin>>n;

	cout<<"please input "<<n<<" numbers"<<endl;
	num_array = get_num(n);

	show_num(num_array, n);

	SingletonFactory *FactoryBubble = SingletonFactory::GetInstance(kFactory_quick);
	FactoryBubble->Sort(num_array, n);

	
	show_num(num_array, n);


	int end;
	cin >> end;
	return 0;
    
}

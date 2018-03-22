#ifndef _FACTORYHEAP_H
#define _FACTORYHEAP_H

#include <iostream>
#include "SingletonFactory.h"

using namespace std;

//Factory Heap

class FactoryHeap : public SingletonFactory
{
	friend class SingletonFactory;

public:
	void Sort(int *L, int n)
	{
		//构造大堆树
		for(int i = n/2-1;i >= 0; i--)
			Heap_Tree(L, i, n);


		//调换n-1次即可
		for(int i = 1; i < n; i++)
		{
			swap(L, 0, n-i);
			//第二个参数都是0，因为从最大树开始移动即可
			Heap_Tree(L, 0, n-i);
		}
		
	}

protected:
	FactoryHeap(){

	}

	~FactoryHeap(){
	
	}

private:

	static FactoryHeap *m_InstanceHeap;

	class GC
	{
	public:
		~GC()
		{
			if(m_InstanceHeap != NULL)
			{
				cout<< "GC Heap test"<<endl;
				delete m_InstanceHeap;
				m_InstanceHeap = NULL;
			}
		}
	};

	static GC gc;

	void Heap_Tree(int *L, int beg, int n);

	
	};

void FactoryHeap::Heap_Tree(int *L, int beg, int n)
{
	
	int temp = L[beg];
	int i;

	//n/2是非叶子节点的数量
	for(i = beg; i < n/2; )
	{
		int j = i*2+1;
		//选出两子节点中的最大值
		if(j + 1 < n && L[j] < L[j + 1])
			j = j+1;

		if(temp > L[j])
			break;

		//换位，i移动
		L[i] = L[j];
		i = j;
	}

	L[i] = temp;


}



#endif
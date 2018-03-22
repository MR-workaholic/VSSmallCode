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
		//��������
		for(int i = n/2-1;i >= 0; i--)
			Heap_Tree(L, i, n);


		//����n-1�μ���
		for(int i = 1; i < n; i++)
		{
			swap(L, 0, n-i);
			//�ڶ�����������0����Ϊ���������ʼ�ƶ�����
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

	//n/2�Ƿ�Ҷ�ӽڵ������
	for(i = beg; i < n/2; )
	{
		int j = i*2+1;
		//ѡ�����ӽڵ��е����ֵ
		if(j + 1 < n && L[j] < L[j + 1])
			j = j+1;

		if(temp > L[j])
			break;

		//��λ��i�ƶ�
		L[i] = L[j];
		i = j;
	}

	L[i] = temp;


}



#endif
#ifndef _FACTORYBUBBLE_H
#define _FACTORYBUBBLE_H

#include <iostream>
#include "SingletonFactory.h"

using namespace std;

// Factory Bubble
class FactoryBubble : public SingletonFactory
{
	friend class SingletonFactory;

public:
	void Sort(int *L, int n)
	{
		
		bool flag = false;
		for(int i = 0; i < n-1; i++)
			{
				flag = false;  //用于快速判断是否已经排序
				for(int j = 0; j < (n - i - 1); j++)
					{
						// if(L[j]%2 != L[j+1]%2)  //一奇一偶
						// 	{
						// 		if(L[j]%2 == 0)
						// 			{
						// 				swap(L, j, j+1);
						// 				flag = true;
						// 			}
						// 	}else
						// 	{
						// 		if(L[j] > L[j + 1])
						// 			{
						// 				swap(L, j, j+1);
						// 				flag = true;
						// 			}
						// 	}
						if (L[j] > L[j + 1]) {
							swap(L, j, j + 1);
							flag = true;
						}
					}

				//假如一次都没有调换，证明已经排好序了
				if(!flag)
					return ;
			}
	}

	//返回一个函数指针
	//void (FactoryBubble::*p) (int *L, int n);

protected:
	FactoryBubble(){


	}
	virtual ~FactoryBubble(){}

private:
	static FactoryBubble *m_InstanceBubble;

	// Just to release the resource
	class GC
	{
	public:
		~GC()
		{
			if (m_InstanceBubble != NULL)
			{
				cout<<"GC Bubble test"<<endl;
				delete m_InstanceBubble;
				m_InstanceBubble = NULL;
			}
		}
	};
	static GC gc;
};


#endif

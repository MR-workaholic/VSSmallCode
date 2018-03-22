#ifndef _FACTORYINSERTION_H
#define _FACTORYINSERTION_H

#include <iostream>
#include "SingletonFactory.h"

using namespace std;

// Factory Insertion
class FactoryInsertion : public SingletonFactory
{
	friend class SingletonFactory;

public:
	void Sort(int *L, int n)
	{

	if(n <= 1)
		return;
	else
	{
		//从第二个数开始，与前一个比较，都是一直往左边比较的
		for(int i = 1; i < n; i++)
		{
			if(L[i] < L[i - 1])
			{
				int temp = L[i];
				int j = i - 1;
				while(j >= 0 && L[j] > temp )
				{
				  L[j + 1] = L[j];
				  j--;
				}
				L[j + 1] = temp;

			}
			/*同样可行的写法
			    if (vec.at(i - 1) > vec.at(i)) {
				  int target = vec.at(i);
				  int j;
				  for (j = i - 1; j >= 0; j--) {
					if (vec.at(j) > target) {
					  vec.at(j + 1) = vec.at(j);
					}else {
					  break;
					}
				  }
				  vec.at(j + 1) = target;
				}
			*/
		}
	}

	}



	//返回一个函数指针
	//void (FactoryBubble::*p) (int *L, int n);

protected:
	FactoryInsertion(){

	}
	virtual ~FactoryInsertion(){}

private:
	static FactoryInsertion *m_InstanceInsertion;

	// Just to release the resource
	class GC
	{
	public:
		~GC()
		{
			if (m_InstanceInsertion != NULL)
			{
				cout<<"GC Insertion test"<<endl;
				delete m_InstanceInsertion;
				m_InstanceInsertion = NULL;
			}
		}
	};
	static GC gc;
};


#endif
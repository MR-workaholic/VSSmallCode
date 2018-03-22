#ifndef _FACTORYSELECTION_H
#define _FACTORYSELECTION_H

#include <iostream>
#include "SingletonFactory.h"

using namespace std;

// Factory Selection
class FactorySelection : public SingletonFactory
{
	friend class SingletonFactory;

public:
	void Sort(int *L, int n)
	{
		
		for(int i = 0; i < n; i++)
			{
				int min = i;
				for(int j = i; j < (n - 1); j++)
					{
						if(L[min] > L[j + 1])
							min = j + 1;
					}
				swap(L, min, i);
			}

	}



	//返回一个函数指针
	//void (FactoryBubble::*p) (int *L, int n);

protected:
	FactorySelection(){

	}
	virtual ~FactorySelection(){}

private:
	static FactorySelection *m_InstanceSelection;

	// Just to release the resource
	class GC
	{
	public:
		~GC()
		{
			if (m_InstanceSelection != NULL)
			{
				cout<<"GC Selection test"<<endl;
				delete m_InstanceSelection;
				m_InstanceSelection = NULL;
			}
		}
	};
	static GC gc;
};


#endif

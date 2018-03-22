#ifndef _SINGLETONFACTORY_H_
#define _SINGLETONFACTORY_H_

#include <iostream>

#include "Constant.h"

using namespace std;

// The singleton factory
class SingletonFactory
{
public:

	static SingletonFactory *GetInstance(FactoryEnum factory);
	virtual void Sort(int *L, int n) = 0; // ´¿Ðéº¯Êý
	//Êý×Ö»¥»»
	void swap(int *L, int i, int j)
	{
		int temp = L[j];
		L[j] = L[i];
		L[i] = temp;
	}

protected:
	SingletonFactory(){
		m_Instance = NULL;
	}
	virtual ~SingletonFactory(){}

private:
	static SingletonFactory *m_Instance;

	// Just to release the resource
	class GC
	{
	public:
		~GC()
		{
			if (m_Instance != NULL)
			{
				cout<<"GC test"<<endl;
				delete m_Instance;
				m_Instance = NULL;
			}
		}
	};
	static GC gc;
};



#endif


#ifndef _FACTORYQUICK_H
#define _FACTORYQUICK_H


#include <iostream>
#include "SingletonFactory.h"

using namespace std;

//Factory Quick

class FactoryQuick : public SingletonFactory
{
	friend class SingletonFactory;

public:
	void Sort(int *L, int n)
	{
		LenofArr = n;
		quick_sort_clothes(L, 0, n-1);
	}

protected:
	FactoryQuick(){

	};
	~FactoryQuick(){};

private:

	static FactoryQuick *m_InstanceQuick;

	class GC{
	
	public:
		~GC(){

		  if(m_InstanceQuick != NULL)
		  {
			cout<< "GC Quick test " <<endl;
			delete m_InstanceQuick;
			m_InstanceQuick = NULL;
		  }
		}
	};

	static GC gc;
	int quick_sort(int *L, int start, int end);
	void quick_sort_clothes(int *L, int start, int end);
	int LenofArr;
};

void FactoryQuick::quick_sort_clothes(int *L, int start, int end)
{
	if(start < end)
	{
		int temp = quick_sort(L, start, end);

		quick_sort_clothes(L, start, temp - 1);
		quick_sort_clothes(L, temp + 1, end);
	}
}

int FactoryQuick::quick_sort(int *L, int start, int end)
{
	//中间值mid
  int mid = (start + end) / 2;

  //先作两次比较的预处理，返回的是两者的最小值的位置
  int min_1 = L[start] < L[end] ? start : end;
  int min_2 = L[mid] < L[end] ? mid : end;

  //中间值的位置
  int med;
  if(min_1 != min_2)
  {
    med = L[min_1] > L[min_2] ? min_1 : min_2;
  }
  else
  {
    med = L[start] < L[mid] ? start : mid;
  }

  //调换中间值与第一个数的位置
  if(med != start)
  {
	swap(L, med, start);
  }

  /* //下面的程序会使L[start] = L[end]的时候，程序处于死循环中
  while(start < end)
  {
	//先移动end指针，注意移动完毕需要调用swap函数
	while(start < end && L[end] > L[start])
		end--;
	swap(L, start, end);

	//再移动start指针，注意移动完毕需要调用swap函数
	while(start < end && L[end] > L[start])
		start++;
	swap(L, start, end);
  }*/

  int i = start, j = ++end;//注意i与j的值
  for(;;){
	while(j > 0 && L[--j] > L[start]);//j不能等于0，到时候--j就越界了，可写成    while (i < j && vec.at(start) < vec.at(--j)); 注意i不能等于j
	while(i < (LenofArr - 1) && L[++i] < L[start]);//i不能等于LenofArr，到时候++i就越界了，可写成    while (i < j && vec.at(start) > vec.at(++i)); 注意i不能等于j
	if(i < j){ //注意i 不能等于j
		swap(L, i, j);
	}else{
		break;
	}
  }
  swap(L, start, j);

  return j;
}

#endif
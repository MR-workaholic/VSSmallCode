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
	//�м�ֵmid
  int mid = (start + end) / 2;

  //�������αȽϵ�Ԥ�������ص������ߵ���Сֵ��λ��
  int min_1 = L[start] < L[end] ? start : end;
  int min_2 = L[mid] < L[end] ? mid : end;

  //�м�ֵ��λ��
  int med;
  if(min_1 != min_2)
  {
    med = L[min_1] > L[min_2] ? min_1 : min_2;
  }
  else
  {
    med = L[start] < L[mid] ? start : mid;
  }

  //�����м�ֵ���һ������λ��
  if(med != start)
  {
	swap(L, med, start);
  }

  /* //����ĳ����ʹL[start] = L[end]��ʱ�򣬳�������ѭ����
  while(start < end)
  {
	//���ƶ�endָ�룬ע���ƶ������Ҫ����swap����
	while(start < end && L[end] > L[start])
		end--;
	swap(L, start, end);

	//���ƶ�startָ�룬ע���ƶ������Ҫ����swap����
	while(start < end && L[end] > L[start])
		start++;
	swap(L, start, end);
  }*/

  int i = start, j = ++end;//ע��i��j��ֵ
  for(;;){
	while(j > 0 && L[--j] > L[start]);//j���ܵ���0����ʱ��--j��Խ���ˣ���д��    while (i < j && vec.at(start) < vec.at(--j)); ע��i���ܵ���j
	while(i < (LenofArr - 1) && L[++i] < L[start]);//i���ܵ���LenofArr����ʱ��++i��Խ���ˣ���д��    while (i < j && vec.at(start) > vec.at(++i)); ע��i���ܵ���j
	if(i < j){ //ע��i ���ܵ���j
		swap(L, i, j);
	}else{
		break;
	}
  }
  swap(L, start, j);

  return j;
}

#endif
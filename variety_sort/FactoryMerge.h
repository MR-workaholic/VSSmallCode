#ifndef _FACTORYMERGE_H
#define _FACTORYMERGE_H

#include <iostream>
#include "SingletonFactory.h"

using namespace std;


class FactoryMerge : public SingletonFactory
{
  friend class SingletonFactory;

public:
  void Sort(int* L, int n)
  {
    lenOfArray = n;
    tempArray = new int[lenOfArray];
    MergeSort(L, tempArray, 0, lenOfArray - 1);
  }
protected:
  FactoryMerge()
  {
  };
  ~FactoryMerge()
  {
    delete[] tempArray;
  };
private:
  static FactoryMerge *m_InstanceMerge;
  class GC
  {
  public:
    ~GC()
    {
      if (m_InstanceMerge != NULL) {
        cout << "GC Merge test "  << "\n";
        delete m_InstanceMerge;
        m_InstanceMerge = NULL;
      }
    }
  };

  static GC gc;
  int* tempArray;
  int lenOfArray;
  void MergeSort(int* dataArray, int* tempArray, int left, int right);
  void Merge(int* dataArray, int* tempArray, int startOfLeft, int startOfRight, int endOfRight);
};

void
FactoryMerge::MergeSort(int* dataArray, int* tempArray, int left, int right)
{
  if (left >= right) {
    return;
  }
  int center = left + ((right - left) >> 1);
  MergeSort(dataArray, tempArray, left, center);
  MergeSort(dataArray, tempArray, center + 1, right);
  Merge(dataArray, tempArray, left, center + 1, right);
}

void
FactoryMerge::Merge(int* dataArray, int* tempArray, int startOfLeft, int startOfRight, int endOfRight)
{
  int endOfLeft = startOfRight - 1;
  int length = endOfRight - startOfLeft + 1;
  int posOfLeft = startOfLeft;
  int posOfRight = startOfRight;
  int posOfTempArray = startOfLeft;

  while (posOfLeft <= endOfLeft && posOfRight <= endOfRight)
  {
    if (dataArray[posOfLeft] <= dataArray[posOfRight]) {
      tempArray[posOfTempArray++] = dataArray[posOfLeft++];
    }else {
      tempArray[posOfTempArray++] = dataArray[posOfRight++];
    }
  }

  if (posOfLeft <= endOfLeft) {
    while (posOfLeft <= endOfLeft) {
      tempArray[posOfTempArray++] = dataArray[posOfLeft++];
    }
  }else{
    while (posOfRight <= endOfRight) {
      tempArray[posOfTempArray++] = dataArray[posOfRight++];
    }
  }

  posOfTempArray--;
  for (int i = length; i > 0; i--) {
    dataArray[endOfRight--] = tempArray[posOfTempArray--];
  }

}

#endif

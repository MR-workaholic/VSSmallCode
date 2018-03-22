#ifndef _FACTORYRADIX_H_
#define _FACTORYRADIX_H_

#include <iostream>
#include "SingletonFactory.h"

using namespace std;

// Factory Radix

class FactoryRadix : public SingletonFactory{

  friend class SingletonFactory;

public:
  void Sort(int *List, int n)
  {
    // 只允许3位数的，创建三个桶，每个桶装的是链表
    LinkList *unitsBucket, *tensBucket, *hundredsBucket;
    unitsBucket = new LinkList[10]; // 创建容量为10个node结构体的数组
    // 初始化桶,并排序个位
    if( initBucket(unitsBucket, 10))
      {
        int unit;
        for (int i = 0; i < n; i++) {
          unit = List[i] % 10;
          LinkList L = unitsBucket[unit]; // 该节点的头部
          while(L->Next != NULL)
            {
              L = L->Next;
            }
          LinkList newEle = new Node;
          newEle->Element = List[i];
          newEle->Next = NULL;
          L->Next = newEle;
        }
      }

    tensBucket = new LinkList[10];
    // 初始化桶并进行10位的排序
    if(initBucket(tensBucket, 10))
      {
        int ten;
        for (int i = 0; i < 10; i++) {
          LinkList LinkBucket = unitsBucket[i]; // 获取头结点
          while(LinkBucket->Next != NULL)
            {
              LinkBucket = LinkBucket->Next;
              ten = (LinkBucket->Element) / 10 % 10;
              LinkList L = tensBucket[ten];
              while(L->Next != NULL)
                {
                  L = L->Next;
                }
               LinkList newEle = new Node;
               newEle->Element = LinkBucket->Element;
               newEle->Next = NULL;
               L->Next = newEle;
            }
        }
      }

     hundredsBucket = new LinkList[10];
    // 初始化桶并进行10位的排序
    if(initBucket(hundredsBucket, 10))
      {
        int hundred;
        for (int i = 0; i < 10; i++) {
          LinkList LinkBucket = tensBucket[i]; // 获取头结点
          while(LinkBucket->Next != NULL)
            {
              LinkBucket = LinkBucket->Next;
              hundred = (LinkBucket->Element) / 100 % 10;
              LinkList L = hundredsBucket[hundred];
              while(L->Next != NULL)
                {
                  L = L->Next;
                }
               LinkList newEle = new Node;
               newEle->Element = LinkBucket->Element;
               newEle->Next = NULL;
               L->Next = newEle;
            }
        }
      }

    // 从第三个桶中获取已经排序好的数据
    int index = 0;
    for (int i = 0; i < 10; i++) {
      LinkList L = hundredsBucket[i];
      while(L->Next != NULL)
        {
          L = L->Next;
          List[index++] = L->Element;
        }
    }


  }

protected:
    FactoryRadix(){}
    virtual ~FactoryRadix(){}

private:
    static FactoryRadix *m_InstanceRadix;

// Just to release the resource

    class GC{
    public:
      ~GC(){
        if(m_InstanceRadix != NULL){
          cout << "GC Radix test"  << "\n";
          delete m_InstanceRadix;
          m_InstanceRadix = NULL;
        }
      }

    };
    static GC gc;

  typedef struct Node
  {
    int Element;
    Node* Next;
  }Node, *LinkList;

  bool initBucket(LinkList* &Bucket, int n)
  {
    for (int i = 0; i < n; i++) {
      Bucket[i] = new Node;
      if(Bucket[i] == NULL)
        {
          return false;
        }else{
          Bucket[i] -> Next = NULL;
      }
    }
    return true;
  }


};

#endif

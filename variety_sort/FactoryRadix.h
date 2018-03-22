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
    // ֻ����3λ���ģ���������Ͱ��ÿ��Ͱװ��������
    LinkList *unitsBucket, *tensBucket, *hundredsBucket;
    unitsBucket = new LinkList[10]; // ��������Ϊ10��node�ṹ�������
    // ��ʼ��Ͱ,�������λ
    if( initBucket(unitsBucket, 10))
      {
        int unit;
        for (int i = 0; i < n; i++) {
          unit = List[i] % 10;
          LinkList L = unitsBucket[unit]; // �ýڵ��ͷ��
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
    // ��ʼ��Ͱ������10λ������
    if(initBucket(tensBucket, 10))
      {
        int ten;
        for (int i = 0; i < 10; i++) {
          LinkList LinkBucket = unitsBucket[i]; // ��ȡͷ���
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
    // ��ʼ��Ͱ������10λ������
    if(initBucket(hundredsBucket, 10))
      {
        int hundred;
        for (int i = 0; i < 10; i++) {
          LinkList LinkBucket = tensBucket[i]; // ��ȡͷ���
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

    // �ӵ�����Ͱ�л�ȡ�Ѿ�����õ�����
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

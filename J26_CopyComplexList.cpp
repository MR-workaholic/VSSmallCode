#include <iostream>

using namespace std;

struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) {
    }
};

void intervalInsert(RandomListNode** ppHead){
    RandomListNode* curNode = *ppHead;
    while (curNode != NULL)
    {
        RandomListNode* temp = new RandomListNode(curNode->label);
        temp->next = curNode->next;
        curNode->next = temp;
        curNode = temp->next;
    }
}

void handleRandomPointer(RandomListNode** ppHead){
    RandomListNode *srcNode = *ppHead, *destNode;
    while (srcNode != NULL)
    {
        destNode = srcNode->next;
        if (srcNode->random != NULL)
        {
            destNode->random = srcNode->random->next;
        }
        srcNode = destNode->next;

    }
}

// 一定要将原始的链表也分离出来 
RandomListNode* decomposeList(RandomListNode* list){
    RandomListNode *srcList = list, *destList = srcList->next, *result = list->next;
    while (srcList != NULL)
    {
        srcList->next = destList->next;
        srcList = srcList->next;
        if (srcList != NULL)
        {
            destList->next = srcList->next;
            destList = destList->next;
        }
    }
    return result;
}

// 安装J的三步法
RandomListNode* Clone(RandomListNode* pHead)
{
    if (pHead == NULL)
    {
        return NULL;
    }
    intervalInsert(&pHead);
    handleRandomPointer(&pHead);
    return decomposeList(pHead);

}
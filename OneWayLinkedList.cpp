/*
头结点带数据
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct ListNode;
typedef size_t ElementType;
typedef ListNode Node;
typedef Node* Pos;
typedef Node* List;

struct ListNode
{
    ElementType _val;
    ListNode* _next;
    ListNode(ElementType x, ListNode* nextPtr = nullptr):
    _val(x),
    _next(nextPtr)
    {}
};

void InsertToHead(List* headPtr, ElementType x){
    if (*headPtr == nullptr)
    {
        *headPtr = new ListNode(x);
    }else
    {
        *headPtr = new ListNode(x, *headPtr);
    }
}

void InsertToTail(List* headPtr, ElementType x){
    while ((*headPtr) != nullptr)
    {
        headPtr = &((*headPtr)->_next);
    }
    *headPtr = new ListNode(x);
}

void PrintList(List head){
    List temp = head;  //不需要也行的
    while (temp != nullptr)
    {
        cout << temp->_val << " ";
        temp = temp->_next;
    }
    cout << endl;
}

void rReversePrintList(List head){
    if (head != nullptr)
    {
        rReversePrintList(head->_next);
        cout << head->_val << " ";  //放在递归前就是正序打印了
    }
}

/* void MakeEmpty(List* headPtr){
    List head = *headPtr;
    while (head != nullptr)
    {
        List temp = head;
        head = head->_next;
        headPtr = &head;
        // headPtr = &((*headPtr)->_next);
        delete temp;
        temp = nullptr;
    }
}
 */
void MakeEmpty(List* headPtr){
    while (*headPtr != nullptr)
    {
        List temp = *headPtr;
        *headPtr = (*headPtr)->_next; // true
        // headPtr = &((*headPtr)->_next);  // false
        delete temp;
        temp = nullptr;
    }
}

Pos Find(List head, ElementType x){
    while (head != nullptr && head->_val != x)
    {
        head = head->_next;
    }
    return head;
}

bool Delete(List* headPtr, ElementType x){
    while (*headPtr != nullptr && (*headPtr)->_val != x)
    {
        headPtr = &((*headPtr)->_next);
    }
    if (*headPtr == nullptr)
    {
        return false;
    }else
    {
        List temp = *headPtr;
        *headPtr = (*headPtr)->_next;
        delete temp;
        temp = nullptr;
        return true;
    }
}

Pos FindPrevious(List head, ElementType x){
    List pre = nullptr;
    List cur = head;
    while (cur != nullptr && cur->_val != x)
    {
        pre = cur;
        cur = cur->_next;
    }
    if (cur == nullptr)
    {
        return nullptr;
    }else
    {
        return pre;
    }
}

void Reverse1(List* headPtr){  // 三指针翻转链表
    List cur, pre, nxt;
    pre = nullptr;
    cur = *headPtr;
    while (cur != nullptr)
    {
        nxt = cur->_next;
        cur->_next = pre;
        pre = cur;
        cur = nxt;
    }
    *headPtr = pre;  //很重要，头指针值回去
}

void Reverse2(List* headPtr){
    if (*headPtr == nullptr || (*headPtr)->_next == nullptr)
    {
        return;
    }
    Pos secondNode = (*headPtr)->_next;
    while (secondNode->_next != nullptr)
    {
        Pos temp = secondNode->_next;
        secondNode->_next = temp->_next;
        temp->_next = (*headPtr)->_next;
        (*headPtr)->_next = temp;
    }
    secondNode->_next = *(headPtr);
    *headPtr = (*headPtr)->_next;
    secondNode->_next->_next = nullptr;
}

List rReverse1(List* headPtr){  //递归，后缀操作，一般递归就不用二级指针
    if (*headPtr == nullptr || (*headPtr)->_next == nullptr)
    {
        return *headPtr;
    }

    List head = rReverse1(&((*headPtr)->_next));

    (*headPtr)->_next->_next = *headPtr;
    (*headPtr)->_next = nullptr;

    return head;
}

List rReverse2(List head){
    if (head == nullptr || head->_next == nullptr)
    {
        return head;
    }
    List newHead = rReverse2(head->_next);
    head->_next->_next = head;
    head->_next = nullptr;

    return newHead;
}

List Merge(List pHead1, List pHead2){ // 有序链表的合并
    if (pHead1 == NULL)
    {
        return pHead2;
    }else if (pHead2 == NULL)
    {
        return pHead1;
    }
    List result, p1, p2;
    if(pHead1->_val < pHead2->_val){
        result = pHead1;
        p1 = pHead1;
        p2 = pHead2;
    }else
    {
        result = pHead2;
        p1 = pHead2;
        p2 = pHead1;
    }
    while (p1->_next != NULL && p2 != NULL)
    {
        if (p1->_next->_val > p2->_val)
        {
            List temp = p2->_next;
            p2->_next = p1->_next;
            p1->_next = p2;
            p2 = temp;
        }else
        {
            p1 = p1->_next;
        }

    }

    if (p1->_next == NULL)
    {
        p1->_next = p2;
    }

    return result;
}

List rMerge(List pHead1, List pHead2){
    if (pHead1 == NULL)
    {
        return pHead2;
    }else if (pHead2 == NULL)
    {
        return pHead1;
    }

    List pNewHead = NULL;
    if (pHead1->_val < pHead2->_val)
    {
        pNewHead = pHead1;
        pNewHead->_next = rMerge(pHead1->_next, pHead2);
    }else
    {
        pNewHead = pHead2;
        pNewHead->_next = rMerge(pHead1, pHead2->_next);
    }

    return pNewHead;
}

int main(int argc, char ** argv){
    streambuf* backup;
    backup = cin.rdbuf();
    fstream fin;
    fin.open("data.in");
    cin.rdbuf(fin.rdbuf());

    // 有序链表合并的测试
    /* string inputline4test;
    ElementType temp4test;
    istringstream iss4test;
    getline(cin, inputline4test);
    iss4test = istringstream(inputline4test);
    List sortedList1 = NULL, sortedList2=NULL;
    while (iss4test >> temp4test)
    {
        InsertToTail(&sortedList1, temp4test);
    }
    getline(cin, inputline4test);
    iss4test = istringstream(inputline4test);
    while (iss4test >> temp4test)
    {
        InsertToTail(&sortedList2, temp4test);
    }
    PrintList(sortedList1);
    PrintList(sortedList2);
    List result = rMerge(sortedList1, sortedList2);
    PrintList(result);
 */
    //

    List head = nullptr;

    string inputline;
    getline(cin, inputline);
    istringstream iss(inputline);
    ElementType temp;
    while (iss >> temp)
    {
        InsertToTail(&head, temp);
    }
    PrintList(head);
    Reverse2(&head);
    PrintList(head);
    head = rReverse1(&head);
    head = rReverse2(head);
    PrintList(head);
    // rReversePrintList(head);
    // MakeEmpty(&head);

    getline(cin, inputline);
    iss = istringstream(inputline);
    while (iss >> temp)
    {
        cout << "Find " << temp << " : " << (Find(head, temp) != nullptr ? "true" : "false") << endl;
    }

    getline(cin, inputline);
    iss = istringstream(inputline);
    while (iss >> temp)
    {
        cout << "Delete " << temp << " : " << (Delete(&head, temp) == true ? "true" : "false") << endl;
        PrintList(head);
    }

    getline(cin, inputline);
    iss = istringstream(inputline);
    while (iss >> temp)
    {
        List fPos = FindPrevious(head, temp);
        cout << "FindPrevious " << temp << " : " << (fPos == nullptr ? "false" : "true" + to_string(fPos->_val)) << endl;
        PrintList(head);
    }



    MakeEmpty(&head);

    cin >> temp;

}


/*
头结点带数据
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <stack>

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

Pos FindFirstCommonNodeWithSet(List pHead1, List pHead2){
    if (pHead1 == nullptr || pHead2 == nullptr)
    {
        return nullptr;
    }
    unordered_set<Pos> record;
    auto p = pHead1;
    while (p != nullptr)
    {
        record.insert(p);
        p = p->_next;
    }
    p = pHead2;
    while (p != nullptr)
    {
        if (record.find(p) != record.end() && p != nullptr)
        {
            return p;
        }
        p = p->_next;
    }
    return nullptr;
}

Pos FindFirstCommonNodeWithStack(List pHead1, List pHead2){
    if (pHead1 == nullptr || pHead2 == nullptr)
    {
        return nullptr;
    }
    Pos p = pHead1;
    stack<Pos> sta1;
    while (p != nullptr)
    {
        sta1.push(p);
        p = p->_next;
    }

    p = pHead2;
    stack<Pos> sta2;
    while (p != nullptr)
    {
        sta2.push(p);
        p = p->_next;
    }

    Pos result(nullptr);
    while (sta1.top() == sta2.top())
    {
        result = sta1.top();
        sta1.pop();
        sta2.pop();
        if (sta1.empty() || sta2.empty())
        {
            break;
        }
    }
    return result;


}

Pos FindFirstCommonNodeWithCounter(List pHead1, List pHead2){
     if (pHead1 == nullptr || pHead2 == nullptr)
    {
        return nullptr;
    }
    int counter1(0);
    Pos p = pHead1;
    while (p != nullptr)
    {
        counter1++;
        p = p->_next;
    }

    int counter2(0);
    p = pHead2;
    while (p != nullptr)
    {
        counter2++;
        p = p->_next;
    }

    Pos p1 = pHead1;
    Pos p2 = pHead2;
    if (counter1 > counter2)
    {
        int counter = counter1 - counter2;
        while (counter--)
        {
            p1 = p1->_next;
        }
    }else
    {
        int counter = counter2 - counter1;
        while (counter--)
        {
            p2 = p2->_next;
        }
    }
    while (p1 != p2)
    {
        p1 = p1->_next;
        p2 = p2->_next;
        if (p1 == nullptr || p2 == nullptr)
        {
            return nullptr;
        }
    }
    return p1;
}

List deleteDuplication(List pHead)
{
    if (pHead == nullptr)
    {
        return pHead;
    }
    Pos curIndex = pHead;
    Pos preIndex = nullptr;
    Pos changeIndex = pHead;
    ElementType deleteVal(0);
    bool isNull(true);
    while (curIndex != nullptr)
    {
        if (preIndex == nullptr)
        {
            preIndex = curIndex;
            curIndex = curIndex->_next;
            continue;
        }
        if (preIndex->_val == curIndex->_val)
        {
            deleteVal = preIndex->_val;
            // changeIndex = preIndex;
            while (preIndex != nullptr && preIndex->_val == deleteVal)
            {
                preIndex = preIndex->_next;
            }
            if (preIndex == nullptr)
            {
                break;
            }
            // changeIndex->_val = preIndex->_val;
            curIndex = preIndex->_next;
            continue;
        }
        if (preIndex->_val != curIndex->_val)
        {
            isNull = false;
            changeIndex->_val = preIndex->_val;
            changeIndex = changeIndex->_next;
            preIndex = curIndex;
            curIndex = curIndex->_next;
        }
    }

    Pos deleteNode;
    if (preIndex != nullptr)
    {
        changeIndex->_val = preIndex->_val;
        deleteNode = changeIndex->_next;
        changeIndex->_next = nullptr;
    }else
    {
        deleteNode = changeIndex;
        if (!isNull)
        {
            for (curIndex = pHead; curIndex->_next != deleteNode; curIndex = curIndex->_next);
            curIndex->_next = nullptr;
        }else
        {
            pHead = nullptr;
        }
    }

    while (deleteNode != nullptr)
    {
        Pos temp = deleteNode;
        deleteNode = deleteNode->_next;
        delete temp;
        temp = nullptr;
    }

    return pHead;
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

    // 寻找公共节点测试
/*     string inputline4test;
    ElementType temp4test;
    istringstream iss4test;
    getline(cin, inputline4test);
    iss4test = istringstream(inputline4test);
    List List1 = NULL, List2=NULL;
    while (iss4test >> temp4test)
    {
        InsertToTail(&List1, temp4test);
    }
    getline(cin, inputline4test);
    iss4test = istringstream(inputline4test);
    while (iss4test >> temp4test)
    {
        InsertToTail(&List2, temp4test);
    }
    getline(cin, inputline4test);
    iss4test = istringstream(inputline4test);
    iss4test >> temp4test;
    Pos q = Find(List1, temp4test);
    if (q && List2)
    {
        List p = List2;
        while (p->_next != nullptr)
        {
            p = p->_next;
        }
        p->_next = q;
    }
    PrintList(List1);
    PrintList(List2);
    Pos res = FindFirstCommonNodeWithCounter(List1, List2);
    PrintList(res);
 */
    //

    // 删除链表中的重复节点
    // 1 1 2 2 3 3
    // 1 1 2 2 3 4 5 5
    // 1 2 3 4 5
    // 1 2 3 3 4 4 5
/*     string inputline4test;
    ElementType temp4test;
    istringstream iss4test;
    getline(cin, inputline4test);
    iss4test = istringstream(inputline4test);
    List sortedList = NULL;
    while (iss4test >> temp4test)
    {
        InsertToTail(&sortedList, temp4test);
    }
    PrintList(sortedList);
    List result = deleteDuplication(sortedList);
    PrintList(result);
 */    //


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


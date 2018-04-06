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
        }
            p1 = p1->_next;
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

// 删除重复的节点，但是是利用val移动法，比较难懂
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

    // 寻找不重复的节点放在changeIndex上，然后再删除后面的节点，移动val而不是删除节点！
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

    // 节点的val移动完毕，可以开始删除节点了

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

// 利用二级指针实现重复节点的删除，实现起来比上面的易懂
void deleteDuplication_2(List* ppHead){
    if (ppHead == nullptr || *ppHead == nullptr)
    {
        return;
    }
    Pos preNode(nullptr), deleteNode(nullptr);
    while (*ppHead != nullptr && (*ppHead)->_next != nullptr)
    {
        if ( (*ppHead)->_val == (*ppHead)->_next->_val)
        {
            deleteNode = *ppHead; // 标记当前的重复节点
            while (*ppHead != nullptr && (*ppHead)->_val == deleteNode->_val)
            {
                *ppHead = (*ppHead)->_next;  //假如要删除的是首部节点，这个语句可以移动首部哟
            }
            // 删除重复节点
            while (deleteNode != *ppHead)
            {
                Pos temp = deleteNode;
                deleteNode = deleteNode->_next;
                if (preNode == temp) // 这一句很重要，temp的删除很可能令preNode成为野指针，所以记得将其赋值为nullptr
                {
                    preNode = nullptr;
                }
                delete temp;
                temp = nullptr;
            }
            // 前一个节点记得重新连接过来
            if (preNode == nullptr)
            {
                preNode = *ppHead;
            }else
            {
                preNode->_next = *ppHead;
                preNode = *ppHead;
            }
        }else
        {
            // 前一个节点不与后一个节点相同，可以移动节点了，因为这里的移动，下一次修改*ppHead不会改变首部了
            preNode = *ppHead;
            ppHead = &((*ppHead)->_next);

        }
    }
}

bool removeNode(Pos pNode) {
    if (pNode == nullptr || pNode->_next == nullptr)
    {
        return false;
    }
    Pos cur = pNode, pre = nullptr;

    while (cur->_next != nullptr)
    {
        cur->_val = cur->_next->_val;
        pre = cur;
        cur = cur->_next;
    }
    pre->_next = nullptr;
    delete cur;
    cur = nullptr;
    return true;
}

// 链表的partition算法
List partition(List pHead, ElementType x) {
    if (pHead == nullptr)
    {
        return  nullptr;
    }
    List minList(nullptr), maxList(nullptr);
    while (pHead != nullptr)
    {
        if (pHead->_val < x)
        {
            InsertToTail(&minList, pHead->_val);
        }else
        {
            InsertToTail(&maxList, pHead->_val);
        }
        pHead = pHead->_next;
    }
    if (minList == nullptr)
    {
        return maxList;
    }
    Pos p = minList;
    while (p->_next != nullptr)
    {
        p = p->_next;
    }
    p->_next = maxList;
    return minList;
}


List plusAB(List a, List b) {
    if (a == nullptr)
    {
        return b;
    }else if (b == nullptr)
    {
        return a;
    }
    ElementType carry(0);
    Pos pa = a, pb = b;
    List result(nullptr);
    while (pa != nullptr || pb != nullptr)
    {
        ElementType val(0);
        if (pa == nullptr)
        {
            val = pb->_val + carry;
            pb = pb->_next;
        }else if (pb == nullptr)
        {
            val = pa->_val + carry;
            pa = pa->_next;
        }else
        {
            val = pa->_val + pb->_val + carry;
            pa = pa->_next;
            pb = pb->_next;
        }

        if (val > 9)
        {
            val -= 10;
            carry = 1;
        }else
        {
            carry = 0;
        }
        InsertToTail(&result, val);
    }

    if (carry)
    {
        InsertToTail(&result, 1);
    }
    return result;
}

int carry(0);

void rePlus2(List a, List b, List* result){
    if (a == nullptr)
    {
        return;
    }
    rePlus2(a->_next, b->_next, result);
    ElementType val(carry);
    val += (a->_val + b->_val);
    carry = val > 9 ? 1 : 0;
    val = val % 10;
    InsertToHead(result, val);
}

List plusAB2(List a, List b){
    if (a == nullptr)
    {
        return b;
    }else if (b == nullptr)
    {
        return a;
    }
    size_t lena(0), lenb(0);
    List ca(a), cb(b);
    while (ca != nullptr)
    {
        lena++;
        ca = ca->_next;
    }
    while (cb != nullptr)
    {
        lenb++;
        cb = cb->_next;
    }
    List addZeroList, noChangeList;
    if (lena != lenb)
    {
        size_t diff;
        if (lena > lenb)
        {
            addZeroList = b;
            noChangeList = a;
            diff = lena - lenb;
        }else
        {
            addZeroList = a;
            noChangeList = b;
            diff = lenb - lena;
        }
        while (diff > 0)
        {
            InsertToHead(&addZeroList, 0);
            --diff;
        }
    }else
    {
        addZeroList = a;
        noChangeList = b;
    }

    List result(nullptr);
    rePlus2(addZeroList, noChangeList, &result);
    if (carry == 1)
    {
        InsertToHead(&result, 1);
    }
    return result;
}

Pos rePalindrome(List mlist, size_t length){

    if (length == 1)
    {
        return mlist->_next;
    }else if (length == 0)
    {
        return mlist;
    }
    Pos ret = rePalindrome(mlist->_next, length-2);
    if (ret == nullptr)
    {
        return ret;
    }
    if (mlist->_val == ret->_val)
    {
        return ret->_next;
    }
    return nullptr;
}


bool isPalindrome(List pHead) {
    if (pHead == nullptr)
    {
        return false;
    }
    size_t length(1);
    Pos p = pHead;
    while (p->_next != nullptr)
    {
        length++;
        p = p->_next;
    }
    if (length == 1)
    {
        return true;
    }
    Pos sentinel = new Node(pHead->_val + 1); // 加哨兵
    p->_next = sentinel;
    Pos result = rePalindrome(pHead, length);
    bool res(false);
    if (result == sentinel)
    {
        res = true;
    }
    p->_next = nullptr;
    delete sentinel;
    return res;
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
    string inputline4test;
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
    // List result = deleteDuplication(sortedList);
    deleteDuplication_2(&sortedList);
    PrintList(sortedList);


    //给定一个链表中的某个节点，删除它，只有该节点作为参数
    // 1 4 2 5 3 6 8 9
    // 4
/*     string inputline4test;
    ElementType temp4test;
    istringstream iss4test;
    getline(cin, inputline4test);
    iss4test = istringstream(inputline4test);
    List testList = NULL;
    while (iss4test >> temp4test)
    {
        InsertToTail(&testList, temp4test);
    }
    PrintList(testList);
    getline(cin, inputline4test);
    iss4test = istringstream(inputline4test);
    iss4test >> temp4test;
    Pos target = Find(testList, temp4test);
    cout << removeNode(target) << endl;
    PrintList(testList);
 */
    // 以给定值x为基准将链表分割成两部分，所有小于x的结点排在大于或等于x的结点之前
    /*
    4 2 6 4 3 9 1 5
    3
     */
/*     string inputline4test;
    ElementType temp4test;
    istringstream iss4test;
    getline(cin, inputline4test);
    iss4test = istringstream(inputline4test);
    List testList = NULL;
    while (iss4test >> temp4test)
    {
        InsertToTail(&testList, temp4test);
    }
    PrintList(testList);
    getline(cin, inputline4test);
    iss4test = istringstream(inputline4test);
    iss4test >> temp4test;
    List result = partition(testList, temp4test);
    PrintList(result);
 */

    // A+B 反向存放
    /*
    7 1 6
    5 9 2
     */
/*     string inputlineA, inputlineB;
    ElementType temp4test;
    istringstream iss4test;
    getline(cin, inputlineA);
    getline(cin, inputlineB);
    List listA(nullptr), listB(nullptr);
    iss4test = istringstream(inputlineA);
    while (iss4test >> temp4test)
    {
        InsertToTail(&listA, temp4test);
    }
    iss4test = istringstream(inputlineB);
    while (iss4test >> temp4test)
    {
        InsertToTail(&listB, temp4test);
    }
    PrintList(listA);
    PrintList(listB);
    List result = plusAB(listA, listB);
    PrintList(result);
 */

    // A+B 正向存放
    /*
    6 1 7
    3 9 5
    1 2 3 4
    9 8 7
    6 1 7
    2 9 5
     */
/*     string inputlineA, inputlineB;
    ElementType temp4test;
    istringstream iss4test;
    getline(cin, inputlineA);
    getline(cin, inputlineB);
    List listA(nullptr), listB(nullptr);
    iss4test = istringstream(inputlineA);
    while (iss4test >> temp4test)
    {
        InsertToTail(&listA, temp4test);
    }
    iss4test = istringstream(inputlineB);
    while (iss4test >> temp4test)
    {
        InsertToTail(&listB, temp4test);
    }
    PrintList(listA);
    PrintList(listB);
    List result = plusAB2(listA, listB);
    PrintList(result);
 */

    // 递归方法实现链的回文检测
    /* 3 3
    0 1 2 2 1 0
    0 1 2 3 2 1 0
    */
/*     string inputline4test;
    ElementType temp4test;
    istringstream iss4test;
    getline(cin, inputline4test);
    iss4test = istringstream(inputline4test);
    List testList(nullptr);
    while (iss4test >> temp4test)
    {
        InsertToTail(&testList, temp4test);
    }
    PrintList(testList);
    cout << isPalindrome(testList) << endl;
 */

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


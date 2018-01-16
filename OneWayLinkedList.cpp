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


int main(int argc, char ** argv){
    streambuf* backup;
    backup = cin.rdbuf();
    fstream fin;
    fin.open("data.in");
    cin.rdbuf(fin.rdbuf());

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


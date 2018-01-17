/*
data.in
70 12 234 31 43 21 56 31 45 65 321 5 65 423 645 45 32
23 43 321 342
12 45 321 54 24 31 56
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>

using namespace std;

struct BinarySearchTreeNode;
typedef size_t ElementType;
typedef BinarySearchTreeNode* Pos;
typedef BinarySearchTreeNode* Tree;
typedef BinarySearchTreeNode  Node;


struct BinarySearchTreeNode{
    ElementType _val;
    Tree _left;
    Tree _right;
    BinarySearchTreeNode(ElementType x) :
    _val(x),
    _left(nullptr),
    _right(nullptr)
    {}
};

Tree rInsert(Tree tree, ElementType x){
    if (tree == nullptr)
    {
        tree =  new Node(x);
    }else
    {
        if (tree->_val < x)
        {
            tree->_right = rInsert(tree->_right, x);
        }else if (tree->_val > x)
        {
            tree->_left = rInsert(tree->_left, x);
        }
    }
    return tree;
}

// 后缀遍历清空二叉查找树
Tree rMakeEnpty(Tree tree){
    if (tree != nullptr)
    {
        rMakeEnpty(tree->_left);
        rMakeEnpty(tree->_right);
        delete tree;
        tree = nullptr;
    }
    return tree;
}

void rInorderTraversal(Tree tree){
    if (tree != nullptr)
    {
        rInorderTraversal(tree->_left);
        cout << tree->_val << " ";
        rInorderTraversal(tree->_right);
    }
}

void inorderTraversal(Tree tree){
    if (tree == nullptr)
    {
        return;
    }
    stack<Tree> tempSta;
    bool start = true;
    while (!tempSta.empty() || start)
    {
        start = false;
        if (tree->_left != nullptr)
        {
            if (!tempSta.empty() && tree == tempSta.top())
            {
                // cout << tree->_val << " ";
                tempSta.pop();
            }else
            {
                tempSta.push(tree);
                tree = tree->_left;
                continue;
            }
        }
        cout << tree->_val << " ";
        if (tree->_right != nullptr)
        {
            tree = tree->_right;
            start = true;
        }else
        {
            if (!tempSta.empty())
            {
                tree = tempSta.top();
            }
            // tempSta.pop();
        }
    }
}



bool rFind(Tree tree, ElementType x){
    if (tree == nullptr)
    {
        return false;
    }else
    {
        if (tree->_val == x)
        {
            return true;
        }else if (tree->_val > x)
        {
            return rFind(tree->_left, x);
        }else
        {
            return rFind(tree->_right, x);
        }
    }
}

Pos rFindMax(Tree tree){
    if (tree == nullptr)
    {
        return nullptr;
    }else
    {
        if (tree->_right == nullptr)
        {
            return tree;
        }else
        {
            return rFindMax(tree->_right);
        }
    }
}

Pos rFindMin(Tree tree){
    if (tree == nullptr)
    {
        return nullptr;
    }else if (tree->_left == nullptr)
    {
        return tree;
    }else
    {
        return rFindMin(tree->_left);
    }
}

bool Find(Tree tree, ElementType x){  //不需要额外的Tree中间量来获取tree的拷贝，不会退出函数后跟指针不会变化的
    while (tree != nullptr)
    {
        if (tree->_val > x)
        {
            tree = tree->_left;
        }else if (tree->_val < x)
        {
            tree = tree->_right;
        }else
        {
            return true;
        }
    }
    return false;
}

Pos FindMax(Tree tree){
    if (tree == nullptr)
    {
        return nullptr;
    }
    while (tree->_right != nullptr)
    {
        tree = tree->_right;
    }
    return tree;
}

Pos FindMin(Tree tree){
    if (tree == nullptr)
    {
        return nullptr;
    }
    while (tree->_left != nullptr)
    {
        tree = tree->_left;
    }
    return tree;
}

Tree rDelete(Tree tree, ElementType x){
    if (tree == nullptr)
    {
        return tree;
    }
    if (tree->_val > x)
    {
        tree->_left = rDelete(tree->_left, x);
    }else if (tree->_val < x)
    {
        tree->_right = rDelete(tree->_right, x);
    }else
    {  // 分三种情况，叶子节点，有一个孩子节点与有两个孩子节点
        if (tree->_left == nullptr && tree->_right == nullptr)
        {
            delete tree;
            tree = nullptr;
        }else if (tree->_left != nullptr && tree->_right != nullptr)
        {
            ElementType leftChildrenMax = FindMax(tree->_left)->_val;
            tree->_val = leftChildrenMax;
            tree->_left = rDelete(tree->_left, leftChildrenMax);
        }else
        {
            Pos temp = tree;
            tree = tree->_left == nullptr ? tree->_right : tree->_left;
            delete temp;
        }
        return tree;
    }
}

Pos rFindLowerBound(Tree tree, ElementType x){ // 找出大于等于给定值的位置
    if (tree == nullptr || tree->_val == x)
    {
        return tree;
    }else if (tree->_val < x)
    {
        return rFindLowerBound(tree->_right, x);
    }else
    {
        Pos temp = FindMax(tree->_left);
        if (temp == nullptr || temp->_val < x)
        {
            return tree;
        }else
        {
            return rFindLowerBound(tree->_left, x);
        }
    }
}

int main(int argc, char **argv){
    streambuf* backup;
    ifstream fin;
    fin.open("data.in");
    backup = cin.rdbuf();
    cin.rdbuf(fin.rdbuf());

    string input;
    getline(cin, input);
    istringstream iss(input);
    ElementType temp;

    Tree myTree = nullptr;
    while (iss >> temp)
    {
        myTree = rInsert(myTree, temp);
    }

    rInorderTraversal(myTree);
    cout << endl;
    inorderTraversal(myTree);
    cout << endl;

    getline(cin, input);
    iss = istringstream(input);
    while(iss >> temp){
        // cout << temp << " : " << (Find(myTree, temp) ? "true" : "false") << endl;
        Pos result = rFindLowerBound(myTree, temp);
        cout << temp << " : " << (result == nullptr ? "no" : "is " + to_string(result->_val)) << endl;
    }

    cout << "Max is " << rFindMax(myTree)->_val << endl;
    cout << "Min is " << rFindMin(myTree)->_val << endl;
    cout << "Max is " << FindMax(myTree)->_val << endl;
    cout << "Min is " << FindMin(myTree)->_val << endl;

    getline(cin, input);
    iss = istringstream(input);
    while (iss >> temp)
    {
        if (Find(myTree, temp))
        {
            cout << "Delete " << temp << endl;
            myTree = rDelete(myTree, temp);
            inorderTraversal(myTree);
            cout << endl;
        }
    }



    rMakeEnpty(myTree);
    cin >> temp;
}



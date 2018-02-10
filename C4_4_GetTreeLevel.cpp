/*
1 2 4 3 5 7 6
2 4 1 7 5 3 6
4
 */
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x, size_t y = 0) : val(x), left(NULL), right(NULL) {}
};

struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

void PrintList(ListNode* p){
    while (p != NULL)
    {
        cout << p->val << " ";
        p = p->next;
    }
    cout << endl;
}

void Insert(ListNode** pp, int val){
    while (*pp != NULL)
    {
        pp = &((*pp)->next);
    }
    *pp = new ListNode(val);
}

ListNode* getTreeLevel(TreeNode* root, int dep) {
    if (root == NULL || dep == 0)
    {
        return NULL;
    }
    vector<queue<TreeNode*>> record;
    record.reserve(2);
    queue<TreeNode*> one, two;
    record.push_back(one);
    record.push_back(two);
    size_t curDep = 1;
    record.at(curDep % 2).push(root);

    TreeNode* temp;
    while (curDep != dep)
    {
        temp = record.at(curDep % 2).front();
        if (temp->left != NULL)
        {
            record.at(1 - curDep % 2).push(temp->left);
        }
        if (temp->right != NULL)
        {
            record.at(1 - curDep % 2).push(temp->right);
        }
        record.at(curDep % 2).pop();
        if (record.at(curDep % 2).empty())
        {
            curDep++;
        }
    }

    ListNode* res = NULL;
    while (!record.at(curDep % 2).empty())
    {
        temp = record.at(curDep % 2).front();
        Insert(&res, temp->val);
        record.at(curDep % 2).pop();
    }
    return res;

}

TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> vin){
    if (pre.size() == 0)
    {
        return NULL;
    }
    if (pre.size() == 1)
    {
        return new TreeNode(pre.at(0));
    }
    TreeNode* result = new TreeNode(pre.at(0));
    auto iFind = find(vin.begin(), vin.end(), pre.at(0));
    vector<int> leftVin(vin.begin(), iFind);
    vector<int> rightVin(iFind + 1, vin.end());

    auto index = pre.begin();
    index = index + 1;
    vector<int> leftPre(index, index + leftVin.size());
    vector<int> rightPre(index + leftVin.size(), pre.end());

    result->left = reConstructBinaryTree(leftPre, leftVin);
    result->right = reConstructBinaryTree(rightPre, rightVin);

    return result;
}

int main(int argc, char **argv){
    streambuf* backup;
    ifstream fin;
    fin.open("data.in");
    backup = cin.rdbuf();
    cin.rdbuf(fin.rdbuf());

    string inputline;
    istringstream iss;
    while (true)
    {
        vector<int> preorder;
        vector<int>  inorder;
        getline(cin, inputline);
        iss = istringstream(inputline);
        int temp;
        while (iss >> temp)
        {
            preorder.push_back(temp);
        }
        getline(cin, inputline);
        iss = istringstream(inputline);
        while (iss >> temp)
        {
            inorder.push_back(temp);
        }
        TreeNode* tree = reConstructBinaryTree(preorder, inorder);
        getline(cin, inputline);
        iss = istringstream(inputline);
        iss >> temp;
        PrintList(getTreeLevel(tree, temp));
    }
}

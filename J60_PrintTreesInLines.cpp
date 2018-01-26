/*
8 6 5 7 10 9 11
5 6 7 8 9 10 11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

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

/* 法一：可以使用队列存储一个pair，pair是TreeNode* + 层数，遍历相应层数的就在相应的result里面插入val */

vector<vector<int>> Print(TreeNode* pRoot) { // 额外记录着每层有多少个节点，什么时候进入下一层
    vector<vector<int>> result;
    if (pRoot == NULL)
    {
        return result;
    }
    queue<TreeNode*> record;
    vector<int> record1;
    record.push(pRoot);
    record1.push_back(1);
    int index(0);
    while (!record.empty())
    {
        auto Node = record.front();
        record.pop();

        if (result.size() == index)
        {
            vector<int> temp;
            result.push_back(temp);
        }
        record1.at(index)--;
        result.at(index).push_back(Node->val);

        if (record1.size() == index + 1)
        {
            record1.push_back(0);
        }

        if (Node->left != NULL)
        {
            record.push(Node->left);
            record1.at(index+1)++;
        }
        if (Node->right != NULL)
        {
            record.push(Node->right);
            record1.at(index+1)++;
        }

        if (record1.at(index) == 0)
        {
            index++;
        }

    }
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
        Print(tree);

    }
}
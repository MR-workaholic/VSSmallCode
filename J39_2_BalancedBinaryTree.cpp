/*
1 2 4 5 7 3 6
4 2 7 5 1 3 6
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

unordered_map<TreeNode*, int> record;

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

int TreeDepth(TreeNode* pRoot)
{
    if (pRoot == NULL)
    {
        record.insert({NULL, 0});
        return 0;
    }

    int leftLen;
    auto ifind = record.find(pRoot->left);
    if (ifind != record.end())
    {
        leftLen = ifind->second;
    }else{
        leftLen = TreeDepth(pRoot->left);
    }
    int rightLen;
    ifind = record.find(pRoot->right);
    if (ifind != record.end())
    {
        rightLen = ifind->second;
    }else{
        rightLen = TreeDepth(pRoot->right);
    }

    int len = max<int>({leftLen, rightLen}) + 1;
    record.insert({pRoot, len});
    return len;
}

bool IsBalanced_Solution(TreeNode* pRoot) {
    if (pRoot == NULL)
    {
        return true;
    }

    if (!IsBalanced_Solution(pRoot->left) || !IsBalanced_Solution(pRoot->right))
    {
        return false;
    }
    int leftLen;
    auto ifind = record.find(pRoot->left);
    if (ifind != record.end())
    {
        leftLen = ifind->second;
    }else{
        leftLen = TreeDepth(pRoot->left);
    }
    int rightLen;
    ifind = record.find(pRoot->right);
    if (ifind != record.end())
    {
        rightLen = ifind->second;
    }else{
        rightLen = TreeDepth(pRoot->right);
    }

    int diff = leftLen - rightLen;
    if (diff < 0)
    {
        diff = -diff;
    }
    if (diff <= 1)
    {
        return true;
    }
    return false;
}

bool ReIsBalanced_Solution(TreeNode* pRoot, int& depth){
    if (pRoot == NULL)
    {
        depth = 0;
        return true;
    }

    int leftDepth(0), rightDepth(0);
    if (ReIsBalanced_Solution(pRoot->left, leftDepth) && ReIsBalanced_Solution(pRoot->right, rightDepth))
    {
        int diff = leftDepth - rightDepth;
        if (diff >= -1 && diff <= 1)
        {
            depth = max<int>({leftDepth, rightDepth}) +1;
            return true;
        }
    }
    return false;
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
        cout << IsBalanced_Solution(tree) << endl;
        int depth(0);
        cout << ReIsBalanced_Solution(tree, depth) << endl;
        cout << depth << endl;


    }
}
/*
5 3 2 4 7 6 8
2 3 4 5 6 7 8
7
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

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

TreeNode* KthNode(TreeNode* pRoot, int* k){
    if (pRoot == NULL)
    {
        return pRoot;
    }
    TreeNode* result = KthNode(pRoot->left, k);
    if (*k == 0)
    {
        return result;
    }else if (*k > 0)
    {
        (*k)--;
        if (*k == 0)
        {
            return pRoot;
        }
    }
    result = KthNode(pRoot->right, k);
    return result;
}

TreeNode* KthNode(TreeNode* pRoot, int k)
{
    if (k == 0)
    {
        return NULL;
    }
    int* pk = new int(k);
    return KthNode(pRoot, pk);
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
        TreeNode* BSTTree = reConstructBinaryTree(preorder, inorder);
        getline(cin, inputline);
        iss = istringstream(inputline);
        int K;
        iss >> K;
        for (size_t i = 1; i <= K; i++)
        {
            TreeNode* target = KthNode(BSTTree, i);
            cout << target->val << endl;
        }

    }
}
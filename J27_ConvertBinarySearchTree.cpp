/*
10 6 4 8 14 12 16
4 6 8 10 12 14 16
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

void ConvertNode(TreeNode* pNode, TreeNode** pLastMaxNode){
    if (pNode == NULL)
    {
        return ;
    }
    if (pNode->left != NULL)
    {
        ConvertNode(pNode->left, pLastMaxNode);
    }
    pNode->left = *pLastMaxNode;
    if (*pLastMaxNode != NULL)
    {
        (*pLastMaxNode)->right = pNode;
    }
    *pLastMaxNode = pNode;
    if (pNode->right != NULL)
    {
        ConvertNode(pNode->right, pLastMaxNode);
    }
}

TreeNode* Convert(TreeNode* pRootOfTree)
{
    if (pRootOfTree == NULL)
    {
        return pRootOfTree;
    }
    TreeNode* pLastMaxNode = NULL;
    ConvertNode(pRootOfTree, &pLastMaxNode);

    TreeNode* result = pLastMaxNode;
    while (result->left != NULL)
    {
        result = result->left;
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
        Convert(tree);
    }
}
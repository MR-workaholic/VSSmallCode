/*
5 8 9 2 4 7 6
9 8 4 2 7 5 6
8 9 2
9 8 2
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

// 空树不是所有树的子结构,因此一开始传入是空树的话需要判负
bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
{
    if (pRoot1 == NULL || pRoot2 == NULL)
    {
        //  if (pRoot2 == NULL)
        // {
        //     return true;
        // }

        return false;
    }
    // 采用前序遍历
    if (pRoot1->val == pRoot2->val)
    {

        if((pRoot2->left == NULL || HasSubtree(pRoot1->left, pRoot2->left)) && (pRoot2->right == NULL || HasSubtree(pRoot1->right, pRoot2->right)))
        {
            return true;
        }
    }

    if(HasSubtree(pRoot1->left, pRoot2) || HasSubtree(pRoot1->right, pRoot2)){
        return true;
    }
    return false;
}

int main(int argc, char **argv){
    streambuf* backup;
    ifstream fin;
    fin.open("data.in");
    backup = cin.rdbuf();
    cin.rdbuf(fin.rdbuf());

    // 采用第6题的方法去构造树
    string inputline;
    istringstream iss;
    vector<TreeNode*> param;
    while (param.size() != 2)
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
        param.push_back(reConstructBinaryTree(preorder, inorder));

    }

    cout << HasSubtree(param.at(0), param.at(1)) << endl;

    return 0;
}
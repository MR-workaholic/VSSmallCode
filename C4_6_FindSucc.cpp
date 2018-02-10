/*
6 4 2 5 8 9
2 4 5 6 8 9
6
 */
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x, size_t y = 0) : val(x), left(NULL), right(NULL) {}
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

int findSucc(TreeNode* root, int p) {
    if (root == NULL)
    {
        return false;
    }
    stack<TreeNode*> record;
    bool start(false);
    record.push(root);
    int result(-1);
    while (!record.empty())
    {
        if (record.top()->left != NULL)
        {
            record.push(record.top()->left);
        }else
        {
            TreeNode* temp = record.top();
            record.pop();
            if (start)
            {
                result = temp->val;
                break;
            }else if (temp->val == p)
            {
                start = true;
            }

            if (!record.empty() && temp->right == NULL)
            {
                record.top()->left = NULL;
            }else if(temp->right != NULL)
            {
                record.push(temp->right);
            }
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
        getline(cin, inputline);
        iss = istringstream(inputline);
        iss >> temp;
        cout << findSucc(tree, temp) << endl;
    }
}

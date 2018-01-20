/*
10 5 4 7 12
4 5 7 10 12
22
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>

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



vector<vector<int>> FindPath(TreeNode* root, int expectNumber) {
    vector<vector<int>> result;
    if (root == NULL || root->val > expectNumber || expectNumber == 0)
    {
        return result;
    }else if (root->val == expectNumber && root->left == NULL && root->right == NULL)
    {
        vector<int> oneNum = {root->val};
        result.push_back(oneNum);
        return result;
    }


    vector<vector<int>> left = FindPath(root->left, expectNumber - root->val);
    vector<vector<int>> right = FindPath(root->right, expectNumber - root->val);

    for(auto var : left)
    {
        var.insert(var.begin(), root->val);
        result.push_back(var);
    }
    for(auto var : right)
    {
        var.insert(var.begin(), root->val);
        result.push_back(var);
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
        vector<vector<int>> result = FindPath(tree, temp);
        for(auto var : result)
        {
            copy(var.begin(), var.end(), ostream_iterator<int>(cout, " "));
            cout << endl;
        }

    }
}
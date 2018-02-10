/*
1 2 4 8 16 9 5 10 11 3 6 12 13 7 14 15
16 8 4 9 2 10 5 11 1 12 6 13 3 14 7 15
1 2 4 5 7 3 6
4 2 7 5 1 3 6
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

bool reIsBalance(TreeNode* root, size_t& length){
    if (root == NULL)
    {
        length = 0;
        return true;
    }
    size_t lLength(0);
    size_t rLength(0);

    if (!reIsBalance(root->left, lLength) || !reIsBalance(root->right, rLength))
    {
        return false;
    }
    size_t lengthDiff = lLength > rLength ? lLength - rLength : rLength - lLength;
    if (lengthDiff > 1)
    {
        return false;
    }
    length = max<size_t>({lLength, rLength}) + 1;
    return true;
}

bool isBalance(TreeNode* root) {
    // write code here
    size_t length(0);
    return reIsBalance(root, length);

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
        cout << isBalance(tree) << endl;


    }
}

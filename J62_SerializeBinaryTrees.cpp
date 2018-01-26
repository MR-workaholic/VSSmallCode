/*
1 2 4 3 5 6
4 2 1 5 3 6
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdlib>

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

void reSerialize(TreeNode* root, string& result){
    if (root == NULL)
    {
        result += ("$,");
        return;
    }
    result += (to_string(root->val) + ',');
    reSerialize(root->left, result);
    reSerialize(root->right, result);
}

char* Serialize(TreeNode *root) {
    string result;
    reSerialize(root, result);
    char* res = new char[result.size()];
    memcpy(res, result.c_str(), result.size());
    res[result.size() - 1] = '\0';
    return res;

}

TreeNode* reDeserialize(string& str){
    if (str == "")
    {
        return NULL;
    }
    TreeNode* Node;
    int pos = str.find(',');
    if (str.at(0) == '$')
    {
        Node = NULL;
    }else{
        string num(str.begin(), str.begin()+pos);
        Node = new TreeNode(atoi(num.c_str()));
    }

    if (pos != string::npos)
    {
        str = str.erase(0, pos+1);
        if (Node != NULL)
        {
            Node->left = reDeserialize(str);
            Node->right = reDeserialize(str);
        }
    }else
    {
        str = "";
    }
    return Node;
}

TreeNode* Deserialize(char *str) {
    string sstr(str);
    return reDeserialize(sstr);
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
        char* result = Serialize(tree);
        cout << result << endl;
        TreeNode* newTree = Deserialize(result);

    }
}
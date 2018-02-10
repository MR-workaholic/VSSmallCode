#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    size_t length;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x, size_t y = 0) : val(x), length(y), left(NULL), right(NULL) {}
};

TreeNode* reBuildTree(vector<int> vals){
    size_t len = vals.size();
    if (len == 0)
    {
        return NULL;
    }else if (len == 1)
    {
        return new TreeNode(vals.at(0), 1);
    }
    size_t mid = len >> 1;
    TreeNode* result = new TreeNode(vals.at(mid));
    result->left = reBuildTree(vector<int>(vals.begin(), vals.begin() + mid));
    result->right = reBuildTree(vector<int>(vals.begin() + mid + 1, vals.end()));
    size_t llen = result->left == NULL ? 0 : result->left->length;
    size_t rlen = result->right == NULL ? 0 : result->right->length;
    result->length = max<size_t>({llen, rlen}) + 1;
    return result;
}

int buildMinimalBST_2(vector<int> vals){
    size_t len = vals.size();
    if (len == 0)
    {
        return 0;
    }
    TreeNode* tree = reBuildTree(vals);
    return tree->length;
}

int buildMinimalBST_1(vector<int> vals) {
    // write code here
    size_t size = vals.size();
    if(size == 0){
        return 0;
    }
    int res = floor(log(static_cast<float>(size)) / log(2.0)) + 1;
    return res;
}




int main(int argc, char ** argv){
    streambuf* backup = cin.rdbuf();
    ifstream fin;
    fin.open("data.in");
    cin.rdbuf(fin.rdbuf());

    string inputline;
    istringstream iss;
    int temp;
    while (true)
    {
        getline(cin, inputline);
        iss = istringstream(inputline);
        vector<int> vals;
        while (iss >> temp)
        {
            vals.push_back(temp);
        }
        cout << buildMinimalBST_2(vals) << endl;
    }

}
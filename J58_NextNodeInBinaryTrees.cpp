#include <iostream>

struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {

    }
};

class Solution {
public:
    TreeLinkNode* GetNext(TreeLinkNode* pNode)
    {
        if (pNode == NULL)
        {
            return NULL;
        }
        TreeLinkNode* result = NULL;
        if (pNode->right == NULL)
        {
            if (pNode->next == NULL)
            {
                return NULL;
            }else if (pNode->next->left == pNode)
            {
                return pNode->next;
            }else if (pNode->next->right == pNode)
            {
                result = pNode->next;
                while (result->next != NULL && result->next->left != result)
                {
                    result = result->next;
                }
                return result->next;
            }
        }else
        {
            result = pNode->right;
            while (result->left != NULL)
            {
                result = result->left;
            }
            return result;
        }
        return result;
    }
};

int main(int argc, char ** argv){

    return 0;
}
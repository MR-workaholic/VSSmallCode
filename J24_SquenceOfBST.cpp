/*
5 7 6 9 11 10 8
7 4 6 5
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

bool reConstructTree(vector<int> post, vector<int> vin)
{
    if (post.size() == 0)
    {
        return true;
    }
    auto tailNode = post.end();
    tailNode--;
    auto rootNode = find(vin.begin(), vin.end(), *tailNode);
    if (rootNode == vin.end())
    {
        return false;
    }
    vector<int> rightChildVin(rootNode + 1, vin.end());
    vector<int> leftChildVin(vin.begin(), rootNode);

    vector<int> rightChildPost(tailNode - rightChildVin.size(), tailNode);
    vector<int> leftChildPost(post.begin(), post.begin() + leftChildVin.size());

    return (reConstructTree(leftChildPost, leftChildVin) && reConstructTree(rightChildPost, rightChildVin));

}

bool VerifySquenceOfBST(vector<int> sequence) {
    if (sequence.size() == 0)
    {
        return false;
    }
    vector<int> vin = sequence;
    sort(vin.begin(), vin.end());
    return reConstructTree(sequence, vin);
}

bool VerifySquenceOfBST_2(vector<int> sequence){
    size_t len = sequence.size();
    if (len == 0)
    {
        return true;
    }

    int rootNode = sequence.at(len-1);
    vector<int> leftChildren, rightChildren;
    size_t index(0);
    for (; index < len - 1; ++index)
    {
        if (sequence.at(index) < rootNode)
        {
            leftChildren.push_back(sequence.at(index));
        }else
        {
            break;
        }
    }

    for (; index < len - 1; ++index)
    {
        if (sequence.at(index) > rootNode)
        {
            rightChildren.push_back(sequence.at(index));
        }else
        {
            return false;
        }
    }
    return VerifySquenceOfBST_2(leftChildren) && VerifySquenceOfBST_2(rightChildren);
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
        getline(cin, inputline);
        iss = istringstream(inputline);
        int temp;
        vector<int> record;
        while (iss >> temp)
        {
            record.push_back(temp);
        }
        cout << VerifySquenceOfBST(record) << endl;
        std::cout << VerifySquenceOfBST_2(record) << '\n';
    }
}
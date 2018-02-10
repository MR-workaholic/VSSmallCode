/*
1 3 6 2 4 8
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stack>
#include <deque>

using namespace std;

void pushFromVecToSta(stack<int>& dest, vector<int>::iterator it, vector<int>& src){
    if (it == src.end())
    {
        return;
    }
    pushFromVecToSta(dest, it+1, src);
    dest.push(*it);
    return;
}

vector<int> twoStacksSort(vector<int> numbers) {
    size_t len = numbers.size();
    vector<int> result;
    if (len <= 0)
    {
        return result;
    }
    stack<int> srcStack, tempStack;
    auto ivec = numbers.begin();
    pushFromVecToSta(srcStack, ivec, numbers);

    int min(srcStack.top());
    size_t index(0);
    while (index != len)
    {
        min = srcStack.top();
        while (srcStack.size() != index)
        {
            min = min < srcStack.top() ? min : srcStack.top();
            tempStack.push(srcStack.top());
            srcStack.pop();
        }
        srcStack.push(min);
        bool deleteOne = true;
        while (!tempStack.empty())
        {
            if (!deleteOne || min != tempStack.top())
            {
                srcStack.push(tempStack.top());
            }else
            {
                deleteOne = false;
            }
            tempStack.pop();
        }
        index++;
    }

    while (!srcStack.empty())
    {
        result.push_back(srcStack.top());
        srcStack.pop();
    }
    return result;
}

int main(int argc, char ** argv){
    streambuf* backup;
    backup = cin.rdbuf();
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
        vector<int> numbers;
        while (iss >> temp)
        {
            numbers.push_back(temp);
        }
        vector<int> result = twoStacksSort(numbers);
    }
}
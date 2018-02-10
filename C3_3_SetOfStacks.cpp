/*
5
1 2 1 3 1 4 1 2 1 3 1 4 2 0 1 4 2 0 1 7 2 0 1 6
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stack>
#include <deque>

using namespace std;

vector<vector<int>> setOfStacks(vector<vector<int>> ope, int size) {
    vector<vector<int>> result;
    if (size == 0 || ope.size() == 0 || ope.at(0).size() != 2)
    {
        return result;
    }
    size_t index(0);
    vector<stack<int>> temp;
    temp.push_back(stack<int>());
    for(auto var : ope)
    {
        if (var.at(0) == 1)
        {
            if (temp.at(index).size() >= size)
            {
                temp.push_back(stack<int>());
                ++index;
            }
            temp.at(index).push(var.at(1));

        }else if (var.at(0) == 2)
        {
            temp.at(index).pop();
            if (temp.at(index).size() == 0)
            {
                index--;
                temp.pop_back();
            }
        }
    }
    for(auto var : temp)
    {
        deque<int> vtemp;
        while (!var.empty())
        {
            vtemp.push_front(var.top());
            var.pop();
        }
        result.push_back(vector<int>(vtemp.begin(), vtemp.end()));
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

    while (true)
    {
        getline(cin, inputline);
        iss = istringstream(inputline);
        int size(0);
        iss >> size;
        getline(cin, inputline);
        iss = istringstream(inputline);
        vector<vector<int>> ope;
        int action(0), val(0);
        while (iss >> action >> val)
        {
            vector<int> temp = {action, val};
            ope.push_back(temp);
        }
        setOfStacks(ope, size);
    }
}
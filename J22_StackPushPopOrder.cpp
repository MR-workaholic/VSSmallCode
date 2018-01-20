/*
1 2 3 4 5
4 5 3 2 1(4 3 5 1 2)
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>

using namespace std;

bool IsPopOrder(vector<int> pushV, vector<int> popV) {
    if (pushV.size() == 0 || popV.size() == 0)
    {
        return false;
    }

    stack<int> simStack;
    size_t index = 0;
    for(auto var : popV)
    {
        while(true)
        {
            if (simStack.empty() || simStack.top() != var)
            {
                if (index == pushV.size())
                {
                    return false;
                }
                simStack.push(pushV.at(index));
                index++;
            }else
            {
                simStack.pop();
                break;
            }
        }
    }
    return simStack.empty();
}

int main(int argc, char ** argv){
    streambuf* backup;
    ifstream fin;
    fin.open("data.in");
    backup = cin.rdbuf();
    cin.rdbuf(fin.rdbuf());

    string inputline;
    istringstream iss;

    while (true)
    {
        vector<int> pushV;
        vector<int> popV;
        int temp;
        getline(cin, inputline);
        iss = istringstream(inputline);
        while (iss >> temp)
        {
            pushV.push_back(temp);
        }

        iss = istringstream(inputline);
        while (iss >> temp)
        {
            popV.push_back(temp);
        }



    }
}
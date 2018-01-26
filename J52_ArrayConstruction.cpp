/*
1 2 3 4
2 3
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector<int> multiply(const vector<int>& A) {
    size_t len = A.size();
    if (len == 0 || len == 1)
    {
        return {};
    }
    vector<int> result, pre, next;
    result.reserve(len);
    pre.reserve(len);
    next.reserve(len);

    pre.assign(len, 0);
    pre.at(0) = 1;
    for (size_t i = 1; i < len; i++)
    {
        pre.at(i) = pre.at(i-1) * A.at(i-1);
    }

    next.assign(len, 0);
    next.at(len-1) = 1;
    for (int i = len - 2; i >= 0; i--)
    {
        next.at(i) = next.at(i+1) * A.at(i+1);
    }

    for (size_t i = 0; i < len; i++)
    {
        result.push_back(pre.at(i) * next.at(i));
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
    int temp;
    while (true)
    {
        getline(cin, inputline);
        iss = istringstream(inputline);
        vector<int> A;
        while (iss >> temp)
        {
            A.push_back(temp);
        }
        vector<int> result = multiply(A);
        for(auto var : result)
        {
            cout << var << " ";
        }
        cout << endl;
    }
}
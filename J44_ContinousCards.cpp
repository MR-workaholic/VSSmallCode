/*
0 3 2 6 4
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>

using namespace std;

bool IsContinuous(vector<int> numbers) {
    size_t len = numbers.size();
    if (len != 5)
    {
        return false;
    }
    set<int> record;
    int count4Zero(0);
    for(auto var : numbers)
    {
        if (var == 0)
        {
            count4Zero++;
            continue;
        }
        record.insert(var);
    }
    if (record.size() != 5 - count4Zero)
    {
        return false;
    }
    size_t pre(0);
    size_t miss(0);
    for(auto var : record)
    {
        if (pre == 0)
        {
            pre = var;
            miss = 0;
        }else
        {
            if (var - pre != 1)
            {
                miss += (var-pre-1);
            }
            pre = var;
        }
    }
    if (count4Zero >= miss)
    {
        return true;
    }
    return false;
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
        vector<int> numbers;
        while (iss >> temp)
        {
            numbers.push_back(temp);
        }
        IsContinuous(numbers);
    }
}
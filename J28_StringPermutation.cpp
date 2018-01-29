/*
abc
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>


using namespace std;

void rePermutation(int index, int count, set<string>& resultSet, vector<int>& record, string& temp, string& str)
{
    record.at(index) = 1;
    temp += str.at(index);
    if (count == str.size() - 1)
    {
        resultSet.insert(temp);
    }else
    {
        for (size_t i = 0; i < str.size(); i++)
        {
            if (record.at(i) == 1)
            {
                continue;
            }
            rePermutation(i, count+1, resultSet, record, temp, str);
        }
    }
    record.at(index) = 0;
    temp.erase(temp.end()- 1);
}

vector<string> Permutation(string str) {
    vector<string> results;
    if (str.size() == 0)
    {
        return results;
    }

    vector<int> record(str.size(), 0);
    set<string> resultSet;
    for (size_t i = 0; i < str.size(); i++)
    {
        string temp("");
        rePermutation(i, 0, resultSet, record, temp, str);
    }


    results.assign(resultSet.begin(), resultSet.end());
    return results;
}

void strSwap(string& str, size_t a, size_t b){
    char temp = str.at(a);
    str.at(a) = str.at(b);
    str.at(b) = temp;
}

vector<string> rePermutation_2(string str, size_t start, size_t end){
    vector<string> res;
    if (start == end)
    {
        res.push_back(string(1, str.at(start)));
        return res;
    }
    for (size_t i = start; i <= end; i++)
    {
        strSwap(str, start, i);
        vector<string> temp = rePermutation_2(str, start + 1, end);
        for(auto var : temp)
        {
            res.push_back(string(1, str.at(start)) + var);
        }
        strSwap(str, start, i);
    }
    return res;
}

vector<string> Permutation_2(string str){
    vector<string> results;
    size_t len = str.size();
    if (len == 0)
    {
        return results;
    }else if (len == 1)
    {
        results.push_back(str);
        return results;
    }
    results = rePermutation_2(str, 0, len-1);
    return results;
}

int main(int argc, char **argv){
    streambuf* backup;
    ifstream fin;
    fin.open("data.in");
    backup = cin.rdbuf();
    cin.rdbuf(fin.rdbuf());

    while (true)
    {
        string inputline;
        getline(cin, inputline);
        vector<string> results = Permutation_2(inputline);
        for(auto var : results)
        {
            cout << var << " ";
        }
    }
}
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
        vector<string> results = Permutation(inputline);
        for(auto var : results)
        {
            cout << var << " ";
        }
    }
}
/* 
abacdedsadddss
 */
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

int FirstNotRepeatingChar(string str) {
    int len = str.size();
    if (len == 0)
    {
        return -1;
    }else if (len == 1)
    {
        return 0;
    }
    unordered_map<char, int> record;
    for(auto var : str)
    {
        if (record.find(var) == record.end())
        {
            record.insert({var, 1});
        }else
        {
            record[var]++;
        }
    }
    for (size_t i = 0; i < len; i++)
    {
        if (record.at(str.at(i)) == 1)
        {
            return i;
        }
    }
        
}

int main(int argc, char **argv){
    streambuf* backup;
    ifstream fin;
    fin.open("data.in");
    backup = cin.rdbuf();
    cin.rdbuf(fin.rdbuf());

    while(true){
        string inputline;
        getline(cin, inputline);
        FirstNotRepeatingChar(inputline);
    }
}
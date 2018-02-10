/*
This is nowcoder
is This nowcoder
Here you are
Are you here
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool checkSam(string stringA, string stringB) {
    size_t lenA = stringA.size();
    size_t lenB = stringB.size();
    if (lenA == 0 || lenA != lenB)
    {
        return false;
    }
    vector<int> record(256, 0);
    record.reserve(256);
    for(auto var : stringA)
    {
        ++record.at(var);
    }
    for(auto var : stringB)
    {
        --record.at(var);
        if (record.at(var) < 0)
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char ** argv){
    streambuf* backup;
    backup = cin.rdbuf();
    ifstream fin;
    fin.open("data.in");
    cin.rdbuf(fin.rdbuf());

    string stringA, stringB;
    while (true)
    {
        getline(cin, stringA);
        getline(cin, stringB);
        cout << checkSam(stringA, stringB) << endl;
    }
}
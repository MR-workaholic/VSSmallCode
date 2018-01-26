/*
123
-123
123.23
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

int StrToInt(string str) {
    if (str == "")
    {
        return 0;
    }
    bool IsN = false;
    long long result(0);
    long long bigNum(0x80000000);
    size_t len = str.size();
    for (size_t i = 0; i < len; i++)
    {
        if (str.at(i) == '-' && i == 0)
        {
            IsN = true;
            continue;
        }else if (str.at(i) == '.')
        {
            break;
        }else if (i == 0 && str.at(i) == '+')
        {
            continue;
        }else if (!isdigit(str.at(i)))
        {
            return 0;
        }
        result = result * 10 + (str.at(i) - '0');
        if ((IsN && result > bigNum) || (!IsN && result > bigNum-1)) // Òç³öÅÐ¶Ï
        {
            return 0;
        }
    }
    if (IsN)
    {
        return -result;
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
    while (true)
    {
        getline(cin, inputline);
        cout << StrToInt(inputline) << endl;
    }

}
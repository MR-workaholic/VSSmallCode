/*
This is nowcoder
 */
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void reversreRange(string& str, size_t start, size_t end){
    if (str == "")
    {
        return;
    }
    while (start < end)
    {
        char temp = str.at(start);
        str.at(start++) = str.at(end);
        str.at(end--) = temp;
    }
}

string reverseString(string iniString) {
    size_t len = iniString.size();
    if (len == 0 || len == 1)
    {
        return iniString;
    }
    reversreRange(iniString, 0, len-1);
    size_t start(0);
    size_t i(0);
    for (; i < len; i++)
    {
        if (iniString.at(i) == ' ')
        {
            if (i == 0)
            {
                start = i + 1;
                continue;
            }
            reversreRange(iniString, start, i-1);
            start = i + 1;
        }
    }
    if (start < i)
    {
        reversreRange(iniString, start, len-1);
    }

    return iniString;
}


int main(int argc, char ** argv){
    streambuf* backup;
    backup = cin.rdbuf();
    ifstream fin;
    fin.open("data.in");
    cin.rdbuf(fin.rdbuf());

    string inputline;
    while (true)
    {
        getline(cin, inputline);
        cout << reverseString(inputline) << endl;
    }
}
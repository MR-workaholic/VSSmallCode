/*
Mr John Smith
Hello  World
 */
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*
length: 原字符串的size而不是capacity
 */
string replaceSpace(string iniString, int length) {
    if (length <= 0 || iniString == "")
    {
        return iniString;
    }
    size_t spaceNum(0);
    for(auto var : iniString)
    {
        if (var == ' ')
        {
            spaceNum++;
        }
    }
    int newLen = spaceNum * 2 + length;
    string result(newLen, ' ');
    size_t j = newLen - 1;
    for (int i = length-1; i >= 0; i--)
    {
        if (iniString.at(i) == ' ')
        {
            result.at(j--) = '0';
            result.at(j--) = '2';
            result.at(j--) = '%';
        }else
        {
            result.at(j--) = iniString.at(i);
        }
    }
    return result;
}

int main(int argc, char **argv){
    streambuf* backup;
    ifstream fin;
    fin.open("data.in");
    backup = cin.rdbuf();
    cin.rdbuf(fin.rdbuf());

    string target;
    while (getline(cin, target))
    {
        cout << replaceSpace(target, target.size()) << endl;
    }
}
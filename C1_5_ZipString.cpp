/*
abbccc
 */
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string zipString(string iniString) {
    size_t len = iniString.size();
    if (len < 3)
    {
        return iniString;
    }
    string result("");
    iniString += (iniString[len-1] + 1); // из╠Ь
    for (size_t i = 0; i < len; i++)
    {
        if (iniString.at(i+1) != iniString.at(i))
        {
            result += (string(1, iniString.at(i))+'1');
        }else
        {
            size_t count = 1;
            char target = iniString.at(i);
            while (iniString.at(i+1) == target)
            {
                i++;
                count++;
            }
            result += (string(1, target) + to_string(count));
        }
    }
    iniString.erase(iniString.end()-1);
    if (result.size() < len)
    {
        return result;
    }

    return iniString;
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
        cout << zipString(target) << endl;
    }
}
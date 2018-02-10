/*
Hello world
worldhello
waterbottle
erbottlewat
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool isSubstring(string str, string pat){
    size_t lens = str.size(), lenp = pat.size();
    if (lens == 0 || lenp == 0)
    {
        return false;
    }
    size_t i(0), j(0);
/*     while (str.at(i) != '\0')
    {
        if (str.at(i) != pat.at(j))
        {
            i++;
            // j++;
        }else
        {
            while (pat.at(j) != '\0' && str.at(i) != '\0' && str.at(i) == pat.at(j))
            {
                ++i;
                ++j;
            }
            if (pat.at(j) == '\0')
            {
                return true;
            }else
            {
                j = 0;
                i = i - j + 1;
            }
        }
    }
 */

    while (i < lens && j < lenp)
    {
        if (str.at(i) == pat.at(j))
        {
            i++;
            j++;
        }else
        {
            i = i - j + 1;
            j = 0;
        }
    }
    if (j == lenp)
    {
        return true;
    }
    return false;
}

bool checkReverseEqual(string s1, string s2) {
    if (s1 == "" || s2 == "")
    {
        return false;
    }
    string str = s1 + s1;
    return isSubstring(str, s2);
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
        cout << checkReverseEqual(stringA, stringB) << endl;
    }
}
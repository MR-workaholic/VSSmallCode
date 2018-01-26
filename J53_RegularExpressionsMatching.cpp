/*
aaa
ab*a*c*a
aaa
a*a
aa
.*

.*
aaa
aa.
aaa
ab*ac*a
aaa
aa.a
aaa
a*b*c*
aaa
a*b*c*
aaa
aaa*b*c*
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

/* 76.67% */
bool match(char* str, char* pattern)
{
    char *p1 = str, *p2 = pattern;

    while (*p1 != '\0' || *p2 != '\0')
    {
        if (*p1 == '\0')
        {
            if (*p2 == '*')
            {
                while (*(p2+1) == *(p1-1) || *(p2+1) == '.')
                {
                    p2++;
                    if (*p2 == '\0')
                    {
                        return true;
                    }
                }
                p2++;
            }
            while (*p2 != '\0')
            {
                if (*(p2+1) == '*')
                {
                    p2 = p2 + 2;
                    continue;
                }
                return false;
            }
            return true;
        }

        if (*p1 == *p2 ||  *p2 == '.')
        {
            p1++;
            p2++;
            continue;
        }
        if (*p1 != *p2)
        {
            if (*p2 == '\0')
            {
                return false;
            }
            if (*p2 == '*' && (*p1 == *(p2-1) || *(p2-1) == '.'))
            {
                p1++;
                continue;
            }else if (*(p2+1) == '*')
            {
                p2 = p2 + 2;
                continue;
            }else if (*p2 == '*' && *p1 == *(p2+1))
            {
                p2 = p2+2;
                p1++;
                continue;
            }
        }

        return false;
    }

    return true;
}

/* book */
bool matchCore(char* str, char* pattern){
    if (*str == '\0' && *pattern == '\0')
    {
        return true;
    }
    if (*str != '\0' && *pattern == '\0')
    {
        return false;
    }

    if (*(pattern+1) == '*')
    {
        if (*str == *pattern || (*pattern=='.' && *str != '\0'))
        {
            return matchCore(str+1, pattern+2) ||  //匹配一个
                   matchCore(str, pattern+2) ||    //忽略一个
                   matchCore(str+1, pattern);      //匹配多个
        }else{
            return matchCore(str, pattern+2);
        }
    }
    if (*str == *pattern || (*pattern == '.' && *str != '\0'))
    {
        return matchCore(str+1, pattern+1);
    }
    return false;
}



int main(int argc, char **argv){
    streambuf* backup;
    ifstream fin;
    fin.open("data.in");
    backup = cin.rdbuf();
    cin.rdbuf(fin.rdbuf());

    string inputline1, inputline2;
    while (true)
    {
        getline(cin, inputline1);
        char* str = const_cast<char*>(inputline1.c_str());
        getline(cin, inputline2);
        char* pattern = const_cast<char*>(inputline2.c_str());
        cout << match(str, pattern) << endl;
    }


}
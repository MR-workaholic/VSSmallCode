/*
+
-.123
.12
+100
5e2
-123
3.14156
-1E-16
12e
1a3.14
1.2.3
+-5
12e+5.4
 */
#include <iostream>
#include <fstream>

using namespace std;

bool reIsNumeric(char* str, char* pat){
    if (*str == '\0')
    {
        if ((*pat == 'd' && *(pat+1) != 'd') || *pat == '.') // (*pat == 'd' && *(pat+1) != 'd')就是为了防止只出现一个+/-符号的情况
        {
            return true;
        }
        return false;
    }
    if (*pat == 's' && (*str == '+' || *str == '-'))
    {
        return reIsNumeric(str+1, pat+1);
    }else if (*pat == 's' && (*str) >= '0' && (*str) <= '9')
    {
        return reIsNumeric(str, pat+1);
    }

    if (*pat == 'd' && (*str) >= '0' && (*str) <= '9')
    {
        if (*(pat+1) == 'd')
        {
            return reIsNumeric(str+1, pat+1);
        }else
        {
            return reIsNumeric(str+1, pat);
        }
    }

    if (*str == '.')
    {
        while (*pat != '\0' && *pat != '.')
        {
            pat++;
        }
        if (*pat == '.')
        {
            return reIsNumeric(str+1, pat+1);
        }
    }
    if ((*str == 'e' || *str == 'E') && *pat == 'd')
    {
        while (*pat != '\0' && *pat != 'e')
        {
            pat++;
        }
        if (*(pat)=='e')
        {
            return reIsNumeric(str+1, pat+1);
        }
    }
    return false;
}

bool isNumeric(char* string)
{
    if (*string == '\0')
    {
        return false;
    }
    char pat[] = "sdd.desd"; // sdd中的两个d是防止只有一个符号，如'+'这种情况出现
    // char* pat = const_cast<char*>(pattern.c_str());
    return reIsNumeric(string, pat);

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
        char* str = const_cast<char*>(inputline.c_str());
        cout << isNumeric(str) << endl;
    }


}
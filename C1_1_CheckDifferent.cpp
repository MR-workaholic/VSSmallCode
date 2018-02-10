/*
abc
abcdsfnrehv
cvsdihvbd
 */
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


typedef enum
{
    MARK = 0x1F,
    BITNUMBER = 32,
    CHARNUM = 256,
    SHIFT = 5

}SomeConst;

void clearBit(size_t* p){
    for (size_t i = 0; i < (CHARNUM / BITNUMBER + 1); i++)
    {
        for (size_t j = 0; j < BITNUMBER; j++)
        {
            p[i] &= ~(0x1 << j);
        }
    }
}

bool checkBit(char v, size_t* p){
    return p[v >> SHIFT] & (0x1 << (v & MARK));
}

void setBit(char v, size_t* p){
    p[v >> SHIFT] |= (0x1 << (v & MARK));
}

bool checkDifferent(string iniString) {
    int len = iniString.size();
    if (len == 0 || len > CHARNUM)
    {
        return false;
    }else if (len == 1)
    {
        return true;
    }
    size_t record[CHARNUM / BITNUMBER + 1];
    clearBit(record);
    for(auto var : iniString)
    {
        if (checkBit(var, record))
        {
            return false;
        }else
        {
            setBit(var, record);
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

    string inputline;
    while (true)
    {
        getline(cin, inputline);
        cout << checkDifferent(inputline) << endl;
    }
}
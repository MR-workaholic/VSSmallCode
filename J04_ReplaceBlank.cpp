/*
We Are Happy!
Ok lalalal haha ds
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>

using namespace std;

void replaceSpace(char* str, int length){
    if (str == nullptr || length <= 0)
    {
        return;
    }
    size_t strLen = 0, spaceNum = 0;
    char* temp = str;
    while (*temp != '\0')
    {
        strLen++;
        if (*temp == ' ')
        {
            spaceNum++;
        }
        temp++;
    }
    size_t newStrLen = strLen + (spaceNum << 1);
    if (newStrLen > length)
    {
        return;
    }
    str[newStrLen] = '\0';
    for (int i = newStrLen - 1, j = strLen - 1; i >= 0;)
    {
        if (str[j] != ' ')
        {
            str[i--] = str[j--];
        }else{
            str[i--] = '0';
            str[i--] = '2';
            str[i--] = '%';
            j--;
        }
    }
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
        int length = 100;
        char* temp = new char[length];
        memcpy(temp, target.c_str(), target.size());
        temp[target.size()] = '\0';
        // char* temp = const_cast<char*>(target.c_str());
        replaceSpace(temp, length);
        cout << temp << endl;
        delete[] temp;
    }
}
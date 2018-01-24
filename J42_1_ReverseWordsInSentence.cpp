/*
I am a student.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void ReverseRange(string& str, int left, int right){
    while (left < right)
    {
        char temp = str.at(left);
        str.at(left++) = str.at(right);
        str.at(right--) = temp;
    }
}

string ReverseSentence(string str) {
    size_t len = str.size();
    if (len == 0 || len == 1)
    {
        return str;
    }
    ReverseRange(str, 0, len-1);
    //cout << 9 << str.at(9) << 11 << str.at(11) << endl;
    int left(0);
    bool endWithSpace(false);
    for (size_t i = 0; i < len; i++)
    {
        if (str.at(i) == ' ')
        {
            ReverseRange(str, left, i-1);
            while (++i < len && str.at(i) == ' ');
            if (i >= len)
            {
                endWithSpace = true;
                break;
            }
            left = i;
        }
    }
    if (!endWithSpace)
    {
        ReverseRange(str, left, len-1);
    }
    return str;
}

int main(int argc, char **argv){
    streambuf* backup;
    ifstream fin;
    fin.open("data.in");
    backup = cin.rdbuf();
    cin.rdbuf(fin.rdbuf());

    string inputline;
    istringstream iss;

    while (true)
    {
        getline(cin, inputline);
        string str = ReverseSentence(inputline);
        cout << str << endl;
    }

}
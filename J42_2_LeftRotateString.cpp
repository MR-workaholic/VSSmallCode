/*
abcdefg
2
abcdefg
6
abcdefg
7
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

string LeftRotateString(string str, int n) {
    if (n == 0 || str == "" || str.size() <= n)
    {
        return str;
    }

    ReverseRange(str, 0, n-1);
    ReverseRange(str, n, str.size()-1);
    ReverseRange(str, 0, str.size()-1);
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
        string num;
        getline(cin, num);
        iss = istringstream(num);
        int n;
        iss >> n;
        string str = LeftRotateString(inputline, n);
        cout << str << endl;
    }

}
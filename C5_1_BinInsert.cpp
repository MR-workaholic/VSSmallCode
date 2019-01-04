/*
1024 19 2 6
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


void clearBit(int& num, int tar){
    num = num & ~(1 << tar);
}

bool getBit(const int num, int tar){
    return (num & (1 << tar)) != 0;
}

void updateBit(int& num, int tar, int val){
    clearBit(num, tar);
    num = num | (val << tar);
}

int binInsert(int n, int m, int j, int i) {
    for (size_t a = j; a <= i; a++)
    {
        updateBit(n, a, getBit(m, a-j));
    }
    return n;
}

int main(int argc, char ** argv){
    streambuf* backup;
    backup = cin.rdbuf();
    ifstream fin;
    fin.open("data.in");
    cin.rdbuf(fin.rdbuf());

    string inputline;
    istringstream iss;
    while (true)
    {
        getline(cin, inputline);
        iss = istringstream(inputline);
        int a, b, c, d;
        iss >> a >> b >> c >> d;
        cout << binInsert(a, b, c, d) << endl;
    }


}
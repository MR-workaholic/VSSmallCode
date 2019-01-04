/*
2
 */
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

int getNext(int num){
    int temp(num), c0(0), c1(0);
    while (((temp & 1) == 0) && (temp != 0))
    {
        c0++;
        temp >>= 1;
    }
    while ((temp & 1) == 1)
    {
        c1++;
        temp >>= 1;
    }
    // 判断num=高位全是1，低位全是0， 或者num=0
    if (c0 + c1 == 31 || c0 + c1 == 0)
    {
        return -1;
    }

    int p = c0 + c1;
    num = num | (1 << p);
    int mark = ~((1 << p) - 1);
    num = num & mark;
    if (c1 - 1 != 0)
    {
        mark = (1 << (c1 - 1)) - 1;
        num = num | mark;
    }
    return num;
}

int getPre(int num){
    int temp(num), c1(0), c0(0);
    while ((temp & 1) == 1)
    {
        c1++;
        temp = temp >> 1;
    }
    while ((temp != 0) && ((temp & 1) == 0))
    {
        c0++;
        temp = temp >> 1;
    }
    // 判断num=低位全是1，高位全是0，或者num=0
    if (c0 == 0)
    {
        return -1;
    }

    int p = c0 + c1;
    int mark = ~((1 << (p + 1)) - 1);
    num = num & mark;
    mark = ((1 << (c1 + 1)) - 1) << (c0 - 1);
    num = num | mark;
    return num;
}

vector<int> getCloseNumber(int x) {
    vector<int> res;
    if (x < 0)
    {
        return res;
    }
    res.push_back(getPre(x));
    res.push_back(getNext(x));
    return res;
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
        int a;
        iss >> a;
        vector<int> res = getCloseNumber(a);
        for(auto var : res)
        {
            cout << var << " ";
        }
        cout << endl;
    }
}
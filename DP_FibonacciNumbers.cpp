/*
求斐波拉契数列相应值
5
6
7
 */
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

size_t dp_fibonacci(size_t val){
    if (val == 0 || val == 1)
    {
        return val;
    }
    vector<size_t> record = {0, 1};
    size_t size;
    while ((size = record.size()) <= val)
    {
        record.push_back(record.at(size-1) + record.at(size-2));
    }
    return record.at(size-1);
}

int main(int argc, char ** argv){
    streambuf* backup;
    ifstream fin;
    fin.open("data.in");
    backup = cin.rdbuf();
    cin.rdbuf(fin.rdbuf());

    string inputline;
    istringstream iss;
    size_t val;
    while (true)
    {
        getline(cin, inputline);
        iss = istringstream(inputline);
        iss >> val;
        cout << dp_fibonacci(val) << endl;
    }

}
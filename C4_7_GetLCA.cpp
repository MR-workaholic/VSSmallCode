#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

int getLevel(int a){
    return floor(log(static_cast<float>(a)) / log(2.0)) + 1;
}

int getLCA(int a, int b) {
    if (a == 0 || b == 0)
    {
        return 0;
    }
    while (getLevel(a) > getLevel(b))
    {
        a /= 2;
    }
    while (getLevel(b) > getLevel(a))
    {
        b /= 2;
    }
    while (a != b)
    {
        a /= 2;
        b /= 2;
    }
    return a;
}

int main(int argc, char **argv){
    streambuf* backup;
    ifstream fin;
    fin.open("data.in");
    backup = cin.rdbuf();
    cin.rdbuf(fin.rdbuf());

    string inputline;
    istringstream iss;
    int a, b;
    while (true)
    {
        getline(cin, inputline);
        iss = istringstream(inputline);
        iss >> a >> b;
        cout << getLCA(a, b) << endl;
    }

}
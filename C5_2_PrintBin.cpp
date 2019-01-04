/*
0.625
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

string printBin(double num) {
    string err = "Error";
    if (num <= 0 || num >= 1)
    {
        return err;
    }
    string res = "0.";
    bool retRes = false;
    for (int i = 1; i <= 32; i++)
    {
        double temp = pow(2.0, static_cast<double>(-i));
        if (num >= temp)
        {
            res += "1";
            num -= temp;
            if (num > -0.00000000001 && num < 0.000000000001)
            {
                retRes = true;
                break;
            }
        }else
        {
            res += "0";
        }
    }
    if (retRes)
    {
        return res;
    }
    return err;
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
        double a;
        iss >> a;
        cout << printBin(a) << endl;
    }
}
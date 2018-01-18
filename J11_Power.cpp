#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

double Power(double base, int exponent) {
    float zero = 0.0000001;
    if ((base - 0.0) > -zero && (base - 0.0) < zero)
    {
        return 0;
    }
    if (exponent == 0)
    {
        return 1;
    }
    bool isN = false;
    if (base < 0 && exponent % 2 == 1)
    {
        isN = true;
        base = -base;
    }
    if (exponent < 0)
    {
        base = 1 / base;
        exponent = -exponent;
    }
    size_t count = 0;
    double result = 1.0;
    while (++count <= exponent)
    {
        result *= base;
    }
    if (isN)
    {
        return -result;
    }
    return result;
}

int main(int argc, char ** argv){
    streambuf* backup;
    fstream fin;
    fin.open("data.in");
    backup = cin.rdbuf();
    cin.rdbuf(fin.rdbuf());

    string inputline;
    istringstream iss;
    while (true)
    {
        getline(cin, inputline);
        iss = istringstream(inputline);
        int base;
        int exponent;
        iss >> base >> exponent;

    }

}
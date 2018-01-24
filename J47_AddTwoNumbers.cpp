/*
5 7
-1 6
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int Add(int num1, int num2)
{
    if (num1 == 0 || num2 == 0)
    {
        return num1 == 0 ? num2 : num1;
    }
    int sum, array;
    do
    {
        sum = num1 ^ num2;
        array = (num1 & num2) << 1;

        num1 = sum;
        num2 = array;
    } while(array != 0);

    return sum;
}

int Add_2(int num1, int num2){
    if (num1 == 0 || num2 == 0)
    {
        return num1 == 0 ? num2 : num1;
    }
    int result(0), shift(0x1);
    char array(0x0);
    for (size_t i = 0; i < 32; i++)
    {
        char a = (num1>>i) & shift;
        char b = (num2>>i) & shift;
        char sum = (a ^ b ^ array) & shift;
        if (sum)
        {
            result |= (shift << i);
        }else{
            result &= ~(shift << i);
        }
        if (a==b && b == array)
        {
            array = sum;
        }else
        {
            array = ((~sum) & shift);
        }
    }
    return result;

}

int main(int argc, char ** argv){
    streambuf* backup;
    ifstream fin;
    fin.open("data.in");
    backup = cin.rdbuf();
    cin.rdbuf(fin.rdbuf());

    while (true)
    {
        int n, m;
        cin >> n >> m;
        cout << n << "+" << m << "=" << Add_2(n, m) << endl;

    }
}
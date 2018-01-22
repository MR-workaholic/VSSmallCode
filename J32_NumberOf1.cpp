#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;

int NumberOf1Between1AndN_Solution(int n)
{
    if (n <= 0)
    {
        return 0;
    }
    string num = to_string(n);
    size_t digits = num.size(), firstNum = num.at(0) - '0';
    if (digits == 1)
    {
        if (firstNum > 0)
        {
            return 1;
        }else
        {
            return 0;
        }
    }

    int numOfFirstNumberIs1;
    if (firstNum > 1)
    {
        numOfFirstNumberIs1 = static_cast<int>(pow(10.0, digits-1));
    }else
    {
        numOfFirstNumberIs1 = atoi(string(num.begin() + 1, num.end()).c_str()) + 1;
    }
    int numOfOtherNumberIs1 = firstNum * static_cast<int>(pow(10.0, digits-2)) * (digits-1);

    return numOfFirstNumberIs1 + numOfOtherNumberIs1 + NumberOf1Between1AndN_Solution(atoi(string(num.begin() + 1, num.end()).c_str()));
}



int main(int argc, char ** argv){

    while (true)
    {
        int temp;
        cin >> temp;
        cout << NumberOf1Between1AndN_Solution(temp) << endl;
    }

}
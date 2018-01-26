/*
5
2 1 3 1 4
11
2 3 1 0 2 5 3 2 2 2 2
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

bool duplicate(int numbers[], int length, int* duplication) {
    if (length == 0)
    {
        return false;
    }
    sort(numbers, numbers + length);
    int count(0);
    int pre;
    bool dupagain = false;
    for (size_t i = 0; i < length; i++)
    {
        if (i == 0)
        {
            pre = numbers[i];
            continue;
        }
        if (pre == numbers[i] && !dupagain)
        {
            duplication[count++] = pre;
            dupagain = true;
            continue;
        }else if (pre == numbers[i] && dupagain)
        {
            continue;
        }
        pre = numbers[i];
        dupagain = false;
    }
    if (count == 0)
    {
        return false;
    }

    return true;
}

int main(int argc, char **argv){
    streambuf* backup;
    ifstream fin;
    fin.open("data.in");
    backup = cin.rdbuf();
    cin.rdbuf(fin.rdbuf());

    string inputline;
    istringstream iss;
    int temp;
    while (true)
    {
        getline(cin, inputline);
        iss = istringstream(inputline);
        iss >> temp;
        int* numbers = new int[temp];
        getline(cin, inputline);
        iss = istringstream(inputline);
        int count(0);
        while (iss >> temp)
        {
            numbers[count++] = temp;
        }
        int* result = new int[temp >> 1];
        bool IsOK = duplicate(numbers, count, result);
        delete[] numbers;
        numbers = nullptr;
        delete[] result;
        result = nullptr;

    }
}
/*
2 4 3 6 3 2 5 5
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

void FindNumsAppearOnce(vector<int> data, int* num1, int *num2) {
    size_t len = data.size();
    if (len == 0 || len == 1 || (len == 2 && data.at(0) == data.at(1)))
    {
        return;
    }else if (len == 2)
    {
        *num1 = data.at(0);
        *num2 = data.at(1);
    }

    int result;
    for (size_t i = 0; i < len; i++)
    {
        if (i == 0)
        {
            result = data.at(i);
        }else
        {
            result = result ^ data.at(i);
        }
    }

    int n(0);
    while ((result & (0x1 << n)) == 0){
        n++;
    }

    vector<int> dataleft, dataright;
    int mark = 0x1 << n;
    for(auto var : data)
    {
        if (var & mark)
        {
            dataright.push_back(var);
        }else
        {
            dataleft.push_back(var);
        }
    }
    len = dataleft.size();
    for (size_t i = 0; i < len; i++)
    {
        if (i == 0)
        {
            *num1 = dataleft.at(i);
        }else
        {
            *num1 = (*num1) ^ dataleft.at(i);
        }
    }

    len = dataright.size();
    for (size_t i = 0; i < len; i++)
    {
        if (i == 0)
        {
            *num2 = dataright.at(i);
        }else
        {
            *num2 = (*num2) ^ dataright.at(i);
        }
    }
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
        vector<int> data;
        while (iss >> temp)
        {
            data.push_back(temp);
        }
        int one, two;
        FindNumsAppearOnce(data, &one, &two);
        cout << one << " " << two << endl;
    }
}
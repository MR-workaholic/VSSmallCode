/*
6 -3 -2 7 -15 1 2 2
 */
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

int FindGreatestSumOfSubArray(vector<int> array) {
    int temp(0), result(0);
    for(auto var : array)
    {
        temp += var;
        temp = temp < 0 ? 0 : temp;
        result = result < temp ? temp : result;
    }
    if (result == 0)
    {
        result = array.at(0);
        for(auto var : array)
        {
            result = var > result ? var : result;
        }
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
        int temp;
        vector<int> record;
        while (iss >> temp)
        {
            record.push_back(temp);
        }
        cout FindGreatestSumOfSubArray(record) << endl;
    }

}
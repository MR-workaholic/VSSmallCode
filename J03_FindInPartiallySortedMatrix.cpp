/*
data.in
5 11 6 16 1 9
1 2 8 9
2 4 9 12
4 7 10 13
6 8 11 15
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

bool Find(int target, const vector<vector<int>>& array){
    int rowLen = array.size();
    if (rowLen == 0)
    {
        return false;
    }
    int columnLen = array.at(0).size();
    if (columnLen == 0)
    {
        return false;
    }
    int row = 0, column = columnLen - 1;

    while (row < rowLen && column >= 0)
    {
        if (array.at(row).at(column) == target)
        {
            return true;
        }else if (array.at(row).at(column) > target)
        {
            column--;
        }else
        {
            row++;
        }
    }

    return false;
}


int main(int argc, char **argv){
    streambuf* backup;
    ifstream fin;
    fin.open("data.in");
    backup = cin.rdbuf();
    cin.rdbuf(fin.rdbuf());

    string inputline;
    getline(cin, inputline);
    istringstream iss(inputline);
    vector<int> targetVec;
    int target;
    while (iss >> target)
    {
        targetVec.push_back(target);
    }
    vector<vector<int>> matrix;

    while (true)
    {
        getline(cin, inputline);
        if (inputline == "")
        {
            break;
        }
        iss = istringstream(inputline);
        vector<int> temp;
        int num;
        while (iss >> num)
        {
            temp.push_back(num);
        }
        matrix.push_back(temp);
    }

    for(auto var : targetVec)
    {
        cout << (Find(var, matrix) ? "yes" : "no") << endl;
    }



    cin >> target;

    return 0;
}
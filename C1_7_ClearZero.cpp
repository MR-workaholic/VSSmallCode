/*
3
1 2 3 0 1 2 0 0 1
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector<vector<int>> clearZero(vector<vector<int>> mat, int n) {
        // write code here
        vector<vector<int>> results;
        if (n == 0)
        {
            return results;
        }else if (n == 1)
        {
            return mat;
        }
        for (size_t i = 0; i < n; i++)
        {
            vector<int> temp(n, 0);
            for (size_t j = 0; j < n; j++)
            {
                if (mat.at(i).at(j) == 0)
                {
                    continue;
                }
                bool isZero(false);
                for (size_t k = 0; k < n; k++)
                {
                    if (mat.at(i).at(k) == 0 || mat.at(k).at(j) == 0)
                    {
                        isZero = true;
                        break;
                    }
                }
                if (!isZero)
                {
                    temp.at(j) = mat.at(i).at(j);
                }
            }
            results.push_back(temp);
        }
        return results;
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
        vector<vector<int>> mat;
        getline(cin, inputline);
        iss = istringstream(inputline);
        int num;
        while (mat.size() != temp)
        {
            vector<int> vtemp;
            while (vtemp.size() != temp)
            {
                iss >> num;
                vtemp.push_back(num);
            }
            mat.push_back(vtemp);
        }
        vector<vector<int>> result = clearZero(mat, temp);
    }
}
/*
3
4
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector<vector<int>> transformImage(vector<vector<int>> mat, int n) {
    // write code here
    if (n < 2)
    {
        return mat;
    }

    for (size_t k = 0; 2*k < (n-1); k++)
    {
        int i = 0+k, j = n-1-k;
        for (size_t o = 0; o < (j-i); o++)
        {
            int temp = mat.at(i).at(i+o);
            mat.at(i).at(i+o) = mat.at(j-o).at(i);
            mat.at(j-o).at(i) = mat.at(j).at(j-o);
            mat.at(j).at(j-o) = mat.at(i+o).at(j);
            mat.at(i+o).at(j) = temp;
        }
    }
    return mat;
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
        int count(0);
        while (mat.size() != temp)
        {
            vector<int> vtemp;
            while (vtemp.size() != temp)
            {
                vtemp.push_back(++count);
            }
            mat.push_back(vtemp);
        }
        vector<vector<int>> result = transformImage(mat, temp);
    }
}
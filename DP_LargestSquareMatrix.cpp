/*
最大方子阵，面积最大的都为零的方形阵
输入格式如下：
4 5
0 0 0 1 1
0 0 0 1 0
0 0 0 1 1
1 0 1 0 1
 */
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>


using namespace std;

size_t dp_largestsquarematrix(size_t rows, size_t cols, vector<vector<bool>> array){
    if (rows == 0 || cols == 0)
    {
        return 0;
    }
    vector<vector<size_t>> record;
    record.reserve(rows+1);
    int tempI = rows + 1;
    while (tempI--)
    {
        vector<size_t> tempV(cols+1, 0);
        tempV.reserve(cols+1);
        record.push_back(tempV);
    }
    size_t maxV(0);
    for (size_t i = 1; i < rows+1; ++i)
    {
        for (size_t j = 1; j < cols+1; ++j)
        {
            if (record.at(i-1).at(j) == 0 || record.at(i).at(j-1) == 0)
            {
                if (!array.at(i-1).at(j-1))
                {
                    record.at(i).at(j) = 1;
                    maxV = max<size_t>({maxV, record.at(i).at(j)});
                }
            }else
            {
                if (!array.at(i-1).at(j-1))
                {
                    record.at(i).at(j) = record.at(i-1).at(j-1) + 1;
                    maxV = max<size_t>({maxV, record.at(i).at(j)});
                }
            }
        }
    }
    return maxV * maxV;
}

int main(int argc, char ** argv){
    streambuf* backup;
    ifstream fin;
    fin.open("data.in");
    backup = cin.rdbuf();
    cin.rdbuf(fin.rdbuf());

    string inputline;
    istringstream iss;
    size_t rows, cols;
    while (true)
    {
        getline(cin, inputline);
        iss = istringstream(inputline);
        iss >> rows >> cols;
        vector<vector<bool>> array;
        int temp = rows;
        while (temp--)
        {
            getline(cin, inputline);
            iss = istringstream(inputline);
            vector<bool> tempV;
            size_t tempI;
            while (iss >> tempI)
            {
                if (tempI == 1)
                {
                    tempV.push_back(true);
                }else
                {
                    tempV.push_back(false);
                }
            }
            array.push_back(tempV);
        }
        cout << dp_largestsquarematrix(rows, cols, array) << endl;

    }

}

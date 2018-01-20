/*
4 4
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector<int> printMatrix(vector<vector<int>> matrix) {
    if (matrix.size() == 0)
    {
        return {};
    }
    int rows = matrix.size();
    int columns = matrix.at(0).size();

    int startPoint = 0;
    vector<int> result;
    while (startPoint * 2 < rows && startPoint * 2 < columns)
    {
        // 打印上边一行
        for (int i = startPoint; i < columns - startPoint; i++)
        {
            result.push_back(matrix.at(startPoint).at(i));
        }
        // 打印右边一列
        for (int i = startPoint + 1; i < rows - startPoint; i++)
        {
            result.push_back(matrix.at(i).at(columns-startPoint-1));
        }
        // 打印下边一行
        if (startPoint != rows - startPoint -1)  // 重点判断，打印上下边的，行是否相同
        {
            for (int i = columns - startPoint -2; i > startPoint - 1; i--)
            {
                result.push_back(matrix.at(rows-startPoint-1).at(i));
            }
        }
        // 打印左边一列
        if (startPoint != columns - startPoint -1) //  重点判断，打印左右列的，列是否相同
        {
            for (int i = rows - startPoint - 2; i > startPoint; i--)
            {
                result.push_back(matrix.at(i).at(startPoint));
            }
        }

        startPoint++;
    }
    return result;
}

int main(int argc, char ** argv){
    streambuf* backup;
    ifstream fin;
    fin.open("data.in");
    backup = cin.rdbuf();
    cin.rdbuf(fin.rdbuf());

    string inputline;
    istringstream iss;
    while (true)
    {
        int rows, columns;
        vector<vector<int> > matrix;
        getline(cin, inputline);
        iss = istringstream(inputline);
        iss >> rows >> columns;

        matrix.reserve(rows);
        getline(cin, inputline);
        iss = istringstream(inputline);
        for (size_t j = 0; j < rows; j++)
        {
            vector<int> tempVec;
            tempVec.reserve(columns);
            for (size_t i = 0; i < columns; i++)
            {
                int temp;
                iss >> temp;
                tempVec.push_back(temp);
            }
            matrix.push_back(tempVec);
        }
        printMatrix(matrix);

    }

}
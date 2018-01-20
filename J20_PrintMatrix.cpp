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
        // ��ӡ�ϱ�һ��
        for (int i = startPoint; i < columns - startPoint; i++)
        {
            result.push_back(matrix.at(startPoint).at(i));
        }
        // ��ӡ�ұ�һ��
        for (int i = startPoint + 1; i < rows - startPoint; i++)
        {
            result.push_back(matrix.at(i).at(columns-startPoint-1));
        }
        // ��ӡ�±�һ��
        if (startPoint != rows - startPoint -1)  // �ص��жϣ���ӡ���±ߵģ����Ƿ���ͬ
        {
            for (int i = columns - startPoint -2; i > startPoint - 1; i--)
            {
                result.push_back(matrix.at(rows-startPoint-1).at(i));
            }
        }
        // ��ӡ���һ��
        if (startPoint != columns - startPoint -1) //  �ص��жϣ���ӡ�����еģ����Ƿ���ͬ
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
/*
����һ��M*N�ľ��󣬼�������Ӿ����
������һ����ά����p���������Ĳ��ֺͣ�p[i][j]��ʾ���Ͻ���(1, 1)��(�±��1��ʼ)�� ���½���(i, j)�ľ�����Ԫ�صĺ͡�
p[i][j] = p[i-1][j] + p[i][j-1] - p[i-1][j-1] + array[i][j]
�������Ҫ��i~j�С�k~m�еľ�����Ԫ�صĺͣ����ǿ���ͨ������ʽ�Ӽ���ó���
sum = p[j][m] - p[j][k-1] - p[i-1][m] + p[i-1][k-1]
��i��j������n^2�ı�������k��m������һά���������Ӷκ͵�˼��

4 4
0 -2 -7 0
9 2 -6 2
-4 1 -4 1
-1 8 0 -2
 */
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <climits>


using namespace std;

int dp_largestsubmatrixsum(size_t rows, size_t cols, vector<vector<int>> array){
    if (rows == 0 || cols == 0)
    {
        return 0;
    }

    vector<vector<int>> p;
    p.reserve(rows+1);
    // �����Ƿ����������
    bool allIsN = true;
    int bigN = INT_MIN;
    for (size_t i = 0; i <= rows; ++i)
    {
        vector<int> tempV(cols+1, 0);
        tempV.reserve(cols+1);
        p.push_back(tempV);
    }
    for (size_t i = 1; i <= rows; i++)
    {
        for (size_t j = 1; j <= cols; j++)
        {
            p.at(i).at(j) = p.at(i-1).at(j) + p.at(i).at(j-1) + array.at(i-1).at(j-1) - p.at(i-1).at(j-1);
            if (allIsN && array.at(i-1).at(j-1) <= 0)
            {
                bigN = max<int>({bigN, array.at(i-1).at(j-1)});
            }else if (allIsN && array.at(i-1).at(j-1) > 0)
            {
                allIsN = false;
            }
        }
    }
    if (allIsN)
    {
        return bigN;
    }

    int result(0);
    for (size_t i = 1; i <= rows; i++)
    {
        for (size_t j = i; j <= rows; j++)
        {
            int temp(0);
            for (size_t k = 1; k <= cols; k++)
            {
                temp += (p.at(j).at(k) - p.at(i-1).at(k) - p.at(j).at(k-1) + p.at(i-1).at(k-1));
                if (temp < 0)
                {
                    temp = 0;
                }else
                {
                    result = max<int>({result, temp});
                }
            }
        }
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
    size_t rows, cols;
    while (true)
    {
        getline(cin, inputline);
        iss = istringstream(inputline);
        iss >> rows >> cols;
        vector<vector<int>> array;
        int temp = rows;
        while (temp--)
        {
            getline(cin, inputline);
            iss = istringstream(inputline);
            vector<int> tempV;
            int tempI;
            while (iss >> tempI)
            {
                tempV.push_back(tempI);
            }
            array.push_back(tempV);
        }
        cout << dp_largestsubmatrixsum(rows, cols, array) << endl;

    }

}

/*
01��������
��ά������һλ���鶼�еĽⷨ
r(i, j)��ʾ�ڳ�����Ϊj��ʱ�򣬿����Ƿ���Ҫ��Ʒi(��r�����У���Ʒ��������1��ʼ����w��v�����У�������0��ʼ)
r(i,j) = max(r(i-1, j), r(i-1, j-w(i-1)) + v(i-1))
����˵�� ����Ҫi��r(i-1,j)���롾Ҫ��Ҫi��r(i-1, j-w(i-1))����ѡ��һ��i��������ѡ�����ֵ
4 5
2 1 3 2
12 10 20 15
5 6
3 2 1 4 5
25 20 15 40 50
 */
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<size_t> dp_knapsackquestion(size_t numOfgoods, size_t totalWeight, vector<size_t> weightVec, vector<size_t> valueVec){
    vector<size_t> results;
    if (numOfgoods == 0 || totalWeight == 0)
    {
        return results;
    }
    // ����record���飬��Ҫ����һ��һ��
    vector<vector<size_t>> record;
    record.reserve(numOfgoods + 1);
    for (size_t i = 0; i < numOfgoods + 1; i++)
    {
        vector<size_t> temp(totalWeight+1, 0);
        record.push_back(temp);
    }

    // �ڳ��������ڵ�����Ʒi����1��ʼ����������������ʱ��ѡ��r(i-1, j)��r(i-1, j-w(i-1)) + v(i-1)֮������ֵ������֮�����ڳ�����j֮��ѡ��Ҫ��Ҫi
    for (size_t i = 1; i <= numOfgoods; i++)
    {
        for (size_t j = 1; j <= totalWeight; j++)
        {
            if (j < weightVec.at(i-1))
            {
                record.at(i).at(j) = record.at(i-1).at(j);
            }else
            {
                record.at(i).at(j) = max<size_t>({ record.at(i-1).at(j), record.at(i-1).at(j-weightVec.at(i-1)) + valueVec.at(i-1) });
            }
        }
    }

    //���ݳ�·������r(i, j) == r(i-1, j)��ʱ���ǲ���Ҫi�ģ���������Ҫi��
    size_t recallI(numOfgoods), recallJ(totalWeight);
    while (recallI != 0 && recallJ != 0)
    {
        if (record.at(recallI).at(recallJ) != record.at(recallI-1).at(recallJ)) // ���������Ʒ��������recallI-1
        {
            results.push_back(recallI-1);
            recallJ -= weightVec.at(recallI-1);
        }
        --recallI;
    }
    return results;
}

// ��һά����ȥrecord����������ȥ��һ�е����Ѱ�����ݣ���˿��Դ��ҵ���ȥ����һά����
size_t dp_knapsackquestion_1d(size_t numOfgoods, size_t totalWeight, vector<size_t> weightVec, vector<size_t> valueVec){
    if (numOfgoods == 0 || totalWeight == 0)
    {
        return 0;
    }
    vector<size_t> record(totalWeight + 1, 0);
    for (size_t i = 1; i <= numOfgoods; ++i)
    {
        for (size_t j = totalWeight; j > 0; --j)
        {
            if (j >= weightVec.at(i-1) && record.at(j) < record.at(j-weightVec.at(i-1)) + valueVec.at(i-1) )
            {
                record.at(j) = record.at(j-weightVec.at(i-1)) + valueVec.at(i-1);
            }
        }
    }

    return record.at(totalWeight);
}

int main(int argc, char ** argv){
    streambuf* backup;
    ifstream fin;
    fin.open("data.in");
    backup = cin.rdbuf();
    cin.rdbuf(fin.rdbuf());

    string inputline;
    istringstream iss;
    size_t numOfgoods(0), totalWeight(0);
    while (true)
    {
        getline(cin, inputline);
        iss = istringstream(inputline);
        iss >> numOfgoods >> totalWeight;
        size_t temp;

        vector<size_t> weightVec;
        weightVec.reserve(numOfgoods);
        getline(cin, inputline);
        iss = istringstream(inputline);
        while (iss >> temp)
        {
            weightVec.push_back(temp);
        }

        vector<size_t> valueVec;
        valueVec.reserve(numOfgoods);
        getline(cin, inputline);
        iss = istringstream(inputline);
        while (iss >> temp)
        {
            valueVec.push_back(temp);
        }

        vector<size_t> goods = dp_knapsackquestion(numOfgoods, totalWeight, weightVec, valueVec);
        cout << dp_knapsackquestion_1d(numOfgoods, totalWeight, weightVec, valueVec) << endl;

    }

}

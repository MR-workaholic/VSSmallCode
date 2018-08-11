/*
��ȫ��������
��ȫ������������Ʒ����Ҫ�������˿��Կ��ɣ�
r(i, j)��ʾ�ڳ�����Ϊj��ʱ�򣬿����Ƿ���Ҫ��Ʒi(��r�����У���Ʒ��������1��ʼ����w��v�����У�������0��ʼ)
r(i,j) = max(r(i-1, j), r(i, j-w(i-1)) + v(i-1))
����˵�� ����Ҫi��r(i-1,j)���롾Ҫi��r(i, j-w(i-1))����ѡ��һ��i��������ѡ�����ֵ
3 7
3 4 2
4 5 3
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// �ձ�Ķ�ά����Ľⷨ
vector<size_t> dp_completeknapsackquestion_2d(size_t kindOfgoods, size_t totalWeight, vector<size_t> weightVec, vector<size_t> valueVec){
    vector<size_t> results;
    if (kindOfgoods == 0 || totalWeight == 0)
    {
        //return 0;
        return results;
    }
    // ����record���飬��Ҫ����һ��һ��
    vector<vector<size_t>> record;
    record.reserve(kindOfgoods + 1);
    for (size_t i = 0; i < kindOfgoods + 1; i++)
    {
        vector<size_t> temp(totalWeight+1, 0);
        record.push_back(temp);
    }

    // �ڳ��������ڵ�����Ʒi��record��1��ʼ��������,weightVec��valueVec��0��ʼ��������ʱ��ѡ��r(i-1, j)��r(i-1, j-w(i-1)) + v(i-1)֮������ֵ������֮�����ڳ�����j֮��ѡ��Ҫ��Ҫi
    for (size_t i = 1; i <= kindOfgoods; i++)
    {
        for (size_t j = 1; j <= totalWeight; j++)
        {
            if (j < weightVec.at(i-1))
            {
                record.at(i).at(j) = record.at(i-1).at(j);
            }else
            {
                record.at(i).at(j) = max<size_t>({ record.at(i-1).at(j), record.at(i).at(j-weightVec.at(i-1)) + valueVec.at(i-1) });
            }
        }
    }

     //���ݳ�·������r(i, j) == r(i-1, j)��ʱ���ǲ���Ҫi�ģ���������Ҫi��
    size_t recallI(kindOfgoods), recallJ(totalWeight);
    while (recallI != 0 && recallJ != 0)
    {
        if (record.at(recallI).at(recallJ) != record.at(recallI-1).at(recallJ)) // ���������Ʒ��������recallI-1
        {
            results.push_back(recallI-1);
            recallJ -= weightVec.at(recallI-1);
        }else{
            --recallI;
        }
    }
    return results;
    //return record.at(kindOfgoods).at(totalWeight);
}

// ��һά����ȥrecord����������ȥ��һ�е�ͬһ��J���ߵ�ǰ�е�ǰһ��J����˿��Դ�����ȥ����һά����
size_t dp_completeknapsackquestion_1d(size_t kindOfgoods, size_t totalWeight, vector<size_t> weightVec, vector<size_t> valueVec){
    if (kindOfgoods == 0 || totalWeight == 0)
    {
        return 0;
    }

    // ����record���飬��Ҫ����һ��
    vector<size_t> record(totalWeight + 1, 0);
    record.reserve(totalWeight+1);

    for (size_t i = 1; i <= kindOfgoods; ++i)
    {
        for (size_t j = 1; j <= totalWeight; ++j)
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
    size_t kindOfgoods(0), totalWeight(0);
    while (true)
    {
        getline(cin, inputline);
        iss = istringstream(inputline);
        iss >> kindOfgoods >> totalWeight;
        size_t temp;

        // ����ÿ����Ʒ������
        vector<size_t> weightVec;
        weightVec.reserve(kindOfgoods);
        getline(cin, inputline);
        iss = istringstream(inputline);
        while (iss >> temp)
        {
            weightVec.push_back(temp);
        }

        // ����ÿ����Ʒ�ļ�ֵ
        vector<size_t> valueVec;
        valueVec.reserve(kindOfgoods);
        getline(cin, inputline);
        iss = istringstream(inputline);
        while (iss >> temp)
        {
            valueVec.push_back(temp);
        }

        vector<size_t> goods = dp_completeknapsackquestion_2d(kindOfgoods, totalWeight, weightVec, valueVec);

        cout << dp_completeknapsackquestion_1d(kindOfgoods, totalWeight, weightVec, valueVec) << endl;

    }

}
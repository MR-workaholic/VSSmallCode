/*
���ر������⣬��Ʒ�����������޵ģ���countVec������
r(i, j)��ʾ�ڳ�����Ϊj��ʱ�򣬿����Ƿ���Ҫ��Ʒi(��r�����У���Ʒ��������1��ʼ����w��v��c�����У�������0��ʼ)
r(i,j) = max{r(i-1, j-k*w(i-1)) + k*v(i-1)} k��0��c(i-1)
����˵�� ����Ҫi��r(i-1,x)+y]��ѡ�����ֵ,xָ���Ƿ�����x�����������Ǽ�����Ҫi֮��ļ�ֵ

2 8
2 4 ����
100 100 ��ֵ
4 2 ����
5 10
5 2 6 5 3
6 3 5 4 6
1 1 1 1 3
 */
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<size_t> dp_multipleknapsackquestion_2d(size_t kindOfgoods, size_t totalWeight, vector<size_t> weightVec, vector<size_t> valueVec, vector<size_t> countVec){
    vector<size_t> results;
    if (kindOfgoods == 0 || totalWeight == 0)
    {
        return results;
    }
    // ����record���飬��Ҫ����һ��һ��
    vector<vector<size_t>> record;
    record.reserve(kindOfgoods+1);
    for (size_t i = 0; i <= kindOfgoods; ++i)
    {
        vector<size_t> temp(totalWeight+1, 0);
        record.push_back(temp);
    }

    // �ڳ��������ڵ�����Ʒi��record��1��ʼ��������,weightVec��valueVec��0��ʼ��������ʱ��ѡ��r(i-1, j)��r(i-1, j-k*w(i-1)) + k*v(i-1)֮������ֵ������֮�����ڳ�����j֮��ѡ��Ҫ��Ҫk��i
    for (size_t i = 1; i <= kindOfgoods; ++i)
    {
        for (size_t j = 1; j <= totalWeight; ++j)
        {
            for (size_t k = 0; k <= countVec.at(i-1); ++k)
            {
                if (j >= k*weightVec.at(i-1))
                {
                    record.at(i).at(j) = max<size_t>({record.at(i).at(j), record.at(i-1).at(j-k*weightVec.at(i-1)) + k*valueVec.at(i-1)});
                }
            }
        }
    }

    size_t recallI(kindOfgoods), recallJ(totalWeight);
    while (recallI != 0 && recallJ != 0)
    {
        if (record.at(recallI).at(recallJ) != record.at(recallI-1).at(recallJ))
        {
            results.push_back(recallI-1);
            recallJ -= weightVec.at(recallI-1);
        }else
        {
            --recallI;
        }
    }

    return results;

}

size_t dp_multipleknapsackquestion_1d(size_t kindOfgoods, size_t totalWeight, vector<size_t> weightVec, vector<size_t> valueVec, vector<size_t> countVec){
    if (kindOfgoods == 0 || totalWeight == 0)
    {
        return 0;
    }
    // ����record���飬��Ҫ����һ��
    vector<size_t> record(totalWeight+1, 0);
    record.reserve(totalWeight+1);

    // �ڳ��������ڵ�����Ʒi��record��1��ʼ��������,weightVec��valueVec��0��ʼ��������ʱ��ѡ��r(i-1, j)��r(i-1, j-k*w(i-1)) + k*v(i-1)֮������ֵ������֮�����ڳ�����j֮��ѡ��Ҫ��Ҫk��i
    for (size_t i = 1; i <= kindOfgoods; ++i)
    {
        for (size_t j = totalWeight; j >0 ; --j)
        {
            for (size_t k = 1; k <= countVec.at(i-1); ++k)
            {
                if (j >= k*weightVec.at(i-1) && record.at(j) < record.at(j-k*weightVec.at(i-1)) + k*valueVec.at(i-1))
                {
                    record.at(j) = record.at(j-k*weightVec.at(i-1)) + k*valueVec.at(i-1);
                }
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

         // ����ÿ����Ʒ����������
        vector<size_t> countVec;
        countVec.reserve(kindOfgoods);
        getline(cin, inputline);
        iss = istringstream(inputline);
        while (iss >> temp)
        {
            countVec.push_back(temp);
        }
        //vector<size_t> goods = dp_completeknapsackquestion_2d(kindOfgoods, totalWeight, weightVec, valueVec);

        dp_multipleknapsackquestion_2d(kindOfgoods, totalWeight, weightVec, valueVec, countVec);
        cout << dp_multipleknapsackquestion_1d(kindOfgoods, totalWeight, weightVec, valueVec, countVec) << endl;

    }

}
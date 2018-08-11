/*
01背包问题
二维数组与一位数组都有的解法
r(i, j)表示在承重量为j的时候，考虑是否需要商品i(在r数组中，商品的索引从1开始，在w与v数组中，索引从0开始)
r(i,j) = max(r(i-1, j), r(i-1, j-w(i-1)) + v(i-1))
就是说从 【不要i的r(i-1,j)】与【要不要i的r(i-1, j-w(i-1))中再选多一个i】两者中选择最大值
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
    // 建立record数组，需要增加一行一列
    vector<vector<size_t>> record;
    record.reserve(numOfgoods + 1);
    for (size_t i = 0; i < numOfgoods + 1; i++)
    {
        vector<size_t> temp(totalWeight+1, 0);
        record.push_back(temp);
    }

    // 在承重量大于等于商品i（从1开始计算索引）的重量时，选择r(i-1, j)与r(i-1, j-w(i-1)) + v(i-1)之间的最大值，言下之意是在承重量j之下选择要不要i
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

    //回溯出路径，当r(i, j) == r(i-1, j)的时候，是不需要i的，否则是需要i的
    size_t recallI(numOfgoods), recallJ(totalWeight);
    while (recallI != 0 && recallJ != 0)
    {
        if (record.at(recallI).at(recallJ) != record.at(recallI-1).at(recallJ)) // 包括这个商品，索引是recallI-1
        {
            results.push_back(recallI-1);
            recallJ -= weightVec.at(recallI-1);
        }
        --recallI;
    }
    return results;
}

// 用一维数组去record，由于总是去上一行的左边寻找内容，因此可以从右到左去遍历一维数组
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

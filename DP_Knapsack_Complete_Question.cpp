/*
完全背包问题
完全背包问题是商品可以要多个，因此可以看成：
r(i, j)表示在承重量为j的时候，考虑是否需要商品i(在r数组中，商品的索引从1开始，在w与v数组中，索引从0开始)
r(i,j) = max(r(i-1, j), r(i, j-w(i-1)) + v(i-1))
就是说从 【不要i的r(i-1,j)】与【要i的r(i, j-w(i-1))中再选多一个i】两者中选择最大值
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

// 普遍的二维数组的解法
vector<size_t> dp_completeknapsackquestion_2d(size_t kindOfgoods, size_t totalWeight, vector<size_t> weightVec, vector<size_t> valueVec){
    vector<size_t> results;
    if (kindOfgoods == 0 || totalWeight == 0)
    {
        //return 0;
        return results;
    }
    // 建立record数组，需要增加一行一列
    vector<vector<size_t>> record;
    record.reserve(kindOfgoods + 1);
    for (size_t i = 0; i < kindOfgoods + 1; i++)
    {
        vector<size_t> temp(totalWeight+1, 0);
        record.push_back(temp);
    }

    // 在承重量大于等于商品i（record从1开始计算索引,weightVec与valueVec从0开始）的重量时，选择r(i-1, j)与r(i-1, j-w(i-1)) + v(i-1)之间的最大值，言下之意是在承重量j之下选择要不要i
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

     //回溯出路径，当r(i, j) == r(i-1, j)的时候，是不需要i的，否则是需要i的
    size_t recallI(kindOfgoods), recallJ(totalWeight);
    while (recallI != 0 && recallJ != 0)
    {
        if (record.at(recallI).at(recallJ) != record.at(recallI-1).at(recallJ)) // 包括这个商品，索引是recallI-1
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

// 用一维数组去record，由于总是去上一行的同一个J或者当前行的前一个J，因此可以从左到右去遍历一维数组
size_t dp_completeknapsackquestion_1d(size_t kindOfgoods, size_t totalWeight, vector<size_t> weightVec, vector<size_t> valueVec){
    if (kindOfgoods == 0 || totalWeight == 0)
    {
        return 0;
    }

    // 建立record数组，需要增加一行
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

        // 接收每样商品的重量
        vector<size_t> weightVec;
        weightVec.reserve(kindOfgoods);
        getline(cin, inputline);
        iss = istringstream(inputline);
        while (iss >> temp)
        {
            weightVec.push_back(temp);
        }

        // 接收每样商品的价值
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
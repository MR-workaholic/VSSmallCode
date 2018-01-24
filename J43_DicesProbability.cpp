#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>


using namespace std;


void BackTracking(int point, vector<int>& record, vector<int>& one, int number){
    one.push_back(point);
    if (one.size() == number)
    {
        record.at(accumulate(one.begin(), one.end(), 0) - number)++;
    }else
    {
        for (size_t i = 1; i <= 6; i++)
        {
            BackTracking(i, record, one, number);
        }
    }
    one.pop_back();
}

vector<float> PrintProbability(int number){
    if (number < 1)
    {
        return {};
    }
    vector<int> record(6*number-number+1, 0);
    record.reserve(6*number-number+1);

    vector<int> one;
    one.reserve(number);

    for (size_t i = 1; i <= 6; i++)
    {
        BackTracking(i, record, one, number);
    }

    float sum = pow(6.0, number);
    vector<float> results;
    for(auto var : record)
    {
        results.push_back(var / sum);
    }

    return results;

}

vector<float> PrintProbability_2(int number){
    if (number == 0)
    {
        return {};
    }
    vector<vector<int>> record;
    record.reserve(2);

    vector<int> temp(6 * number + 1, 0);
    record.push_back(temp);
    record.push_back(temp);
    for (size_t i = 1; i <= 6; i++)  // 就如动态规划的初始化第一粒骰子
    {
        record.at(0).at(i) = 1;
    }

    size_t flag = 0;
    for (size_t i = 2; i <= number; i++) // i是第i粒骰子加进来
    {
        for (size_t j = i; j < 6*i; j++)  // 清空下一个记录数组 将可能用到的值都清空
        {
            record.at(1 - flag).at(j) = 0;
        }

        for (size_t j = i; j <= 6*i; j++) // 可能的值的计算
        {
            for(size_t k = 1; k < j && k <= 6; k++)  /* k代表本轮扔出的点数， k从1到6，当然k要小于目标值 */
            {
                record.at(1 - flag).at(j) += record.at(flag).at(j-k);
            }
        }
        flag = 1 - flag;  // 换数组
    }

    float sum = pow(6.0, number);
    vector<float> results;
    for (size_t i = number; i <= 6*number; i++)
    {
        results.push_back(record.at(flag).at(i) / sum);
    }
    return results;

}

int main(int argc, char ** argv){
    while (true)
    {
        int n;
        cin >> n;
        vector<float> results = PrintProbability_2(n);
        for(auto var : results)
        {
            cout << var << " "; /*for 3： 0.00462963 0.0138889 0.0277778 0.0462963 0.0694444 0.0972222 0.115741 0.125 0.125 0.115741 0.0972222 0.0694444 0.0462963 0.0277778 0.0138889 0.00462963 */
        }
        cout << endl;
    }
}
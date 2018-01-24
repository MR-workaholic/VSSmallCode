/*
1 2 4 7 11 13 15
15
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <numeric>

using namespace std;

void BackTracking(vector<int>& record, int index, vector<int>& array, int& sum, vector<int>& result){
    record.push_back(array.at(index));
    if (record.size() == 2)
    {
        if (accumulate(record.begin(), record.end(), 0) == sum)
        {
            if (result.size() == 0)
            {
                result.assign(record.begin(), record.end());
                result.push_back(record.at(0) * record.at(1));
            }else if (result.at(2) > record.at(0) * record.at(1))  // 其实不会判断进去这里，因为最左边的数字搭配某个数字必然是乘积最小的那个
            {
                result.clear();
                result.assign(record.begin(), record.end());
                result.push_back(record.at(0) * record.at(1));
            }
        }
    }else
    {
        for (size_t i = index+1; i < array.size(); i++)
        {
            BackTracking(record, i, array, sum, result);  // 可以在这里判断result的长度并退出循环
        }
    }
    record.pop_back();
}

vector<int> FindNumbersWithSum(vector<int> array, int sum) {
    size_t len = array.size();
    if (len < 2 || (len == 2 && accumulate(array.begin(), array.end(), 0) != sum))
    {
        return {};
    }else if (len == 2)
    {
        return array;
    }

    vector<int> record;
    vector<int> result;
    record.reserve(2);
    result.reserve(3);
    for (size_t i = 0; i < len; i++)
    {
        BackTracking(record, i, array, sum, result);
    }
    if (result.size() == 0)
    {
        return {};
    }
    return vector<int>(result.begin(), result.end()-1);
}

vector<int> FindNumbersWithSum_2(vector<int> array, int sum){
    size_t len = array.size();
    if (len < 2 || (len == 2 && accumulate(array.begin(), array.end(), 0) != sum))
    {
        return {};
    }else if (len == 2)
    {
        return array;
    }
    auto left = array.begin(), right = array.end()-1;
    vector<int> result;
    result.reserve(2);
    while (left < right)
    {
        int tempSum = *left + *right;
        if (tempSum == sum)
        {
            result.push_back(*left);
            result.push_back(*right);
            break;
        }else if (tempSum > sum)
        {
            right--;
        }else
        {
            left++;
        }
    }
    if (result.size() == 0)
    {
        return {};
    }
    return result;

}

int main(int argc, char **argv){
    streambuf* backup;
    ifstream fin;
    fin.open("data.in");
    backup = cin.rdbuf();
    cin.rdbuf(fin.rdbuf());

    string inputline;
    istringstream iss;
    int temp;
    while (true)
    {
        getline(cin, inputline);
        iss = istringstream(inputline);
        vector<int> data;
        while (iss >> temp)
        {
            data.push_back(temp);
        }
        getline(cin, inputline);
        iss = istringstream(inputline);
        iss >> temp;
        vector<int> result =  FindNumbersWithSum(data, temp);
        for(auto var : result)
        {
            cout << var << " ";
        }
        cout << endl;
    }
}
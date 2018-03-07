/*
给定一排n个硬币，其面值为正整数c1，c2，c3……cn，这些整数
不一定两两不同， 请问如何选择硬币，使得在其原始位置互不相邻的条件下
所选择的硬币的总金额最大
5 1 2 10 6 2
5 1 2 10 6
 */
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;
 
size_t dp_maximizecurrency(const vector<size_t>& money){
    size_t len = money.size();
    if (len == 0)
    {
        return 0;
    }else if (len == 1)
    {
        return money.at(0);
    }
    vector<size_t> record = {0, money.at(0)};
    record.reserve(len + 1);
    for (size_t i = 1; i < len; i++)
    {
        record.push_back(max<size_t>({record.at(i), record.at(i-1) + money.at(i)}));
    }
    return record.at(len);
}

vector<size_t> dp_maximizecurrency_recall(const vector<size_t>& money){
    size_t len = money.size();
    vector<size_t> result;
    if (len == 0)
    {
        return result;
    }else if (len == 1)
    {
        return {money.at(0)};
    }
    vector<size_t> record = {0, money.at(0)};
    record.reserve(len + 1);
    vector<bool> recall = {true};
    recall.reserve(len);
    size_t withcur(0), notwithcur(0), maxone(0);
    for (size_t i = 1; i < len; i++)
    {
        withcur = record.at(i-1) + money.at(i);
        notwithcur = record.at(i);
        maxone = max<size_t>({withcur, notwithcur});
        record.push_back(maxone);
        if (maxone == withcur)
        {
            recall.push_back(true);
        }else
        {
            recall.push_back(false);
        }
    }
    for (int i = len - 1; i >= 0;)
    {
        if (recall.at(i))
        {
            result.push_back(money.at(i));
            i -= 2;
        }else
        {
            i--;
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
    size_t val;
    while (true)
    {
        getline(cin, inputline);
        iss = istringstream(inputline);
        vector<size_t> money;
        while (iss >> val)
        {
            money.push_back(val);
        }
        cout << dp_maximizecurrency(money) << endl;
        vector<size_t> result = dp_maximizecurrency_recall(money);
        for(auto var : result)
        {
            cout << var << " ";
        }
        cout << endl;
    }

}
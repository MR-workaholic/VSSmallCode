/*
找零问题，找出数量最少的能凑成N元的硬币，有多少种情况都打印出来
6 1 3 4
5 1 2 3 4
假如只需要找出一种最优解的话，可以用一个recall数组，记录最后添加了什么硬币达到相应的价钱即可，如dp_changemaking_oneans
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>

using namespace std;

vector<vector<size_t>> dp_changemaking(size_t target, vector<size_t> money){
    vector<vector<size_t>> results;
    if (target == 0 || money.size() == 0)
    {
        return results;
    }
    vector<set<multiset<size_t>>> temp; //由于要找出所有解，因此这里比较复杂，只找出数量的话用vector<size_t>即可，要找出一种最优解的话，额外加一个recall数组即可
    temp.reserve(target + 1);
    set<multiset<size_t>> nomoney;
    temp.push_back(nomoney);

    for (size_t i = 1; i <= target; i++)
    {
        vector<size_t> addMoney;
        for(auto var : money)  //这函数的作用是看看可以增加哪些面值的货币，并且是令货币的数量最小。假如不是货币的数量最小的话，可以不用这个循环但是要保证var<=i
        {
            if (var <= i && var == money.at(0))
            {
                addMoney.push_back(var);
            }else if (var <= i)
            {
                if (temp.at(i - var).empty() ||
                    (*(temp.at(i - var).begin())).size() <  (*(temp.at(i - addMoney.at(0)).begin())).size()
                    )  //假如temp里面的set为空，则添加这个硬币进去；假如这个set非空而且第一个元素的multiset的size比较少，则清空addMoney，并加入元素
                {
                    addMoney.clear();
                    addMoney.push_back(var);
                }else if (!temp.at(i - var).empty() &&
                    (*(temp.at(i - var).begin())).size() == (*(temp.at(i - addMoney.at(0)).begin())).size()
                    ) //假如set非空而且和第一个元素的multiset的size一样，则加入元素
                {
                    addMoney.push_back(var);
                }
            }else
            {
                break;
            }
        }
        temp.push_back(nomoney);
        // size_t index = temp.size() - 1;
        for(auto var : addMoney)
        {
            if (temp.at(i - var).empty())
            {
                multiset<size_t> t;
                t.insert(var);
                temp.at(i).insert(t);
            }else{
                for(auto var1 : temp.at(i - var))
                {
                    var1.insert(var);
                    temp.at(i).insert(var1);
                }
            }
        }
    }

    for(auto var : temp.at(target))
    {
        vector<size_t> t(var.begin(), var.end());
        results.push_back(t);
    }
    return results;

}

vector<size_t> dp_changemaking_oneans(size_t target, vector<size_t> money){
    vector<size_t> result;
    if (target == 0 || money.size() == 0)
    {
        return result;
    }
    vector<size_t> record;
    record.reserve(target+1);
    record.push_back(0);

    vector<size_t> recall;
    recall.reserve(target+1);
    recall.push_back(0);

    for (size_t i = 1; i <= target; i++)
    {
        record.push_back(0);
        recall.push_back(0);
        for(auto var : money)
        {
            if (var > i)
            {
                continue;
            }
            if ((record.at(i) == 0) || (record.at(i) > record.at(i-var) + 1))
            {
                record.at(i) = record.at(i-var) + 1;
                recall.at(i) = var;
            }
        }
    }

    size_t changeTarget(target);
    while (changeTarget)
    {
        result.push_back(recall.at(changeTarget));
        changeTarget -= recall.at(changeTarget);
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
    size_t val(0), target(0);
    while (true)
    {
        getline(cin, inputline);
        iss = istringstream(inputline);
        iss >> target;
        vector<size_t> money;
        while (iss >> val)
        {
            money.push_back(val);
        }

        vector<vector<size_t>> result = dp_changemaking(target, money);
        for(auto var : result)
        {
            for(auto var1 : var)
            {
                cout << var1 << " ";
            }
            cout << endl;
        }
        vector<size_t> res = dp_changemaking_oneans(target, money);
    }

}
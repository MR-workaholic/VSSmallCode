#include <iostream>
#include <vector>
#include <utility>
#include <list>

using namespace std;

int LastRemaining_Solution(int n, int m)
{
    if (n == 0 || m == 0)
    {
        return -1;
    }

    vector<pair<int, bool>> record;
    record.reserve(n);
    for (size_t i = 0; i < n; i++)
    {
        record.push_back({i, true});
    }
    size_t cur(0);
    for (size_t i = 0; i < n-1; i++)
    {
        int step = m;
        while (true)
        {
            while(!record.at(cur).second){
                cur++;
                if (cur == n)
                {
                    cur = 0;
                }
            }
            step--;
            if (step == 0)
            {
                break;
            }
            cur++;
            if (cur == n)
            {
                cur = 0;
            }
        }
        record.at(cur).second = false;
    }

    int result;
    for(auto var : record)
    {
        if (var.second)
        {
            result = var.first;
            break;
        }
    }
    return result;

}

int LastRemaining_Solution_2(int n, int m){
    if (n == 0 || m == 0)
    {
        return -1;
    }
    int result(0);
    for (size_t i = 2; i <= n; i++)
    {
        result = result + m;
        if (result >= i)
        {
            result -= i;
        }
    }
    return result;
}

int LastRemaining_Solution_3(int n, int m){
    if (n == 0 || m == 0)
    {
        return -1;
    }
    list<int> record;
    for (size_t i = 0; i < n; i++)
    {
        record.push_back(i);
    }
    list<int>::iterator it = record.begin();
    while (record.size() != 1)
    {
        int step = m;
        while (--step)
        {
            it++;
            if (it == record.end())
            {
                it = record.begin();
            }
        }
        it = record.erase(it);
        if (it == record.end())
        {
            it = record.begin();
        }
    }
    return record.front();
}

int main(int argc, char ** argv){
    while (true)
    { 
        int n, m;
        cin >> n >> m;
        cout << LastRemaining_Solution_3(n, m);
    }
}

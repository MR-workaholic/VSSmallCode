/*
5 2 3 4 1 6 7 0 8
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

template<typename T>
class Solution {
public:
    void Insert(int num)
    {
        if (((minHead.size() + maxHead.size()) & 0x1) == 0)
        {
            if (maxHead.size() > 0 && num < maxHead.at(0))
            {
                maxHead.push_back(num);
                push_heap(maxHead.begin(), maxHead.end(), less<T>());
                num = maxHead.at(0);
                pop_heap(maxHead.begin(), maxHead.end(), less<T>());
                maxHead.pop_back();
            }
            minHead.push_back(num);
            push_heap(minHead.begin(), minHead.end(), greater<T>());
        }else
        {
            if (minHead.size() > 0 && num > minHead.at(0))
            {
                minHead.push_back(num);
                push_heap(minHead.begin(), minHead.end(), greater<T>());
                num = minHead.at(0);
                pop_heap(minHead.begin(), minHead.end(), greater<T>());
                minHead.pop_back();

            }
            maxHead.push_back(num);
            push_heap(maxHead.begin(), maxHead.end(), less<T>());
        }
    }

    double GetMedian()
    {
        if (((minHead.size() + maxHead.size()) & 0x1) == 0)
        {
            return (minHead.at(0) + maxHead.at(0)) / 2.0;
        }else
        {
            return minHead.at(0);
        }
    }

private:
    vector<T> minHead;
    vector<T> maxHead;

};

int main(int argc, char ** argv){
    streambuf* backup;
    fstream fin;
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
        Solution<int> m;
        while (iss >> temp)
        {
            m.Insert(temp);
            cout << m.GetMedian() << endl;
        }

    }

}

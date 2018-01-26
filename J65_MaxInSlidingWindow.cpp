/*
2 3 4 2 6 2 5 1
3
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

vector<int> maxInWindows(const vector<int>& num, unsigned int size)
{
    vector<int> result;
    if (num.size() < size || size == 0)
    {
        return result;
    }
    if (size == 1)
    {
        return num;
    }
    queue<int> curQue, maxQue;
    for(auto var : num)
    {
        if (curQue.size() < size)
        {
            curQue.push(var);
            if (maxQue.size() > 0 && maxQue.back() > var)
            {
                maxQue.push(maxQue.back());
            }else
            {
                maxQue.push(var);
            }
        }else{

            int popNum = curQue.front();
            curQue.pop();
            curQue.push(var);
            if (popNum != maxQue.back())
            {
                maxQue.pop();
            }else
            {
                while (!maxQue.empty())
                {
                    maxQue.pop();
                }

                for (size_t i = 0; i < size - 1; i++)
                {
                    int temp = curQue.front();
                    if (maxQue.size() > 0 && maxQue.back() > temp)
                    {
                        maxQue.push(maxQue.back());
                    }else
                    {
                        maxQue.push(temp);
                    }
                    curQue.pop();
                    curQue.push(temp);
                }
                curQue.push(curQue.front());
                curQue.pop();
            }
            if (maxQue.size() > 0 && maxQue.back() > var)
            {
                maxQue.push(maxQue.back());
            }else
            {
                maxQue.push(var);
            }
        }

        if (curQue.size() == size)
        {
            result.push_back(maxQue.back());
        }
    }
    return result;
}

/* 法二  见书本介绍*/

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
        vector<int> nums;
        while (iss >> temp)
        {
            nums.push_back(temp);
        }

        getline(cin, inputline);
        iss = istringstream(inputline);
        iss >> temp;
        vector<int> result = maxInWindows(nums, temp);
        for(auto var : result)
        {
            cout << var << " ";
        }
        cout << endl;
    }

}

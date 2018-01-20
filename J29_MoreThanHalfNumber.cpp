/*
1 2 3 2 4 2 5 2 3
3 8 3 5 3 3 2 1 1 2 3 8 3 3 3
 */
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

void swap(vector<int> &input, int i, int j){
    if (i == j)
    {
        return;
    }
    int temp = input.at(j);
    input.at(j) = input.at(i);
    input.at(i) = temp;
}

int MoreThanHalfNum_Solution(vector<int> numbers) {

    int len = numbers.size();
    if (len == 1)
    {
        return numbers.at(0);
    }else if (len == 2)
    {
        if (numbers.at(0) == numbers.at(1))
        {
            return numbers.at(0);
        }else
        {
            return 0;
        }
    }

    int left = 0, right = len - 1, mid;
    int targetNum;

    while (true)
    {
        mid = left + ((right - left) >> 1);
        int b1 = numbers.at(left) > numbers.at(right) ? left : right;
        int b2 = numbers.at(left) > numbers.at(mid) ? left : right;
        int m;
        if (b1 == b2)
        {
            m = numbers.at(right) > numbers.at(mid) ? right : mid;
        }else
        {
            m = numbers.at(b1) < numbers.at(b2) ? b1 : b2;
        }
        swap(numbers, left, m);

        int i = left, j = right + 1;
        while (i < j)
        {
            while (i < j && numbers.at(left) < numbers.at(--j));
            while (i < j && numbers.at(left) > numbers.at(++i));
            if (i < j && numbers.at(i) != numbers.at(j))
            {
                swap(numbers, i, j);
            }
        }
        swap(numbers, left, j);
        if (j == len >> 1)
        {
            targetNum = numbers.at(j);
            break;
        }else if (j > len >> 1)
        {
            right = j - 1;
        }else
        {
            left = j + 1;
        }
    }

    size_t time = 0;
    for(auto var : numbers)
    {
        if (var == targetNum)
        {
            time++;
        }
    }
    if (time >= (len >> 1) + 1)
    {
        return targetNum;
    }
    return 0;

}

int MoreThanHalfNum_Solution2(vector<int> numbers){
    int len = numbers.size();
    if (len == 1)
    {
        return numbers.at(0);
    }else if (len == 2)
    {
        if (numbers.at(0) == numbers.at(1))
        {
            return numbers.at(0);
        }else
        {
            return 0;
        }
    }
    vector<int> record(len, 0);
    int target;
    while(true)
    {
        for (int i=-1, j=len; i < j;)
        {
            while (i<j && record.at(++i) == 1);
            while (i<j && (record.at(--j) == 1 || numbers.at(i) == numbers.at(j)));

            if (i < j)
            {
                record.at(i) = 1;
                record.at(j) = 1;
            }
        }
        bool first = true, end = true, notarget = true;
        int temp;
        for (size_t i = 0; i < len; i++)
        {
            if (record.at(i) == 0)
            {
                notarget = false;
                if (first)
                {
                    first = false;
                    temp = numbers.at(i);
                    target = temp;
                }else{
                    if (numbers.at(i) != temp){
                        end = false;
                        break;
                    }
                }
            }
        }
        if (notarget)
        {
            return 0;
        }
        if (end)
        {
            break;
        }
    }

    size_t time = 0;
    for(auto var : numbers)
    {
        if (var == target)
        {
            time++;
        }
    }
    if (time >= (len >> 1) + 1)
    {
        return target;
    }
    return 0;


}

int main(int argc, char ** argv){
    streambuf* backup;
    fstream fin;
    fin.open("data.in");
    backup = cin.rdbuf();
    cin.rdbuf(fin.rdbuf());

    string inputline;
    istringstream iss;

    while (true)
    {
        getline(cin, inputline);
        iss = istringstream(inputline);
        int temp;
        vector<int> nums;
        while (iss >> temp)
        {
            nums.push_back(temp);
        }
        cout << MoreThanHalfNum_Solution2(nums);
    }
}
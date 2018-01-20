/*
4 5 1 6 2 7 2 8
2
4 5 1 6 2 7 3 8
1
4 5 1 6 2 7 3 8
4
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

vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
    int len = input.size();
    if (len < k || k == 0)
    {
        return {};
    }else if (len == k)
    {
        return input;
    }

    int start = 0, end = len - 1, mid;
    while (true)
    {
        mid = start + ((end - start) >> 1);
        size_t b1 = input.at(start) > input.at(end) ? start : end;
        size_t b2 = input.at(start) > input.at(mid) ? start : mid;
        size_t m1;
        if (b1 == b2)
        {
            m1 = input.at(end) > input.at(mid) ? end : mid;
        }else
        {
            m1 = input.at(b1) < input.at(b2) ? b1 : b2;
        }
        swap(input, start, m1);

        int i = start, j = end + 1;
        while (i < j)
        {
            while(i < j && input.at(--j) > input.at(start));
            while(i < j && input.at(++i) < input.at(start));
            if (i < j)
            {
                swap(input, i, j);
            }
        }
        swap(input, start, j);
        if (j == k-1)
        {
            return vector<int>(input.begin(), input.begin()+k);
        }else if (j < k - 1)
        {
            start = j + 1;
        }else{
            end = j - 1;
        }
    }


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
        getline(cin, inputline);
        iss = istringstream(inputline);
        iss >> temp;
        vector<int> result = GetLeastNumbers_Solution(nums, temp);
        for(auto var : result)
        {
            cout << var << " ";
        }
        cout << endl;
    }
}
/*
1 2 3 3 3 3 4 5
3
3 3 3 3 4 5
3
1 2 3 3 3 3
3
1 3 3 3 3 3 4 5
2
 */
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

int GetNumberOfK(vector<int> data, int k) {
    if (data.size() == 0)
    {
        return 0;
    }
    vector<int>::iterator ileft = lower_bound(data.begin(), data.end(), k);
    if (ileft == data.end())
    {
        return 0;
    }
    vector<int>::iterator iright = upper_bound(data.begin(), data.end(), k);
    return iright - ileft;
}

size_t my_lower_bound(vector<int> data, size_t len, int k){ // 求左界用左闭右闭
    int left = 0, right = len - 1;
    while (left < right)
    {
        int mid = left + ((right - left) >> 1);
        if (data.at(mid) > k)
        {
            right = mid - 1;
        }else if(data.at(mid) < k)
        {
            left = mid +1;
        }else
        {
            right = mid;
        }
    }
    return left;
}

size_t my_upper_bound(vector<int> data, size_t len, int k){ //求右界用左闭右开
    int left = 0, right = len;
    while (left < right)
    {
        int mid = left + ((right - left) >> 1);
        if (data.at(mid) > k)
        {
            right = mid;
        }else if(data.at(mid) <= k)
        {
            left = mid + 1;
        }
    }

    return left;
}

int GetNumberOfK_2(vector<int> data, int k){
    if (data.size() == 0)
    {
        return 0;
    }
    size_t leftIndex = my_lower_bound(data, data.size(), k);
    if (data.at(leftIndex) != k)
    {
        return 0;
    }else if (leftIndex == data.size() - 1)
    {
        return 1;
    }
    size_t rightIndex = my_upper_bound(data, data.size(), k);
    return rightIndex - leftIndex;
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

        cout << GetNumberOfK(nums, temp) << endl;
    }
}
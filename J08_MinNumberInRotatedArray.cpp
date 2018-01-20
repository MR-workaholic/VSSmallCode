/*
3 4 5 1 2
1 2 3 4 5
1 1 1 0 1
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int minNumberInRotateArray(vector<int> rotateArray) {
    if (rotateArray.size() == 0)
    {
        return 0;
    }else if (rotateArray.size() == 1)
    {
        return rotateArray.at(0);
    }
    int left = 0, right = rotateArray.size() - 1, minIndex = left;
    // 一直维持着left索引的数比right大
    while (rotateArray.at(left) >= rotateArray.at(right))
    {
        int mid = left + ((right - left) >> 1);
        if (mid == left)
        {
            minIndex = right;
            break;
        }
        // 对于1 1 1 0 1  and 1 0 1 1 1的情况，只能顺序找了
        if (rotateArray.at(left) == rotateArray.at(mid) && rotateArray.at(left) == rotateArray.at(right))
        {
            int min = rotateArray.at(left);
            for (size_t i = left; i <= right; i++)
            {
                min = min > rotateArray.at(i) ? rotateArray.at(i) : min;
            }
            return min;
        }
        if (rotateArray.at(mid) >= rotateArray.at(left))
        {
            left = mid;
        }else
        {
            right = mid;
        }
    }
    return rotateArray.at(minIndex);
}


int main(int argc, char ** argv){
    streambuf* backup;
    backup = cin.rdbuf();
    fstream fin;
    fin.open("data.in");
    cin.rdbuf(fin.rdbuf());

    string inputline;
    istringstream iss;
    while (true)
    {
        getline(cin, inputline);
        iss = istringstream(inputline);
        vector<int> inputVec;
        int temp;
        while (iss >> temp)
        {
            inputVec.push_back(temp);
        }
    }
}
/*
7 5 6 4
1 2 3 4 5 6 7 0
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int InversePairs(vector<int> data) {
    size_t len = data.size();
    if (len == 0 || len == 1)
    {
        return 0;
    }
    size_t result(0);
    for (size_t i = 0; i < len; i++)
    {
        for (size_t j = i+1; j < len; j++)
        {
            if (data.at(i) > data.at(j))
            {
                if (++result == 1000000007)
                {
                    result = 1000000007;
                }
            }
        }
    }
    return result;
}

void checkBigNum(size_t& result){
    if (result >= 1000000007)
    {
        result -= 1000000007;
    }
}

int InversePairsHandle(vector<int>& data, vector<int>& tempVec, int left, int right){
    if (left == right)
    {
        return 0;
    }
    size_t mid = left + ((right - left) >> 1);
    size_t leftResult = InversePairsHandle(data, tempVec, left, mid);
    size_t rightResult = InversePairsHandle(data, tempVec, mid + 1, right);
    size_t result = leftResult + rightResult;
    checkBigNum(result);

    int p1 = mid, p2 = right, p3 = right;
    while (p1 >= left && p2 >= mid+1)
    {
        if (data.at(p1) > data.at(p2))
        {
            result += (p2 - mid); // p2 - (mid + 1) + 1
            checkBigNum(result);
            tempVec.at(p3--) = data.at(p1--);
        }else
        {
            tempVec.at(p3--) = data.at(p2--);
        }
    }
    while (p1 >= left)
    {
        tempVec.at(p3--) = data.at(p1--);
    }
    while (p2 >= mid+1)
    {
        tempVec.at(p3--) = data.at(p2--);
    }

    for (size_t i = left; i <= right; i++)
    {
        data.at(i) = tempVec.at(i);
    }



    return result;
}



int InversePairs2(vector<int> data) {
    size_t len = data.size();
    if (len == 0 || len == 1)
    {
        return 0;
    }
    vector<int> tempVec(len, 0);
    tempVec.reserve(len);
    return InversePairsHandle(data, tempVec, 0, len-1);

}

int main(int argc, char ** argv){
    streambuf* backup;
    ifstream fin;
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
        vector<int> record;
        while (iss >> temp)
        {
            record.push_back(temp);
        }
        cout << InversePairs2(record) << endl;
    }

}
#include <iostream>
#include <vector>

using namespace std;

int myAccumulate(int small, int big){
    int result(0);
    for (size_t i = small; i <= big; i++)
    {
        result += i;
    }
    return result;
}

vector<int> makeVector(int small, int big){
    vector<int> result;
    for (size_t i = small; i <= big; i++)
    {
        result.push_back(i);
    }
    return result;
}

vector<vector<int>> FindContinuousSequence(int sum) {
    vector<vector<int>> results;
    if (sum < 3)
    {
        return results;
    }
    int small = 1, big = 2;
    int result(0);
    result = myAccumulate(small, big);
    while (small <= (sum >> 1) && small < big)
    {

        if (result == sum)
        {
            results.push_back(makeVector(small, big));
            small++;
            result = myAccumulate(small, big);
        }else if (result < sum)
        {
            big++;
            result += big;
        }else
        {
            result -= small;
            small++;
        }
    }

    return results;
}

int main(int argc, char **argv){

    while (true)
    {
        int temp;
        cin >>  temp;
        FindContinuousSequence(temp);
    }

}
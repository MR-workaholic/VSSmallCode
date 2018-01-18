#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

/*
一只青蛙一次可以跳上1级台阶，也可以跳上2级。求该青蛙跳上一个n级的台阶总共有多少种跳法。
 */
int jumpFloor(int number) {
    vector<int> record = {0, 1, 2};

    if (number < 3)
    {
        return record.at(number);
    }
    int count = 2;
    while (count++ != number)
    {
        record.push_back(record.at(count - 1) + record.at(count - 2));
    }
    return record.at(count-1);
}

/*
一只青蛙一次可以跳上1级台阶，也可以跳上2级……它也可以跳上n级。求该青蛙跳上一个n级的台阶总共有多少种跳法。
 */
int jumpFloorII(int number) {
    vector<int> result = {0, 1};
    if (number < 2)
    {
        return result.at(number);
    }
    int count = 1;
    while (++count <= number)
    {
        result.push_back(accumulate(result.begin(), result.end(), 0) + 1);
    }
    return result.at(count-1);
}

/*
我们可以用2*1的小矩形横着或者竖着去覆盖更大的矩形。请问用n个2*1的小矩形无重叠地覆盖一个2*n的大矩形，总共有多少种方法？
 */
int rectCover(int number) {

}

int main(int argc, char ** argv){
    int number;
    while (cin >> number)
    {
        cout << jumpFloorII(number) << endl;
    }


}
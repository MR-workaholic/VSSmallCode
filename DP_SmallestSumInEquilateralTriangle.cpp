/*
在下图的等边三角型中
   2
  5 4
 1 4 7
8 6 9 6
中
从顶点走到底边的总和最少
测试数据输入：
2 5 4 1 4 7 8 6 9 6
 */
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int startIndexInEachLevel(int level){ // 返回每一层在数组中的起点坐标，输入层数（层数从零开始），record数组的有效数据也是从索引0开始
    return (level) * (level + 1) / 2;
}

size_t sizeToLevelNum(size_t size){
    //如何从数据的size，计算出层数，首先，第n层有n个数据，根据求和公式，(1+n) * n / 2 = size
    // n^2 + n - 2*size = 0
    return (sqrt(2*size*4+1)-1) / 2;
}

int dp_smallestsum(vector<int> nums){
    size_t sizeOfNums = nums.size();
    if (sizeOfNums == 0)
    {
        return -1;
    }
    size_t levelnum = sizeToLevelNum(sizeOfNums);
    if (levelnum == 1)
    {
        return nums.at(0);
    }
    vector<int> record;
    record.reserve(nums.size());
    record.push_back(nums.at(0)); // or record.push_back(nums.at(startIndexInEachLevel(0)))

    // 注意了，第i层(从0开始)的第一个数据在record索引是startIndexInEachLevel(i) + 0;最后一个数据时startIndexInEachLevel(i)+i
    for (size_t i = 1; i < levelnum; i++)
    {
        for (size_t j = 0; j < i + 1; j++)
        {
            size_t index = startIndexInEachLevel(i) + j; //求目标节点在nums数组中的索引
            if (j == 0) // 每行第一个节点，上层相邻节点只有一个
            {
                record.push_back(record.at(startIndexInEachLevel(i-1)) + nums.at(index)); // 插入上层第一个节点的记录值 + 本身
            }else if (j == i) // 每行的最后一个节点，上层相邻节点只有一个
            {
                record.push_back(record.at(startIndexInEachLevel(i-1) + i - 1) + nums.at(index)); // 插入上层最后一个节点的记录值 + 本身
            }else
            {

                size_t leftParentIndex = startIndexInEachLevel(i-1) + j - 1;
                size_t rightParentIndex = leftParentIndex +1;
                size_t minOne = min<int>({record.at(leftParentIndex), record.at(rightParentIndex)}); // 找出两个上层相邻节点的最小值
                record.push_back(minOne + nums.at(index)); // 最小值加上本身
            }

        }
    }

    size_t startIndex = startIndexInEachLevel(levelnum - 1);
    size_t endIndex = startIndex + levelnum;
    int res;
    for (size_t i = startIndex; i < endIndex; i++)
    {
        if (i == startIndex)
        {
            res = record.at(i);
        }else
        {
            res = min<int>({res, record.at(i)});
        }
    }
    return res;
}

int main(int argc, char ** argv){
    streambuf* backup;
    ifstream fin;
    fin.open("data.in");
    backup = cin.rdbuf();
    cin.rdbuf(fin.rdbuf());

    string inputline;
    istringstream iss;
    int val;
    while (true)
    {
        getline(cin, inputline);
        iss = istringstream(inputline);
        vector<int> nums;
        while (iss >> val)
        {
            nums.push_back(val);
        }
        cout << dp_smallestsum(nums) << endl;
    }

}
/*
����ͼ�ĵȱ���������
   2
  5 4
 1 4 7
8 6 9 6
��
�Ӷ����ߵ��ױߵ��ܺ�����
�����������룺
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

int startIndexInEachLevel(int level){ // ����ÿһ���������е�������꣬����������������㿪ʼ����record�������Ч����Ҳ�Ǵ�����0��ʼ
    return (level) * (level + 1) / 2;
}

size_t sizeToLevelNum(size_t size){
    //��δ����ݵ�size����������������ȣ���n����n�����ݣ�������͹�ʽ��(1+n) * n / 2 = size
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

    // ע���ˣ���i��(��0��ʼ)�ĵ�һ��������record������startIndexInEachLevel(i) + 0;���һ������ʱstartIndexInEachLevel(i)+i
    for (size_t i = 1; i < levelnum; i++)
    {
        for (size_t j = 0; j < i + 1; j++)
        {
            size_t index = startIndexInEachLevel(i) + j; //��Ŀ��ڵ���nums�����е�����
            if (j == 0) // ÿ�е�һ���ڵ㣬�ϲ����ڽڵ�ֻ��һ��
            {
                record.push_back(record.at(startIndexInEachLevel(i-1)) + nums.at(index)); // �����ϲ��һ���ڵ�ļ�¼ֵ + ����
            }else if (j == i) // ÿ�е����һ���ڵ㣬�ϲ����ڽڵ�ֻ��һ��
            {
                record.push_back(record.at(startIndexInEachLevel(i-1) + i - 1) + nums.at(index)); // �����ϲ����һ���ڵ�ļ�¼ֵ + ����
            }else
            {

                size_t leftParentIndex = startIndexInEachLevel(i-1) + j - 1;
                size_t rightParentIndex = leftParentIndex +1;
                size_t minOne = min<int>({record.at(leftParentIndex), record.at(rightParentIndex)}); // �ҳ������ϲ����ڽڵ����Сֵ
                record.push_back(minOne + nums.at(index)); // ��Сֵ���ϱ���
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
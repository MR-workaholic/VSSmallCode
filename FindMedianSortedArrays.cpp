/*
Median of Two Sorted Arrays(���������������λ��)

https://blog.csdn.net/qq_14821023/article/details/50806849

2 6 9 34
4 6 8 9
1 3 5 7 9
2 4
1 2 3 4

 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;


// �鲢�����ں���������������λ�� ʱ�临�Ӷ���O(m+n)
int FindMedianSortedArrays(const vector<int>& sortedArray1, const vector<int>& sortedArray2){
    size_t len1(sortedArray1.size()), len2(sortedArray2.size());
    if (len1 == 0 && len2 == 0)
    {
        return -1;
    }
    vector<int> sortedArray3(len1+len2, 0);
    sortedArray3.reserve(len1+len2);
    size_t start1(0), start2(0), start3(0);

    while (start1 < len1 && start2 < len2)
    {
        if (sortedArray1.at(start1) < sortedArray2.at(start2))
        {
            sortedArray3.at(start3++) = sortedArray1.at(start1++);
        }else
        {
            sortedArray3.at(start3++) = sortedArray2.at(start2++);
        }
    }

    if (start1 == len1)
    {
        while (start2 < len2)
        {
            sortedArray3.at(start3++) = sortedArray2.at(start2++);
        }
    }else
    {
        while (start1 < len1)
        {
            sortedArray3.at(start3++) = sortedArray1.at(start1++);
        }
    }

    // ����д�����۳���Ϊ����ż������
    return (sortedArray3.at(start3 >> 1) + sortedArray3.at(((start3 - 1) >> 1))) >> 1;

}

int findkInTwoArrays(const vector<int>& sortedArray1, int start1, const vector<int>& sortedArray2, int start2, int end){

    if (start1 >= sortedArray1.size())
    {
        // �������ҿ����ǵ�-1
        return sortedArray2.at(start2 + end - 1);
    }else if (start2 >= sortedArray2.size())
    {
        return sortedArray1.at(start1 + end - 1);
    }else if (end == 1)
    {
        return min<int>({sortedArray1.at(start1), sortedArray2.at(start2)});
    }

    int min1(INT_MAX), min2(INT_MAX);
    if (start1 + (end >> 1) - 1 < sortedArray1.size())
    {
        min1 = sortedArray1.at(start1 + (end >> 1) - 1);
    }
    if (start2 + (end >> 1) - 1 < sortedArray2.size())
    {
        min2 = sortedArray2.at(start2 + (end >> 1) - 1);
    }

    if (min1 < min2)
    {
        return findkInTwoArrays(sortedArray1, start1 + (end >> 1), sortedArray2, start2, end - (end >> 1));
    }
    return findkInTwoArrays(sortedArray1, start1, sortedArray2, start2 + (end >> 1), end - (end >> 1));



}

// ���ֲ��ҵ�˼�룬�¼����Ӷ���O(log(m+n)) ע����**����ҿ�**��
int FindMedianSortedArrays_2(const vector<int>& sortedArray1, const vector<int>& sortedArray2){
    size_t len1(sortedArray1.size()), len2(sortedArray2.size());
    if (len1 == 0 && len2 == 0)
    {
        return -1;
    }else if (len1 == 0)
    {
        // ����д�����۳���Ϊ����ż������
        return (sortedArray2.at(((len2 - 1) >> 1)) + sortedArray2.at(len2 >> 1)) >> 1;

    }else if (len2 == 0)
    {
        // ����д�����۳���Ϊ����ż������
        return (sortedArray1.at(((len1 - 1) >> 1)) + sortedArray1.at(len1 >> 1)) >> 1;
    }

    // �����ҿ��Ĳ���
    int total1 = (len1 + len2 + 1) >> 1;
    int total2 = (len1 + len2 + 2) >> 1;

    return (findkInTwoArrays(sortedArray1, 0, sortedArray2, 0, total1) + findkInTwoArrays(sortedArray1, 0, sortedArray2, 0, total2)) >> 1;

}

int main(int argc, char ** argv){
    streambuf* backup;
    ifstream fin;
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
        vector<int> sortedArray1;
        while (iss >> temp)
        {
            sortedArray1.push_back(temp);
        }

        getline(cin, inputline);
        iss = istringstream(inputline);
        vector<int> sortedArray2;
        while (iss >> temp)
        {
            sortedArray2.push_back(temp);
        }

        cout << FindMedianSortedArrays_2(sortedArray1, sortedArray2);
        cout << endl;
    }

    return 0;
}
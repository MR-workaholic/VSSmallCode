#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

/*
һֻ����һ�ο�������1��̨�ף�Ҳ��������2���������������һ��n����̨���ܹ��ж�����������
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
һֻ����һ�ο�������1��̨�ף�Ҳ��������2��������Ҳ��������n���������������һ��n����̨���ܹ��ж�����������
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
���ǿ�����2*1��С���κ��Ż�������ȥ���Ǹ���ľ��Ρ�������n��2*1��С�������ص��ظ���һ��2*n�Ĵ���Σ��ܹ��ж����ַ�����
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
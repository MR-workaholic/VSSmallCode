#include <iostream>
#include <vector>

using namespace std;

int minOf3Num(int a, int b, int c){
    int min = a < b ? a : b;
    min = min < c ? min : c;
    return min;
}

int GetUglyNumber_Solution(int index) {
    if (index == 0)
    {
        return 0;
    }
    if (index == 1)
    {
        return 1;
    }
    vector<int> record;
    record.push_back(1);
    int T2 = 0, T3 = 0, T5 = 0;
    while (record.size() != index)
    {
        record.push_back(minOf3Num(2*record.at(T2), 3*record.at(T3), 5*record.at(T5)));
        int  M = record.back();
        while (T2 < record.size()-1 && 2*record.at(T2) <= M)
        {
            T2++;
        }
        while (T3 < record.size()-1 && 3*record.at(T3) <= M)
        {
            T3++;
        }
        while (T5 < record.size()-1 && 5*record.at(T5) <= M)
        {
            T5++;
        }
    }

    return record.back();
}

int main(int argc, char ** argv){
    while (true)
    {
        int temp;
        cin >> temp;
        cout << GetUglyNumber_Solution(temp) << endl;
    }

}
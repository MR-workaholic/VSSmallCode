#include <iostream>
#include <vector>

using namespace std;
size_t N;
vector<int> record;

void rePrintNumber(int num, int digit){

    record.push_back(num);

    if (digit == 1)
    {
        for(auto var : record)
        {
            cout << var;
        }
        cout << ' ';
        record.pop_back();
        return;
    }


    for (size_t i = 0; i < 10; i++)
    {
        rePrintNumber(i, digit-1);
    }
    record.pop_back();
    return;
}

int main(int argc, char ** argv){
    cin >> N;
    record.reserve(N);

    for (size_t i = 0; i < 10; i++)
    {
        rePrintNumber(i, N);
        cout << endl;
    }
    return 0;
}
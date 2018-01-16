/* 
data.in:
ALABLABC
ABC
afbicwsdhbvedbnvfhbskedfyankjvbdshbcfdjbncdshhbcjhs
cvsdhbvcsjvndfjndsuhlcjsdnvfjdsjbklsnmdvsjhsdvhdfjkn
 */
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <set>

using namespace std;

int main(int argc, char ** argv){
    streambuf *backup;
    ifstream fin;
    fin.open("data.in");
    backup = cin.rdbuf();
    cin.rdbuf(fin.rdbuf());

    while (true)
    {
        string input1;
        string input2;
        getline(cin, input1);
        getline(cin, input2);
        input1 = ' ' + input1;
        input2 = ' ' + input2;
        size_t size1 = input1.size();
        size_t size2 = input2.size();
        vector<vector<size_t>> recordVec;
        for (size_t i = 0; i < size2; i++)
        {
            vector<size_t> temp(size1, 0);
            recordVec.push_back(temp);
        }
        // 动态规划
        for (size_t i = 1; i < size2; i++)
        {
            for (size_t j = 1; j < size1; j++)
            {
                if (input1.at(j) == input2.at(i))
                {
                    recordVec.at(i).at(j) = recordVec.at(i-1).at(j-1) + 1;
                }else
                {
                    recordVec.at(i).at(j) = 0;
                }
            }
        }
        // 打印数组
        for(auto var : recordVec)
        {
            for(auto val : var)
            {
                cout << setw(2) << val << ' ';
            }
            cout << endl;
        }
        // 找出最大子串的长度
        size_t count = 0;
        for(vector<size_t> var : recordVec)
        {
            size_t maxVal = *max_element(var.begin(), var.end());
            count = count < maxVal ? maxVal : count;
        }
        cout << "substring size is " << count << endl;
        // 找出最大子串的长度与值，或者结合上面，先找最大子串长再找值
        size_t result = 0;
        set<string> results; 
        for (size_t i = 1; i < size2; i++)
        {
            for (size_t j = 1; j < size1; j++)
            {
                if (recordVec.at(i).at(j) > result)
                {
                    result = recordVec.at(i).at(j);
                    results.clear();
                    results.insert(input1.substr(j - result + 1, result));
                }else if (result != 0 && recordVec.at(i).at(j) == result)
                {
                    results.insert(input1.substr(j - result + 1, result));
                } 
            }
        }
        cout << "substring size is " << result << endl;
        for(auto var : results)
        {
            cout << var << endl;
        }
    }


}


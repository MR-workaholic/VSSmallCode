/* 
data.in:
afbicwsdhbvedbnvfhbskedfyankjvbdshbcfdjbncdshhbcjhs
cvsdhbvcsjvndfjndsuhlcjsdnvfjdsjbklsnmdvsjhsdvhdfjkn
ALBLCL
ABC
cadvsd
casdsacsa
 */
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm> 
#include <iomanip>

using namespace std;

int main(int argc, char ** argv){
    streambuf *backup;
    ifstream fin;
    fin.open("data.in");
    backup = cin.rdbuf();
    cin.rdbuf(fin.rdbuf());

    while(true){
        string input1;
        string input2;
        vector<vector<int>> recordVec;  
        getline(cin, input1);
        getline(cin, input2);
        input1 = ' ' + input1; 
        input2 = ' ' + input2; 
        size_t size1 = input1.size();
        size_t size2 = input2.size();
        for(size_t i = 0; i < size2; i++){
            vector<int> row(size1, 0);
            recordVec.push_back(row);
        }
        // 动态规划
        for(size_t i = 1; i < size2; i++){
            for(size_t j = 1; j < size1; j++){
                if(input1.at(j) == input2.at(i)){
                    recordVec.at(i).at(j) = recordVec.at(i-1).at(j-1) + 1;
                }else{
                    recordVec.at(i).at(j) = max<int>(recordVec.at(i-1).at(j), recordVec.at(i).at(j-1));
                }
            }
        }
        // 打印数组
        for (auto x : recordVec){
            for(auto y : x){
                cout << setw(2) << y << ' ';
            }
            cout << endl;
        }
        // 找出最大子序列的长度（数组右下角）以及其中一个序列的值
        // vector<int> lastRow = recordVec.at(size2 - 1);
        // int count = *max_element(lastRow.begin(), lastRow.end());
        int count = recordVec.at(size2 - 1).at(size1 - 1);
        string result("");
        for (size_t i = size2 - 1, j = size1 - 1, k = count; ;)
        {
            if (recordVec.at(i).at(j-1) == k && 
                recordVec.at(i-1).at(j) == k && 
                recordVec.at(i-1).at(j-1) == k)
            {
                i--;
                j--;
            }else if (recordVec.at(i).at(j-1) == k-1 && 
                      recordVec.at(i-1).at(j) == k-1 && 
                      recordVec.at(i-1).at(j-1) == k-1)
            {
                result = input1.at(j) + result;
                i--;
                j--;
                k--;
            }else if (recordVec.at(i).at(j-1) == k-1 && 
                      recordVec.at(i-1).at(j) == k && 
                      recordVec.at(i-1).at(j-1) == k-1)
            {
                i--;
            }else if (recordVec.at(i).at(j-1) == k && 
                      recordVec.at(i-1).at(j) == k-1 && 
                      recordVec.at(i-1).at(j-1) == k-1)
            {
                j--;
            }
            if (k == 0)
            {
                break;
            }
        }
        cout << count << " " << result << endl; 
    }
    cin.rdbuf(backup);
    int a;
    cin >> a;
    return 0;
}

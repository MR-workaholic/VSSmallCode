/*
在下面地图中实现收集硬币并回溯出路径,只能向右或者向下，-1表示不可达点
和前一题的差别是附加边采用-1表示不可达
0 -1 0 1 0 0
1 0 0 -1 1 0
0 1 0 -1 1 0
0 0 0 1 0 1
-1 -1 -1 0 1 0
 */
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;


vector<pair<int, int>> dp_coincollection1(vector<vector<int>> map, int& result){
    vector<pair<int, int>> path;
    if (map.size() == 0 || map.at(0).size() == 0)
    {
        return path;
    }
    size_t rows = map.size(), cols = map.at(0).size();
    vector<vector<int>> record;
    record.reserve(rows + 1);
    record.push_back(vector<int>(cols + 1, -1));
    for (size_t i = 0; i < rows; i++)
    {
        vector<int> tempRow(cols + 1, 0);
        tempRow.reserve(cols + 1);
        tempRow.at(0) = -1;
        record.push_back(tempRow);
    }


    for (size_t i = 1; i < rows+1; i++)
    {
        for (size_t j = 1; j < cols+1; j++)
        {
            if (i == 1 && j == 1)
            {
                record.at(i).at(j) = map.at(i-1).at(j-1);
                continue;
            }
            if (map.at(i-1).at(j-1) == -1)
            {
                record.at(i).at(j) = -1;
                continue;
            }
            int upPoint(record.at(i-1).at(j)), leftPoint(record.at(i).at(j-1));
            if (upPoint == -1 && leftPoint == -1)
            {
                record.at(i).at(j) = -1;
            }else
            {
                record.at(i).at(j) = max<int>({upPoint, leftPoint}) + map.at(i-1).at(j-1);
            }
        }
    }
    if (record.at(rows).at(cols) == -1)
    {
        return path;
    }
    // 回溯出路径
    path.push_back({rows-1, cols-1});
    for (size_t i = rows, j = cols; !((i == 2 && j == 1) || (i == 1 && j == 2));)
    {
        if (record.at(i-1).at(j) > record.at(j-1).at(i))
        {
            i = i - 1;
            path.insert(path.begin(), {i-1, j-1});
        }else
        {
            j = j - 1;
            path.insert(path.begin(), {i-1, j-1});
        }
    }
    path.insert(path.begin(), {0, 0});
    return path;
}

int main(int argc, char ** argv){
    streambuf* backup;
    ifstream fin;
    fin.open("data.in");
    backup = cin.rdbuf();
    cin.rdbuf(fin.rdbuf());

    string inputline;
    istringstream iss;
    int val(0);
    vector<vector<int>> map;
    while (true)
    {
        getline(cin, inputline);
        if (inputline == "")
        {
            break;
        }
        iss = istringstream(inputline);
        vector<int> temp;
        while (iss >> val)
        {
            temp.push_back(val);
        }
        map.push_back(temp);
    }
    int result(-1);
    vector<pair<int, int>> path = dp_coincollection1(map, result);

}
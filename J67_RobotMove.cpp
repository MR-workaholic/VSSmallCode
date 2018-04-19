/*
120 2 2
 */
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

typedef enum
{
    UP,
    RIGHT,
    DOWN,
    LEFT
}Dir;

bool check(int x, int y, int threshold){
    string temp;
    temp = to_string(x);
    temp += to_string(y);
    int sum(0);
    for(auto var : temp)
    {
        sum += (var - '0');
    }
    return sum <= threshold;
}

void rwBackTracking(vector<vector<char>>& record, int x, int y, Dir dir, const int rows, const int cols, const int threshold, int& result){
    if (dir == UP)
    {
        x--;
    }else if (dir == RIGHT)
    {
        y++;
    }else if (dir == DOWN)
    {
        x++;
    }else
    {
        y--;
    }

    if ((dir == UP && (x == -1 || record[x][y] == 0 || !check(x, y, threshold))) ||
        (dir == RIGHT && (y == cols || record[x][y] == 0 || !check(x, y, threshold))) ||
        (dir == DOWN && (x == rows || record[x][y] == 0 || !check(x, y, threshold))) ||
        (dir == LEFT && (y == -1 || record[x][y] == 0 || !check(x, y, threshold))))
    {
        return;
    }
    result++;

    record[x][y] = 0;
    for (size_t i = 0; i < 4; i++)
    {
        rwBackTracking(record, x, y, static_cast<Dir>(i), rows, cols, threshold, result);
    }
    //record[x][y] = 1; //走过的格无须继续计算


}

int movingCount(int threshold, int rows, int cols)
{
    if (rows < 1 || cols < 1 || threshold < 0)
    {
        return 0;
    }

    if (rows == 1 && cols == 1)
    {
        return 1;
    }

    int result(1);
    vector<vector<char>> record;
    for (size_t i = 0; i < rows; i++)
    {
        vector<char> temp(cols, 1);
        record.push_back(temp);
    }

    record[0][0] = 0;
    for (size_t i = 0; i < 4; i++)
    {
        rwBackTracking(record, 0, 0, static_cast<Dir>(i), rows, cols, threshold, result);
    }
    // record[0][0] = 1;

    return result;
}

int main(int argc, char ** argv){
    streambuf* backup;
    fstream fin;
    fin.open("data.in");
    backup = cin.rdbuf();
    cin.rdbuf(fin.rdbuf());

    string inputline;
    istringstream iss;

    while (true)
    {
        getline(cin, inputline);
        iss = istringstream(inputline);
        int threshold, rows, cols;
        iss >> threshold >> rows >> cols;
        cout << movingCount(threshold, rows, cols) << endl;
    }

}
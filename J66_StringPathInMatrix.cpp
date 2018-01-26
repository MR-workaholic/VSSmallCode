/*
3 4
abcesfcsadee
bcced
5 8
ABCEHJIGSFCSLOPQADEEMNOEADIDEJFMVCEIFGGS
SGGFIECVAASABCEHJIGQEM
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

typedef enum
{
    UP,
    RIGHT,
    DOWN,
    LEFT
}Dir;

bool BackTracking(vector<vector<char>>& map, int x, int y, Dir dir, const int rows, const int cols, char* str){
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

    if ((dir == UP && (x == -1 || map[x][y] == '\0' || map[x][y] != *str)) ||
        (dir == RIGHT && (y == cols || map[x][y] == '\0'|| map[x][y] != *str)) ||
        (dir == DOWN && (x == rows || map[x][y] == '\0'|| map[x][y] != *str)) ||
        (dir == LEFT && (y == -1 || map[x][y] == '\0'|| map[x][y] != *str)))
    {
        return false;
    }

    if (*(str+1) == '\0')
    {
        return true;
    }

    char temp = map[x][y];
    map[x][y] = '\0';
    bool result = false;
    for (size_t i = 0; i < 4; i++)
    {
        result = BackTracking(map, x, y, static_cast<Dir>(i), rows, cols, str+1);
        if (result)
        {
            return result;
        }
    }

    map[x][y] = temp;
    return false;



}

bool hasPath(char* matrix, int rows, int cols, char* str)
{
    if (matrix == NULL || rows == 0 || cols == 0 || str == NULL)
    {
        return false;
    }
    vector<vector<char>> map;
    vector<pair<int, int>> start;
    for (size_t i = 0; i < rows; i++)
    {
        vector<char> temp;
        for (size_t j = 0; j < cols; j++)
        {
            temp.push_back(*matrix);
            if (*matrix == *str)
            {
                start.push_back({i, j});
            }
            matrix++;
        }
        map.push_back(temp);
    }
    bool result = false;
    if (start.empty())
    {
        return false;
    }
    if (*(str+1) == '\0')
    {
        if (start.empty())
        {
            return false;
        }
        return true;
    }

    for(auto var : start)
    {
        char temp = map[var.first][var.second];
        map[var.first][var.second] = '\0';
        for (size_t i = 0; i < 4; i++)
        {
            result =  BackTracking(map, var.first, var.second, static_cast<Dir>(i), rows, cols, str+1);
            if (result)
            {
                return result;
            }
        }
        map[var.first][var.second] = temp;
    }


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
    int itemp;
    char ctemp;

    while (true)
    {
        getline(cin, inputline);
        iss = istringstream(inputline);
        int rows, cols;
        iss >> rows >> cols;

        string matrix, str;
        getline(cin, matrix);
        getline(cin, str);
        cout << hasPath(const_cast<char*>(matrix.c_str()), rows, cols, const_cast<char*>(str.c_str())) << endl;
    }

}
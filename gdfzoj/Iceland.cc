#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <climits>
#include <cstdlib>

using namespace std;

typedef enum {
  UP = 0,
  RIGHT,
  DOWN,
  LEFT
} DIR;

size_t res(INT_MAX);
size_t N;

void run_map(vector<vector<short>> map, pair<int, int> point, DIR dir, pair<int, int>& target, size_t tres) {
    if (dir == UP)
    {
        point.first--;
    }else if (dir == RIGHT)
    {
        point.second++;
    }else if (dir == DOWN)
    {
        point.first++;
    }else
    {
        point.second--;
    }
  // for (size_t i = 0; i < N; i++) {
  //   for (size_t j = 0; j < N; j++) {
  //     cout << map[i][j]  << " ";
  //   }
  //   cout   << "\n";
  // }

  // cout << (map[point.first][point.second] == 1)  << "\n";
    if ((dir == UP && (point.first == -1 || map[point.first][point.second] == 1 )) ||
        (dir == RIGHT && (point.second == N || map[point.first][point.second] == 1 )) ||
        (dir == DOWN && (point.first == N || map[point.first][point.second] == 1 )) ||
        (dir == LEFT && (point.second == -1 || map[point.first][point.second] == 1 )))
    {
      // cout << "out:(" << point.first << ", " << point.second << ")"  << "\n";
        return;
    }
    ++tres;
    map[point.first][point.second] = 1;
    cout << "(" << point.first << ", " << point.second << ")"  << "\n";
    // exit(0);
    if (point.first == target.first && point.second == target.second) {
      res = min<size_t>(res, tres);
      cout << "bingo" << res << endl;
      return;
    }
    if (tres >= res) {
      return;
    }
    for (size_t i = 0; i < 4; ++i) {
      run_map(map, point, static_cast<DIR>(i), target, tres);
    }
}

int main(int argc, char *argv[])
{
  cin >> N;
  vector<vector<short>> mymap;
  mymap.reserve(N);

  size_t temp(N);
  while (temp--) {
    vector<short> temp_vec;
    temp_vec.reserve(N);
    size_t temp2(N);
    while (temp2--) {
      short temp_ch;
      cin >> temp_ch ;
      temp_vec.push_back(temp_ch);
    }
    mymap.push_back(temp_vec);
  }


  pair<int, int> start, end;
  int a, b;
  cin >> a >> b;
  start = make_pair(a-1, b-1);
  cin >> a >> b;
  end = make_pair(a-1, b-1);

  for (size_t i = 0; i < 4; ++i) {
    mymap[start.first][start.second] = 1;
    run_map(mymap, start, static_cast<DIR>(i), end, 0);
  }

  if (res == INT_MAX) {
    cout << "impossible" << "\n";
  }else {
    cout << res  << "\n";
  }


  return 0;
}

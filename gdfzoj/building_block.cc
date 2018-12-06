#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main(int argc, char *argv[])
{
  size_t num;
  cin >> num;

  vector<size_t> width, height;
  width.reserve(num);
  size_t temp(num);
  while (temp--) {
    size_t w, h;
    cin >> w >> h;
    width.push_back(w);
    height.push_back(h);
  }

  size_t target;
  cin >> target;

  size_t res(UINT_MAX);
  for (size_t i = 0; i < num; i++) {
    vector<size_t> temp;
    size_t w(0), index(i);
    while(index < num && w < target) {
      w += width.at(index);
      temp.push_back(height.at(index));
      ++index;
    }
    if (index >= num && w < target) {
      break;
    }
    res = min<size_t>(res, *max_element(temp.begin(), temp.end()));
  }

  cout << res + target  << "\n";
  cout << INT_MAX  << "\n";

  return 0;
}

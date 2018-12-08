#include <iostream>
#include <vector>

using namespace std;

size_t find_ans(vector<size_t> &vec) {
  size_t ans(vec.at(0));
  size_t count(1);
  for (size_t i = 1; i < vec.size();) {
    if (ans == vec.at(i)) {
      ++count;
      ++i;
    }else{
      --count;
      if (count == 0 && (i+1) < vec.size()) {
        ans = vec.at(i+1);
        count = 1;
        i += 2;
      }
      ++i;
    }
  }
  return ans;
}

int main(int argc, char *argv[])
{
  size_t N;
  cin >> N;

  while (N--) {
    size_t num;
    cin >> num;
    vector<size_t> vec;
    vec.reserve(num);
    while (num--) {
      size_t temp;
      cin >> temp;
      vec.push_back(temp);
    }
    cout << find_ans(vec) << "\n";
  }

  return 0;
}

#include <iostream>
#include <vector>

using namespace std;

vector<size_t> decomposition(size_t num) {
  vector<size_t> res;
  while (num >= 10) {
    res.push_back(num % 10);
    num /= 10;
  }
  res.push_back(num);
  return res;

}

int main(int argc, char *argv[])
{
  size_t N;
  cin >> N;
  vector<size_t> ans;
  ans.resize(10);

  for (size_t i = 1; i <= N; ++i) {
    vector<size_t> dec = decomposition(i);
    for (auto var : dec) {
      ++ans.at(var);
    }
  }
  for (auto var : ans) {
    cout << var  << " ";
  }


  return 0;
}

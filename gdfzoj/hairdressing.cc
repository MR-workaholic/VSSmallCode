#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
  int N;
  string input;
  cin >> N >> input;

  char record[26] = {0};

  size_t res(0);
  for(auto var : input) {
    size_t index = var - 'A';
    if (record[index] == 0) {
      record[index] = 1;
      --N;
      if (N < 0) {
        ++res;
      }
    }else {
      record[index] = 0;
      ++N;
    }
  }

  cout << res  << "\n";

  return 0;
}

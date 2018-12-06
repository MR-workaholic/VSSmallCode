#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
  size_t L, M;
  cin >> L >> M;
  bool record[L + 1];
  for (size_t i = 0; i < L+1; i++) {
    record[i] = true;
  }
  while (M--) {
    size_t begin, end;
    cin >> begin >> end;
    for (size_t i = begin; i < end + 1; ++i) {
      record[i] = false;
    }
  }

  size_t res(0);
  for (size_t i = 0; i < L+1; ++i) {
    if (record[i] == true) {
      ++res;
    }
  }

  cout << res  << "\n";

  return 0;
}

#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{

  size_t N;
  while (N--) {
    size_t num;
    cin >> num;
    vector v;
    v.reserve(num);
    while (num--) {
      int temp;
      cin >> temp;
      v.push_back(temp);

    }
  }

  return 0;
}

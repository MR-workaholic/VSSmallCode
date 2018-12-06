#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
  size_t N;
  cin >> N;

  size_t arr[N];
  for (size_t i = 0; i < N; i++) {
    cin >> arr[i];
  }

  size_t target;
  cin >> target;

  size_t left(0), right(N), res(-1);
  while (left < right) {
    size_t mid = left + ((right - left) >> 1);
    if (arr[mid] == target) {
      res = mid + 1;
      break;
    }else if(arr[mid] < target) {
      left = mid + 1;
    }else {
      right = mid;
    }
  }
  cout << res << "\n";
  return 0;
}

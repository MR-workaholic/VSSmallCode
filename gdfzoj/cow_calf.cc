#include <iostream>

using namespace std;
size_t num = 1;

void cow(size_t age, size_t thisyear, size_t target) {
  if (thisyear > target) {
    return;
  }
  if (age >= 4) {
    ++num;
    cow(1, thisyear, target);
  }
  cow(++age, ++thisyear, target);
}

int main(int argc, char *argv[])
{
  size_t year;
  while (true) {
    cin >> year;
    if (year == 0) {
      break;
    }
    num = 1;
    cow(1, 1, year);
    cout << num << "\n";
  }

  return 0;
}

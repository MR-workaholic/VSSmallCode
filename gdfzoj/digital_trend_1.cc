#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[])
{
  size_t N;
  cin >> N;

  unsigned short start(1);
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      cout << setw(3) << start;
      start += 1;
    }
    cout << "\n";
  }

  return 0;
}

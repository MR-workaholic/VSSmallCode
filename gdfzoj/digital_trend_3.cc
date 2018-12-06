#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[])
{
  size_t N;
  cin >> N;


  for (size_t i = 0; i < N; i++) {
    unsigned short start(i + 1);
    for (size_t j = 0; j < N; j++) {
      cout << setw(3) << start;
      start += N;
    }
    cout << "\n";
  }

  return 0;
}

#include <iostream>
#include <map>

using namespace std;


int main(int argc, char *argv[])
{
  map<size_t, unsigned short> res;

  size_t n;
  cin >> n;
  while (n--) {
    size_t temp;
    cin >> temp;
    if (res.find(temp) == res.end()) {
      res.insert({temp, 1});
    }else {
      ++res[temp];
    }
  }
  for (auto var : res) {
      cout << var.first << " " << var.second << "\n";
  }


  return 0;
}

/*
1 2 3 4 5 6
 */
#include <iostream>
#include <fstream>
#include <string>


using namespace std;

enum SomeConst
{
    A = 'A',
    B = 'B',
    C = 'C'
};

void printline(size_t target, char src, char dest){
    cout << "push " << target << " from " << src << " to " << dest << endl;
}

void reHanoi(size_t target, char src, char dest, char mid){
    if (target == 1)
    {
        printline(target, src, dest);
        return;
    }
    reHanoi(target-1, src, mid, dest);
    printline(target, src, dest);
    reHanoi(target-1, mid, dest, src);

}

void hanoi(size_t n){
    if (n == 0)
    {
        return;
    }
    reHanoi(n, A, C, B);
}

int main(int argc, char ** argv){
    streambuf* backup;
    backup = cin.rdbuf();
    ifstream fin;
    fin.open("data.in");
    cin.rdbuf(fin.rdbuf());

    while (true)
    {
        size_t n;
        cin >> n;
        hanoi(n);
    }
}
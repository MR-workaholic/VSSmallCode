/*
100
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class SumClass{
public:
    SumClass(){
        N++;
        SUM += N;
    }
    static void Reset(){
        N = 0;
        SUM = 0;
    }
    static size_t GetSum(){
        return SUM;
    }
private:
    static size_t N;
    static size_t SUM;
};

size_t SumClass::N = 0;
size_t SumClass::SUM = 0;

int Sum_Solution_1(int n) {
    SumClass::Reset();
    SumClass* temp = new SumClass[n];
    delete[] temp;
    temp = nullptr;

    return SumClass::GetSum();

}

//////////////////////////////////////////////

template<int n>
int SumFunc(){
    return n + SumFunc<n-1>();
}

template<>
int SumFunc<1>(){
    return 1;
}

int Sum_Solution_2(int n){
    return SumFunc<100>();  // 缺点是参数必输是编译器确定的
}

//////////////////////////////////////////////
class A;
A* array[2];

class A{
public:
    virtual int sum(int n){
        return 0;
    }
};
class B : public A{
public:
    virtual int sum(int n){
        return array[!!n]->sum(n-1) + n; // 当n=0的时候才调用父类的函数，因此父类的函数的n是-1的
    }
};


int Sum_Solution_3(int n){
    B b;
    A a;
    array[0] = &a;
    array[1] = &b;
    return b.sum(n);
}

////////////////////////////////////////////

typedef int (*func)(int);

int Sum_Zero(int){return 0;}

int Sum_No_Zero(int n){
    func functions[2] = {Sum_Zero, Sum_No_Zero};
    return n + functions[!!n](n-1);
}

int Sum_Solution_4(int n){
    return Sum_No_Zero(n);
}

/////////////////////////////////////////

int main(int argc, char ** argv){
    streambuf* backup;
    ifstream fin;
    fin.open("data.in");
    backup = cin.rdbuf();
    cin.rdbuf(fin.rdbuf());

    while (true)
    {
        int temp;
        cin >> temp;
        cout << Sum_Solution_4(temp) << endl;

    }
}
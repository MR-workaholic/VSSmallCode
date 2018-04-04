#include <iostream>

using namespace std;

template<typename T>
class MakeSealed{
    friend T;
    private:
    MakeSealed(){}
    ~MakeSealed(){}
};

class NewClass :  virtual private MakeSealed<NewClass>{
    public:
    NewClass(){
        cout << "Construct NewClass" << endl;
    }
};

class Try : public NewClass{
    public:
    Try(){
        cout << "Construct Try" << endl;
    }
};

int main(int argc, char ** argv){
    NewClass boo;
    Try coo;
    cout << sizeof(boo) << " " << sizeof(coo);
    return 0;
}
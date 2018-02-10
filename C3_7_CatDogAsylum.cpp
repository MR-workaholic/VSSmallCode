#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <utility>
#include <list>

using namespace std;

class CatDogAsylum{
public:
    CatDogAsylum() : age(0){}

    void enqueue(int animal){
        if (animal > 0)
        {
            dogs.push_back({animal, ++age});
        }else
        {
            cats.push_back({animal, ++age});
        }
    }

    int dequeueDog(){
        if (dogs.empty())
        {
            return 0;
        }
        int res = dogs.front().first;
        dogs.pop_front();
        return res;
    }

    int dequeueCat(){
        if (cats.empty())
        {
            return 0;
        }
        int res = cats.front().first;
        cats.pop_front();
        return res;
    }

    int dequeueAny(){
        int res(0);
        if (dogs.empty() && cats.empty())
        {
            return res;
        }
        if(!dogs.empty() && !cats.empty())
        {
            if (dogs.front().second < cats.front().second)
            {
                res = dogs.front().first;
                dogs.pop_front();
            }else
            {
                res = cats.front().first;
                cats.pop_front();
            }
        }else if (dogs.empty())
        {
            res = cats.front().first;
            cats.pop_front();
        }else if (cats.empty())
        {
            res = dogs.front().first;
            dogs.pop_front();
        }
        return res;
    }
private:
    int age;
    list<pair<int, int>> dogs, cats;
};

vector<int> asylum(vector<vector<int>> ope) {
    vector<int> result;
    size_t len = ope.size();
    if (len == 0 || ope.at(0).size() != 2)
    {
        return result;
    }
    CatDogAsylum temp;
    for(auto var : ope)
    {
        if (var.at(0) == 1)
        {
            temp.enqueue(var.at(1));
        }else
        {
            int animal(0);
            if (var.at(1) == 0)
            {
                animal = temp.dequeueAny();
            }else if (var.at(1) == 1)
            {
                animal = temp.dequeueDog();
            }else
            {
                animal = temp.dequeueCat();
            }
            if (animal != 0)
            {
                result.push_back(animal);
            }
        }
    }

    return result;
}


int main(int argc, char ** argv){
    streambuf* backup;
    backup = cin.rdbuf();
    ifstream fin;
    fin.open("data.in");
    cin.rdbuf(fin.rdbuf());

    string inputline;
    istringstream iss;

    while (true)
    {
        getline(cin, inputline);
        iss = istringstream(inputline);
        vector<vector<int>> ope;
        int action(0), val(0);
        while (iss >> action >> val)
        {
            vector<int> temp = {action, val};
            ope.push_back(temp);
        }
        vector<int> result = asylum(ope);
    }
}
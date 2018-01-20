#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

/*
    不要求交换后的顺序一致
 */
void reOrderArray(vector<int> &array) {
    if (array.size() == 0)
    {
        return;
    }
    vector<int>::iterator left = array.begin();
    vector<int>::iterator right = array.end();
    right--;
    while (left < right)
    {
        while (left < right && *left % 2 == 1)
        {
            left++;
        }
        while (left < right && *right % 2 == 0)
        {
            right--;
        }
        if (left >= right)
        {
            break;
        }
        int temp = *left;
        *left = *right;
        *right = temp;
        left++;
        right--;
    }
}

void reOrderArrayStable(vector<int> &array){
    if (array.size() == 0)
    {
        return;
    }

    int size = array.size();
    for (size_t i = 1; i < size; i++)
    {
        bool isSort = true;
        for (size_t j = 1; j < size - i + 1; j++)
        {
            // if (array.at(j) < array.at(j-1))
            if((array.at(j) % 2 == 1) && (array.at(j-1) % 2 == 0))
            {
                int temp = array.at(j);
                array.at(j) = array.at(j-1);
                array.at(j-1) = temp;
                isSort = false;
            }
        }
        if (isSort)
        {
            break;
        }
    }

}

int main(int argc, char ** argv){
    streambuf* backup;
    backup = cin.rdbuf();
    fstream fin;
    fin.open("data.in");
    cin.rdbuf(fin.rdbuf());

    string inputline;
    istringstream iss;
    while (true)
    {
        getline(cin, inputline);
        iss = istringstream(inputline);
        vector<int> array;
        int temp;
        while (iss >> temp)
        {
            array.push_back(temp);
        }
        reOrderArrayStable(array);
        int a = 2;
    }
}

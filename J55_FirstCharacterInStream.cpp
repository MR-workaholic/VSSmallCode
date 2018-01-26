/*
google
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>

using namespace std;

vector<pair<char, size_t>> record;

//Insert one char from stringstream
void Insert(char ch)
{
    auto it = record.begin();
    while (it != record.end())
    {
        if (it->first == ch)
        {
            (it->second)++;
            return;
        }
        it++;
    }
    record.push_back(make_pair(ch, 1));
}
//return the first appearence once char in current stringstream
char FirstAppearingOnce()
{
    for(auto var : record)
    {
        if (var.second == 1)
        {
            return var.first;
        }
    }
    return '#';
}


int main(int argc, char ** argv){
    streambuf* backup;
    backup = cin.rdbuf();
    ifstream fin;
    fin.open("data.in");
    cin.rdbuf(fin.rdbuf());

    string inputline;
    istringstream iss;
    char temp;
    while (true)
    {
        getline(cin, inputline);
        iss = istringstream(inputline);
        while (iss >> temp)
        {
            Insert(temp);
            cout << FirstAppearingOnce() << endl;
        }
    }

}
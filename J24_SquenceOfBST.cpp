#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

bool reConstructTree(vector<int> post, vector<int> vin)
{
    if ()
    {

    }
    auto tailNode = post.end();
    tailNode--;
    auto rootNode = find(vin.begin(), vin.end(), *tailNode);
    if (rootNode == vin.end())
    {
        return false;
    }
    vector<int> rightChildVin(rootNode + 1, vin.end());
    vector<int> leftChindVin(vin.begin(), rootNode);

}

bool VerifySquenceOfBST(vector<int> sequence) {
    if (sequence.size() == 0)
    {
        return false;
    }
    vector<int> vin = sequence;
    sort(vin.begin(), vin.end());
    return reConstructTree(sequence, vin);
}



int main(int argc, char **argv){
    streambuf* backup;
    ifstream fin;
    fin.open("data.in");
    backup = cin.rdbuf();
    cin.rdbuf(fin.rdbuf());

    string inputline;
    istringstream iss;
    while (true)
    {
        getline(cin, inputline);
        iss = istringstream(inputline);
        int temp;
        vector<int> record;
        while (iss >> temp)
        {
            record.push_back(temp);
        }

    }
}
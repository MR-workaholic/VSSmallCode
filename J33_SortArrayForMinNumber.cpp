/*
3 32 321
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

string Compare(string str1, string str2){
    if (str1 == "")
    {
        return str2;
    }else{
        int len = str1.size();
        for (size_t i = 0; i < len; i++)
        {
            if (str1.at(i) == str2.at(i))
            {
                continue;
            }else if (str1.at(i) > str2.at(i))
            {
                return str2;
            }else
            {
                return str1;
            }
        }
    }
    return str1;
}

void reMinNumber(int index, int count, vector<int>& numbers, vector<int>& record, string& temp, string& target){
    record.at(index) = 1;
    temp += to_string(numbers.at(index));
    if (count == numbers.size() - 1)
    {
        target = Compare(target, temp);
    }else{
        for (size_t i = 0; i < numbers.size(); i++)
        {
            if (record.at(i) == 1)
            {
                continue;
            }
            reMinNumber(i, count+1, numbers, record, temp, target);
        }
    }
    record.at(index) = 0;
    temp.erase(temp.end() - to_string(numbers.at(index)).size(), temp.end());
}

string PrintMinNumber(vector<int> numbers) {
    int len = numbers.size();
    if (len == 0)
    {
        return "";
    }else if (len == 1)
    {
        return to_string(numbers.at(0));
    }

    vector<int> record(len, 0);
    string target = "";
    for (size_t i = 0; i < len; i++)
    {
        string temp = "";
        reMinNumber(i, 0, numbers, record, temp, target);
    }
    return target;
}

string PrintMinNumber2(vector<int> numbers) {
    int len = numbers.size();
    if (len == 0)
    {
        return "";
    }else if (len == 1)
    {
        return to_string(numbers.at(0));
    }

    vector<string> strnumbers;
    for(auto var : numbers)
    {
        strnumbers.push_back(to_string(var));
    }

    sort(strnumbers.begin(), strnumbers.end(), [](string a, string b){
        string ab = a + b;
        string ba = b + a;
        return ab < ba;
    });
    string result("");
    for(auto var : strnumbers)
    {
        result += var;
    }
    return result;
}

string PrintMinNumber3(vector<int> numbers) {
    size_t len = numbers.size();
    if (len == 0)
    {
        return "";
    }else if(len == 1)
    {
        return to_string(numbers.at(0));
    }
    vector<string> strNumbers;
    for(auto var : numbers)
    {
        strNumbers.push_back(to_string(var));
    }
    sort(strNumbers.begin(), strNumbers.end());
    string res("");
    do
    {
        string temp("");
        for(auto var : strNumbers)
        {
            temp += var;
        }
        res = Compare(res, temp);
    } while(next_permutation(strNumbers.begin(), strNumbers.end()));

    return res;
}

int main(int argc, char **argv){
    streambuf* backup;
    ifstream fin;
    fin.open("data.in");
    backup = cin.rdbuf();
    cin.rdbuf(fin.rdbuf());

    string inputline;
    istringstream iss;
    int temp;

    while (true)
    {
        getline(cin, inputline);
        iss = istringstream(inputline);
        vector<int> numbers;
        while (iss >> temp)
        {
            numbers.push_back(temp);
        }
        cout << PrintMinNumber2(numbers) << endl;
        std::cout << PrintMinNumber3(numbers) << '\n';
    }

}
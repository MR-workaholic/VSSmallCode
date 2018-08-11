/*
�и�ľ��
��֪Сľ�������ۼ۸�pi�ͳ���i�йأ�i=1,2,3����n����ΰѳ���Ϊn��ľ���и�
Ϊ���ɸ�����Ϊ������Сľ����ʹ���������ۼ۸�����������ÿ�����ȶ�Ӧ�ļ�Ǯ
0.6 1.2 1.7
0.6 1.2 1.7 3.5 3.9 4.5
dp_cuttingwoodenstick���ص������п��ܽ������dp_cuttingwoodenstick_oneans�Ƿ���һ�����
����ı��ֿ������ҳ��۸���ߣ��������ٵ�ľ������dp_cuttingwoodenstick_oneans�����ϼӶ�һ����¼ÿһ�ε����������鼴��
 */
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <utility>


using namespace std;

int floatCmp(float v1, float v2){
    float t = v1 - v2;
    if (t < 0.000000001 && t > -0.000000001)
    {
        return 0;
    }
    if (t > 0)
    {
        return 1;
    }
    return -1;
}

vector<vector<size_t>> dp_cuttingwoodenstick(const vector<float>& price){
    vector<vector<size_t>> results;
    size_t len = price.size();
    if (len == 0)
    {
        return results;
    }
    vector<map<multiset<size_t>, float>> record;
    // map<multiset<size_t>, float> nothing({}, 0.0);
    map<multiset<size_t>, float> nothing;
    nothing.insert({{}, 0.0});
    record.reserve(len + 1);
    record.push_back(nothing);

    for (size_t i = 1; i <= len; i++)
    {
        vector<size_t> cutLen;
        float curPrice;
        for (int j = i; j > 0 ; j--)
        {

            if (j == i)
            {
                cutLen.push_back(j);
                curPrice = price.at(j - 1);
            }else if (floatCmp(curPrice, (*(record.at(i - j).begin())).second + price.at(j-1)) == 0)
            {
                cutLen.push_back(j);
            }else if (floatCmp(curPrice, (*(record.at(i - j).begin())).second + price.at(j-1)) == -1)
            {
                curPrice = (*(record.at(i - j).begin())).second + price.at(j-1);
                cutLen.clear();
                cutLen.push_back(j);
            }
        }
        map<multiset<size_t>, float> truenothing;
        record.push_back(truenothing);
        for(auto var : cutLen)
        {
            for(auto var1 : record.at(i - var))
            {
                pair<multiset<size_t>, float> t(var1);
                t.first.insert(var);
                t.second += price.at(var - 1);
                record.at(i).insert(t);
            }
        }
    }

    for(auto var : record.at(len))
    {
        vector<size_t> temp(var.first.begin(), var.first.end());
        results.push_back(temp);
    }
    return results;
}

vector<size_t> dp_cuttingwoodenstick_oneans(const vector<float>& price){
    vector<size_t> result;
    size_t len = price.size();
    if (len == 0)
    {
        return result;
    }
    vector<float> record;
    vector<size_t> recall;
    record.reserve(len + 1);
    record.push_back(0.0);
    recall.reserve(len + 1);
    recall.push_back(0);

    for (size_t i = 1; i <= len; i++)
    {
        for (size_t j = 0; j < i; j++)
        {
            if (j == 0) // ��cut
            {
                record.push_back(price.at(i-1));
                recall.push_back(i);
            }else if (floatCmp(record.at(i), record.at(i - j)+price.at(j-1)) == -1) // cut ����Ϊj��ľ��
            {
                record.at(i) = record.at(i - j)+price.at(j-1);
                recall.at(i) = j;
            }
        }
    }

    size_t changeLen(len);
    while (changeLen)
    {
        result.push_back(recall.at(changeLen));
        changeLen -= recall.at(changeLen);
    }

    return result;
}


int main(int argc, char ** argv){
    streambuf* backup;
    ifstream fin;
    fin.open("data.in");
    backup = cin.rdbuf();
    cin.rdbuf(fin.rdbuf());

    string inputline;
    istringstream iss;
    float val(0.0);
    while (true)
    {
        getline(cin, inputline);
        iss = istringstream(inputline);
        vector<float> price;
        while (iss >> val)
        {
            price.push_back(val);
        }

        vector<vector<size_t>> result = dp_cuttingwoodenstick(price);
        for(auto var : result)
        {
            for(auto var1 : var)
            {
                cout << var1 << " ";
            }
            cout << endl;
        }

        vector<size_t> res = dp_cuttingwoodenstick_oneans(price);
    }

}
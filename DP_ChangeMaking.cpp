/*
�������⣬�ҳ��������ٵ��ܴճ�NԪ��Ӳ�ң��ж������������ӡ����
6 1 3 4
5 1 2 3 4
����ֻ��Ҫ�ҳ�һ�����Ž�Ļ���������һ��recall���飬��¼��������ʲôӲ�Ҵﵽ��Ӧ�ļ�Ǯ���ɣ���dp_changemaking_oneans
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>

using namespace std;

vector<vector<size_t>> dp_changemaking(size_t target, vector<size_t> money){
    vector<vector<size_t>> results;
    if (target == 0 || money.size() == 0)
    {
        return results;
    }
    vector<set<multiset<size_t>>> temp; //����Ҫ�ҳ����н⣬�������Ƚϸ��ӣ�ֻ�ҳ������Ļ���vector<size_t>���ɣ�Ҫ�ҳ�һ�����Ž�Ļ��������һ��recall���鼴��
    temp.reserve(target + 1);
    set<multiset<size_t>> nomoney;
    temp.push_back(nomoney);

    for (size_t i = 1; i <= target; i++)
    {
        vector<size_t> addMoney;
        for(auto var : money)  //�⺯���������ǿ�������������Щ��ֵ�Ļ��ң�����������ҵ�������С�����粻�ǻ��ҵ�������С�Ļ������Բ������ѭ������Ҫ��֤var<=i
        {
            if (var <= i && var == money.at(0))
            {
                addMoney.push_back(var);
            }else if (var <= i)
            {
                if (temp.at(i - var).empty() ||
                    (*(temp.at(i - var).begin())).size() <  (*(temp.at(i - addMoney.at(0)).begin())).size()
                    )  //����temp�����setΪ�գ���������Ӳ�ҽ�ȥ���������set�ǿն��ҵ�һ��Ԫ�ص�multiset��size�Ƚ��٣������addMoney��������Ԫ��
                {
                    addMoney.clear();
                    addMoney.push_back(var);
                }else if (!temp.at(i - var).empty() &&
                    (*(temp.at(i - var).begin())).size() == (*(temp.at(i - addMoney.at(0)).begin())).size()
                    ) //����set�ǿն��Һ͵�һ��Ԫ�ص�multiset��sizeһ���������Ԫ��
                {
                    addMoney.push_back(var);
                }
            }else
            {
                break;
            }
        }
        temp.push_back(nomoney);
        // size_t index = temp.size() - 1;
        for(auto var : addMoney)
        {
            if (temp.at(i - var).empty())
            {
                multiset<size_t> t;
                t.insert(var);
                temp.at(i).insert(t);
            }else{
                for(auto var1 : temp.at(i - var))
                {
                    var1.insert(var);
                    temp.at(i).insert(var1);
                }
            }
        }
    }

    for(auto var : temp.at(target))
    {
        vector<size_t> t(var.begin(), var.end());
        results.push_back(t);
    }
    return results;

}

vector<size_t> dp_changemaking_oneans(size_t target, vector<size_t> money){
    vector<size_t> result;
    if (target == 0 || money.size() == 0)
    {
        return result;
    }
    vector<size_t> record;
    record.reserve(target+1);
    record.push_back(0);

    vector<size_t> recall;
    recall.reserve(target+1);
    recall.push_back(0);

    for (size_t i = 1; i <= target; i++)
    {
        record.push_back(0);
        recall.push_back(0);
        for(auto var : money)
        {
            if (var > i)
            {
                continue;
            }
            if ((record.at(i) == 0) || (record.at(i) > record.at(i-var) + 1))
            {
                record.at(i) = record.at(i-var) + 1;
                recall.at(i) = var;
            }
        }
    }

    size_t changeTarget(target);
    while (changeTarget)
    {
        result.push_back(recall.at(changeTarget));
        changeTarget -= recall.at(changeTarget);
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
    size_t val(0), target(0);
    while (true)
    {
        getline(cin, inputline);
        iss = istringstream(inputline);
        iss >> target;
        vector<size_t> money;
        while (iss >> val)
        {
            money.push_back(val);
        }

        vector<vector<size_t>> result = dp_changemaking(target, money);
        for(auto var : result)
        {
            for(auto var1 : var)
            {
                cout << var1 << " ";
            }
            cout << endl;
        }
        vector<size_t> res = dp_changemaking_oneans(target, money);
    }

}
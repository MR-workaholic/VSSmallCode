/*
data.in
BBC ABCDAB ABCDABCDABDE
ABCDABD
abacababc
abab
 */
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int ViolentMatch(string str, string pat){
    size_t slen = str.size();
    size_t plen = pat.size();

    for (size_t i = 0; i < slen; i++)
    {
        if (str.at(i) == pat.at(0))
        {
            bool success = true;
            for (size_t j = 0; j < plen; j++)
            {
                if (pat.at(j) == str.at(i + j))
                {
                    continue;
                }else
                {
                    success = false;
                    break;
                }
            }
            if (success)
            {
                return i;
            }
        }
    }
    return -1;
}

int KMPMatch(string str, string pat){
    size_t slen = str.size();
    size_t plen = pat.size();

    // ����next����
    vector<int> next(plen, -1);
    next.reserve(plen);
    // next.at(0) = (-1);
    for (int j = 0, k = -1; j < plen - 1;) //��Ϊ��һ���Ѿ����غã��ʼ�ȥһ��
    {
        if (k == -1 || pat.at(k) == pat.at(j))
        {
            j++;
            k++;
            if (pat.at(j) != pat.at(k)) // ���ʹp[j] != p[ next[j] ],��Ϊһ��ʧ�䣬��j = next[j];
            {
                next.at(j) = (k); // ��֪��ǰj�������j+1��next��ֵ
            }else
            {
                next.at(j) = next.at(k);
            }
        }else
        {
            k = next.at(k);
        }
    }

    for (int i = 0, j = 0; i < slen;)
    {
        if (j != -1 && str.at(i) == pat.at(j))
        {
            bool success = true;
            for (; j < plen-1;)
            {
                if (pat.at(++j) == str.at(++i))
                {
                    continue;
                }else
                {
                    success = false;
                    j = next[j];
                    break;
                }
            }
            if (success)
            {
                return i - j;
            }
        }else if(j != -1)
        {
            j = next[j];
        }else
        {
            i++;
            j++;
        }

    }
    return -1;
}
/* ���ϴ����£�KMP���Ӽ���׶����������㷨�����ҵĸ��Ӻ�,���������ϴ𰸵ı��������ϴ𰸵�KMP����һ��ʮ�ֺõĹ��� */
/*
int ViolentMatch(char* s, char* p)
{
    int sLen = strlen(s);
    int pLen = strlen(p);

    int i = 0;
    int j = 0;
    while (i < sLen && j < pLen)
    {
        if (s[i] == p[j])
        {
            //�������ǰ�ַ�ƥ��ɹ�����S[i] == P[j]������i++��j++
            i++;
            j++;
        }
        else
        {
            //�����ʧ�䣨��S[i]! = P[j]������i = i - (j - 1)��j = 0
            i = i - j + 1;
            j = 0;
        }
    }
    //ƥ��ɹ�������ģʽ��p���ı���s�е�λ�ã����򷵻�-1
    if (j == pLen)
        return i - j;
    else
        return -1;
}

int KmpSearch(char* s, char* p)
{
    int i = 0;
    int j = 0;
    int sLen = strlen(s);
    int pLen = strlen(p);
    while (i < sLen && j < pLen)
    {
        //�����j = -1�����ߵ�ǰ�ַ�ƥ��ɹ�����S[i] == P[j]��������i++��j++
        if (j == -1 || s[i] == p[j])
        {
            i++;
            j++;
        }
        else
        {
            //�����j != -1���ҵ�ǰ�ַ�ƥ��ʧ�ܣ���S[i] != P[j]�������� i ���䣬j = next[j]
            //next[j]��Ϊj����Ӧ��nextֵ
            j = next[j];
        }
    }
    if (j == pLen)
        return i - j;
    else
        return -1;
}


//�Ż������next ������
void GetNextval(char* p, int next[])
{
    int pLen = strlen(p);
    next[0] = -1;
    int k = -1;
    int j = 0;
    while (j < pLen - 1)
    {
        //p[k]��ʾǰ׺��p[j]��ʾ��׺
        if (k == -1 || p[j] == p[k])
        {
            ++j;
            ++k;
            //��֮ǰnext�����󷨣��Ķ�������4��
            if (p[j] != p[k])
                next[j] = k;   //֮ǰֻ����һ��
            else
                //��Ϊ���ܳ���p[j] = p[ next[j ]]�����Ե�����ʱ��Ҫ�����ݹ飬k = next[k] = next[next[k]]
                next[j] = next[k];
        }
        else
        {
            k = next[k];
        }
    }
}

 */


int main(int argc, char ** argv){
    streambuf* backup;
    fstream fin;
    fin.open("data.in");
    backup = cin.rdbuf();
    cin.rdbuf(fin.rdbuf());

    while (true)
    {
        string str;
        string pat;
        getline(cin, str);
        getline(cin, pat);
        cout << "result is " << KMPMatch(str, pat) << endl;
    }


    return 0;
}
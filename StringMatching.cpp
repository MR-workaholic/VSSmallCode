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

    // 计算next数组
    vector<int> next(plen, -1);
    next.reserve(plen);
    // next.at(0) = (-1);
    for (int j = 0, k = -1; j < plen - 1;) //因为第一个已经加载好，故减去一次
    {
        if (k == -1 || pat.at(k) == pat.at(j))
        {
            j++;
            k++;
            if (pat.at(j) != pat.at(k)) // 务必使p[j] != p[ next[j] ],因为一旦失配，就j = next[j];
            {
                next.at(j) = (k); // 已知道前j个，求第j+1的next的值    
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
/* 网上答案如下，KMP更加简便易懂，而暴力算法则是我的更加好 */
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
            //①如果当前字符匹配成功（即S[i] == P[j]），则i++，j++      
            i++;  
            j++;  
        }  
        else  
        {  
            //②如果失配（即S[i]! = P[j]），令i = i - (j - 1)，j = 0      
            i = i - j + 1;  
            j = 0;  
        }  
    }  
    //匹配成功，返回模式串p在文本串s中的位置，否则返回-1  
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
        //①如果j = -1，或者当前字符匹配成功（即S[i] == P[j]），都令i++，j++      
        if (j == -1 || s[i] == p[j])  
        {  
            i++;  
            j++;  
        }  
        else  
        {  
            //②如果j != -1，且当前字符匹配失败（即S[i] != P[j]），则令 i 不变，j = next[j]      
            //next[j]即为j所对应的next值        
            j = next[j];  
        }  
    }  
    if (j == pLen)  
        return i - j;  
    else  
        return -1;  
}  


//优化过后的next 数组求法  
void GetNextval(char* p, int next[])  
{  
    int pLen = strlen(p);  
    next[0] = -1;  
    int k = -1;  
    int j = 0;  
    while (j < pLen - 1)  
    {  
        //p[k]表示前缀，p[j]表示后缀    
        if (k == -1 || p[j] == p[k])  
        {  
            ++j;  
            ++k;  
            //较之前next数组求法，改动在下面4行  
            if (p[j] != p[k])  
                next[j] = k;   //之前只有这一行  
            else  
                //因为不能出现p[j] = p[ next[j ]]，所以当出现时需要继续递归，k = next[k] = next[next[k]]  
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
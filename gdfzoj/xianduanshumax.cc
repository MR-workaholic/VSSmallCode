#include <iostream>
#include <algorithm>
#include <stdio.h>

// #define ONLINE

using namespace std;

const int MAXNUM = 100000;

typedef unsigned long long ull;
typedef long long ll;

struct SegTreeNode
{
    ll val;
};

SegTreeNode segTree[MAXNUM];

// bs be 左闭右闭
void build(int root, ll arr[], int bs, int be)
{
    if (bs == be)
    {
        segTree[root].val = arr[bs];
    }
    else
    {
        int bm = bs + ((be - bs) >> 1);
        build((root << 1) + 1, arr, bs, bm);
        build((root << 1) + 2, arr, bm + 1, be);
        // 求max
        segTree[root].val = max<ll>(segTree[(root << 1) + 1].val, segTree[(root << 1) + 2].val);
    }
}

void updateOne(int root, int us, int ue, int index /*待更新节点的原数组索引*/, int newVal /*量*/)
{
    if (us == ue)
    {
        if (us == index)
        {
            segTree[root].val = newVal;
        }
    }
    else
    {
        int um = us + ((ue - us) >> 1);
        if (index <= um)
        {
            updateOne((root << 1) + 1, us, um, index, newVal);
        }
        else
        {
            updateOne((root << 1) + 2, um + 1, ue, index, newVal);
        }
        // 求max
        segTree[root].val = max<ll>(segTree[(root << 1) + 1].val, segTree[(root << 1) + 2].val);
    }
}

int query(int root, int cs, int ce, int qs, int qe)
{
    // 查询的区间没有交集
    if (qe < cs || qs > ce)
    {
        return 0;
    }
    else if (qs <= cs && qe >= ce) // 当前节点区间包含在查询区间内
    {
        return segTree[root].val;
    }
    int cm = cs + ((ce - cs) >> 1);
    return max<ll>(query((root << 1) + 1, cs, cm, qs, qe), query((root << 1) + 2, cm + 1, ce, qs, qe));
}

int main(int argc, char **argv)
{
#ifndef ONLINE
    freopen("testdata.in", "r", stdin);
    freopen("myout.out", "w", stdout);
#endif // !ONLINE
    int N, M;
    cin >> N >> M;
    ll arr[MAXNUM];

    int temp(0);
    while (temp != N)
    {
        cin >> arr[temp++];
    }

    build(0, arr, 0, N - 1);

    while (M--)
    {
        char handle;
        cin >> handle;

        if (handle == 'Q')
        {
            size_t qs, qe;
            cin >> qs >> qe;
            std::cout << query(0, 0, N - 1, qs - 1, qe - 1) << '\n';
        }
        else if (handle == 'U')
        {
            ll a, b;
            cin >> a >> b;
            if (arr[a - 1] < b)
            {
                updateOne(0, 0, N - 1, a - 1, b);
            }
        }
    }

#ifndef ONLINE
    fclose(stdin);
    fclose(stdout);

#endif // !ONLINE
    return 0;
}
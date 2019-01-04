#include <iostream>

using namespace std;

const int MAXNUM = 1000;

struct SegTreeNode
{
    int val;
};

SegTreeNode segTree[MAXNUM];

// bs be 左闭右闭
void build(int root, int arr[], int bs, int be)
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
        // 求和
        segTree[root].val = segTree[(root << 1) + 1].val + segTree[(root << 1) + 2].val;
    }
}

void updateOne(int root, int us, int ue, int index /*待更新节点的原数组索引*/, int addVal /*增量*/)
{
    if (us == ue)
    {
        if (us == index)
        {
            segTree[root].val += addVal;
        }
    }
    else
    {
        int um = us + ((ue - us) >> 1);
        if (index <= um)
        {
            updateOne((root << 1) + 1, us, um, index, addVal);
        }
        else
        {
            updateOne((root << 1) + 2, um + 1, ue, index, addVal);
        }
        // 求和
        segTree[root].val = segTree[(root << 1) + 1].val + segTree[(root << 1) + 2].val;
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
    return query((root << 1) + 1, cs, cm, qs, qe) + query((root << 1) + 2, cm + 1, ce, qs, qe);
}

int main(int argc, char **argv)
{
    int arr[] = {2, 5, 1, 4, 9, 3};
    build(0, arr, 0, 5);

    updateOne(0, 0, 5, 3, 6);
    int a;
    a =  query(0, 0, 5, 2, 4);

    return 0;
}
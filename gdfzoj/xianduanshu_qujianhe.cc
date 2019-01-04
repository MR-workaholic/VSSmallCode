#include <iostream>

using namespace std;

const int MAXNUM = 200000;

typedef unsigned long long ull;
typedef long long ll;

struct SegTreeNode
{
    ll val;
    ll addMark;
};

SegTreeNode segTree[MAXNUM];

// bs be 左闭右闭
void build(int root, ll arr[], int bs, int be)
{
    segTree[root].addMark = 0; /* 初始化修改标记 */
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

/*
延迟标记：每个节点新增加一个标记，记录这个节点是否进行了某种
修改(这种修改操作会影响其子节点)，对于任意区间的修改，我们先
按照区间查询query的方式将其划分成线段树中的节点，然后修改这些节点
的信息，并给这些节点标记上代表这种修改操作的标记。在**修改**和**查
询**的时候，如果我们到了一个节点p，并且决定考虑其子节点，那么
我们就要看节点p是否被标记，如果有，就要按照标记修改其子节点
的信息，并且给子节点都标上相同的标记，同时消掉节点p的标记。
 */
void pushDown(int root, int cs, int ce)
{
    // 将标记往下传递，同时修改孩子节点的值即可
    if (segTree[root].addMark != 0 && cs != ce)
    {
        // 标记
        segTree[(root << 1) + 1].addMark += segTree[root].addMark;
        segTree[(root << 1) + 2].addMark += segTree[root].addMark;
        // 修改，不一定只加1，需要看实际情况，求最小值就只是加1，但是求和，可不一定加一
        int cm = cs + ((ce - cs) >> 1);
        segTree[(root << 1) + 1].val += (segTree[root].addMark * (cm - cs + 1));
        segTree[(root << 1) + 2].val += (segTree[root].addMark * (ce - cm));
    }
    segTree[root].addMark = 0;
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

/* 类似查询，区间的操作 */
void update(int root, int cs, int ce, int us, int ue, int addVal)
{
    if (ue < cs || us > ce)
    {
        return;
    }
    else if (us <= cs && ue >= ce)
    {
        segTree[root].addMark += addVal;
        segTree[root].val += (addVal * (ce - cs + 1));
        return; //在这里直接结束了，延时子树的更改
    }
    pushDown(root, cs, ce); /* 延迟标记向下传递 */
    int cm = cs + ((ce - cs) >> 1);
    update((root << 1) + 1, cs, cm, us, ue, addVal);
    update((root << 1) + 2, cm + 1, ce, us, ue, addVal);
    //求和
    segTree[root].val = segTree[(root << 1) + 1].val + segTree[(root << 1) + 2].val;
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
        //pushDown(root);
        return segTree[root].val;
    }
    pushDown(root, cs, ce);
    int cm = cs + ((ce - cs) >> 1);
    return query((root << 1) + 1, cs, cm, qs, qe) + query((root << 1) + 2, cm + 1, ce, qs, qe);
}

int main(int argc, char **argv)
{

    size_t N, M;
    cin >> N >> M;
    size_t temp(0);
    ll arr[MAXNUM];

    while (temp != N)
    {
        cin >> arr[temp++];
    }

    build(0, arr, 0, N - 1);

    while (M--)
    {
        size_t handle;
        cin >> handle;
        if (handle == 2)
        {
            size_t qs, qe;
            cin >> qs >> qe;
            std::cout << query(0, 0, N - 1, qs - 1, qe - 1) << '\n';
        }
        else
        {
            size_t us, ue;
            int addVal;
            cin >> us >> ue >> addVal;
            update(0, 0, N-1, us-1, ue-1, addVal);
        }
    }

/*     update(0, 0, N - 1, 2 - 1, 3 - 1, 2);
    std::cout << query(0, 0, N - 1, 3 - 1, 4 - 1) << '\n';
    update(0, 0, N - 1, 1 - 1, 5 - 1, 1);
    std::cout << query(0, 0, N - 1, 1 - 1, 4 - 1) << '\n';
 */
    return 0;
}
#include <iostream>
#include <stdio.h>
// #define ONLINE

using namespace std;

const int MAXNUM = 2000;

typedef unsigned long long ull;
typedef long long ll;
ll P;

struct SegTreeNode
{
    ll val;
    ll addMark;
    ll mulMark;
};

SegTreeNode segTree[MAXNUM];

// bs be ����ұ�
void build(int root, ll arr[], int bs, int be)
{
    segTree[root].addMark = 0; /* ��ʼ��+��� */
    segTree[root].mulMark = 1; /* ��ʼ��*��� */
    if (bs == be)
    {
        segTree[root].val = arr[bs];
    }
    else
    {
        int bm = bs + ((be - bs) >> 1);
        build((root << 1) + 1, arr, bs, bm);
        build((root << 1) + 2, arr, bm + 1, be);
        // ��Ͳ�ȡģ
        segTree[root].val = segTree[(root << 1) + 1].val + segTree[(root << 1) + 2].val;
        segTree[root].val %= P;
    }
}

/*
�ӳٱ�ǣ�ÿ���ڵ�������һ����ǣ���¼����ڵ��Ƿ������ĳ��
�޸�(�����޸Ĳ�����Ӱ�����ӽڵ�)����������������޸ģ�������
���������ѯquery�ķ�ʽ���仮�ֳ��߶����еĽڵ㣬Ȼ���޸���Щ�ڵ�
����Ϣ��������Щ�ڵ����ϴ��������޸Ĳ����ı�ǡ���**�޸�**��**��
ѯ**��ʱ��������ǵ���һ���ڵ�p�����Ҿ����������ӽڵ㣬��ô
���Ǿ�Ҫ���ڵ�p�Ƿ񱻱�ǣ�����У���Ҫ���ձ���޸����ӽڵ�
����Ϣ�����Ҹ��ӽڵ㶼������ͬ�ı�ǣ�ͬʱ�����ڵ�p�ı�ǡ�
 */
void pushDown(int root, int cs, int ce)
{
    // ��������´��ݣ�ͬʱ�޸ĺ��ӽڵ��ֵ����

    // �ȸĳ˷� �ٸļӷ�
    if (segTree[root].mulMark != 1 && cs != ce)
    {
        // ���
        segTree[(root << 1) + 1].mulMark = (segTree[(root << 1) + 1].mulMark * segTree[root].mulMark) % P;
        segTree[(root << 1) + 2].mulMark = (segTree[(root << 1) + 2].mulMark * segTree[root].mulMark) % P;
        segTree[(root << 1) + 1].addMark = (segTree[(root << 1) + 1].addMark * segTree[root].mulMark) % P;
        segTree[(root << 1) + 2].addMark = (segTree[(root << 1) + 2].addMark * segTree[root].mulMark) % P;
        // (lval + rval) * mulVal   ��ͬ�� (root) *mulVal
        segTree[(root << 1) + 1].val = (segTree[(root << 1) + 1].val * segTree[root].mulMark) % P;
        segTree[(root << 1) + 2].val = (segTree[(root << 1) + 2].val * segTree[root].mulMark) % P;
    }


    if (segTree[root].addMark != 0 && cs != ce)
    {
        // ���
        segTree[(root << 1) + 1].addMark = (segTree[(root << 1) + 1].addMark + segTree[root].addMark) % P;
        segTree[(root << 1) + 2].addMark = (segTree[(root << 1) + 2].addMark + segTree[root].addMark) % P;

        // �޸ģ���һ��ֻ��1����Ҫ��ʵ�����������Сֵ��ֻ�Ǽ�1��������ͣ��ɲ�һ����һ
        int cm = cs + ((ce - cs) >> 1);
        segTree[(root << 1) + 1].val = (segTree[(root << 1) + 1].val + (segTree[root].addMark * (cm - cs + 1))) % P;
        // segTree[(root << 1) + 1].val %= P;
        segTree[(root << 1) + 2].val = (segTree[(root << 1) + 2].val + (segTree[root].addMark * (ce - cm))) % P;
        // segTree[(root << 1) + 2].val %= P;
    }

    segTree[root].addMark = 0;
    segTree[root].mulMark = 1;
}

void updateOne(int root, int us, int ue, int index /*�����½ڵ��ԭ��������*/, int addVal /*����*/)
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
        // ���
        segTree[root].val = segTree[(root << 1) + 1].val + segTree[(root << 1) + 2].val;
    }
}

/* ���Ʋ�ѯ������Ĳ��� */
void update_add(int root, int cs, int ce, int us, int ue, int addVal)
{
    if (ue < cs || us > ce)
    {
        return;
    }
    else if (us <= cs && ue >= ce)
    {
        segTree[root].addMark += addVal;
        segTree[root].val += (addVal * (ce - cs + 1));
        return; //������ֱ�ӽ����ˣ���ʱ�����ĸ���
    }
    pushDown(root, cs, ce); /* �ӳٱ�����´��� */
    int cm = cs + ((ce - cs) >> 1);
    update_add((root << 1) + 1, cs, cm, us, ue, addVal);
    update_add((root << 1) + 2, cm + 1, ce, us, ue, addVal);
    //���
    segTree[root].val = segTree[(root << 1) + 1].val + segTree[(root << 1) + 2].val;
}

void update_mul(int root, int cs, int ce, int us, int ue, int mulVal)
{
    if (ue < cs || us > ce)
    {
        return;
    }
    else if (us <= cs && ue >= ce)
    {
        segTree[root].mulMark *= mulVal;
        segTree[root].mulMark %= P;
        segTree[root].addMark *= mulVal;
        segTree[root].addMark %= P;
        // (lval + rval) * mulVal   ��ͬ�� (root) *mulVal
        segTree[root].val *= mulVal;
        segTree[root].val %= P;
        return; //�ӳ��޸�
    }
    pushDown(root, cs, ce);
    int cm = cs + ((ce - cs) >> 1);
    update_mul((root << 1) + 1, cs, cm, us, ue, mulVal);
    update_mul((root << 1) + 2, cm + 1, ce, us, ue, mulVal);
    //���
    segTree[root].val = (segTree[(root << 1) + 1].val + segTree[(root << 1) + 2].val) % P;
}

int query(int root, int cs, int ce, int qs, int qe)
{
    // ��ѯ������û�н���
    if (qe < cs || qs > ce)
    {
        return 0;
    }
    else if (qs <= cs && qe >= ce) // ��ǰ�ڵ���������ڲ�ѯ������
    {
        //pushDown(root);
        return segTree[root].val;
    }
    pushDown(root, cs, ce);
    int cm = cs + ((ce - cs) >> 1);
    return (query((root << 1) + 1, cs, cm, qs, qe) + query((root << 1) + 2, cm + 1, ce, qs, qe)) % P;
}

int main(int argc, char **argv)
{
#ifndef ONLINE
    freopen("testdata.in", "r", stdin);
#endif // !ONLINE

    size_t N, M;
    cin >> N >> M >> P;
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
        if (handle == 1)
        {
            size_t us, ue;
            int mulVal;
            cin >> us >> ue >> mulVal;
            update_mul(0, 0, N - 1, us - 1, ue - 1, mulVal);
        }else if (handle == 3)
        {
            size_t qs, qe;
            cin >> qs >> qe;
            std::cout << query(0, 0, N - 1, qs - 1, qe - 1) << '\n';
        }
        else if (handle == 2)
        {
            size_t us, ue;
            int addVal;
            cin >> us >> ue >> addVal;
            update_add(0, 0, N - 1, us - 1, ue - 1, addVal);
        }
    }

        /*     update(0, 0, N - 1, 2 - 1, 3 - 1, 2);
    std::cout << query(0, 0, N - 1, 3 - 1, 4 - 1) << '\n';
    update(0, 0, N - 1, 1 - 1, 5 - 1, 1);
    std::cout << query(0, 0, N - 1, 1 - 1, 4 - 1) << '\n';
 */
#ifndef ONLINE
    fclose(stdin);
#endif // !ONLINE
    return 0;
}
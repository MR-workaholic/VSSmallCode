// luogu-judger-enable-o2
// luogu-judger-enable-o2
#include <iostream>
#include <algorithm>
#include <stdio.h>

// #define ONLINE
using namespace std;
int n, k, x, y;
int tree[800000];
void build(int l, int r, int t)
{
    if (l == r)
    {
        cin >> tree[t];
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, t * 2);
    build(mid + 1, r, t * 2 + 1);
    tree[t] = max(tree[t * 2], tree[t * 2 + 1]);
}
int ask(int l, int r, int t)
{
    int re = -2147483647;
    if (y < l || x > r)
    {
        return 0;
    }else if (x <= l && r <= y)
    {
        re = tree[t];
    }
    else
    {
        int mid = (l + r) / 2;
        re = max(ask(l, mid, t*2), ask(mid+1, r, t*2+1));
    }
    return re;
}

void change(int l, int r, int t)
{
    if (l == r)
    {
        if (l == x)
        {
            tree[t] = max(tree[t], y);
        }
        return;
    }
    int mid = (l + r) / 2;
    if (x <= mid)
        change(l, mid, t * 2);
    else
        change(mid + 1, r, t * 2 + 1);
    tree[t] = max(tree[t * 2], tree[t * 2 + 1]);
}


int main()
{

#ifndef ONLINE
    freopen("testdata.in", "r", stdin);
    freopen("myout.out", "w", stdout);
#endif // !ONLINE
    char q;
    cin >> n >> k;
    build(1, n, 1);
    for (int i = 1; i <= k; i++)
    {
        cin >> q;
        if (q == 'Q')
        {
            cin >> x >> y;
            cout << ask(1, n, 1) << endl;
        }
        if (q == 'U')
        {
            cin >> x >> y;
            change(1, n, 1);
        }
    }

#ifndef ONLINE
    fclose(stdin);
    fclose(stdout);

#endif // !ONLINE
    return 0;
}
#include <bits/stdc++.h>
#define ll long long
const int Maxn = 5e4 + 20;
using namespace std;
ll a[Maxn][50];
int cnt[Maxn];
struct L_B
{
    long long d[35]; //若为LL,开63++;
    L_B()
    {
        memset(d, 0, sizeof(d));
    }
    void init()
    {
        memset(d, 0, sizeof(d));
    }
    void insert(ll x)
    {
        for (int i = 32; i >= 0; i--)
        { //or 64
            if (x & (1ll << i))
            {
                if (!d[i])
                {
                    d[i] = x;
                    break;
                }
                x ^= d[i];
            }
        }
    }
    bool check(ll x)
    {
        for (int i = 32; i >= 0; i--)
        {
            if (x & (1ll << i))
                x ^= d[i];
        }
        return x == 0ll;
    }
    L_B merge(L_B k)
    {
        L_B res, tmp = k;
        res.init();
        for (int i = 0; i <= 32; i++)
        {
            ll x = d[i], y = 0;
            bool flag = false;
            for (int j = 32; j >= 0; j--)
            {
                if ((x >> j) & 1)
                {
                    if (k.d[j])
                        x ^= k.d[j], y ^= tmp.d[j];
                    else
                    {
                        k.d[j] = x;
                        tmp.d[j] = y;
                        flag = true;
                        break;
                    }
                }
            }
            if (!flag)
                res.d[i] = y;
        }
        return res;
    }
} tree[(Maxn) << 2];

void build(int o, int l, int r)
{
    tree[o].init();
    if (l == r)
    {
        for (int j = 1; j <= cnt[l]; j++)
            tree[o].insert(a[l][j]);
    }
    else
    {
        int mid = (l + r) / 2;
        build(o << 1, l, mid);
        build(o << 1 | 1, mid + 1, r);
        tree[o] = tree[o << 1].merge(tree[o << 1 | 1]);
    }
}
bool query(int o, int l, int r, int ql, int qr, ll x)
{
    if (ql <= l && qr >= r)
        return tree[o].check(x);
    int mid = (l + r) / 2;
    bool ans = true;
    if (ql <= mid)
        ans = ans & query(o << 1, l, mid, ql, qr, x);
    if (qr >= mid + 1)
        ans = ans & query(o << 1 | 1, mid + 1, r, ql, qr, x);
    return ans;
}
int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> cnt[i];
        for (int j = 1; j <= cnt[i]; j++)
            cin >> a[i][j];
    }
    build(1, 1, n);
    while (m--)
    {
        int l, r;
        ll x;
        cin >> l >> r >> x;
        if (query(1, 1, n, l, r, x))
        {
            puts("YES");
        }
        else
            puts("NO");
    }
    return 0;
}
#include <bits/stdc++.h>
#define LL long long
using namespace std;
unordered_map<LL, LL> mp;
int loop, up;
LL n, x0, a, b, p, v;
LL _pow(LL a, LL b, LL Mod)
{
    LL ret = 1;
    LL mul = a % Mod;
    while (b > 0)
    {
        if (b & 1)
            ret = ret * mul % Mod;
        mul = mul * mul % Mod;
        b = b >> 1;
    }
    return ret;
}
LL inv(LL x, LL P)
{
    return _pow(x, P - 2, P);
}
void pre_BSGS(int p, int a)
{ //预处理一部分a^y
    mp.clear();
    up = ceil(pow(p, 2.0 / 3));

    int t = 1;
    for (int i = 0; i <= up; i++)
    {
        if (i == up)
            loop = t;
        mp[t] = i;
        t = 1LL * t * a % p;
    }
}
LL BSGS(LL B, LL N, LL P)
{ //B^ans=N(%p)
    int m = ceil(pow(p, 1.0 / 3));
    int obj = inv(N, P);
    for (int i = 1; i <= m; i++)
    {
        obj = 1LL * obj * loop % P;
        if (mp.count(obj))
        {
            return 1LL * i * up - mp[obj];
        }
    }
    return -1;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%lld%lld%lld%lld%lld", &n, &x0, &a, &b, &p);
        int Q;
        scanf("%d", &Q);
        pre_BSGS(p, a);
        while (Q--)
        {
            scanf("%lld", &v);
            LL bi = b + ((a - 1) * v % p);
            bi = bi % p;
            bi = bi * inv((b + x0 * (a - 1)) % p, p) % p;
            LL ans = BSGS(a, bi, p); //a^ans=bi(%p)
            if (ans >= n)
                ans = -1;
            printf("%lld\n", ans);
        }
    }
    return 0;
}
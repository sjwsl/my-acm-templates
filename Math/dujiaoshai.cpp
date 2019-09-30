#include <bits/stdc++.h>
#define LL long long
const int P = 1e9 + 7;
using namespace std;
LL _pow(LL a, LL b)
{
    LL ret = 1;
    LL mul = a % P;
    while (b)
    {
        if (b & 1)
            ret = ret * mul % P;
        mul = mul * mul % P;
        b = b >> 1;
    }
    return ret;
}
namespace dujiao
{
unordered_map<LL, LL> mapi;
const int M = 1e6 + 7;
LL sum[M] = {0};
int cnt = 0;
LL prim[M], phi[M];
bool vis[M];
void init(int maxn)
{
    mapi.clear();
    memset(vis, 0, sizeof(vis));
    phi[1] = 1;
    for (int i = 2; i <= maxn; i++)
    {
        if (!vis[i])
        {
            prim[++cnt] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= cnt && prim[j] * i <= maxn; j++)
        {
            vis[i * prim[j]] = 1;
            if (i % prim[j] == 0)
            {
                phi[i * prim[j]] = phi[i] * prim[j];
                break;
            }
            else
                phi[i * prim[j]] = phi[i] * (prim[j] - 1);
        }
    }
    for (int i = 1; i <= maxn; i++)
        sum[i] = (sum[i - 1] + (i * phi[i]) % P) % P;
}
inline LL s_fg(LL n)
{
    LL ans = n * (n + 1) % P;
    ans = ans * (2 * n + 1) % P;
    ans = ans * _pow(6, P - 2) % P;
    return ans;
}
LL go(LL n)
{
    if (n < M)
        return sum[n];
    if (mapi[n])
        return mapi[n];
    LL ans = s_fg(n);
    for (int i = 2; i <= n;)
    {
        int j = n / (n / i);
        LL t1 = 1LL * j * (j + 1) / 2 - 1LL * i * (i - 1) / 2;
        t1 = t1 % P;
        ans = (ans - t1 * go(n / i) % P + P) % P;
        i = j + 1;
    }
    return mapi[n] = ans;
}
LL solve(LL n)
{
    return go(n);
}
} // namespace dujiao
int main()
{
    int T;
    scanf("%d", &T);
    int M = 1e6 + 7;
    dujiao::init(M);
    while (T--)
    {
        LL n;
        int a, b;
        scanf("%lld%d%d", &n, &a, &b);
        LL ans = dujiao::go(n);
        ans = (ans - 1 + P) % P;
        ans = ans * _pow(2, P - 2) % P;
        printf("%lld\n", ans);
    }
    return 0;
}
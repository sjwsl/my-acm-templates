#include <bits/stdc++.h>
#define rep(ii, a, b) for (int ii = a; ii <= b; ii++)
#define ll long long
using namespace std;
ll qpow(ll a, ll b, ll nmod)
{
    ll res = 1;
    while (b)
    {
        if (b & 1)
            res = res * a % nmod;
        a = a * a % nmod;
        b >>= 1;
    }
    return res;
}

void exgcd(ll a, ll b, ll &x, ll &y, ll &d)
{
    b ? (exgcd(b, a % b, y, x, d), y -= x * (a / b)) : (x = 1, y = 0, d = a);
}
ll inv(ll a, ll m)
{
    ll x, y, d;
    exgcd(a, m, x, y, d);
    return x >= 0 ? x % m : x % m + m;
}
ll crt(ll a, ll m, ll m0)
{ //m0 | m; (m0,m/m0)=1
    return m / m0 * inv(m / m0, m0) % m * a % m;
}

ll fact(ll n, ll p, ll pk)
{ //(n!/p^x)%(p^k)
    if (n <= 1)
        return 1;
    ll ans = 1, tmp = n % pk;
    rep(i, 1, pk)
    {
        if (i % p)
            ans = ans * i % pk;
    }
    ans = qpow(ans, n / pk, pk);
    rep(i, 1, tmp)
    {
        if (i % p)
            ans = ans * i % pk;
    }
    return ans * fact(n / p, p, pk) % pk;
}

ll c(ll n, ll m, ll p, ll pk)
{ //c(n,m)%(p^k)
    ll sum = 0;
    for (ll i = n; i; i /= p)
        sum += i / p;
    for (ll i = m; i; i /= p)
        sum -= i / p;
    for (ll i = n - m; i; i /= p)
        sum -= i / p;
    return qpow(p, sum, pk) * fact(n, p, pk) % pk * inv(fact(m, p, pk), pk) % pk * inv(fact(n - m, p, pk), pk) % pk;
}

ll fac[40][2], pf; //0 p;  1 pk
void getfac(ll n)
{
    ll tmp = sqrt(n);
    rep(i, 2, tmp)
    {
        if (n % i == 0)
        {
            fac[++pf][0] = i, fac[pf][1] = 1;
            while (n % i == 0)
                n /= i, fac[pf][1] *= i;
        }
    }
    if (n > 1)
        fac[++pf][0] = n, fac[pf][1] = n;
}
ll exlucas(ll n, ll m, ll p)
{
    ll ans = 0;
    getfac(p);
    rep(i, 1, pf)
    {
        ans = (ans + crt(c(n, m, fac[i][0], fac[i][1]), p, fac[i][1])) % p;
    }
    return ans;
}
int main()
{
    ll n, m, p;
    cin >> n >> m >> p;
    cout << exlucas(n, m, p) << endl;
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using VI = vector<int64_t>;
class Linear_Seq
{
public:
    static const int N = 50020; ///多项式系数最大值
    int64_t res[N], c[N], md[N], COEF[N] /**COEF是多项式系数*/, Mod;
    vector<int> Md;
    inline static int64_t gcdEx(int64_t a, int64_t b, int64_t &x, int64_t &y)
    {
        if (!b)
        {
            x = 1;
            y = 0;
            return a;
        }
        int64_t d = gcdEx(b, a % b, y, x);
        y -= (a / b) * x;
        return d;
    }
    static int64_t Inv(int64_t a, int64_t Mod)
    {
        int64_t x, y;
        return gcdEx(a, Mod, x, y) == 1 ? (x % Mod + Mod) % Mod : -1;
    };

    inline void mul(int64_t *a, int64_t *b, int k)
    { ///下边的线性齐次递推用的.
        fill(c, c + 2 * k, 0);
        for (int i(0); i < k; ++i)
            if (a[i])
                for (int j(0); j < k; ++j)
                    c[i + j] = (c[i + j] + a[i] * b[j]) % Mod;
        for (int i(2 * k - 1); i >= k; --i)
            if (c[i])
                for (size_t j(0); j < Md.size(); ++j)
                    c[i - k + Md[j]] = (c[i - k + Md[j]] - c[i] * md[Md[j]]) % Mod;
        copy(c, c + k, a);
    }
    VI BM(VI s)
    { ///BM算法求模数是质数的递推式子的通项公式,可以单独用
        VI C(1, 1), B(1, 1);
        int L(0), m(1), b(1);
        for (size_t n(0); n < s.size(); ++n)
        {
            int64_t d(0);
            for (int i(0); i <= L; ++i)
                d = (d + (int64_t)C[i] * s[n - i]) % Mod;
            if (!d)
                ++m;
            else
            {
                VI T(C);
                int64_t c(Mod - d * Inv(b, Mod) % Mod);
                while (C.size() < B.size() + m)
                    C.push_back(0);
                for (size_t i(0); i < B.size(); ++i)
                    C[i + m] = (C[i + m] + c * B[i]) % Mod;
                if (2 * L <= (int)n)
                {
                    L = n + 1 - L;
                    B = T;
                    b = d;
                    m = 1;
                }
                else
                    ++m;
            }
        }
        return C;
    }
    int solve(int64_t n, VI A, VI B)
    { //线性齐次递推:A系数,B初值B[n]=A[0]*B[n-1]+...
        ///这里可以可以单独用,给出递推系数和前几项代替矩阵快速幂求递推式第n项.
        int64_t ans(0), cnt(0);
        int k(A.size());
        for (int i(0); i < k; ++i)
            md[k - i - 1] = -A[i];
        md[k] = 1;
        Md.clear();
        for (int i(0); i < k; ++i)
        {
            res[i] = 0;
            if (md[i])
                Md.push_back(i);
        }
        res[0] = 1;
        while ((1LL << cnt) <= n)
            ++cnt;
        for (int p(cnt); ~p; --p)
        {
            mul(res, res, k);
            if ((n >> p) & 1)
            {
                copy(res, res + k, res + 1);
                res[0] = 0;
                for (size_t j(0); j < Md.size(); ++j)
                    res[Md[j]] = (res[Md[j]] - res[k] * md[Md[j]]) % Mod;
            }
        }
        for (int i(0); i < k; ++i)
            ans = (ans + res[i] * B[i]) % Mod;
        return ans + (ans < 0 ? Mod : 0);
    }
    inline static void extand(VI &a, size_t d, int64_t value = 0)
    {
        if (d <= a.size())
            return;
        a.resize(d, value);
    }
    static int64_t CRT(const VI &c, const VI &m)
    { ///中国剩余定理合并
        int n(c.size());
        int64_t M(1), ans(0);
        for (int i = 0; i < n; ++i)
            M *= m[i];
        for (int i = 0; i < n; ++i)
        {
            int64_t x, y, tM(M / m[i]);
            gcdEx(tM, m[i], x, y);
            ans = (ans + tM * x * c[i] % M) % M;
        }
        return (ans + M) % M;
    }

    static VI ReedsSloane(const VI &s, int64_t Mod)
    { ///求模数不是质数的递推式系数
        auto L = [](const VI &a, const VI &b) {
            int da = (a.size() > 1 || (a.size() == 1 && a[0])) ? a.size() - 1 : -1000;
            int db = (b.size() > 1 || (b.size() == 1 && b[0])) ? b.size() - 1 : -1000;
            return max(da, db + 1);
        };
        auto prime_power = [&](const VI &s, int64_t Mod, int64_t p, int64_t e) {
            vector<VI> a(e), b(e), an(e), bn(e), ao(e), bo(e);
            VI t(e), u(e), r(e), to(e, 1), uo(e), pw(e + 1);
            ;
            pw[0] = 1;
            for (int i(pw[0] = 1); i <= e; ++i)
                pw[i] = pw[i - 1] * p;
            for (int64_t i(0); i < e; ++i)
            {
                a[i] = {pw[i]};
                an[i] = {pw[i]};
                b[i] = {0};
                bn[i] = {s[0] * pw[i] % Mod};
                t[i] = s[0] * pw[i] % Mod;
                if (!t[i])
                {
                    t[i] = 1;
                    u[i] = e;
                }
                else
                    for (u[i] = 0; t[i] % p == 0; t[i] /= p, ++u[i])
                        ;
            }
            for (size_t k(1); k < s.size(); ++k)
            {
                for (int g(0); g < e; ++g)
                {
                    if (L(an[g], bn[g]) > L(a[g], b[g]))
                    {
                        int id(e - 1 - u[g]);
                        ao[g] = a[id];
                        bo[g] = b[id];
                        to[g] = t[id];
                        uo[g] = u[id];
                        r[g] = k - 1;
                    }
                }
                a = an;
                b = bn;
                for (int o(0); o < e; ++o)
                {
                    int64_t d(0);
                    for (size_t i(0); i < a[o].size() && i <= k; ++i)
                        d = (d + a[o][i] * s[k - i]) % Mod;
                    if (d == 0)
                    {
                        t[o] = 1;
                        u[o] = e;
                    }
                    else
                    {
                        for (u[o] = 0, t[o] = d; !(t[o] % p); t[o] /= p, ++u[o])
                            ;
                        int g(e - 1 - u[o]);
                        if (!L(a[g], b[g]))
                        {
                            extand(bn[o], k + 1);
                            bn[o][k] = (bn[o][k] + d) % Mod;
                        }
                        else
                        {
                            int64_t coef = t[o] * Inv(to[g], Mod) % Mod * pw[u[o] - uo[g]] % Mod;
                            int m(k - r[g]);
                            extand(an[o], ao[g].size() + m);
                            extand(bn[o], bo[g].size() + m);
                            auto fun = [&](vector<VI> &vn, vector<VI> &vo, bool f) {
                                for (size_t i(0); i < vo[g].size(); ++i)
                                {
                                    vn[o][i + m] -= coef * vo[g][i] % Mod;
                                    if (vn[o][i + m] < 0)
                                        vn[o][i + m] += Mod * (f ? 1 : -1);
                                }
                                while (vn[o].size() && !vn[o].back())
                                    vn[o].pop_back();
                            };
                            fun(an, ao, 1);
                            fun(bn, bo, -1);
                        }
                    }
                }
            }
            return make_pair(an[0], bn[0]);
        };
        vector<tuple<int64_t, int64_t, int>> fac;
        for (int64_t i(2); i * i <= Mod; ++i)
            if (!(Mod % i))
            {
                int64_t cnt(0), pw(1);
                while (!(Mod % i))
                {
                    Mod /= i;
                    ++cnt;
                    pw *= i;
                }
                fac.emplace_back(pw, i, cnt);
            }
        if (Mod > 1)
            fac.emplace_back(Mod, Mod, 1);
        vector<VI> as;
        size_t n = 0;
        for (auto &&x : fac)
        {
            int64_t Mod, p, e;
            VI a, b;
            std::tie(Mod, p, e) = x;
            auto ss = s;
            for (auto &&x : ss)
                x %= Mod;
            std::tie(a, b) = prime_power(ss, Mod, p, e);
            as.emplace_back(a);
            n = max(n, a.size());
        }
        VI a(n), c(as.size()), m(as.size());
        for (size_t i(0); i < n; ++i)
        {
            for (size_t j(0); j < as.size(); ++j)
            {
                m[j] = std::get<0>(fac[j]);
                c[j] = i < as[j].size() ? as[j][i] : 0;
            }
            a[i] = CRT(c, m);
        }
        return a;
    }
    int64_t solve(VI a, int64_t n, int64_t Mod, bool prime = true)
    {
        VI c;
        this->Mod = Mod;
        if (prime)
            c = BM(a); ///如果已经知道系数了,直接输入到c就行了,不用调用BM().
        else
            c = ReedsSloane(a, Mod);
        c.erase(c.begin());
        for (size_t i(0); i < c.size(); ++i)
            c[i] = (Mod - c[i]) % Mod;
        return solve(n, c, VI(a.begin(), a.begin() + c.size()));
    }
};
ll _pow(ll a, ll b, ll Mod)
{
    ll ret = 1LL % Mod;
    ll mul = a % Mod;
    while (b)
    {
        if (b & 1)
            ret = ret * mul % Mod;
        mul = mul * mul % Mod;
        b >>= 1;
    }
    return ret;
};
ll f[2020], sum[2020];

int main()
{
    VI vec;
    vec.clear();
    for (int i = 0; i <= 2000; i++)
        vec.push_back(sum[i]);
    Linear_Seq bmi;
    printf("%lld\n", bmi.solve(vec, n, P, false));
}
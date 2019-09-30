#include <bits/stdc++.h>
using namespace std;
long long Mod;
struct Matrix
{
    long long a[2][2];
    Matrix operator*(const Matrix &b) const
    {
        Matrix tmp;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                tmp.a[i][j] = 0;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                for (int k = 0; k < 2; k++)
                {
                    tmp.a[i][j] += a[i][k] * b.a[k][j];
                    tmp.a[i][j] %= Mod;
                }
        return tmp;
    }
};
Matrix Matrixpow(Matrix x, int b)
{
    Matrix ans1;
    ans1.a[0][0] = 1;
    ans1.a[1][1] = 1;
    ans1.a[1][0] = 0;
    ans1.a[0][1] = 0;
    Matrix ret = x;
    while (b)
    {
        if (b & 1)
            ans1 = ans1 * ret;
        ret = ret * ret;
        b = b / 2;
    }
    return ans1;
}
int main()
{
    ios::sync_with_stdio(false);
    long long x0, x1, a, b;
    cin >> x0 >> x1 >> a >> b;
    string s;
    cin >> s;
    cin >> Mod;
    int len = s.length();
    Matrix ans;
    ans.a[0][0] = 1;
    ans.a[1][1] = 1;
    ans.a[1][0] = 0;
    ans.a[0][1] = 0;
    Matrix mult;
    mult.a[0][0] = a;
    mult.a[0][1] = b;
    mult.a[1][0] = 1;
    mult.a[1][1] = 0;
    for (int i = len - 1; i >= 0; i--)
    {
        ans = ans * Matrixpow(mult, s[i] - '0');
        mult = Matrixpow(mult, 10);
    }
    long long tot = ans.a[1][1] * x0 % Mod + ans.a[1][0] * x1 % Mod;
    tot = tot % Mod;
    cout << tot << endl;
    return 0;
}
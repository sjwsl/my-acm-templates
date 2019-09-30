#include <bits/stdc++.h>
using namespace std;
const int N=1e5+7;

int n,q,p;

long long a[N];

#define ls o * 2, l, m
#define rs o * 2 + 1, m + 1, r
static const long long M = N * 4, RS = 7e18 - 1;
long long addv[M], setv[M], minv[M], maxv[M], sumv[M], mulv[M];
void init()
{
    memset(addv, 0, sizeof addv);
    memset(mulv,0,sizeof(mulv));
    fill(setv, setv + M, RS);
    memset(minv, 0, sizeof minv);
    memset(maxv, 0, sizeof maxv);
    memset(sumv, 0, sizeof sumv);
}
void maintain(int o, int l, int r)
{
    if (l < r)
    {
        long long lc = o * 2, rc = o * 2 + 1;
        sumv[o] = sumv[lc] + sumv[rc];
        minv[o] = min(minv[lc], minv[rc]);
        maxv[o] = max(maxv[lc], maxv[rc]);
    }
    else
        sumv[o] = minv[o] = maxv[o] = 0;
    if (setv[o] != RS)
    {
        minv[o] = maxv[o] = setv[o];
        sumv[o] = setv[o] * (r - l + 1);
    }
    if (addv[o])
    {
        minv[o] += addv[o];
        maxv[o] += addv[o];
        sumv[o] += addv[o] * (r - l + 1);
    }
}
void build(int o, int l, int r)
{
    if (l == r)
        addv[o] = a[l];
    else
    {
        long long m = (l + r) / 2;
        build(ls);
        build(rs);
    }
    maintain(o, l, r);
}
void pushdown(int o)
{
    long long lc = o * 2, rc = o * 2 + 1;
    if (setv[o] != RS)
    {
        setv[lc] = setv[rc] = setv[o];
        addv[lc] = addv[rc] = 0;
        setv[o] = RS;
    }
    if (addv[o])
    {
        addv[lc] += addv[o];
        addv[rc] += addv[o];
        addv[o] = 0;
    }
}
void update(long long p, long long q, long long o, long long l, long long r, long long v, long long op)
{
    if (p <= r && l <= q)
        if (p <= l && r <= q)
        {
            if (op == 2)
            {
                setv[o] = v;
                addv[o] = 0;
            }
            else
                addv[o] += v;
        }
        else
        {
            pushdown(o);
            long long m = (l + r) / 2;
            update(p, q, ls, v, op);
            update(p, q, rs, v, op);
        }
    maintain(o, l, r);
}
void query(long long p, long long q, long long o, long long l, long long r, long long add, long long &ssum, long long &smin, long long &smax)
{  
    if (p > r || l > q)
        return;
    if (setv[o] != RS)
    {
        long long v = setv[o] + add + addv[o];
        ssum += v * (min(r, q) - max(l, p) + 1);
        smin = min(smin, v);
        smax = max(smax, v);
    }
    else if (p <= l && r <= q)
    {
        ssum += sumv[o] + add * (r - l + 1);
        smin = min(smin, minv[o] + add);
        smax = max(smax, maxv[o] + add);
    }
    else
    {
        long long m = (l + r) / 2;
        query(p, q, ls, add + addv[o], ssum, smin, smax);
        query(p, q, rs, add + addv[o], ssum, smin, smax);
    }
}

int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    init();
    build(1,1,n);
    
    while(q--){
        int opt,l,r;
        long long k;
        scanf("%d",&opt);
        if(opt==1){
            scanf("%d%d%lld",&l,&r,&k);
            update(l,r,1,1,n,k,1);
        }
        else {
            scanf("%d%d",&l,&r);
            long long res=0,aa,bb;
            query(l,r,1,1,n,0,res,aa,bb);

            printf("%lld\n",res);
        }
    }
}
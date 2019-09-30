const int maxn = 5e5 + 7;
const int maxp = 21; //最大高度log 1e5->18 1e4->15

int n, m, s;

int fa[maxn], dep[maxn], pa[maxn][maxp];

vector<int> G[maxn];

void dfs(int u, int fa)
{
    pa[u][0] = fa;
    dep[u] = dep[fa] + 1;
    for (int i = 1; i < maxp; i++)
        pa[u][i] = pa[pa[u][i - 1]][i - 1];
    for (int &v : G[u])
    {
        if (v == fa)
            continue;
        dfs(v, u);
    }
}

int lca(int u, int v)
{
    if (dep[u] < dep[v])
        swap(u, v);
    int t = dep[u] - dep[v];
    for (int i = 0; i < maxp; i++)
        if (t & (1 << i))
            u = pa[u][i];
    for (int i = maxp - 1; i >= 0; i--)
    {
        int uu = pa[u][i], vv = pa[v][i];
        if (uu != vv)
        {
            u = uu;
            v = vv;
        }
    }
    return u == v ? u : pa[u][0];
}

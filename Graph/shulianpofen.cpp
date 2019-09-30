//调用predfs(root,1) dfs(root,root) 多组数据把clk赋0
const int N = 1e5 + 7;
vector<int> G[N];
int n, m, s, mod;

int fa[N], dep[N], idx[N], out[N], ridx[N], sz[N], son[N], top[N], v[N], clk;

void predfs(int u, int d)
{
    dep[u] = d;
    sz[u] = 1;
    int &maxs = son[u] = -1;
    for (int &v : G[u])
    {
        if (v == fa[u])
            continue;
        fa[v] = u;
        predfs(v, d + 1);
        sz[u] += sz[v];
        if (maxs == -1 || sz[v] > sz[maxs])
            maxs = v;
    }
}
void dfs(int u, int tp)
{
    top[u] = tp;
    idx[u] = ++clk;
    ridx[clk] = u;
    if (son[u] != -1)
        dfs(son[u], tp);
    for (int &v : G[u])
        if (v != fa[u] && v != son[u])
            dfs(v, v);
    out[u] = clk;
}

void go(int u, int v)
{
    int uu = top[u], vv = top[v];
    while (uu != vv)
    {
        if (dep[uu] < dep[vv])
        {
            swap(uu, vv);
            swap(u, v);
        }
        //do sth. in [idx[uu],idx[u]]
        u = fa[uu];
        uu = top[u];
    }
    if (dep[u] < dep[v])
        swap(u, v);
    //do sth. in [idx[v],idx[u]]
}

int up(int u, int d)
{
    while (d)
    {
        if (dep[u] - dep[top[u]] < d)
        {
            d -= dep[u] - dep[top[u]];
            u = top[u];
        }
        else
            return ridx[idx[u] - d];
        u = fa[u];
        --d;
    }
    return u;
}
int finds(int u, int rt)
{ // 找 u 在 rt 的哪个儿子的子树中
    while (top[u] != top[rt])
    {
        u = top[u];
        if (fa[u] == rt)
            return u;
        u = fa[u];
    }
    return ridx[idx[rt] + 1];
}

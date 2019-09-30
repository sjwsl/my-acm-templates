//求树上长度小于等于k的路径数 

int n, m, k, cnt;

long long ans;

struct edge
{
    int to, d;
};

bool vis[maxn];

int h[maxn];

vector<edge> G[maxn];

int q[maxn], fa[maxn], sz[maxn], mx[maxn], dep[maxn];

void get_dep(int u, int fa, int d)
{
    dep[u] = d;
    h[++cnt] = d;
    for (int i = 0; i < G[u].size(); i++)
    {
        edge e = G[u][i];
        int v = e.to;
        if (vis[v] || v == fa)
            continue;
        get_dep(v, u, d + e.d);
    }
}

int get_rt(int u)
{
    int p = 0, cur = -1;
    q[p++] = u;
    fa[u] = -1;
    while (++cur < p)
    {
        u = q[cur];
        mx[u] = 0;
        sz[u] = 1;
        for (int i = 0; i < G[u].size(); i++)
        {
            edge e = G[u][i];
            if (!vis[e.to] && e.to != fa[u])
                fa[q[p++] = e.to] = u;
        }
    }
    for (int i = p - 1; i >= 0; i--)
    {
        u = q[i];
        mx[u] = max(mx[u], p - sz[u]);
        if (mx[u] * 2 <= p)
            return u;
        sz[fa[u]] += sz[u];
        mx[fa[u]] = max(mx[fa[u]], sz[u]);
    }
}

long long cal(int u, int x)
{
    long long res = 0;
    cnt = 0;
    get_dep(u, -1, 0);
    sort(h + 1, h + 1 + cnt);
    int r = cnt;
    for (int l = 1; l < r; l++)
    {
        while (h[l] + h[r] > x && r > l)
            r--;
        res += r - l;
    }
    return res;
}

void dfs(int u)
{
    u = get_rt(u);
    vis[u] = true;
    ans += cal(u, k);
    for (int i = 0; i < G[u].size(); i++)
    {
        edge e = G[u][i];
        int v = e.to;
        if (vis[v])
            continue;
        ans -= cal(v, k - e.d * 2);
        dfs(v);
    }
}
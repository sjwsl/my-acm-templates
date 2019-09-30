const int maxn = 2e4 + 7;

int n, m, top;

vector<int> G[maxn];

int st[maxn], pre[maxn], low[maxn], sccno[maxn], clk, cnt;

void dfs(int u)
{
    pre[u] = low[u] = ++clk;
    st[++top] = u;
    for (int &v : G[u])
    {
        if (!pre[v])
        {
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
        else if (!sccno[v])
            low[u] = min(low[u], pre[v]);
    }
    if (low[u] == pre[u])
    {
        cnt++;
        for (;;)
        {
            int x = st[top--];
            sccno[x] = cnt;
            if (u == x)
                break;
        }
    }
}

void find_scc(int n)
{
    clk = cnt = top = 0;
    memset(sccno, 0, sizeof(sccno));
    memset(pre, 0, sizeof(pre));
    for (int i = 1; i <= n; i++)
    {
        if (!pre[i])
            dfs(i);
    }
}
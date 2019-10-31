struct MaxMatch {
    int n, m;
    vector<int> G[N];
    int vis[N], left[N], clk;

    void addedge(int u, int v) {
        G[u].push_back(v);
    }

    //共n个点 前m个点是左边的 也可以全当成左边的跑 结果一样
    void init(int n, int m) {
        this->n = n;
        this->m = m;
        for (int i = 0; i <= n; i++)G[i].clear();
        memset(left, -1, sizeof left);
        memset(vis, -1, sizeof vis);
    }

    bool dfs(int u) {
        for (int v: G[u])
            if (vis[v] != clk) {
                vis[v] = clk;
                if (left[v] == -1 || dfs(left[v])) {
                    left[v] = u;
                    return true;
                }
            }
        return false;
    }

    int match() {
        int ret = 0;
        for (clk = 0; clk <= m; ++clk)
            if (dfs(clk)) ++ret;
        return ret;
    }

} MM;
void dfs(int u, int fa) {
    vis[u] = 1;
    f[u] = fa;
    dep[u] = dep[fa] + 1;
    for (auto v:e[u]) {
        if (v == fa)continue;
        if (vis[v]) {
            if (dep[u] < dep[v])continue;
            int cnt = 1;
            int x = u;
            while (x != v) {
                cnt++;
                x = f[x];
            }
            // cnt:环的长度
        } else dfs(v, u);
    }
}


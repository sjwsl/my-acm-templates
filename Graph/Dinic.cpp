struct edge {
    int to, nxt, c;
} e[maxm << 1]

void add(int a, int b, int c) {
    e[pos].to = b, e[pos].nxt = head[a], e[pos].c = c;
    head[a] = pos;
    pos++;
}

bool bfs() {
    while (!q.empty())q.pop();
    for (int i = 1; i <= n; i++)
        vis[i] = 0;
    d[s] = 1;
    vis[s] = 1;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = e[i].nxt) {
            int v = e[i].to;
            if (vis[v] || e[i].c <= 0)continue;
            d[v] = d[u] + 1;
            vis[v] = 1;
            q.push(v);
        }
    }
    return vis[t];
}

int dfs(int u, int a) {
    if (u == t || a == 0)return a;
    int f, flow = 0;
    for (int &i = cur[u]; i != -1; i = e[i].nxt) {
        int v = e[i].to;
        if (d[v] == d[u] + 1 && (f = dfs(v, min(a, e[i].c))) > 0) {
            e[i].c -= f;
            e[i ^ 1].c += f;
            flow += f;
            a -= f;
            if (a == 0)break;
        }
    }
    return flow;
}

int dinic() {
    int ans = 0;
    while (bfs()) {
        for (int i = 1; i <= n; i++)
            cur[i] = head[i];
        ans += dfs(s, inf);
    }
    return ans;
}
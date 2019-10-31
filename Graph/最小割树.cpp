//无向图上任意两点的最小割 预处理复杂度为n次最大流

#include<bits/stdc++.h>

using namespace std;
int n, m, node[505], dep[505], fa[505][10], mn[505][10];
int cnt, top[505], to[1005], len[1005], nex[1005];

int read() {
    int re = 0;
    char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) re = (re << 3) + (re << 1) + ch - '0', ch = getchar();
    return re;
}

void add_edge(int x, int y, int z) {
    to[++cnt] = y, len[cnt] = z, nex[cnt] = top[x], top[x] = cnt;
    to[++cnt] = x, len[cnt] = z, nex[cnt] = top[y], top[y] = cnt;
}

namespace GHT {
    int s, t;
    int tot, cur[505], dep[505], col[505], col_bucket[505];
    int cnt = 1, top[505], to[3005], cap[3005], flow[3005], nex[3005];

    void add_edge(int x, int y, int z) {
        to[++cnt] = y, cap[cnt] = z, flow[cnt] = 0, nex[cnt] = top[x], top[x] = cnt;
        to[++cnt] = x, cap[cnt] = z, flow[cnt] = 0, nex[cnt] = top[y], top[y] = cnt;
    }

    bool BFS() {
        memset(cur, 0, sizeof cur);
        memset(dep, 0, sizeof dep);
        dep[s] = 1, cur[s] = top[s];
        queue<int> Q;
        Q.push(s);
        while (!Q.empty()) {
            int now = Q.front();
            Q.pop();
            for (int i = top[now]; i; i = nex[i])
                if (!dep[to[i]] && cap[i] > flow[i]) {
                    dep[to[i]] = dep[now] + 1;
                    cur[to[i]] = top[to[i]];
                    Q.push(to[i]);
                }
        }
        return dep[t] != 0;
    }

    int DFS(int now, int rest) {
        if (now == t) return rest;
        int re = 0;
        for (int &i = cur[now]; i; i = nex[i])
            if (dep[to[i]] == dep[now] + 1 && cap[i] > flow[i]) {
                int lzq = DFS(to[i], min(rest, cap[i] - flow[i]));
                if (lzq) {
                    rest -= lzq, re += lzq;
                    flow[i] += lzq, flow[i ^ 1] -= lzq;
                    if (!rest) break;
                }
            }
        return re;
    }

    int Dinic(int x, int y) {
        int re = 0;
        s = x, t = y;
        for (int i = 1; i <= cnt; i++) flow[i] = 0;
        while (BFS()) re += DFS(s, 0x3f3f3f3f);
        return re;
    }

    void get_color(int now, int color) {
        col[now] = color;
        for (int i = top[now]; i; i = nex[i])
            if (cap[i] > flow[i] && col[to[i]] != color)
                get_color(to[i], color);
    }

    void build(int l, int r) {
        if (l == r) return;
        int x = node[l], y = node[l + 1];
        int cut = Dinic(x, y);
        get_color(x, ++tot);
        int L = l, R = r;
        for (int i = l; i <= r; i++)
            if (col[node[i]] == tot) col_bucket[L++] = node[i];
            else col_bucket[R--] = node[i];
        for (int i = l; i <= r; i++) node[i] = col_bucket[i];
        ::add_edge(x, y, cut);
        build(l, L - 1);
        build(R + 1, r);
    }
}

void dfs(int now) {
    for (int i = 1; i <= 9; i++) {
        fa[now][i] = fa[fa[now][i - 1]][i - 1];
        mn[now][i] = min(mn[now][i - 1], mn[fa[now][i - 1]][i - 1]);
    }
    for (int i = top[now]; i; i = nex[i]) {
        if (to[i] == fa[now][0]) continue;
        dep[to[i]] = dep[now] + 1, fa[to[i]][0] = now, mn[to[i]][0] = len[i];
        dfs(to[i]);
    }
}

int getcut(int x, int y) {
    int re = INT_MAX;
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = 9; i >= 0; i--) if (dep[fa[x][i]] >= dep[y]) re = min(re, mn[x][i]), x = fa[x][i];
    if (x == y) return re;
    for (int i = 9; i >= 0; i--)
        if (fa[x][i] != fa[y][i])
            re = min(re, min(mn[x][i],
                             mn[y][i])), x = fa[x][i], y = fa[y][i];
    return min(re, min(mn[x][0], mn[y][0]));
}

int main() {
    n = read(), m = read();
    while (m--) {
        int x = read(), y = read(), z = read();
        GHT::add_edge(x, y, z);
    }
    for (int i = 1; i <= n; i++) node[i] = i;
    GHT::build(1, n);
    dep[1] = 1;
    dfs(1);
    m = read();
    while (m--) {
        int x = read(), y = read();
        printf("%d\n", getcut(x, y));
    }
    return 0;
}
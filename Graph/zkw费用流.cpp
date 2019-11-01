//不能用于负权图！！！
//在正权图上一般都比普通费用流快不少

struct E {
    int to, cp, v;

    E() {}

    E(int to, int cp, int v) : to(to), cp(cp), v(v) {}
};

struct MCMF {
    int n, m, s, t, cost, D;
    vector<E> edges;
    vector<int> G[N];
    bool vis[N];

    void init(int _n, int _s, int _t) {
        n = _n;
        s = _s;
        t = _t;
        for (int i = 0; i <= n; i++) G[i].clear();
        edges.clear();
        m = 0;
    }

    void addedge(int from, int to, int cap, int cost) {
        edges.emplace_back(to, cap, cost);
        edges.emplace_back(from, 0, -cost);
        G[from].push_back(m++);
        G[to].push_back(m++);
    }

    int aug(int u, int cp) {
        if (u == t) {
            cost += D * cp;
            return cp;
        }
        vis[u] = true;
        int tmp = cp;
        for (int idx : G[u]) {
            E &e = edges[idx];
            if (e.cp && !e.v && !vis[e.to]) {
                int f = aug(e.to, min(cp, e.cp));
                e.cp -= f;
                edges[idx ^ 1].cp += f;
                cp -= f;
                if (!cp)
                    break;
            }
        }
        return tmp - cp;
    }

    bool modlabel() {
        int d = INF;
        for (int u = 0; u <= n; u++)
            if (vis[u])
                for (int &idx : G[u]) {
                    E &e = edges[idx];
                    if (e.cp && !vis[e.to])
                        d = min(d, e.v);
                }
        if (d == INF)
            return false;
        for (int u = 0; u <= n; u++)
            if (vis[u])
                for (int &idx : G[u]) {
                    edges[idx].v -= d;
                    edges[idx ^ 1].v += d;
                }
        D += d;
        return true;
    }

    ll go() {
        cost = D = 0;
        int flow = 0;
        while (true) {
            memset(vis, 0, sizeof vis);
            int t = aug(s, INF);
            if (!t && !modlabel())
                break;
            flow += t;
        }
        return cost;
    }
} MM;
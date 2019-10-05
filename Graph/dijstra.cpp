struct edge {
    int v, d;
};

struct node {
    int d, u;

    bool operator<(const node &x) const {
        return d > x.d;
    }
};

vector <edge> e[maxn];

void add(int u, int v, int d) {
    e[u].push_back(edge{v, d});
}


int dij(int s, int nd) {
    priority_queue <node> q;
    for (int i = 0; i <= N; i++)d[i] = inf;
    d[s] = 0;
    pre[s] = -1;
    q.push(node{0, s});
    while (!q.empty()) {
        node x = q.top();
        q.pop();
        int u = x.u;
        if (vis[u])continue;
        vis[u] = 1;
        for (auto E:e[u]) {
            if (d[E.v] > d[u] + E.d) {
                d[E.v] = d[u] + E.d;
                pre[E.v] = u;
                q.push(node{d[E.v], E.v});
            }
        }
    }
}
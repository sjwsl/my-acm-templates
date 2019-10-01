//
const int maxn = 1e3 + 7;

struct edge {
    int u, v;
};

int n, m, cnt;

stack <edge> st;

int pre[maxn], iscut[maxn], bccno[maxn], clk, bcc_cnt;

vector<int> G[maxn], bcc[maxn];

void init() {
    for (int i = 1; i <= n; i++)G[i].clear();
    n = 0;
}

int dfs(int u, int fa) {
    int lowu = pre[u] = ++clk;
    int child = 0;
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        edge e = edge{u, v};
        if (!pre[v]) {
            st.push(e);
            child++;
            int lowv = dfs(v, u);
            lowu = min(lowu, lowv);
            if (lowv >= pre[u]) {
                iscut[u] = 1;
                bcc[++bcc_cnt].clear();
                for (;;) {
                    edge x = st.top();
                    st.pop();
                    if (bccno[x.u] != bcc_cnt) {
                        bcc[bcc_cnt].push_back(x.u);
                        bccno[x.u] = bcc_cnt;
                    }
                    if (bccno[x.v] != bcc_cnt) {
                        bcc[bcc_cnt].push_back(x.v);
                        bccno[x.v] = bcc_cnt;
                    }
                    if (x.u == u && x.v == v)break;
                }
            }
        } else if (pre[v] < pre[u] && v != fa) {
            st.push(e);
            lowu = min(lowu, pre[v]);
        }
    }
    if (fa < 0 && child == 1)iscut[u] = 0;
    return lowu;
}

void find_bcc(int n) {
    memset(pre, 0, sizeof(pre));
    memset(iscut, 0, sizeof(iscut));
    memset(bccno, 0, sizeof(bccno));
    clk = bcc_cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (!pre[i])dfs(i, -1);
    }
}
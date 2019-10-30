//
//n^3
//



const int maxn = 305;
const int INF = 0x3f3f3f3f;
int match[maxn], lx[maxn], ly[maxn], slack[maxn];
int G[maxn][maxn];
bool visx[maxn], visy[maxn];
int n, nx, ny, ans;

bool findpath(int x) {
    int tempDelta;

    visx[x] = true;
    for (int y = 0; y < ny; ++y) {
        if (visy[y]) continue;
        tempDelta = lx[x] + ly[y] - G[x][y];
        if (tempDelta == 0) {//(x,y)在相等子图中
            visy[y] = true;
            if (match[y] == -1 || findpath(match[y])) {
                match[y] = x;
                return true;
            }
        } else if (slack[y] > tempDelta)
            slack[y] = tempDelta;//(x,y)不在相等子图中且y不在交错树中
    }
    return false;
}

void KM() {

    for (int x = 0; x < nx; ++x) {
        for (int j = 0; j < ny; ++j) slack[j] = INF;//这里不要忘了，每次换新的x结点都要初始化slack
        while (true) {
            memset(visx, false, sizeof(visx));
            memset(visy, false, sizeof(visy));//这两个初始化必须放在这里,因此每次findpath()都要更新
            if (findpath(x)) break;
            else {
                int delta = INF;
                for (int j = 0; j < ny; ++j)//因为dfs(x)失败了所以x一定在交错树中，y不在交错树中，第二类边
                    if (!visy[j] && delta > slack[j])
                        delta = slack[j];
                for (int i = 0; i < nx; ++i)
                    if (visx[i]) lx[i] -= delta;
                for (int j = 0; j < ny; ++j) {
                    if (visy[j])
                        ly[j] += delta;
                    else
                        slack[j] -= delta;
                    //修改顶标后，要把所有的slack值都减去delta
                    //这是因为lx[i] 减小了delta
                    //slack[j] = min(lx[i] + ly[j] -w[i][j]) --j不属于交错树--也需要减少delta，第二类边
                }
            }
        }
    }
}

void solve() {

    memset(match, -1, sizeof(match));
    memset(ly, 0, sizeof(ly));
    for (int i = 0; i < nx; ++i) {
        lx[i] = -INF;
        for (int j = 0; j < ny; ++j)
            if (lx[i] < G[i][j])
                lx[i] = G[i][j];
    }
    KM();
}
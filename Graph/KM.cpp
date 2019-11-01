//最大权完美匹配
//最大权时把不存在的边当作0 最小权时边权取反 把不存在的边当作-INF

const int maxn = 220;
const int MAXINT = 1e9 + 7;

int n, cst[maxn + 5][maxn + 5];
int Lx[maxn + 5], Ly[maxn + 5], MINs[maxn + 5], who[maxn + 5];
bool S[maxn + 5], T[maxn + 5];


bool Find(int x) //为x找匹配
{
    S[x] = true;
    for (int i = 1; i <= n; i++)
        if (!T[i]) {
            int s = Lx[x] + Ly[i] - cst[x][i];
            if (!s) //这条边可以走
            {
                T[i] = true;
                if (!who[i] || Find(who[i])) {
                    who[i] = x;
                    return true;
                }
            } else
                MINs[i] = min(MINs[i], s); //不可以走，修正松弛量
        }
    return false;
}

int KM() {
    memset(Ly, 0, sizeof(Ly));
    for (int i = 1; i <= n; i++) Lx[i] = -MAXINT;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            Lx[i] = max(Lx[i], cst[i][j]); //初始可行顶标
    memset(who, 0, sizeof(who));
    for (int now = 1; now <= n; now++) //为每一个x找匹配
    {
        for (int i = 1; i <= n; i++) MINs[i] = MAXINT;
        while (true) //直到匹配成功为止
        {
            memset(S, 0, sizeof(S));
            memset(T, 0, sizeof(T));
            if (Find(now)) break; //匹配成功
            int MIN = MAXINT;
            for (int i = 1; i <= n; i++) if (!T[i]) MIN = min(MIN, MINs[i]);
            //刷出MIN
            for (int i = 1; i <= n; i++) {
                if (S[i]) Lx[i] -= MIN; //均减少MIN
                if (T[i]) Ly[i] += MIN;
                else //均加上MIN
                    MINs[i] -= MIN; //由于S[i]=true的Lx[i]都减少MIN了，所以松弛量减少MIN
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) ans += cst[who[i]][i]; //答案
    return ans;
}
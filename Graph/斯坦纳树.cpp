#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;
typedef long long int ll;
const int maxm = 1010;
const int maxn = 35;
const ll INF = 1e18;
struct Node {
    int end, next, value;
} Map[maxm * 2];
struct Point {
    int i, be;        //i  所有点中的位置   be  根中的位置
} N[maxn];
int head[maxm], sum;
int n, m;
ll dp[maxn][maxm], bin[maxn], ans;
int lin[maxn], Li;
bool vis[maxn];
map<string, int> num;
queue<int> q;

void addedge(int start, int end, int value) {
    Map[sum].end = end;
    Map[sum].next = head[start];
    Map[sum].value = value;
    head[start] = sum++;
    Map[sum].end = start;
    Map[sum].next = head[end];
    Map[sum].value = value;
    head[end] = sum++;
}

void Init() {
    memset(vis, false, sizeof(vis));
    memset(head, -1, sizeof(head));
    for (int i = 0; i < bin[8]; i++)
        for (int j = 1; j <= n; j++)
            dp[j][i] = INF;
    sum = 0;
    return;
}

void spfa(int s) {
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = false;
        //	cout<<now<<"--------"<<endl;
        for (int i = head[now]; i != -1; i = Map[i].next)
            if (dp[Map[i].end][s] > dp[now][s] + Map[i].value) {
                //		cout<<now<<" -> "<<Map[i].end<<endl;
                dp[Map[i].end][s] = dp[now][s] + Map[i].value;
                if (vis[Map[i].end] == false) {
                    vis[Map[i].end] = true;
                    q.push(Map[i].end);
                }
            }
    }
}

ll cho[maxn], book[maxn];
bool v[maxn];

void dfs2(int cnt, int sum, ll pos)    //起点,数量,和
{
    if (cnt == 8) {
        ll s = 0;
        for (int i = 1; i <= sum; i++) {
            s += dp[N[cho[i]].i][book[i]];
            //		cout<<cho[i]<<" "<<book[i]<<" ";
        }
        //	cout<<endl;
        if (ans > s) {
            ans = s;
            //			cout<<pos<<endl;
            //			for (int i=1;i<=sum;i++)
            //			 	cout<<N[cho[i]].i<<" "<<book[i]<<" "<<dp[N[cho[i]].i][book[i]]<<endl;
            //			cout<<endl;
        }
        return;
    }
    for (int i = 1; i <= sum; i++)
        if (pos & bin[cnt] || pos & bin[cnt ^ 1]) dfs2(cnt + 1, sum, pos);    //不能选择同一对的点
        else {
            book[i] += bin[cnt] + bin[cnt ^ 1];        //某个状态选了一个点，就要选择同一对点的另一个点
            pos += bin[cnt] + bin[cnt ^ 1];
            dfs2(cnt + 1, sum, pos);
            book[i] -= (bin[cnt] + bin[cnt ^ 1]);
            pos -= (bin[cnt] + bin[cnt ^ 1]);
        }
}

void dfs1(int cnt, int sum, int pos)        //起点,数量   找sum个点
{
    if (cnt == sum + 1) {
        ll c = 0;
        for (int i = 1; i <= sum; i++) {
            book[i] = bin[N[cho[i]].be] + bin[N[cho[i]].be ^ 1];
            c += book[i];
            //		cout<<N[cho[i]].i<<" "<<"="<<book[i]<<" ";
        }
        //	cout<<endl;
        dfs2(0, sum, c);
        return;
    }
    for (int i = pos; i < 8; i++)
        if (cnt == 1) {
            cho[cnt] = i;
            dfs1(cnt + 1, sum, i + 1);
        } else if (N[i].be != (N[cho[cnt - 1]].be ^ 1)) {
            cho[cnt] = i;
            dfs1(cnt + 1, sum, i + 1);
        }
    return;
}

int main() {
    cin >> n >> m;
    string s, t;
    int en;
    int w;
    for (int i = 1; i <= n; i++) {
        cin >> s;
        num[s] = i;
    }
    bin[0] = 1;
    for (int i = 1; i <= 31; i++) bin[i] = bin[i - 1] << 1;
    Init();
    for (int i = 1; i <= m; i++) {
        cin >> s >> t >> w;
        addedge(num[s], num[t], w);
    }
    Li = 0;
    for (int i = 0; i < 4; i++) {
        cin >> s >> t;
        dp[num[s]][bin[i * 2]] = 0;
        dp[num[t]][bin[i * 2 + 1]] = 0;
        N[i * 2].be = Li++;
        N[i * 2].i = num[s];
        N[i * 2 + 1].be = Li++;
        N[i * 2 + 1].i = num[t];
    }
    for (int k = 1; k < bin[8]; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = k & (k - 1); j; j = (j - 1) & k)
                dp[i][k] = min(dp[i][k], dp[i][j] + dp[i][k ^ j]);
            if (dp[i][k] != INF && vis[i] == false) {
                q.push(i);
                vis[i] = true;
            }
        }
        spfa(k);
    }
    ans = INF;
    cho[0] = -1;
    for (int i = 1; i <= 4; i++)
        dfs1(1, i, 0);
    cout << ans << endl;
    return 0;
}


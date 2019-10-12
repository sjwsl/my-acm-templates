#include <bits/stdc++.h>

using namespace std;

const int N = 10000;

struct Edge {
    int u, v;

    int get_other(int i) {
        if (i == u)return v;
        return u;
    }

};

int n;
int S[N << 1], top, deg[N];
vector<int> path;
Edge edges[N << 1];
set<int> to[N];

void DFS(int x) {
    for(auto a=to[x].begin();a!=to[x].end();a=to[x].begin()){//auto类型为C++11标准，可进行自动类型推断
        int u=*a;
        to[x].erase(u);
        to[u].erase(x);//删边
        DFS(u);//递归
    }
    S[top++] = x;
}

void fleury(int start) {
    DFS(start);
    while (top) {
        int u = S[--top];
        path.push_back(u);
    }
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        char x, y;
        cin >> x >> y;
        to[x].insert(y);
        to[y].insert(x);
        deg[x]++;
        deg[y]++;
        //edges[i] = Edge{x, y};
    }

    int cnt = 0;

    for (int i = 'A'; i <= 'z'; i++) {
        if (deg[i] & 1) {
            cnt++;
            //cout<<"No Solution";
        }
    }

    if (cnt != 0 && cnt != 2) {
        cout << "No Solution";
        return 0;
    }

    for (int i = 'A'; i <= 'z'; i++) {
        if (cnt == 0 && deg[i]) {
            fleury(i);
            break;
        }
        if (cnt && deg[i] % 2 == 1) {
            fleury(i);
            break;
        }
    }

    //reverse(path.begin(), path.end());

    for (auto u:path) {
        cout << (char) u;
    }
}
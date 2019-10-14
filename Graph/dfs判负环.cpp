/*
判负环比bfs快很多
*/

#include<bits/stdc++.h>
using namespace std;

const int maxn=1e5+7;

struct edge{
    int v,d;
};

int n,m,in[maxn],vis[maxn],dis[maxn];

vector<edge> e[maxn];

int dfs(int u){
    in[u]=1;
    vis[u]=1;
    for(auto E:e[u]){
        if(dis[E.v]>dis[u]+E.d){
            if(in[E.v]){
                in[u]=0;
                return 0;
            }
            else {
                dis[E.v]=dis[u]+E.d;
                int f=dfs(E.v);
                if(!f){
                    in[u]=0;
                    return 0;
                }
            }
        }
    }
    in[u]=0;
    return 1;
}

//是否存在负环
int judge(){
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            dis[i]=0;
            if(!dfs(i))return 0;
        }
    }
    return 1;
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,d;
        cin>>u>>v>>d;
        e[u].push_back(edge{v,d});
        //e[v].push_back(edge{u,d});
    }
    cout<<judge();
}
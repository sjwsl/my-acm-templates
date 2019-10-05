//cnt[i]表示节点i表示的本质不同的串的个数（建树时求出的不是完全的，最后count()函数跑一遍以后才是正确的）
#include<bits/stdc++.h>
using namespace std;
const int maxa=2e5+20,cha=30,MAXN=1e6+20;//maxa 字符串最长长度，cha 字符集大小 
typedef long long ll;
struct SAM{
    int cnt,las,root;
    int ch[MAXN][30],fa[MAXN],len[MAXN];
      
    inline void init(){root = las = ++cnt;}
      
    inline void insert(int x){
        int p = las;
        int np = las = ++cnt;
        len[np] = len[p] + 1;
        for(;p && !ch[p][x];p = fa[p]) ch[p][x] = np;
        if(!p) fa[np] = root;
        else{
            int q = ch[p][x];
            if(len[q] == len[p] + 1) fa[np] = q;
            else {
                int nq = ++cnt;
                fa[nq] = fa[q];fa[q] = fa[np] = nq;
                memcpy(ch[nq],ch[q],sizeof(ch[nq]));
                len[nq] = len[p] + 1;
                for(;p && ch[p][x] == q;p = fa[p]) ch[p][x] = nq;
            }
        }
    }
    inline long long sum(int x){
        return len[x] - len[fa[x]];
    }
}T;
char str[maxa];
ll ans=0;
int main()
{
    scanf("%s",str);
    int len=strlen(str);
     
    ll ans=0;
    T.init();
    for(int i = 0;i < len;i++) T.insert(str[i] - 'a');
    T.las = T.root;
    for(int i = len-1;i >=0;i--) T.insert(str[i] - 'a');
    for(int i = 0;i <= T.cnt;i++) ans = ans + T.sum(i);

    return 0;
}
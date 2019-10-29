#include<bits/stdc++.h>
const int Maxn=5e4+20;
using namespace std;
int a[Maxn];
struct L_B{
    long long d[35];  //若为LL,开63++;
    L_B(){
        memset(d,0,sizeof(d));
    }
    void init(){
        memset(d,0,sizeof(d));
    }
    void insert(int x) {
        for (int i = 32; i >= 0; i--) {  //or 64
            if (x&(1 << i)) {
                if (!d[i]) { d[i] = x; break; }
                x ^= d[i];
            }
        }
    }
    bool check(int x) {
        for (int i = 32; i >= 0; i--) {
            if (x&(1 << i)) x ^= d[i];
        }
        return x == 0;
    }
    L_B operator+(const L_B &b)const
    {
        L_B ret=b;
        for(int i=32; i>=0; i--)
            if(d[i])ret.insert(d[i]);
        return ret;
    }
	int Query(){
		int ret=0;
		for(int i=32;i>=0;i--){
			if((ret^(d[i]))>ret)
				ret^=(d[i]);
		}
		return ret;
	}
}tree[(Maxn)<<2];

void build(int o,int l,int r,int k){
    tree[o].init();
    if (l==r) {
          tree[o].insert((~k)&a[l]);
    }
    else{
        int mid=(l+r)/2;
        build(o<<1,l,mid,k);
        build(o<<1|1,mid+1,r,k);
        tree[o]=tree[o<<1]+tree[o<<1|1];
    }
}
L_B query(int o,int l,int r,int ql,int qr){
    if (ql<=l&&qr>=r) return tree[o];
    int mid=(l+r)/2;
    L_B ans;
    if (ql<=mid) ans=ans+query(o<<1,l,mid,ql,qr);
    if (qr>=mid+1) ans=ans+query(o<<1|1,mid+1,r,ql,qr);
    return ans;
}
int main(){
   int T;
   scanf("%d",&T);
   while(T--){
       int n,m,k;
       scanf("%d%d%d",&n,&m,&k);
       for (int i=1;i<=n;i++)
           scanf("%d",&a[i]);
       build(1,1,n,k);
       while(m--){
           int l,r;
           scanf("%d%d",&l,&r);
           int t=query(1,1,n,l,r).Query();
           printf("%d\n",t|k);
       }
   }
    return 0;
}
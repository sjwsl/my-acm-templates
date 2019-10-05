//num[i]表示以节点i表示的最长回文串的最右端点为回文串结尾的回文串个数
#include<bits/stdc++.h>
using namespace std;
const int maxa=2e5+20,cha=30,MAXN=1e6+20;//maxa 字符串最长长度，cha 字符集大小 
typedef long long ll;
struct PalindromicTree
{
    int next[maxa][cha],fail[maxa],cnt[maxa],len[maxa],num[maxa];
    int tot,s[maxa],p,last;
    int newnode(int l)
    {
        for(int i=0;i<cha;i++) next[p][i]=0;
        len[p]=l;
        cnt[p]=num[p]=0;
        return p++;
    }
    void init()
    {
        tot=p=last=0;
        s[0]=-1,fail[0]=1;//0为存储 偶数回文串 树根节点，1为存储 奇数回文串 树根节点
        newnode(0);/*p==0,偶数回文串树根节点编号为0,len值为0*/
        newnode(-1);/*p==1,奇数回文串树根节点编号为1,len值为-1*/
    }
    int getfail(int x)
    {
        while(s[tot-len[x]-1]!=s[tot]) x=fail[x];
        return x;
    }
    void insert(char c)
    {
        c-='a';
        s[++tot]=c;
        int cur=getfail(last);
        if(!next[cur][c])
        {
            int now=newnode(len[cur]+2);
            fail[now]=next[getfail(fail[cur])][c];
            next[cur][c]=now;
            num[now]=num[fail[now]]+1;
        }
        last=next[cur][c];
        cnt[last]++;
    }
    void makecnt() //统计本质相同的回文串的出现次数
    {
        for(int i=p-1;i>=2;i--) cnt[fail[i]]+=cnt[i];//根节点cnt无意义，i>=2即可 
    }
}pt;
char str[maxa];
ll ans=0;
int main()
{
    scanf("%s",str);
    int len=strlen(str);
    pt.init();
    for(int i=0;i<len;i++) pt.insert(str[i]);
    pt.makecnt();
    cout<<(pt.p-1)/2<<endl;
    return 0;
}
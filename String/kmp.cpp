
// 数组为0 - n-1 时 ，nxt[1 - n]是有意义的
// nxt[i] 为满足 x[i-z...i-1]=x[0...z-1] 的最大 z 值
// len = i-nxt[i]为s[0 - i-1]的最小循环节（可能是aaabbbaaab这种不完整的循环） 如果i mod len = 0 才一定是aaabbbaaabbb这种完整循环串
void kmp_pre(int nxt[], int m, char t[]) {
    int i, j;
    j = nxt[0] = -1;
    i = 0;
    while (i < m) {
        while (-1 != j && t[i] != t[j])j = nxt[j];
        nxt[++i] = ++j;
    }
}

//用t匹配s position中存所有成功匹配的起点
void kmp(int nxt[], int n, int s[], int m, int t[]) {
    for (int i = 0, j = 0; i < n; i++) {
        if (j < n && s[i] == t[j]) {
            j++;
        } else {
            while (j > 0) {
                j = nxt[j];
                if (s[i] == t[j]) {
                    j++;
                    break;
                }
            }
        }
        if (j == m)position.push_back(i - m + 1);
    }
}

例题

/*
 * poj2752
 * 求字符串的所有相等前后缀
 */

#include<cstdio>
#include<cstring>
#include <vector>

using namespace std;

const int maxn = 4e5 + 7;

int nxt[maxn];

char s[maxn];

void kmp_pre(int nxt[], int m, char t[]) {
    int i, j;
    j = nxt[0] = -1;
    i = 0;
    while (i < m) {
        while (-1 != j && t[i] != t[j])j = nxt[j];
        nxt[++i] = ++j;
    }
}

int main() {
    while (scanf("%s", s) == 1) {
        kmp_pre(nxt, strlen(s), s);
        int now = strlen(s);
        vector<int> ans;
        while (now != -1) {
            ans.push_back(now);
            now = nxt[now];
        }
        for (int i = ans.size() - 2; i >= 0; i--) {
            printf("%d", ans[i]);
            if (i)putchar(' ');
        }
        printf("\n");
    }
}

//
// 求num数组 num[i]表示有s[0 - i-1]有多少不重叠的相等前后缀
// Created by 徐天舒 on 2019/10/6.
//

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6 + 7;
const int mod = 1e9 + 7;

int nxt[maxn], len, dep[maxn], mem[maxn], ans = 1;
char s[maxn];

void kmp_pre(int nxt[], int m, char t[]) {
    int i, j;
    j = nxt[0] = -1;
    i = 0;
    while (i < m) {
        while (-1 != j && t[i] != t[j])j = nxt[j];
        nxt[++i] = ++j;
        dep[i] = dep[j] + 1;
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%s", s);
        memset(mem, -1, sizeof(mem));
        int len = strlen(s);
        kmp_pre(nxt, len, s);
        ans = 1;

        int j = 0;

        for (int i = 1; i < len; i++) {
            while (j != -1 && s[j] != s[i])j = nxt[j];
            j++;
            while (j * 2 > i + 1)j = nxt[j];
            ans = 1LL * ans * (dep[j] + 1) % mod;
        }
        printf("%d\n", ans);
    }
}

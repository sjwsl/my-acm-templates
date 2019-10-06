
// 数组为0 - n-1 时 ，nxt[1 - n]是有意义的
// nxt[i] 为满足 x[i-z...i-1]=x[0...z-1] 的最大 z 值
// len = i-nxt[i]为s[0 - i-1]的最小循环节（可能是aaabbbaaab这种不完整的循环） 如果i mod len = 0 才一定是aaabbbaaabbb这种完整循环串
void kmp_pre(char nxt[], int m, char t[]) {
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
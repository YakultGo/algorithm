const int MAXN = 6e5 + 10;
int a[MAXN], f[MAXN][24];

int func(int a, int b) {
    return max(a, b);
}
void init(int n) {
    for (int i = 1; i <= n; i++) f[i][0] = a[i];
    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            f[i][j] = func(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int query(int l, int r) {
    int k = 31 - __builtin_clz(r - l + 1);
    return func(f[l][k], f[r - (1 << k) + 1][k]);
}
P3865 【模板】ST 表 https://www.luogu.com.cn/problem/P3865

```c++
int a[100010], lg[100010], f[100010][20];
void newSt(int n) {
    lg[1] = 0;
    for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
    for (int j = 1; j <= lg[n]; j++) {
        for (int i = 1; i <= n - (1 << j) + 1; i++) {
            f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
        }
    }
}
int query(int x, int y) {
    int l = lg[y - x + 1];
    return max(f[x][l], f[y - (1 << l) + 1][l]);
}
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> f[i][0];
    newSt(n);
    for (int i = 1; i <= m; i++) {
        int x,y;
        cin >> x >> y;
        cout << query(x, y) << "\n";
    }
}
```


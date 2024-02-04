#### LCA模板

```c++
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;

void solve() {
    int n, m, s;
    cin >> n >> m >> s;
    // 建树
    vector<int> g[n + 1];
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    // 预处理
    vector<int> dep(n + 1);
    vector<vector<int>> pa(20, vector<int>(n + 1));
    function<void(int, int, int)> dfs = [&](int u, int fa, int d) {
        dep[u] = d;
        for (int i = 0; i < 20; i++) {
            if (i == 0) {
                pa[i][u] = fa;
            } else {
                pa[i][u] = pa[i - 1][pa[i - 1][u]];
            }
        }
        for (auto v : g[u]) {
            if (v == fa) continue;
            dfs(v, u, d + 1);
        }
    };
    dfs(s, 0, 1);
    auto lca = [&](int u, int v) {
        // 保证 u 在下面
        if (dep[u] < dep[v]) swap(u, v);
        // 先跳到同一深度
        for (int i = 19; i >= 0; i--) {
            if (dep[pa[i][u]] >= dep[v]) {
                u = pa[i][u];
            }
        }
        // v是u的祖先
        if(u == v) return v;
        for(int i = 19; i >= 0; i--) {
            if(pa[i][u] != pa[i][v]) {
                u = pa[i][u];
                v = pa[i][v];
            }
        }
        return pa[0][u];
    };
    // 查询
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << endl;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T = 1;
    while (T--) {
        solve();
    }
    return 0;
}
```

LCA

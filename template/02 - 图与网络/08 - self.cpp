const int N = 1e5 + 10;
int parent[N], dep[N], sz[N], son[N], top[N], in[N], out[N], rnk{N};
vector<vector<int>> adj;
int cnt = 0;
void work(int root = 1) {
    dfs1(root, 0);
    dfs2(root, root);
}
void dfs1(int x, int fa) {
    parent[x] = fa;
    dep[x] = dep[fa] + 1;
    sz[x] = 1;
    for (int y : adj[x]) {
        if (y == fa) continue;
        dfs1(y, x);
        sz[x] += sz[y];
        if (sz[y] > sz[son[x]]) son[x] = y;
    }
}
void dfs2(int x, int r) {
    top[x] = r;
    in[x] = ++cnt;
    rnk[cnt] = x;
    if (!son[x]) {
        out[x] = cnt;
        return;
    }
    dfs2(son[x], r);
    for (int y : adj[x]) {
        if (y == parent[x] || y == son[x]) continue;
        dfs2(y, y);
    }
    out[x] = cnt;
}
int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        u = parent[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}
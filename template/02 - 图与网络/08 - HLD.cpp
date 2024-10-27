struct HLD {
    int n;
    vector<int> parent, dep, sz, son, top, in, out, rnk;
    vector<vector<int>> adj;
    int cnt;
    HLD() {}
    HLD(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        sz.resize(n + 1);
        top.resize(n + 1);
        dep.resize(n + 1);
        parent.resize(n + 1);
        in.resize(n + 1);
        out.resize(n + 1);
        son.resize(n + 1);
        rnk.resize(n + 1);
        cnt = 0;
        adj.assign(n + 1, {});
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void work(int root = 1) {
        dep[0] = -1;
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
    int dis(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
    int rootedLca(int a, int b, int c) {
        return lca(a, b) ^ lca(b, c) ^ lca(c, a);
    }
};

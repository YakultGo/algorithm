struct VDCC {
    vector<vector<int>> g, ng, dcc;
    vector<int> dfn, low, id;
    vector<bool> cut;
    stack<int> stk;
    int tot, top, cnt, num, root;
    int n;
    VDCC(int n) {
        this->n = n;
        g.resize(n + 1);
        dcc.resize(n + 1);
        dfn.resize(n + 1);
        low.resize(n + 1);
        id.resize(n + 1);
        cut.resize(n + 1);
        tot = top = cnt = num = root = 0;
    }
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    void work() {
        for (root = 1; root <= n; root++)
            if (!dfn[root])
                tarjan(root);
        num = cnt;
        for (int i = 1; i <= n; i++)
            if (cut[i])
                id[i] = ++num;
        ng.resize(num + 1);
        for (int i = 1; i <= cnt; i++) {
            for (int j = 0; j < dcc[i].size(); j++) {
                int x = dcc[i][j];
                if (cut[x]) {
                    ng[i].push_back(id[x]);
                    ng[id[x]].push_back(i);
                }
            }
        }
    }
    void tarjan(int x) {
        dfn[x] = low[x] = ++tot;
        stk.push(x);
        if (x == root && !g[x].size()) {
            dcc[++cnt].push_back(x);
            return;
        }
        int child = 0;
        for (int y : g[x]) {
            if (!dfn[y]) {
                tarjan(y);
                low[x] = min(low[x], low[y]);
                if (low[y] >= dfn[x]) {
                    child++;
                    if (x != root || child > 1)
                        cut[x] = true;
                    int z;
                    cnt++;
                    do {
                        z = stk.top();
                        stk.pop();
                        dcc[cnt].push_back(z);
                    } while (z != y);
                    dcc[cnt].push_back(x);
                }
            } else
                low[x] = min(low[x], dfn[y]);
        }
    }
};
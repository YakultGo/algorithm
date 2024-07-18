struct EDCC {
    vector<vector<int>> g, ng;
    vector<int> dfn, low, dcc, din;
    vector<pair<int, int>> bridges;
    stack<int> stk;
    int tot, cnt, n;
    EDCC(int n) {
        this->n = n;
        g.resize(n + 1);
        ng.resize(n + 1);
        dfn.resize(n + 1);
        low.resize(n + 1);
        dcc.resize(n + 1);
        din.resize(n + 1);
        tot = cnt = 0;
    }
    void add_edge(int x, int y) {
        g[x].push_back(y);
        g[y].push_back(x);
    }
    void work() {
        for (int i = 1; i <= n; i++)
            if (!dfn[i])
                tarjan(i, 0);
        for (int x = 1; x <= n; x++) {
            for (int y : g[x]) {
                if (dcc[x] == dcc[y]) continue;
                din[dcc[x]]++;
                ng[dcc[x]].push_back(dcc[y]);
            }
        }
    }
    void tarjan(int x, int fa) {
        bool vis = false;
        dfn[x] = low[x] = ++tot;
        stk.push(x);
        for (int y : g[x]) {
            if (y == fa) {
                if (!vis) {
                    vis = true;
                    continue;
                }
            }
            if (!dfn[y]) {
                tarjan(y, x);
                low[x] = min(low[x], low[y]);
                if (low[y] > dfn[x]) {
                    bridges.push_back({x, y});
                }
            } else {
                low[x] = min(low[x], dfn[y]);
            }
        }
        if (dfn[x] == low[x]) {
            ++cnt;
            while (true) {
                int y = stk.top();
                stk.pop();
                dcc[y] = cnt;
                if (y == x) break;
            }
        }
    }
};
struct SCC {
    vector<vector<int>> g, ng;
    vector<int> dfn, low, instk, scc, din, dout;
    stack<int> stk;
    int n, tot, cnt;
    SCC(int n) {
        this->n = n;
        g.resize(n + 1);
        dfn.resize(n + 1);
        low.resize(n + 1);
        instk.resize(n + 1);
        scc.resize(n + 1);
        din.resize(n + 1);
        dout.resize(n + 1);
        tot = cnt = 0;
    }
    void add_edge(int u, int v) {
        g[u].push_back(v);
    }
    void work() {
        for (int i = 1; i <= n; i++)
            if (!dfn[i])
                tarjan(i);
        ng.resize(cnt + 1);
        for (int x = 1; x <= n; x++) {
            for (int y : g[x]) {
                if (scc[x] == scc[y]) continue;
                din[scc[y]]++;
                dout[scc[x]]++;
                ng[scc[x]].push_back(scc[y]);
            }
        }
    }
    void tarjan(int x) {
        dfn[x] = low[x] = ++tot;
        stk.push(x), instk[x] = 1;
        for (int y : g[x]) {
            if (!dfn[y]) {
                tarjan(y);
                low[x] = min(low[x], low[y]);
            } else if (instk[y])
                low[x] = min(low[x], dfn[y]);
        }
        if (dfn[x] == low[x]) {
            int y;
            ++cnt;
            do {
                y = stk.top();
                stk.pop();
                instk[y] = 0;
                scc[y] = cnt;
            } while (y != x);
        }
    }
};
struct TwoSat {
    int n;
    vector<vector<int>> g;
    vector<bool> ans;
    TwoSat(int n) : n(n), g(2 * n + 1), ans(n + 1) {}
    int id(int x) {
        return x > 0 ? x : n - x;
    }
    void add(int x, int y) {
        g[x].push_back(y);
    }
    bool satisfiable() {
        vector<int> scc(2 * n + 1), dfn(2 * n + 1), low(2 * n + 1), inStack(2 * n + 1, 0);
        vector<int> stk;
        int now = 0, cnt = 0;
        function<void(int)> tarjan = [&](int u) {
            stk.push_back(u);
            dfn[u] = low[u] = ++now;
            inStack[u] = 1;
            for (auto v : g[u]) {
                if (dfn[v] == 0) {
                    tarjan(v);
                    low[u] = min(low[u], low[v]);
                } else if (inStack[v]) {
                    low[u] = min(low[u], dfn[v]);
                }
            }
            if (dfn[u] == low[u]) {
                int v;
                do {
                    v = stk.back();
                    stk.pop_back();
                    scc[v] = cnt;
                    inStack[v] = 0;
                } while (v != u);
                cnt++;
            }
        };
        for (int i = 1; i <= 2 * n; i++)
            if (dfn[i] == 0) tarjan(i);
        for (int i = 1; i <= n; i++) {
            if (scc[id(i)] == scc[id(-i)]) return false;
            ans[i] = scc[id(i)] < scc[id(-i)];
        }
        return true;
    }
    vector<bool> answer() {
        return ans;
    }
};
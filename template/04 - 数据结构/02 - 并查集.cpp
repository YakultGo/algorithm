struct dsu {
    std::vector<int> pa, sze;
    int connected;
    dsu() {}
    dsu(int n) {
        init(n);
    }
    void init(int n) {
        pa.resize(n);
        sze.assign(n, 1);
        std::iota(pa.begin(), pa.end(), 0);
        connected = n;
    }
    void unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (sze[x] < sze[y]) std::swap(x, y);
        pa[y] = x;
        sze[x] += sze[y];
        connected--;
    }
    int find(int x) {
        return pa[x] == x ? x : pa[x] = find(pa[x]);
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    int size(int x) {
        return sze[find(x)];
    }
    bool isConnect() {
        return connected == 1;
    }
};
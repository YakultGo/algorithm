template <typename T>
struct RMQ {
    int n;
    vector<T> a;
    vector<array<T, 30>> f;
    function<T(T, T)> func;
    RMQ(vector<T> _a) {
        init(_a, [&](T a, T b) { return max(a, b); });
    }
    RMQ(vector<T> _a, function<T(T, T)> _func) {
        init(_a, _func);
    }
    void init(vector<T> _a, function<T(T, T)> _func) {
        a = _a;
        n = a.size();
        func = _func;
        f.resize(n);
        for (int i = 0; i < n; i++) {
            f[i][0] = a[i];
        }
        for (int j = 1; (1 << j) <= n; j++) {
            for (int i = 0; i + (1 << j) - 1 < n; i++) {
                f[i][j] = func(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    T query(int l, int r) {
        int k = 31 - __builtin_clz(r - l + 1);
        return func(f[l][k], f[r - (1 << k) + 1][k]);
    }
};
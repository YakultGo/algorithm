template <typename T>
struct BIT {
    std::vector<T> tr;
    BIT() {}
    BIT(int n) : tr(n + 10, 0) {}
    static inline int lowbit(int x) {
        return x & (-x);
    }
    void add(int x, T delta) {
        if (x == 0) return;
        while (x < tr.size()) {
            tr[x] += delta;
            x += lowbit(x);
        }
    }
    T query(int x) {
        T res = 0;
        while (x > 0) {
            res += tr[x];
            x -= lowbit(x);
        }
        return res;
    }
    T calc(int l, int r) {
        if (l > r) return T(0);
        return query(r) - query(l - 1);
    }
};
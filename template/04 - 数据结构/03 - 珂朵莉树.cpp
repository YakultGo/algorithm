struct node {
    ll l, r;
    mutable ll v;
    node(ll _l, ll _r, ll _v) : l(_l), r(_r), v(_v) {}
    bool operator<(const node& o) const { return l < o.l; }
};
struct ODT {
    set<node> tree;
    ODT(set<node>& tr) : tree(tr) {}
    auto split(ll pos) {
        auto it = tree.lower_bound(node(pos, 0, 0));
        if (it != tree.end() && it->l == pos) return it;
        it--;
        ll l = it->l, r = it->r, v = it->v;
        tree.erase(it);
        tree.insert(node(l, pos - 1, v));
        return tree.insert(node(pos, r, v)).first;
    }
    void assign(ll l, ll r, ll v) {
        auto end = split(r + 1), begin = split(l);
        tree.erase(begin, end);
        tree.insert(node(l, r, v));
    }
    void add(ll l, ll r, ll v) {
        auto end = split(r + 1);
        for (auto it = split(l); it != end; it++) {
            it->v += v;
        }
    }
    ll querySum(ll l, ll r) {
        ll res = 0;
        auto end = split(r + 1);
        for (auto it = split(l); it != end; it++) {
            res += (it->r - it->l + 1) * it->v;
        }
        return res;
    }
    ll querykth(ll l, ll r, ll k) {
        auto end = split(r + 1);
        vector<pair<ll, ll>> v;
        for (auto it = split(l); it != end; it++)
            v.push_back(make_pair(it->v, it->r - it->l + 1));
        sort(v.begin(), v.end());
        for (int i = 0; i < v.size(); i++) {
            k -= v[i].second;
            if (k <= 0)
                return v[i].first;
        }
        return -1;
    }
};
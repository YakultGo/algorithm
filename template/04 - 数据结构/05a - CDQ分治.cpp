#include <bits/stdc++.h>
constexpr int MAXN = 1e5 + 10;
constexpr int MAXK = 2e5 + 10;

struct Element {
    int a, b, c;
    int cnt;
    int res;

    bool operator!=(const Element other) const {
        if (a != other.a) return true;
        if (b != other.b) return true;
        if (c != other.c) return true;
        return false;
    }
};

Element e[MAXN];
Element ue[MAXN];
int res[MAXN];

struct BinaryIndexedTree {
    int node[MAXK];
    static int lowbit(const int x) { return x & -x; }

    void Add(int pos, int val) {
        while (pos < MAXK) {
            node[pos] += val;
            pos += lowbit(pos);
        }
    }

    int Ask(int pos) {
        int res = 0;
        while (pos) {
            res += node[pos];
            pos -= lowbit(pos);
        }
        return res;
    }
} BIT;

bool cmpA(const Element &x, const Element &y) {
    if (x.a != y.a) return x.a < y.a;
    if (x.b != y.b) return x.b < y.b;
    return x.c < y.c;
}

bool cmpB(const Element &x, const Element &y) {
    if (x.b != y.b) return x.b < y.b;
    return x.c < y.c;
}

void CDQ(int l, int r) {
    if (l == r) return;
    int mid = (l + r) / 2;
    CDQ(l, mid);
    CDQ(mid + 1, r);
    std::sort(ue + l, ue + mid + 1, cmpB);
    std::sort(ue + mid + 1, ue + r + 1, cmpB);
    int i = l;
    int j = mid + 1;
    while (j <= r) {
        while (i <= mid && ue[i].b <= ue[j].b) {
            BIT.Add(ue[i].c, ue[i].cnt);
            i++;
        }
        ue[j].res += BIT.Ask(ue[j].c);
        j++;
    }
    for (int k = l; k < i; k++) BIT.Add(ue[k].c, -ue[k].cnt);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, k;
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++) std::cin >> e[i].a >> e[i].b >> e[i].c;
    std::sort(e + 1, e + n + 1, cmpA);
    int m = 0, t = 0;
    for (int i = 1; i <= n; i++) {
        t++;
        if (e[i] != e[i + 1]) {
            m++;
            ue[m].a = e[i].a;
            ue[m].b = e[i].b;
            ue[m].c = e[i].c;
            ue[m].cnt = t;
            t = 0;
        }
    }
    CDQ(1, m);
    for (int i = 1; i <= m; i++) res[ue[i].res + ue[i].cnt - 1] += ue[i].cnt;
    for (int i = 0; i < n; i++) std::cout << res[i] << '\n';
    return 0;
}

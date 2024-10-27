const int MAXN = 6e5 + 10;
const int N = 2;
struct persistenTrie {
    int n, m, idx, cnt;
    int rt[MAXN], ch[MAXN * 25][N], siz[MAXN * 25];
    void insert(int val) {
        rt[++idx] = ++cnt;
        int x = rt[idx - 1], y = rt[idx];
        for (int i = 23; i >= 0; i--) {
            int j = (val >> i) & 1;
            ch[y][!j] = ch[x][!j];
            ch[y][j] = ++cnt;
            x = ch[x][j];
            y = ch[y][j];
            siz[y] = siz[x] + 1;
        }
    }
    int query(int l, int r, int val) {
        int res = 0;
        l = rt[l], r = rt[r];
        for (int i = 23; i >= 0; i--) {
            int j = (val >> i) & 1;
            if (siz[ch[r][!j]] > siz[ch[l][!j]]) {
                res |= 1 << i;
                l = ch[l][!j];
                r = ch[r][!j];
            } else {
                l = ch[l][j];
                r = ch[r][j];
            }
        }
        return res;
    }
};
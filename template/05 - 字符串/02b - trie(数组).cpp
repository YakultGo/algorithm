const int MAXN = 3e5 + 10;
const int N = 26;
struct trie {
    int nex[MAXN][N];
    int tag[MAXN];
    int tot;

    void insert(const string &s) {
        int p = 0;
        for (char c : s) {
            int idx = c - 'a';
            if (!nex[p][idx]) {
                nex[p][idx] = ++tot;
            }
            p = nex[p][idx];
        }
        tag[p]++;
    }

    void del(const string &s) {
        int p = 0;
        for (char c : s) {
            p = nex[p][c - 'a'];
        }
        tag[p]--;
    }

    void search(const string &s) {
        int p = 0;
        for (char c : s) {
            p = nex[p][c - 'a'];
            if (!p) {
                cout << "No" << endl;
                return;
            }
        }
        cout << (tag[p] ? "Yes" : "No") << endl;
    }
};

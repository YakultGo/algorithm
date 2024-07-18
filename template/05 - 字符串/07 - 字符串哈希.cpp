vector<ll> Mod = {1610612741, 0, 805306457, 402653189, 201326611, 100663319, 50331653, 1000000007, 1000000009};
struct Hash {
    int n{};
    vector<ll> M1, M2, h1, h2;
    ll p1 = 131, p2 = 13331;
    Hash() {}
    Hash(string &s) {
        Init(s);
    }
    void Init(string &s) {
        if (Mod[1] == 0) change();
        n = s.size();
        work(1, n, s);
    }
    void change() {
        mt19937 rng(chrono::system_clock::now().time_since_epoch().count());
        while (Mod[1] == 0 || Mod[2] == 0) shuffle(Mod.begin(), Mod.end(), rng);
    }
    void work(int st, int len, string &s) {
        M1.resize(len + 1);
        M2.resize(len + 1);
        h1.resize(len + 1);
        h2.resize(len + 1);
        M1[0] = 1;
        M2[0] = 1;
        for (int i = st; i <= len; i++) {
            M1[i] = (M1[i - 1] * p1) % Mod[1];
            h1[i] = (h1[i - 1] * p1 + s[i - st]) % Mod[1];
            M2[i] = (M2[i - 1] * p2) % Mod[2];
            h2[i] = (h2[i - 1] * p2 + s[i - st]) % Mod[2];
        }
    }
    pair<ll, ll> get(int l, int r) {
        l++, r++;
        ll t1 = ((h1[r] - h1[l - 1] * M1[r - l + 1]) % Mod[1] + Mod[1]) % Mod[1];
        ll t2 = ((h2[r] - h2[l - 1] * M2[r - l + 1]) % Mod[2] + Mod[2]) % Mod[2];
        return {t1, t2};
    }

    pair<ll, ll> mul(pair<ll, ll> l, pair<ll, ll> r, ll len) {
        pair<ll, ll> it;
        l.first *= M1[len] %= Mod[1];
        l.second *= M2[len] %= Mod[2];
        it.first = (l.first + r.first) % Mod[1];
        it.second = (l.second + r.second) % Mod[2];
        return it;
    }

    bool same(pair<ll, ll> l, pair<ll, ll> r) {
        return l.first == r.first && l.second == r.second;
    }
};
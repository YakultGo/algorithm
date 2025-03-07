struct Manacher {
    string s;
    Manacher(string s) : s(s) {
    }
    string process() {
        if (s.size() == 0) return "^$";
        string ret = "^#";
        for (int i = 0; i < s.size(); i++) {
            ret += s[i];
            ret += "#";
        }
        ret += "$";
        return ret;
    }
    vector<int> work() {
        string t = process();
        int n = t.size();
        vector<int> p(n, 0);
        int M = 0, R = 0;
        for (int i = 1; i < n; i++) {
            int j = 2 * M - i;
            if (R > i) {
                p[i] = min(R - i, p[j]);
            }else {
                p[i] = 0;
            }
            while (t[i + p[i] + 1] == t[i - p[i] - 1]) {
                p[i]++;
            }
            if (i + p[i] > R) {
                M = i;
                R = i + p[i];
            }
        }
        return p;
    }
};
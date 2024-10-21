struct KMP {
    vector<int> prefix(string &s) {
        int n = s.size();
        vector<int> nex(n);
        for (int i = 1; i < n; i++) {
            int j = nex[i - 1];
            while (j > 0 && s[i] != s[j]) j = nex[j - 1];
            if (s[i] == s[j]) j++;
            nex[i] = j;
        }
        return nex;
    }
    vector<int> work(string &text, string &pattern) {
        vector<int> nex = prefix(pattern);
        vector<int> res;
        int j = 0, m = pattern.size();
        for (int i = 0; i < text.size(); i++) {
            while (j > 0 && text[i] != pattern[j]) j = nex[j - 1];
            if (text[i] == pattern[j]) j++;
            if (j == m) {
                res.push_back(i - m + 1);
                j = nex[j - 1];
            }
        }
        return res;
    }
};
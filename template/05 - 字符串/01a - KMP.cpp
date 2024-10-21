struct KMP {
    vector<int> nex(string &s) {
        int n = s.size();
        vector<int> pi(n);
        for (int i = 1; i < n; i++) {
            int j = pi[i - 1];
            while (j > 0 && s[i] != s[j]) j = pi[j - 1];
            if (s[i] == s[j]) j++;
            pi[i] = j;
        }
        return pi;
    }
    vector<int> work(string &text, string &pattern) {
        vector<int> pi = nex(pattern);
        vector<int> res;
        int j = 0, m = pattern.size();
        for (int i = 0; i < text.size(); i++) {
            while (j > 0 && text[i] != pattern[j]) j = pi[j - 1];
            if (text[i] == pattern[j]) j++;
            if (j == m) {
                res.push_back(i - m + 1);
                j = pi[j - 1];
            }
        }
        return res;
    }
};
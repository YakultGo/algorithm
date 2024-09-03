struct KMP {
    vector<int> prefix_function(string &s) {
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
    vector<int> kmp(string &text, string &pattern) {
        vector<int> pi = prefix_function(pattern);
        vector<int> res;
        int c = 0, m = pattern.size();
        for (int i = 0; i < text.size(); i++) {
            char v = text[i];
            while (c && pattern[c] != v) {
                c = pi[c - 1];
            }
            if (pattern[c] == v) {
                c++;
            }
            if (c == m) {
                res.push_back(i - m + 1);
                c = pi[c - 1];
            }
        }
        return res;
    }
};
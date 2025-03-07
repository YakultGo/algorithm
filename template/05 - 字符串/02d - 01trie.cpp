struct trie {
    trie *nex[2]{};
    int tag;
    trie() {
        memset(nex, 0, sizeof(nex));
        tag = 0;
    }
    void insert(int num) {
        trie *p = this;
        for (int j = 29; j >= 0; --j) {
            int bit = (num >> j) & 1;
            if (p->nex[bit] == nullptr) {
                p->nex[bit] = new trie();
            }
            p = p->nex[bit];
            p->tag++;
        }
    }
    void del(int num) {
        trie *p = this;
        for (int j = 29; j >= 0; --j) {
            int bit = (num >> j) & 1;
            p = p->nex[bit];
            p->tag--;
        }
    }
    int getmin(int num) {
        trie *p = this;
        int res = 0;
        for (int j = 29; j >= 0; --j) {
            int bit = (num >> j) & 1;
            if (p->nex[bit] != nullptr && p->nex[bit]->tag > 0) {
                p = p->nex[bit];
            } else {
                p = p->nex[bit ^ 1];
                res += (1 << j);
            }
        }
        return res;
    }
};
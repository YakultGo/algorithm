struct trie {
    struct trie *nex[26]{};
    int tag;
    trie(){
        memset(nex, 0, sizeof(nex));
        tag = 0;
    }
    void insert(const string &s){
        trie *p = this;
        for (char i : s) {
            if (p->nex[i - 'a'] == nullptr) {
                p->nex[i - 'a'] = new trie();
            }
            p = p->nex[i - 'a'];
        }
        p->tag = 1;
    }
    void del(const string &s) {
        trie *p = this;
        for (char i : s) {
            p = p->nex[i - 'a'];
        }
        p->tag--;
    }
    bool search(const string &s){
        trie *p = this;
        for (char i : s) {
            if (p->nex[i - 'a'] == nullptr) {
                return false;
            }
            p = p->nex[i - 'a'];
        }
        return p->tag;
    }
};
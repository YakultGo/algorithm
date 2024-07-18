### 动态维护区间前k小之和

```c++
// 两个 multiset 维护滑动窗口中的前 K 小值
struct Magic {
    int K;
    // st1 保存前 K 小值，st2 保存其它值
    multiset<long long> st1, st2;
    // sm 表示 st1 中所有数的和
    long long sm;
    Magic(int K): K(K), sm(0) {}
    // 调整 st1 和 st2 的大小，保证调整后 st1 保存前 K 小值
    void adjust() {
        while (st1.size() < K && st2.size() > 0) {
            long long t = *(st2.begin());
            st1.insert(t);
            sm += t;
            st2.erase(st2.begin());
        }
        while (st1.size() > K) {
            long long t = *prev(st1.end());
            st2.insert(t);
            st1.erase(prev(st1.end()));
            sm -= t;
        }
    }
    // 插入元素 x
    void add(long long x) {
        if (!st2.empty() && x >= *(st2.begin())) st2.insert(x);
        else st1.insert(x), sm += x;
        adjust();
    }

    // 删除元素 x
    void del(long long x) {
        auto it = st1.find(x);
        if (it != st1.end()) st1.erase(it), sm -= x;
        else st2.erase(st2.find(x));
        adjust();
    }
};
Magic magic(k);
```

### 动态维护区间前k大之和

```c++
struct Magic {
    int K;
    multiset<long long> st1, st2;
    long long sm;
    Magic(int K): K(K), sm(0) {}
    void adjust() {
        while (st1.size() < K && st2.size() > 0) {
            long long t = *(prev(st2.end()));
            st1.insert(t);
            sm += t;
            st2.erase(prev(st2.end()));
        }
        while (st1.size() > K) {
            long long t = *st1.begin();
            st2.insert(t);
            st1.erase(st1.begin());
            sm -= t;
        }
    }
    // 插入元素 x
    void add(long long x) {
        if (!st2.empty() && x <= *(st2.rbegin()))
            st2.insert(x);
        else
            st1.insert(x), sm += x;
        adjust();
    }

    // 删除元素 x
    void del(long long x) {
        auto it = st1.find(x);
        if (it != st1.end())
            st1.erase(it), sm -= x;
        else
            st2.erase(st2.find(x));
        adjust();
    }
};
```




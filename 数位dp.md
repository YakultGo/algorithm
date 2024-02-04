### [2376. 统计特殊整数](https://leetcode.cn/problems/count-special-integers/)

```c++
class Solution {
public:
    long long countSpecialNumbers(int n) {
        auto s = to_string(n);
        long long m = s.length(), memo[m][1 << 10];
        memset(memo, -1, sizeof(memo));
        function<long long(int, int, bool, bool)> f = [&](int pos, int mask, bool is_limit, bool is_num) -> long long {
            if (pos == m)
                return is_num; 
            if (!is_limit && is_num && memo[pos][mask] != -1)
                return memo[pos][mask];
            long long res = 0;
            if (!is_num)
                res = f(pos + 1, mask, false, false);
            int up = is_limit ? s[pos] - '0' : 9; 
            for (int d = 1 - is_num; d <= up; ++d) 
                if ((mask >> d & 1) == 0) 
                    res += f(pos + 1, mask | (1 << d), is_limit && d == up, true);
            if (!is_limit && is_num)
                memo[pos][mask] = res;
            return res;
        };
        return f(0, 0, true, false);
    }
};
```

```c++
class Solution {
public:
    long long numberOfPowerfulInt(long long start, long long finish, int limit, string s) {
        string low = to_string(start);
        string high = to_string(finish);
        int n = high.size();
        low = string(n - low.size(), '0') + low; // 补前导零，和 high 对齐
        int diff = n - s.size();
        vector<long long> memo(n, -1);
        function<long long(int, bool, bool)> dfs = [&](int i, bool limit_low, bool limit_high) -> long long {
            if (i == low.size()) {
                return 1;
            }
            if (!limit_low && !limit_high && memo[i] != -1) {
                return memo[i]; // 之前计算过
            }
            // 第 i 个数位可以从 lo 枚举到 hi
            // 如果对数位还有其它约束，应当只在下面的 for 循环做限制，不应修改 lo 或 hi
            int lo = limit_low ? low[i] - '0' : 0;
            int hi = limit_high ? high[i] - '0' : 9;

            long long res = 0;
            if (i < diff) { // 枚举这个数位填什么
                for (int d = lo; d <= min(hi, limit); d++) {
                    res += dfs(i + 1, limit_low && d == lo, limit_high && d == hi);
                }
            } else { // 这个数位只能填 s[i-diff]
                int x = s[i - diff] - '0';
                if (lo <= x && x <= min(hi, limit)) {
                    res = dfs(i + 1, limit_low && x == lo, limit_high && x == hi);
                }
            }
            if (!limit_low && !limit_high) {
                memo[i] = res; // 记忆化 (i,false,false)
            }
            return res;
        };
        return dfs(0, true, true);
    }
};
```


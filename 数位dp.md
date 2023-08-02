### [2376. 统计特殊整数](https://leetcode.cn/problems/count-special-integers/)

```c++
class Solution {
public:
    long long countSpecialNumbers(int n) {
        auto s = to_string(n);
        long long m = s.length(), memo[m][1 << 10];
        memset(memo, -1, sizeof(memo)); // -1 表示没有计算过
        function<long long(int, int, bool, bool)> f = [&](int pos, int mask, bool is_limit, bool is_num) -> long long {
            if (pos == m)
                return is_num; // is_num 为 true 表示得到了一个合法数字
            if (!is_limit && is_num && memo[pos][mask] != -1)
                return memo[pos][mask];
            long long res = 0;
            if (!is_num) // 可以跳过当前数位
                res = f(pos + 1, mask, false, false);
            int up = is_limit ? s[pos] - '0' : 9; // 如果前面填的数字都和 n 的一样，那么这一位至多填数字 s[pos]（否则就超过 n 啦）
            for (int d = 1 - is_num; d <= up; ++d) // 枚举要填入的数字 d
                if ((mask >> d & 1) == 0) // d 不在 mask 中
                    res += f(pos + 1, mask | (1 << d), is_limit && d == up, true);
            if (!is_limit && is_num)
                memo[pos][mask] = res;
            return res;
        };
        return f(0, 0, true, false);
    }
};
```

### [6957. 统计范围内的步进数字数目](https://leetcode.cn/problems/count-stepping-numbers-in-range/) 

```c++
class Solution {
    const int MOD = 1e9 + 7;
    int calc(string &s) {
        int m = s.length(), memo[m][10];
        memset(memo, -1, sizeof(memo)); // -1 表示没有计算过
        function<int(int, int, bool, bool)> f = [&](int pos, int pre, bool is_limit, bool is_num) -> int {
            if (pos == m)
                return is_num; // is_num 为 true 表示得到了一个合法数字
            if (!is_limit && is_num && memo[pos][pre] != -1)
                return memo[pos][pre];
            int res = 0;
            if (!is_num) // 可以跳过当前数位
                res = f(pos + 1, pre, false, false);
            int up = is_limit ? s[pos] - '0' : 9; // 如果前面填的数字都和 s 的一样，那么这一位至多填数字 s[pos]（否则就超过 s 啦）
            for (int d = 1 - is_num; d <= up; ++d) // 枚举要填入的数字 d
                if (!is_num || abs(d - pre) == 1) // 第一位数字随便填，其余必须相差 1
                    res = (res + f(pos + 1, d, is_limit && d == up, true)) % MOD;
            if (!is_limit && is_num)
                memo[pos][pre] = res;
            return res;
        };
        return f(0, 0, true, false);
    }

    bool valid(string &s) {
        for (int i = 1; i < s.length(); i++)
            if (abs(int(s[i]) - int(s[i - 1])) != 1)
                return false;
        return true;
    }

public:
    int countSteppingNumbers(string low, string high) {
        return (calc(high) - calc(low) + MOD + valid(low)) % MOD; // +MOD 防止算出负数
    }
};

```

### [233. 数字 1 的个数](https://leetcode.cn/problems/number-of-digit-one/)

```c++
class Solution {
public:
    int countDigitOne(int n) {
        string s = to_string(n);
        int m = s.length(), memo[m][m];
        memset(memo, -1, sizeof(memo)); // -1 表示没有计算过
        function<int(int, int, bool, bool)> f = [&](int pos, int cnt, bool is_limit, bool is_num) -> int {
            if (pos == m)
                return cnt;
            if (!is_limit && is_num && memo[pos][cnt] != -1)
                return memo[pos][cnt];
            int res = 0;
            if (!is_num) // 可以跳过当前数位
                res = f(pos + 1, cnt, false, false);
            int up = is_limit ? s[pos] - '0' : 9; // 如果前面填的数字都和 n 的一样，那么这一位至多填数字 s[pos]（否则就超过 n 啦）
            for (int d = 1 - is_num; d <= up; ++d) // 枚举要填入的数字 d
                res += f(pos + 1, cnt + (d==1), is_limit && d == up, true) ;
            if (!is_limit && is_num)
                memo[pos][cnt] = res;
            return res;
        };
        return f(0, 0, true, false);
    }
};
```


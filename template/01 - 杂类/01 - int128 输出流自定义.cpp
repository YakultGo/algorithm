using i128 = __int128;

std::ostream &operator<<(std::ostream &os, i128 n) {
    std::string s;
    if (n < 0) {
        os << '-';
        n = -n;
    }
    if(n == 0) {
        return os << '0';
    }
    while (n) {
        s += '0' + n % 10;
        n /= 10;
    }
    std::reverse(s.begin(), s.end());
    return os << s;
}
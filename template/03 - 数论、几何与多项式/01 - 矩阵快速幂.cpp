const int mod = 1e9 + 7;
struct matrix {
    vector<vector<ll>> m;
    int M;
    matrix(int M) : M(M) {
        m.resize(M, vector<ll>(M, 0));
    }
    matrix operator*(const matrix& b) {
        matrix c(M);
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < M; j++) {
                for (int k = 0; k < M; k++) {
                    c.m[i][j] = (c.m[i][j] + (m[i][k] * b.m[k][j]) % mod) % mod;
                }
            }
        }
        return c;
    }
};
matrix ksm(matrix b, ll n) {
    matrix a(b.M);
    for (int i = 0; i < a.M; ++i) a.m[i][i] = 1;
    while (n) {
        if (n & 1) a = a * b;
        n >>= 1;
        b = b * b;
    }
    return a;
}
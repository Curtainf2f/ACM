#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define test(x) cerr << #x << "=" << x << endl
#else
    #define test(x)
#endif

typedef long long LL;

const int MAXN = 5;

LL MOD;

struct Matrix {
    int m, n;
    LL data[MAXN][MAXN];
    Matrix(int _m = 0, int _n = 0) : m(_m), n(_n) {
        memset(data, 0, sizeof(data));
    }
} a, b;

Matrix multiply(const Matrix &a, const Matrix &b) {
    Matrix c;
    c.m = a.m, c.n = b.n;
    for (int i = 1; i <= c.m; i++) {
        for (int j = 1; j <= c.n; j++) {
            c.data[i][j] = 0;
            for (int k = 1; k <= a.n; k++) {
                c.data[i][j] = (c.data[i][j] + a.data[i][k] * b.data[k][j]) % MOD;
            }
        }
    }
    return c;
}

Matrix quick_pow_matrix(Matrix a, LL n) {
    Matrix ans(a.n, a.n);
    for (int i = 1; i <= a.n; i++) ans.data[i][i] = 1;
    while (n) {
        if (n & 1) ans = multiply(ans, a);
        a = multiply(a, a);
        n >>= 1;
    }
    return ans;
}

char str[1000005];

int main() {
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    int x0, x1, a, b;
    long long n = 0;
    scanf("%d%d%d%d", &x0, &x1, &a, &b);
    scanf("%s%lld", str, &MOD);
    int len = strlen(str);
    for (int i = 0; str[i]; ++i) {
        n = (n * 10LL + str[i] - '0') % MOD;
    }
    n += MOD;
    Matrix x(1, 2);
    x.data[1][1] = x1;
    x.data[1][2] = x0;

    Matrix y(2, 2);
    y.data[1][1] = a;
    y.data[1][2] = 1;
    y.data[2][1] = b;
    y.data[2][2] = 0;
    if(n == 0) printf("%lld\n", x0);
    else if(n == 1) printf("%lld\n", x1);
    else{
        Matrix ans = multiply(x, quick_pow_matrix(y, n));
        printf("%lld\n", ans.data[1][1]);
    }
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
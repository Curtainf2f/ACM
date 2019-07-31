#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define fuck(x) cerr << #x << "=" << x << endl
#else
    #define fuck(x)
#endif

typedef long long LL;

const int N = 1e6;
const int K = N;
const int M = 2 * N;
const int INF = 0x3F3F3F3F;
const LL INFLL = 0x3F3F3F3F3F3F3F3FLL;

LL quickMul(LL a, LL n, LL mod) {
    LL ans = 0;
    while (n) {
        if (n & 1) ans = (ans + a) % mod;
        a = (a + a) % mod, n >>= 1;
    }
    return ans;
}

LL quickPow(LL a, LL b, LL p) {
    LL r = 1;
    while (b) {
        if (b & 1) r = r * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return r;
}

LL inv(LL a, LL p) {
    return quickPow(a, p - 2, p);
}

LL random(LL n) { // 产生2到n-2的随机数
    return double(rand()) / RAND_MAX * (n - 4) + 2;
}

bool millerRobbin(LL n, int cnt) {
    if (n == 2 || n == 3) return true;
    if (n < 2 || !(n & 1)) return false;
    int t = 0;
    LL a, x, y, u = n - 1;
    while (!(u & 1)) ++t, u >>= 1;
    for (int i = 0; i < cnt; ++i) {
        a = random(n), x = quickPow(a, u, n);
        for (int j = 0; j < t; ++j, x = y) {
            y = quickMul(x, x, n);
            if (y == 1 && x != 1 && x != n - 1) return false;
        }
        if (x != 1) return false;
    }
    return true;
}

int main() {
#ifdef _LOCAL
    freopen("data.in", "r", stdin);
#endif
    srand(time(NULL));
    int T;
    long long in;
    scanf("%d", &T);
    while (T--) {
        scanf("%I64d", &in);
        LL p = in;
        LL ans = p - 1, mod = p;
        LL t = 1;
        for (LL i = p - 1; !millerRobbin(i, 20); --i) {
            t = t * i % mod;
        }
        ans = ans * inv(t, mod) % mod;
        printf("%I64d\n", (long long)ans);
    }

#ifdef _LOCAL
    fprintf(stderr, "\nTime elapsed: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
#endif
    return 0;
}
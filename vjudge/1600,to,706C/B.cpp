#include <bits/stdc++.h>
 
using namespace std;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;
 
#ifdef _LOCAL
#define show(x) cerr << "[" << #x << ": " << x << "] (" << __LINE__ << ", in `" << __FUNCTION__ << "`)\n"
struct Tester {
    Tester() { freopen("data.in", "r", stdin); }
    ~Tester() { fprintf(stderr, "\nTime: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC)); }
} _shower;
#else
#define show(x)
#endif
 
const int N = 105;
const LL MOD = 1e9+7;

LL dp[N][N];

int main(int argc, char const *argv[]) {
    int n, k, d;
    scanf("%d%d%d", &n, &k, &d);
    dp[0][0] = 1;
    for(int i = 0; i <= n; i ++){
        for(int j = 0; j <= 100; j ++){
            for(int l = 1; l <= k; l ++){
                if(i+l>100) continue;
                dp[i+l][max(j,l)] += dp[i][j];
                dp[i+l][max(j,l)] %= MOD;
            }
        }
    }
    LL ans = 0;
    for(int i = d; i <= k; i ++){
        ans += dp[n][i];
        ans %= MOD;
    }
    printf("%I64d\n", ans);
    return 0;
}
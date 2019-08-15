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
 
const int N = 1e5+5;

int a[N];
LL dp[N];

int main(int argc, char const *argv[]) {
    int n;
    scanf("%d", &n);
    for(int i = 1, x; i <= n; i ++){
        scanf("%d", &x);
        a[x] ++;
    }
    dp[1] = a[1];
    for(int i = 2; i < N; i ++){
        dp[i] = max(dp[i-1], dp[i]);
        dp[i] = max(dp[i-2] + 1LL*a[i]*i, dp[i]);
    }
    printf("%I64d\n", dp[N-1]);
    return 0;
}
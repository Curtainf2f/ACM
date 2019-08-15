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

const int N = 100005;
const LL INF = 0x3f3f3f3f3f3f3f3f;

LL dp[N][2], c[N];
string s[N];

int main(int argc, char const *argv[]) {
    int n;
    cin >> n;
    for(int i = 1; i <= n; i ++){
        cin >> c[i];
    }
    for(int i = 1; i <= n; i ++){
        cin >> s[i];
    }
    for(int i = 1; i <= n; i ++){
        dp[i][0] = dp[i][1] = INF;
    }
    dp[1][0] = 0;
    dp[1][1] = c[1];
    for(int i = 2; i <= n; i ++){
        string now = s[i], nowrev = s[i], pre = s[i-1], prerev = s[i-1];
        reverse(nowrev.begin(), nowrev.end());
        reverse(prerev.begin(), prerev.end());
        if(now >= pre) dp[i][0] = min(dp[i-1][0], dp[i][0]);
        if(now >= prerev) dp[i][0] = min(dp[i-1][1], dp[i][0]);
        if(nowrev >= pre) dp[i][1] = min(dp[i-1][0] + c[i], dp[i][1]);
        if(nowrev >= prerev) dp[i][1] = min(dp[i-1][1] + c[i], dp[i][1]);
    }
    LL ans = min(dp[n][0], dp[n][1]);
    if(ans == INF) cout << -1 << endl;
    else cout << ans << endl;
    return 0;
}
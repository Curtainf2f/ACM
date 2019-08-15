#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define test(x) cerr << #x << "=" << x << endl
#else
    #define test(x)
#endif

typedef long long LL;
const int N = 1 << 18;
const LL INF = 0x7fffffffffffffff;
LL dp[N][19];
int rew[19][19];
int a[N];
LL q[N];
int ea[19];
vector<int> all[19];

int main() {
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < (1 << n); i++)
        for(int j = 0; j < n; j ++)
            dp[i][j] = -INF;
    dp[0][18] = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &ea[i]);
    }
    for (int i = 0; i < (1 << n); i++) {
        int x = i, cur = 0;
        LL val = 0;
        for (int j = 0; j < n; j++) {
            if (((x >> j) & 1) == 1) {
                cur++;
                val += 1LL * ea[j];
            }
        }
        all[cur].push_back(i);
        a[i] = cur;
        q[i] = val;
    }
    for (int i = 0; i < k; i++) {
        int b, a, c;
        scanf("%d%d%d", &a, &b, &c);
        b --;
        a --;
        rew[a][b] = c;
    }
    for(int i = 1; i <= n; i ++){
        for(int cas = 0; cas < all[i].size(); cas++){
            int j = all[i][cas];
            for (int k = 0; k < n; k++) {
                if (((j >> k) & 1) == 1) {
                    int pre = j^(1<<k);
                    for(int l = 0; l < n; l ++){
                        dp[j][k] = max(dp[j][k], dp[pre][l] + 1LL*rew[l][k]);
                        // printf("[%d,%d,%d]=%lld [%d,%d,%d]=%lld %d->%d=+%d\n", i, j, k, dp[i][j][k], i-1, pre, l, dp[i-1][pre][l], l, k, rew[l][k]);
                    }
                    dp[j][k] = max(dp[j][k], dp[pre][18]);
                }
            }
        }
    }
    LL ans = 0;
    for (int j = 0; j < (1 << n); j++) {
        for(int k = 0; k < n; k ++){
            // printf("%d %d %lld\n", j, a[j], q[j]);
            if(a[j] <= m) ans = max(ans, q[j] + dp[j][k]);
        }
    }
    printf("%lld\n", ans);
    return 0;
}
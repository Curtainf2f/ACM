#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define test(x) cerr << #x << "=" << x << endl
#else
    #define test(x)
#endif

typedef long long LL;

const int N = 3005;
const LL MOD = 998244353;

char a[N], b[N];
LL C[N][N];
int dp[N][N];

void get_C(int maxn)
{
    C[0][0] = 1;
    for(int i=1;i<N;i++)
    {
        C[i][0] = 1;
        for(int j=1;j<=i;j++)
            C[i][j] = (C[i-1][j]+C[i-1][j-1])%MOD;
    }
}

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    get_C(N);
    int t;
    scanf("%d", &t);
    while(t --){
        int n, m;
        scanf("%d%d", &n, &m);
        scanf("%s%s", a + 1, b + 1);
        LL ans = 0;
        for(int i = 1; i <= m; i ++){
            for(int j = 0; j <= n; j ++){
                dp[i][j] = 0;
            }
        }
        for(int j = 1; j <= n; j ++){
            if(a[j] == b[1]) dp[1][j] = 1;
            else if(a[j] > b[1]) ans = (ans + C[n-j][m-1]) % MOD;
        }
        for(int i = m + 1; i <= n; i ++){
            ans = (ans + C[n][i]) % MOD;
        }
        for(int i = 1; i <= n; i ++){
            if(a[i] == '0'){
                for(int j = m; j <= n-i; j ++)
                    ans = (ans + MOD - C[n-i][j]) % MOD;
            }
        }
        for(int i = 2; i <= m; i ++){
            LL sum = 0;
            for(int j = 1; j <= n; j ++){
                if(a[j] == b[i]){
                    dp[i][j] = sum;
                }
                if(a[j] > b[i]){
                    ans = (ans + sum * C[n-j][m-i] % MOD) % MOD;
                }
                sum = (sum + dp[i-1][j]) % MOD;
            }
        }
        printf("%lld\n", ans);
    }
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define test(x) cerr << #x << "=" << x << endl
#else
    #define test(x)
#endif
 
typedef long long LL;
 
const LL INF = 0x7fffffffffffffffLL;
const int N = 1005;
 
LL a[N][N];
LL d[N];
LL sum[N][N];
deque<int> q[N];
 
int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    int t;
    scanf("%d", &t);
    for(int cas = 1; cas <= t; cas ++){
        int n, m;
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; i ++){
            for(int j = 1; j <= m; j ++){
                scanf("%lld", &a[i][j]);
            }
        }
        for(int i = 1; i <= m; i ++){
            scanf("%lld", &d[i]);
        }
        for(int i = 1; i <= n; i ++){
            for(int j = 1; j <= m; j ++){
                sum[i][j] = sum[i][j-1] + a[i][j];
                while (!q[i].empty() && sum[i][q[i].back()] > sum[i][j]) {
                    q[i].pop_back();
                }
                q[i].push_back(j);
            }
        }
        LL ans = 0;
        LL cur = 0;
        LL get = 0;
        for(int j = 0; j <= m; j ++){
            LL _max = -INF;
            LL plus = 0;
            for(int i = 1; i <= n; i ++){
                cur += a[i][j];
                while (q[i].front() < j) q[i].pop_front();
                LL del = sum[i][q[i].front()] - sum[i][j];
                if(del > 0) del = 0;
                _max = max(del, _max);
                plus += del;
            }
            get += d[j];
            plus -= _max;
            ans = max(ans, get - (cur + plus));
        }
        printf("Case #%d: %lld\n", cas, ans);
        for(int i = 1; i <= n; i ++){
            q[i].clear();
        }
    }
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
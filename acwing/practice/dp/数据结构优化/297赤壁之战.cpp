#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define test(x) cerr << #x << "=" << x << endl
#else
    #define test(x)
#endif
#define lson(x) x << 1
#define rson(x) x << 1 | 1

typedef long long LL;

const int N = 1e3+5;
const int MOD = 1e9+7;
const LL INF = 0x3f3f3f3f3f3f3f3f;

LL a[N], c[N];

inline int lowbit(int x){
    return x & -x;
}

void update(int pos, LL value){
    while(pos < N){
        c[pos] += value;
        c[pos] %= MOD;
        pos += lowbit(pos);
    }
}

LL sum(int pos){
    LL ans = 0;
    while(pos > 0){
        ans += c[pos];
        ans %= MOD;
        pos -= lowbit(pos);
    }
    return ans;
}

LL f[N][N];
vector<int> id;

inline int get(int x){
    return lower_bound(id.begin(), id.end(), x) - id.begin() + 1;
}

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    a[0] = -INF;
    int t;
    scanf("%d", &t);
    for(int cas = 1; cas <= t; cas ++){
        int n, m;
        scanf("%d%d", &n, &m);
        f[0][0] = 1;
        for(int i = 1; i <= m; i ++){
            for(int j = 0; j <= n; j ++){
                f[i][j] = 0;
            }
        }
        for(int i = 1; i <= n; i ++) scanf("%lld", &a[i]);
        for(int i = 0; i <= n; i ++) id.push_back(a[i]);
        sort(id.begin(), id.end());
        id.erase(unique(id.begin(), id.end()), id.end());
        for(int i = 1; i <= m; i ++){
            memset(c, 0, sizeof(c));
            update(get(a[0]), f[i-1][0]);
            for(int j = 1; j <= n; j ++){
                f[i][j] = sum(get(a[j]) - 1);
                update(get(a[j]), f[i-1][j]);
            }
        }
        LL ans = 0;
        for(int i = 1; i <= n; i ++) ans += f[m][i], ans %= MOD;
        printf("Case #%d: %lld\n", cas, ans);
        id.clear();
    }
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
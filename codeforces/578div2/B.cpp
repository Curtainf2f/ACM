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

const int N = 1e5+5;
const int MOD = 1e9+7;
const LL INF = 0x3f3f3f3f3f3f3f3f;

LL a[105];

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    int t;
    scanf("%d", &t);
    while(t --){
        int n; 
        LL m, k;
        scanf("%d%I64d%I64d", &n, &m, &k);
        for(int i = 1; i <= n; i ++){
            scanf("%I64d", &a[i]);
        }
        bool ok = true;
        for(int i = 1; i < n; i ++){
            if(a[i] + m >= a[i+1] - k){
                int cur = a[i+1] - k;
                if(cur < 0) cur = 0; 
                m += a[i] - cur;
            }else{
                ok = false;
                break;
            }
        }
        if(ok) puts("YES");
        else puts("NO");
    }
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
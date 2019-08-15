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

const int N = 1e6+5;
const int MOD = 1e9+7;
const LL INF = 0x3f3f3f3f3f3f3f3f;

LL gcd(LL a,LL b)
{
    return b?gcd(b,a%b):a;
}

LL a[N];

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++){
        scanf("%I64d", &a[i]);
    }
    LL ans = a[1];
    for(int i = 2; i <= n; i ++){
        ans = gcd(ans, a[i]);
    }
    LL aans = 0;
    LL k = sqrt(ans);
    for(LL i = 1; i <= k; i ++){
        if(ans % i == 0){
            if(i*i == ans){
                aans += 1;
            }else{
                aans += 2;
            }
        }
    }
    printf("%I64d\n", aans);
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
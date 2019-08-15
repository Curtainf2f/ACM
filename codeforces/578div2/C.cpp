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

LL gcd(LL a,LL b)
{
    return b ? gcd(b,a%b):a;
}

const int N = 1e3+5;
const int MOD = 1e9+7;
const LL INF = 0x3f3f3f3f3f3f3f3f;

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    LL n, m, q;
    scanf("%I64d%I64d%I64d", &n, &m, &q);
    LL g = gcd(n, m);
    LL dn = n / g, dm = m / g;
    LL sx, sy, ex, ey;
    while (q --) {
        scanf("%I64d%I64d%I64d%I64d", &sx, &sy, &ex, &ey);
        LL s1, e1;
        if(sx == 1){
            s1 = (sy - 1) / dn;
        }else{
            s1 = (sy - 1) / dm;
        }
        if(ex == 1){
            e1 = (ey - 1) / dn;
        }else{
            e1 = (ey - 1) / dm;
        }
        if(s1 == e1) puts("YES");
        else puts("NO");
    }
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
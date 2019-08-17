#include <bits/stdc++.h>
   
using namespace std;
typedef __int128 LL;
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
  
LL exgcd(LL a, LL b, LL &d, LL &x, LL &y){
    if(b == 0) d = a, x = 1, y = 0;
    else{
        exgcd(b, a%b, d, y, x);
        y -= a/b*x;
    }
}
  
LL solve(LL a, LL b, LL n){
    LL d, x, y;
    exgcd(a, n, d, x, y);
    if(b%d) return -1;
    x *= b/d;
    LL r = n/d;
    if(r < 0) r = -r;
    return (x%r + r) % r;
}
  
bool Merge(LL a[], LL n[], LL num, LL &A, LL &N){
    LL d, x, y;
    A = a[0], N = n[0];
    for(LL i = 1; i < num; i ++){
        exgcd(N, n[i], d, x, y);
        if((a[i] - A) % d){
            return false;
        }
        x = (a[i] - A) / d * x;
        y = n[i] / d;
        x = (x % y + y) % y;
        A = x*N + A;
        N = (N * n[i]) / d;
    }
    return true;
}
  
const int MAXN = 1005;
LL a[MAXN], n[MAXN];
long long _max = 0;

int main(){
    long long k, m;
    cin >> k >> m;
        for(int i = 0; i < k; i ++){
            long long aa, bb;
            cin >> aa >> bb;
            n[i] = aa;
            a[i] = bb;
            _max = max(bb, _max);
        }
        LL ansA, ansN;
        if(Merge(a, n, k, ansA, ansN)){
            while(ansA < _max) ansA += ansN;
            if(ansA > m) puts("he was probably lying");
            else printf("%lld\n", (long long)ansA);
        }
        else
            puts("he was definitely lying");
    return 0;
}

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
 
const int N = 1005;
const LL MOD = 1e9+7;

int a[N];

int main(int argc, char const *argv[]) {
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
    int ans = 0;
    for(int i = 2; i < n; i ++){
        if(a[i] > a[i-1] && a[i] > a[i+1]) ans ++;
        else if(a[i] < a[i-1] && a[i] < a[i+1]) ans ++;
    }
    printf("%d\n", ans);
    return 0;
}
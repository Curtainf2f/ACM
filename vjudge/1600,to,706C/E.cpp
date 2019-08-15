#include <bits/stdc++.h>
 
using namespace std;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;
 
#ifdef _LOCAL
#define test(x) cerr << "[" << #x << ": " << x << "] (" << __LINE__ << ", in `" << __FUNCTION__ << "`)\n"
struct Tester {
    Tester() { freopen("data.in", "r", stdin); }
    ~Tester() { fprintf(stderr, "\nTime: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC)); }
} _shower;
#else
#define test(x)
#endif

const int N = 2e5+5;

int a[N], mk[N];
pair<int, int> pp[N];

int main(int argc, char const *argv[]) {
    int n, q;
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; i ++){
        scanf("%d", &a[i]);
    }
    sort(a + 1, a + n + 1);
    for(int i = 1; i <= q; i ++){
        int l, r;
        scanf("%d%d", &l, &r);
        mk[l] ++;
        mk[r+1] --;
    }
    int now = 0;
    for(int i = 1; i <= n; i ++){
        now += mk[i];
        pp[i] = make_pair(now, i);
    }
    sort(pp + 1, pp + 1 + n);
    LL ans = 0;
    for(int i = 1; i <= n; i ++){
        ans += 1LL*pp[i].first*a[i];
    }
    printf("%I64d\n", ans);
    return 0;
}
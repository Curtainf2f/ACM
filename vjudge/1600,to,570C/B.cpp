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
 
const int N = 3333;
const LL MOD = 1e9+7;

int a[N];

int main(int argc, char const *argv[]) {
    for(int i = 0; i < 6; i ++){
        scanf("%d", &a[i]);
    }
    LL sum = a[1] * 2 - 1;
    LL ans  = 0;
    for(int i = 1; i <= min(a[0], a[2]); i ++){
        sum += 2;
        ans += sum;
    }
    test(ans);
    for(int i = min(a[0], a[2]) + 1; i <= max(a[0], a[2]); i ++){
        ans += sum + 1;
    }
    test(sum);
    test(ans);
    sum += 2;
    for(int i = max(a[0], a[2]) + 1; sum/2 != a[4];i++){
        test(sum);
        sum -= 2;
        ans += sum;
    }
    test(ans);
    printf("%I64d\n", ans);
    return 0;
}
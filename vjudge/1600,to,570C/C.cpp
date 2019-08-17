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
 
const int N = 105;
const LL MOD = 1e9+7;

int main(int argc, char const *argv[]) {
    int n;
    scanf("%d", &n);
    if(n == 1) puts("1");
    else if(n == 2) puts("2");
    else{
        for(int i = n; i >= 1; i --){
            if(n & 1){
                if(__gcd(i, n) ==   1 && __gcd(i-1, n) == 1){
                    printf("%I64d\n", 1LL*i*(i-1)*n);
                    break;
                }
            }else{
                if(__gcd(i, n) == 1 && __gcd(i-2, n) == 1){
                    printf("%I64d\n", 1LL*i*(i-2)*n);
                    break;
                }
            }
        }
    }
    return 0;
}
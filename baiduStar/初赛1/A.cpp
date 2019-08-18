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

int a[N], b[N];

int main(int argc, char const *argv[]) {
    int t;
    scanf("%d", &t);
    while(t --){
        int n;
        scanf("%d", &n);
        for(int i = 1; i <= n; i ++){
            scanf("%d", &a[i]);
        }
        for(int i = 1; i <= n; i ++){
            scanf("%d", &b[i]);
        }
        int type = 0;
        int aa, bb;
        for(int i = n; i >= 1; i --){
            if(a[i] != 0 || b[i] != 0){
                if(a[i] != 0 && b[i] == 0){
                    type = 1;
                    break;
                }else if(a[i] == 0 && b[i] != 0){
                    type = -1;
                    break;
                }
                aa = a[i];
                bb = b[i];
                break;
            }
        }
        if(type == 1) puts("1/0");
        else if(type == -1) puts("0/1");
        else{
            int gcdgcd = __gcd(aa, bb);
            aa /= gcdgcd;
            bb /= gcdgcd;
            printf("%d/%d\n", aa, bb);
        }
    }
    return 0;
}
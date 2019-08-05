#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define test(x) cerr << #x << "=" << x << endl
#else
    #define test(x)
#endif

typedef long long LL;

const int N = 2e5+5;

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    int n;
    scanf("%d", &n);
    int ans = 0;
    for(int i = 1; i <= n; i ++){
        int x = i;
        int odd = 0;
        while(x) x /= 10, odd ++;
        if(odd & 1) ans ++;
    }
    printf("%d\n", ans);
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
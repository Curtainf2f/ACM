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
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    int ans = b + c - a;
    if(ans < 0) ans = 0;
    cout << ans << endl;
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
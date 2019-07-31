#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define test(x) cerr << #x << "=" << x << endl
#else
    #define test(x)
#endif

typedef long long LL;

const int N = 1e5+5;
const int INF = 0x7fffffff;

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    int l, h;
    scanf("%d%d", &h, &l);
    printf("%.10f\n", ((1.0*l*l + 1.0*h*h) / (2.0*h)) - h);
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define test(x) cerr << #x << "=" << x << endl
#else
    #define test(x)
#endif

typedef long long LL;

const int N = 1e5+5;

int a[N];

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
    a[1] --;
    for(int i = 2; i <= n; i ++){
        if(a[i] > a[i-1]) a[i] --;
    }
    bool ok = true;
    for(int i = 2; i <= n; i ++){
        if(a[i] < a[i-1]){
            ok = false;
            break;
        }
    }
    if(ok) puts("Yes");
    else puts("No");
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
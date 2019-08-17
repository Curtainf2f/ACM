#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define test(x) cerr << #x << "=" << x << endl
#else
    #define test(x)
#endif

typedef long long LL;

const int N = 100005;
const int INF = 0x7fffffff;

int a[N];

int main() {
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    int t;
    scanf("%d", &t);
    while(t --){
        int _min = INF;
        int _max = 0;
        int n;
        scanf("%d", &n);
        for(int i = 1; i <= n; i ++){
            scanf("%d", &a[i]);
            _min = min(a[i], _min);
            if(a[i] > a[_max]) _max = i;
        }
        LL time = 0;
        LL add = 0; 
        for(int i = 1; i <= n; i ++){
            time += 1LL * (a[i] - _min);
            if(i != _max) add += 1LL * (a[i] - _min);
        }

        printf("%lld %lld\n", time, a[_max] + add);
    }
    return 0;
}
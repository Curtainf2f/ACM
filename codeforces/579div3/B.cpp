#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define test(x) cerr << #x << "=" << x << endl
#else
    #define test(x)
#endif
#define lson(x) x << 1
#define rson(x) x << 1 | 1

typedef long long LL;

const int N = 1e5+5;
const int MOD = 1e9+7;
const LL INF = 0x3f3f3f3f3f3f3f3f;

vector<int> a;

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    int t;
    scanf("%d", &t);
    while(t --){
        int n;
        scanf("%d", &n);
        for(int i = 1, x; i <= 4*n; i ++){
            scanf("%d", &x);
            a.push_back(x);
        }
        sort(a.begin(), a.end());
        test(a.size());
        int S = -1;
        bool ok = true;
        for(int i = 0; i < a.size()/2; i += 2){
            if(a[i] != a[i+1] || a[a.size()-i-1] != a[a.size()-i-2]){
                test(a[i]);
                test(a[i+1]);
                test(a[a.size()-i-1]);
                test(a[a.size()-i-2]);
                ok = false;
                break;
            }
            if(S == -1){
                S = a[i] * a[a.size()-i-1];
            }else if(a[i] * a[a.size()-i-1] != S){
                ok = false;
                break;
            }
        }
        if(ok) puts("YES");
        else puts("NO");
        a.clear();
    }
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
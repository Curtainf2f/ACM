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

int a[N];

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    int t;
    scanf("%d", &t);
    while(t --){
        int n;
        scanf("%d", &n);
        for(int i = 1; i <= n; i ++){
            scanf("%d", &a[i]);
            a[i+n] = a[i];
        }
        bool ok = false;
        for(int i = 1; i <= n; i ++){
            int now = 1;
            bool okk = true;
            for(int j = i; j < i + n; j ++){
                if(a[j] == now){
                    now ++;
                }else{
                    okk = false;
                }
            }
            if(okk) ok = true;
        }
        for(int i = 2 * n; i >= n; i --){
            int now = 1;
            bool okk = true;
            for(int j = i; j > i - n; j --){
                if(a[j] == now){
                    now ++;
                }else{
                    okk = false;
                }
            }
            if(okk) ok = true;
        }
        if(ok) puts("YES");
        else puts("NO");
    }
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
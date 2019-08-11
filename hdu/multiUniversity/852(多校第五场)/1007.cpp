#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define test(x) cerr << #x << "=" << x << endl
#else
    #define test(x)
#endif

typedef long long LL;

const int N = 36;
int n = 10;

int a[N];

bool jud(int x, int y){
    if(a[1] != x) return false;
    if(a[n] != y) return false;
    for(int i = 2; i <= n; i ++){
        if(abs(a[i]-a[i-1]) > 2) return false;
    }
    return true;
}

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    for(int x = 1; x <= n; x ++){
        for(int y = 1; y <= n; y ++){
            if(x == y) continue;
            int ans = 0;
            for(int i = 1; i <= n; i ++) a[i] = i;
            do{
                if(jud(x, y)){
                    for(int i = 1; i <= n; i ++){
                        printf("%d ", a[i]);
                    }
                    puts("");
                    ans ++;
                }
            }while(next_permutation(a + 1, a + 1 + n));
            printf("[%d, %d], %d\n\n", x, y, ans);
        }
    }
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
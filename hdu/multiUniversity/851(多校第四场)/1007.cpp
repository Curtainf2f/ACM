#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define test(x) cerr << #x << "=" << x << endl
#else
    #define test(x)
#endif

typedef long long LL;

const int N = 2e5+5;

int tt[25];

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    int t;
    scanf("%d", &t);
    while (t --){
        int loc;
        for(int i = 0; i < 16; i ++){
            scanf("%d", &tt[i]);
            if(tt[i] == 0) loc = i;
        }
        int sum = 0;
        for(int i = 0; i < 16; i ++){
            if(tt[i] == 0) continue;
            for(int j = 0; j < i; j ++){
                if(tt[j] == 0) continue;
                if(tt[i] < tt[j]) sum ++;
            }
        }
        test(loc/4);
        sum += (3 - loc / 4);
        if(sum&1) puts("No");
        else puts("Yes");
    }
    
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
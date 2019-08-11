#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define test(x) cerr << #x << "=" << x << endl
#else
    #define test(x)
#endif

typedef long long LL;

const int N = 55555;

struct Node
{
    int a[22];
}a[N];

int n;

bool cmp(const Node &a, const Node &b){
    int start;
    if(n <= 8) start = 1;
    else start = n - 8;
    for(int i = start; i < n; i ++){
        if(a.a[i] - a.a[i-1] == b.a[i] - b.a[i-1]) continue;
        return a.a[i] - a.a[i-1] < b.a[i] - b.a[i-1];
    }
    return false;
}

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    int t, k;
    scanf("%d", &t);
    while(t --){
        int sign = 0;
        scanf("%d%d", &n, &k);
        if(n <= 8){
            for(int i = 0; i < n; i ++){
                a[0].a[i] = i+1;
            }
            do{
                sign ++;
                for(int i = 0; i < n; i ++){
                    a[sign].a[i] = a[sign-1].a[i];
                }
            }while(next_permutation(a[sign].a, a[sign].a + n));
        }else{
            a[0].a[0] = n;
            for(int i = 1; i < n; i ++){
                a[0].a[i] = i;
            }
            do{
                sign ++;
                for(int i = 0; i < n; i ++){
                    a[sign].a[i] = a[sign-1].a[i];
                }
            }while(next_permutation(a[sign].a + n - 8, a[sign].a + n));
        }
        sort(a + 1, a + 1 + sign, cmp);
        for(int i = 0; i < n; i ++){
            if(i) putchar(' ');
            printf("%d", a[k].a[i]);
        }
        puts("");
    }
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
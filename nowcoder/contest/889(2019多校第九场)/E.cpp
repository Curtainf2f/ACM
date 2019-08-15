#include <bits/stdc++.h>
 
using namespace std;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;
 
#ifdef _LOCAL
#define show(x) cerr << "[" << #x << ": " << x << "] (" << __LINE__ << ", in `" << __FUNCTION__ << "`)\n"
struct Tester {
    Tester() { freopen("data.in", "r", stdin); }
    ~Tester() { fprintf(stderr, "\nTime: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC)); }
} _shower;
#else
#define show(x)
#endif
 
const int N = 1e5+5;
 
class UnionFind{
public:
    int root[N];
    __int128 sum[N];
    __int128 num;
    void clear(int n){
        for(int i = 1; i <= n; i ++){
            root[i] = i;
            sum[i] = 1;
        }
        num = n;
    }
    int find(int x){
        int bossX = x;
        while (bossX != root[bossX]) {
            bossX = root[bossX];
        }
        while (x != bossX) {
            int tmp = root[x];
            root[x] = bossX;
            x = tmp;
        }
        return bossX;
    }
    bool join(int x, int y){
        int bossX = find(x), bossY = find(y);
        if(bossX == bossY) return false;
        -- num;
        if(sum[bossX] > sum[bossY]) swap(bossX, bossY);
        sum[bossY] += sum[bossX];
        root[bossX] = bossY;
        return true;
    }
}uf;
 
int main(int argc, char const *argv[]) {
    int n, m;
    scanf("%d%d", &n, &m);
    uf.clear(n);
    __int128 tmp = n;
    __int128 ans;
    if(n >= 4){
        ans = tmp*(tmp-1)*(tmp-2)*(tmp-3)/24;
    }else{
        ans = 0;
    }
    printf("%lld\n", (LL)ans);
    __int128 kkk = tmp * (tmp - 1) / 2;
    __int128 ssum = n;
    for(int i = 1; i <= m; i ++){
        int a, b;
        scanf("%d%d", &a, &b);
        int bossA = uf.find(a), bossB = uf.find(b);
        if(ans == 0 || bossA == bossB){
            printf("%lld\n", (LL)ans);
            continue;
        }
        if(uf.num <= 4){
            ans = 0;
            puts("0");
            continue;
        }
        __int128 together = uf.sum[bossA] + uf.sum[bossB];
        kkk -= uf.sum[bossA] * (ssum - uf.sum[bossA]);
        kkk -= uf.sum[bossB] * (ssum - together);
        ans -= uf.sum[bossA] * uf.sum[bossB] * kkk;
        kkk += together * (ssum - together);
        printf("%lld\n", (LL)ans);
        uf.join(bossA, bossB);
    }
    return 0;
}
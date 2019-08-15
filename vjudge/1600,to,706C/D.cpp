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
 
const int N = 555;

char mp[N][N];
bool use[N][N];
int n, m, k;
int cur;

void dfs(int i, int j){
    if(i < 1 || j < 1 || i > n || j > m) return ;
    if(cur == k) return ;
    if(mp[i][j] == '#' || mp[i][j] == 'X') return ;
    if(use[i][j]) return ;
    use[i][j] = true;
    dfs(i-1, j);
    dfs(i, j-1);
    dfs(i+1, j);
    dfs(i, j+1);
    if(cur == k) return ;
    mp[i][j] = 'X';
    cur ++;
    use[i][j] = false;
}

int main(int argc, char const *argv[]) {
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1; i <= n; i ++){
        scanf("%s", mp[i] + 1);
    }
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
            if(mp[i][j] == '.'){
                dfs(i, j);
                break;
            }
        }
        if(cur == k) break;
    }
    for(int i = 1; i <= n; i ++){
        printf("%s\n", mp[i] + 1);
    }
    return 0;
}
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
 
const int N = 1e4+5;
const int M = 1e4+5;
const LL MOD = 1e9+7;

struct Edge
{
    int to, next;
}edge[M];

int first[N], sign = 1;

inline void addEdge(int u, int v){
    edge[sign].to = v;
    edge[sign].next = first[u];
    first[u] = sign ++;
}

int a[N];
vector<pair<int, int> > p;

int main(int argc, char const *argv[]) {
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++){
        scanf("%d", &a[i]);
        p.push_back(make_pair(a[i], i));
    }
    sort(p.begin(), p.end(), greater<pair<int, int> >());
    for(int i = 1; i <= m; i ++){
        int u, v;
        scanf("%d%d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    LL ans = 0;
    for(int i = 0; i < p.size(); i ++){
        LL cur = 0;
        for(int j = first[p[i].second]; j != 0; j = edge[j].next){
            int to = edge[j].to;
            cur += 1LL * a[to];
        }
        a[p[i].second] = 0;
        ans += cur;
    }
    printf("%I64d\n", ans);
    return 0;
}
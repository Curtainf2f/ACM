#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define test(x) cerr << #x << "=" << x << endl
#else
    #define test(x)
#endif

typedef long long LL;
typedef pair<int, int> Height;
const int N = 1e5+5;
const int M = 1e4+5;
const int INF = 0x7fffffff;
const long double DINF = 1e18;

int n, m;
set<Height> hSorted;
int nac[N], nbc[N], h[N];
int ntc[N][17];
LL distA[N][17], distB[N][17];

void getNextCity(){
    hSorted.insert(make_pair(INF, 0));
    hSorted.insert(make_pair(INF-1, 0));
    hSorted.insert(make_pair(-INF+1, 0));
    hSorted.insert(make_pair(-INF, 0));
    for(int i = n; i >= 1; i --){
        set<Height>::iterator it = hSorted.lower_bound(make_pair(h[i], i));
        set<Height>::iterator pre = it;
        set<Height>::iterator next = it;
        pre --;
        next ++;
        set<Height>::iterator ppre = pre;
        ppre --;
        if(1LL*(it->first) - h[i] >= 1LL*h[i] - (pre->first)){
            nbc[i] = pre->second;
            if(1LL*(it->first) - h[i] >= 1LL*h[i] - (ppre->first)){
                nac[i] = ppre->second;
            }else{
                nac[i] = it->second;
            }
        }
        else{
            nbc[i] = it->second;
            if(1LL*(next->first) - h[i] >= 1LL*h[i] - (pre->first)){
                nac[i] = pre->second;
            }else{
                nac[i] = next->second;
            }
        }
        hSorted.insert(make_pair(h[i], i));
    }
}

inline int dist(int x, int y){
    return abs(h[x] - h[y]);
}

void getST(){
    for(int i = 1; i <= n; i ++){
        ntc[i][0] = nac[i];
        distA[i][0] = dist(i, nac[i]);
        distB[i][0] = 0;
    }
    for(int j = 1; j < 17; j ++){
        for(int i = 1; i <= n; i ++){
                if(j == 1){
                    int to = nac[i];
                    ntc[i][j] = nbc[to];
                    distA[i][j] = distA[i][j-1];
                    distB[i][j] = distB[i][j-1] + dist(to, nbc[to]);
                }else{
                    int to = ntc[i][j-1];
                    ntc[i][j] = ntc[to][j-1];
                    distA[i][j] = distA[i][j-1] + distA[to][j-1];
                    distB[i][j] = distB[i][j-1] + distB[to][j-1];
                }
        }
    }
}

pair<LL, LL> calS(int s, int x){
    pair<LL, LL> cur(0, 0);
    for(int i = 16; i >= 0; i --){
        if(ntc[s][i] && cur.first + cur.second + distA[s][i] + distB[s][i] <= x){
            cur.first += distA[s][i];
            cur.second += distB[s][i];
            s = ntc[s][i];
        }
    }
    return cur;
}

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++){
        scanf("%d", &h[i]);
    }
    getNextCity();
    getST();
    int s, x;
    scanf("%d", &x);
    pair<LL, LL> cur;
    long double _min = 1e18;
    for(int i = 1; i <= n; i ++){
        cur = calS(i, x);
        if(cur.second != 0){
            if(cur.first * 1.0 / cur.second < _min){
                _min = cur.first * 1.0 / cur.second;
                s = i;
            }else if(cur.first * 1.0 / cur.second == _min && h[i] > h[s]){
                s = i;
            }
        }else if(_min == INF && h[i] > h[s]){
            s = i;
        }
    }
    printf("%d\n", s);
    scanf("%d", &m);
    for(int i = 1; i <= m; i ++){
        scanf("%d%d", &s, &x);
        cur = calS(s, x);
        printf("%lld %lld\n", cur.first, cur.second);
    }
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
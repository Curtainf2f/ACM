#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define test(x) cerr << #x << "=" << x << endl
#else
    #define test(x)
#endif

typedef long long LL;

const int N = 1e5+5;
const LL INF = 0x7fffffffffffffff;

vector<pair<LL, LL> > c[205];
vector<int> id;
struct Node
{
    int h, c, p;
}node[N];

LL h[N], sumC[N];

inline int get(int x){
    return lower_bound(id.begin(), id.end(), x) - id.begin();
}

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    int n;
    while(~scanf("%d", &n)){
        memset(h, 0, sizeof(h));
        memset(sumC, 0, sizeof(sumC));
        for(int i = 1; i <= 200; i ++) c[i].clear();
        for(int i = 1; i <= n; i ++){
            scanf("%d%d%d", &node[i].h, &node[i].c, &node[i].p);
            id.push_back(node[i].h);
        }
        sort(id.begin(), id.end());
        id.erase(unique(id.begin(), id.end()), id.end());
        LL sum = 0;
        for(int i = 1; i <= n; i ++){
            node[i].h = get(node[i].h);
            c[node[i].c].push_back(make_pair(1LL*node[i].h, 1LL*node[i].p));
            sum += node[i].p;
            h[node[i].h] += 1LL * node[i].p;
            sumC[node[i].h] += (1LL * node[i].c * node[i].p);
        }
        for(int i = 1; i <= n; i ++){
            h[i] += h[i-1];
            sumC[i] += sumC[i-1];
        }
        for(int i = 1; i <= 200; i ++){
            sort(c[i].begin(), c[i].end());
            for(int j = 1; j < c[i].size(); j ++){
                c[i][j].second += c[i][j-1].second;
            }
        }
        LL ans = INF;
        for(int i = id.size() - 1; i >= 0; i --){
            LL cur = sum - h[id.size()] - h[i];
            LL cut = cur - 2*(h[i]-h[i-1]);
            LL cutalready = h[id.size()] - h[i];
            LL val = sumC[id.size()] - sumC[i];
            test(cur);
            test(cut);
            test(cutalready);
            test(val);
            int now = 1;
            while (cutalready < cut){
                LL delPos = lower_bound(c[now].begin(), c[now].end(), make_pair(1LL*i, 0LL)) - c[now].begin();
                if(cutalready + c[now][delPos].second <= cut){
                    cutalready += c[now][delPos].second;
                    val += 1LL * now * c[now][delPos].second;
                }else{
                    val += 1LL * now * (cut - cutalready);
                    cutalready = cut;
                }
                now ++;
            }
            ans = min(ans, val);
        }
        printf("%lld\n", ans);
    }
    // #ifdef _LOCAL
    //     fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    // #endif
    return 0;
}
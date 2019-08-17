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

int deg[N], vis[N];

pair<int, int> bfs(int s){
    fill(vis, vis + 7, 0);
    queue<pair<int, int> > q;
    q.push({s, 1});
    pair<int, int> ans(0, 0);
    while (!q.empty()) {
        pair<int, int> now = q.front();
        q.pop();
        if(vis[now.first]) continue;
        vis[now.first] = now.second;
        if(now.second > ans.second) ans = now;
        for(int i = first[now.first]; i != 0; i = edge[i].next){
            int to = edge[i].to;
            q.push({to, now.second + 1});
        }
    }
    return ans;
}

int path[N];
bool dfs(int now, int end){
    if(now == end){
        path[end] = 1;
        return true;
    }
    for(int i = first[now]; i != 0; i = edge[i].next){
        int to = edge[i].to;
        if(vis[to] == vis[now] + 1){
            if(dfs(to, end)){
                path[now] = 1;
                return true;
            }
        }
    }
    return false;
}

vector<int> link;
vector<int> anslink;
bool use[N];
void check(int now, int code = 1){
    if(use[now]) return;
    use[now] = true;
    for(int i = first[now]; i != 0; i = edge[i].next){
        int to = edge[i].to;
        if(path[to]) check(to, code + 1);
        else link.push_back(code);
    }
}

int main(int argc, char const *argv[]) {
    int t;
    scanf("%d", &t);
    while(t --){
        fill(deg, deg + 7, 0);
        sign = 1;
        fill(first, first + 7, 0);
        for(int i = 1; i <= 5; i ++){
            int a, b;
            scanf("%d%d", &a, &b);
            addEdge(a, b);
            addEdge(b, a);
            deg[a] ++;
            deg[b] ++;
        }
        pair<int, int> ans;
        int _max = 0;
        for(int i = 1; i <= 6; i ++){
            if(deg[i] == 1){
                pair<int, int> cur = bfs(i);
                show(i);
                if(cur.second > _max){
                    _max = cur.second, ans.first = i, ans.second = cur.first;
                    link.clear();
                    fill(path, path + 7, 0);
                    fill(use, use + 7, 0);
                    dfs(i, ans.second);
                    check(i);
                    sort(link.begin(), link.end());
                    anslink = link;
                    show(_max);
                }else if(cur.second == _max){
                    _max = cur.second, ans.first = i, ans.second = cur.first;
                    link.clear();
                    fill(path, path + 7, 0);
                    fill(use, use + 7, 0);
                    show(ans.second);
                    dfs(i, ans.second);
                    check(i);
                    sort(link.begin(), link.end());
                    for(int i = 0; i < link.size(); i ++){
                        if(link[i] < anslink[i]){
                            anslink = link;
                            break;
                        }
                    }
                }
            }
        }
        if(anslink.size() == 2){
            printf("%d,%d-dimethylbutane\n", anslink[0], anslink[1]);
        }else if(anslink.size() == 1){
            printf("%d-methylpentane\n", anslink[0]);
        }else{
            printf("n-hexane\n");
        }
    }
    return 0;
}
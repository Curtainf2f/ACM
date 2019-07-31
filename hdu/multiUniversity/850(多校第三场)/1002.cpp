#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define fuck(x) cerr << #x << "=" << x << endl
#else
    #define fuck(x)
#endif

class Graphics{
    const static int N = 100005;
    const static int M = 300005;
public:
    struct Edge{
        int to, next;
    }edge[M];
    struct Point{
        int dfn, low, color, cnt, ans;
        bool cut;
        Point(){dfn = low = color = 0;}
    }point[N], emptyPoint;
    int deg[N];
    int first[N], sign, sumOfPoint;
    int way[N];
    vector<int> center;
    queue<int> q;
    bool vis[N];
    void clear(int n){
        sign = 0;
        sumOfPoint = n;
        for(int i = 1; i <= n; i ++){
            first[i] = -1;
            vis[i] = false;
            deg[i] = 0;
            point[i] = emptyPoint;
        }
    }
    void addEdgeOneWay(int u, int v){
        edge[sign].to = v;
        edge[sign].next = first[u];
        deg[v] ++;
        first[u] = sign ++;
    }
    void getCnt(){
        for(int i = 1; i <= sumOfPoint; i ++){
            if(!deg[i]) center.push_back(i);
        }
        for(int cas = 0; cas < (int)center.size(); cas ++){
            q.push(center[cas]);
            for(int i = 1; i <= sumOfPoint; i ++) vis[i] = false;
            while (!q.empty()) {
                int now = q.front();
                q.pop();
                if(vis[now]) continue;
                vis[now] = true;
                point[now].cnt ++;
                for(int i = first[now]; i != -1; i = edge[i].next){
                    int to = edge[i].to;
                    q.push(to);
                }
            }
        }
    }
    void getCut(){
        for(int i = 0; i < (int)center.size(); i ++){
            for(int i = 1; i <= sumOfPoint; i ++) way[i] = 0;
            q.push(center[i]);
            while (q.push)
            {

            }
        }
    }
    void getAns(){
        for(int i = 1; i <= sumOfPoint; i ++) vis[i] = false;
        for(int i = 0; i < (int)center.size(); i ++) q.push(center[i]);
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            if(vis[now]) continue;
            vis[now] = true;
            for(int i = first[now]; i != -1; i = edge[i].next){
                int to = edge[i].to;
                if(point[to].cnt == point[now].cnt){
                    if(point[to].cut) point[to].ans = point[now].ans + 1;
                    else point[to].ans = point[now].ans;
                }else{
                    point[to].ans = 0;
                }
            }
        }
    }
    void preWork(){
        getCnt();
        getCut();
        getAns();
        for(int i = 1; i <= sumOfPoint; i ++){
            printf("%d cnt = %d isCut = %d ans = %d\n", i, point[i].cnt, point[i].cut, point[i].ans);
        }
        puts("center: ");
        for(int i = 0; i < (int)center.size(); i ++){
            printf("%d ", center[i]);
        }
        puts("");
    }
}graph;

int main() {
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    int t;
    scanf("%d", &t);
    while (t --)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        graph.clear(n);
        for(int i = 0, a, b; i < m; i ++){
            scanf("%d%d", &a, &b);
            graph.addEdgeOneWay(b, a);
        }
        graph.preWork();
        int q;
        scanf("%d", &q);
        while (q --) {
            int a, b;
            scanf("%d%d", &a, &b);
            printf("%d\n", graph.point[a].ans + graph.point[b].ans + 2);
        }
        
    }
    
    #ifdef _LOCAL
        fprintf(stderr, "\nTime elapsed: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
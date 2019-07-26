#include<stdio.h>
#include<deque>
#include<algorithm>
using namespace std;

class Graphics{
const static int MAXN = 505;
const static int MAXM = 2505 * 2 + 205;
const static int INF = 0x7fffffff;
private:
    struct Edge{
        int to, dist, next;
    }edge[MAXM];
    int first[MAXN], sign, sumOfPoint;
public:
    void init(int n){
        sumOfPoint = n;
        for(int i = 1; i <= n; i ++){
            first[i] = -1;
        }
        sign = 0;
    }
    void addEdgeOneWay(int u, int v, int w){
        edge[sign].dist = w;
        edge[sign].to = v;
        edge[sign].next = first[u];
        first[u] = sign ++;
    }
    void addEdgeTwoWay(int u, int v, int w){
        addEdgeOneWay(u, v, w);
        addEdgeOneWay(v, u, w);
    }
    bool spfaNegRing(int start){
        bool *vis = new bool[sumOfPoint+1];
        int *dist = new int[sumOfPoint+1];
        int *cnt = new int[sumOfPoint+1];
        for(int i = 1; i <= sumOfPoint; i ++){
            vis[i] = 0;
            cnt[i] = 0;
            dist[i] = INF;
        }
        deque<int> que;
        que.push_front(start);
        dist[start] = 0;
        vis[start] = 1;
        while(!que.empty()){
            int now = que.front();
            que.pop_front();
            vis[now] = 0;
            for(int i = first[now]; i != -1; i = edge[i].next){
                int to = edge[i].to, eDist = edge[i].dist;
                if(dist[now] + eDist < dist[to]){
                    dist[to] = dist[now] + eDist;
                    cnt[to] ++;
                    if(cnt[to] >= sumOfPoint) {
                        delete []vis; delete []dist; return true;
                    }
                    if(!vis[to]){
                        vis[to] = 1;
                        if(que.empty() || dist[to] <= dist[que.front()])
                            que.push_front(to);
                        else
                            que.push_back(to);
                    }
                }
            }
        }
        delete []vis; delete []dist; return false;
    }
}graph;

int main(){
    int f;
    scanf("%d", &f);
    while(f --){
        int n, m, w;
        scanf("%d%d%d", &n, &m, &w);
        graph.init(n);
        while(m --){
            int s, e, t;
            scanf("%d%d%d", &s, &e, &t);
            graph.addEdgeTwoWay(s, e, t);
        }
        while(w --){
            int s, e, t;
            scanf("%d%d%d", &s, &e, &t);
            graph.addEdgeOneWay(s, e, -t);
        }
        printf("%s\n", graph.spfaNegRing(1) ? "YES" : "NO");
    }
    return 0;
}

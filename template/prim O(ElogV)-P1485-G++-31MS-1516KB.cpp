#include <cstdio>
#include <queue>
using namespace std;

const int MAXN = 105;
const int MAXM = MAXN * (MAXN - 1) + MAXN * (MAXN + 1);

class Graphics
{
private:
    struct Edge
    {
        int to, cost, next;
        Edge(){}
        Edge(int to, int cost):to(to), cost(cost){}
        bool friend operator < (const Edge &a, const Edge &b){
            return a.cost > b.cost;
        }
    }edge[MAXM];
    int first[MAXN], sign, sumOfPoint;
public:
    inline void clear(int n){
        sumOfPoint = n;
        for (int i = 0; i <= sumOfPoint; ++i){
            first[i] = -1;
        }
        sign = 0;
    }
    inline void addEdgeOneWay(int u, int v, int cost){
        edge[sign].cost = cost;
        edge[sign].to = v;
        edge[sign].next = first[u];
        first[u] = sign ++;
    }
    inline void addEdgeTwoWay(int u, int v, int cost){
        addEdgeOneWay(u, v, cost);
        addEdgeOneWay(v, u, cost);
    }
    int prim(){
        priority_queue<Edge> que;
        vector<bool> visit(sumOfPoint+1, false);
        int cost = 0, now = 1;
        visit[1] = 1;
        for(int time = 0; time < sumOfPoint - 1; time ++){
            for (int i = first[now]; i != -1; i = edge[i].next){
                int to = edge[i].to, cost = edge[i].cost;
                if(!visit[to]){
                    que.push(Edge(to, cost));
                }
            }
            while(!que.empty() && visit[que.top().to])
                que.pop();
            if(que.empty()) return -1;
            Edge shortEdge = que.top();
            que.pop();
            cost += shortEdge.cost;
            visit[shortEdge.to] = 1;
            now = shortEdge.to;
        }
        return cost;
    }
}graph;

int main(int argc, char const *argv[])
{
    int n, cost;
    while(~scanf("%d", &n)){
        graph.clear(n);
        for(int i = 1; i <= n; i ++){
            for(int j = 1; j <= n; j ++){
                scanf("%d", &cost);
                if(i != j){
                    graph.addEdgeOneWay(i, j, cost);
                }
            }
        }
        int q;
        scanf("%d", &q);
        while(q --){
            int a, b;
            scanf("%d%d", &a, &b);
            graph.addEdgeTwoWay(a, b, 0);
        }
        printf("%d\n", graph.prim());
    }
    return 0;
}

#include<cstdio>
#include<queue>
using namespace std;

const int MAXN = 1005;
const int MAXM = 4005;
const int INF = 0x3f3f3f3f;

class Graphics{
private:
    struct Edge{
        int to, next, dist;
    }edge[MAXM];
    int first[MAXN], sign;
    int sumOfPoint;
public:
    void clear(int n){
        sumOfPoint = n;
        sign = 0;
        for(int i = 0; i <= sumOfPoint; i ++){
            first[i] = -1;
        }
    }
    void addEdgeOneWay(int u, int v, int dist){
        edge[sign].to = v;
        edge[sign].dist = dist;
        edge[sign].next = first[u];
        first[u] = sign ++;
    }
    void addEdgeTwoWay(int u, int v, int dist){
        addEdgeOneWay(u, v, dist);
        addEdgeOneWay(v, u, dist);
    }
    int spfa(int u, int v){
        vector<bool> visit(sumOfPoint + 1, false);
        vector<int> dist(sumOfPoint + 1, INF);
        queue<int> bfs;
        bfs.push(u);
        visit[u] = 1;
        dist[u] = 0;
        while(!bfs.empty()){
            int now = bfs.front();
            bfs.pop();
            visit[now] = 0;
            for(int i = first[now]; i != -1; i = edge[i].next){
                int to = edge[i].to, w = edge[i].dist;
                if(dist[to] > w + dist[now]){
                    dist[to] = w + dist[now];
                    if(!visit[to]){
                        bfs.push(to);
                        visit[to] = 1;
                    }
                }
            }
        }
        return dist[v];
    }
}graph;

int main(){
    int SumofPoint_l_i, Start_l_i, End_l_i;
    while(~scanf("%d%d%d", &SumofPoint_l_i, &Start_l_i, &End_l_i)){
        graph.clear(SumofPoint_l_i);
        for(int i = 1; i <= SumofPoint_l_i; i ++){
            int SumofDestination_t_i, End_t_i;
            scanf("%d%d", &SumofDestination_t_i, &End_t_i);
            graph.addEdgeOneWay(i, End_t_i, 0);
            for(int j_t_i = 1; j_t_i < SumofDestination_t_i; j_t_i ++){
                scanf("%d", &End_t_i);
                graph.addEdgeOneWay(i, End_t_i, 1);
            }
        }
        int Ans_t_i = graph.spfa(Start_l_i, End_l_i);
        if(Ans_t_i == INF){
            puts("-1");
        }
        else{
            printf("%d\n", Ans_t_i);
        }
    }
    return 0;
}

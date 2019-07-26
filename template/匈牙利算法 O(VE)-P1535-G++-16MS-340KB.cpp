#include <cstdio>

const int MAXM = 205*205;
const int MAXN = 405;

class Graphics{
private:
    struct Edge
    {
        int to, next;
    }edge[MAXM];
    int first[MAXN], sign, sumOfPoint, link[MAXN];
    bool visit[MAXN];
    bool found(int x){
        for(int i = first[x]; i != -1; i = edge[i].next){
            int to = edge[i].to;
            if(!visit[to]){
                visit[to] = 1;
                if(!link[to] || found(link[to])){
                    link[to] = x;
                    return 1;
                }
            }
        }
        return 0;
    }
public:
    void clear(int n){
        sumOfPoint = n;
        for(int i = 0; i <= n; i ++){
            first[i] = -1;
            link[i] = 0;
        }
        sign = 0;
    }
    inline void addEdgeOneWay(int u, int v){
        edge[sign].to = v;
        edge[sign].next = first[u];
        first[u] = sign ++;
    }
    inline void addEdgeTwoWay(int u, int v){
        addEdgeOneWay(u, v);
        addEdgeOneWay(v, u);
    }
    int hungarian(int matchRange){
        int ans = 0;
        for (int i = 0; i <= matchRange; ++i){
            for (int j = 0; j <= sumOfPoint; ++j){
                visit[j] = 0;
            }
            if(found(i)){
                ans ++;
            }
        }
        return ans;
    }
}graph;

int main(int argc, char const *argv[])
{
    int SumofCow, SumofStalls;
    while(~scanf("%d%d", &SumofCow, &SumofStalls)){
        graph.clear(SumofCow + SumofStalls);
        for (int i = 1; i <= SumofCow; ++i){
            int SumofLikeStalls;
            scanf("%d", &SumofLikeStalls);
            while(SumofLikeStalls --){
                int x;
                scanf("%d", &x);
                graph.addEdgeTwoWay(i, x + SumofCow);
            }
        }
        printf("%d\n", graph.hungarian(SumofCow));
    }
    return 0;
}

#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define test(x) cerr << #x << "=" << x << endl
#else
    #define test(x)
#endif
#define lson(x) x << 1
#define rson(x) x << 1 | 1

typedef long long LL;

const int N = 350005;
const int M = 5000005;
const int INF = 0x3f3f3f3f;

class Graphics{
private:
    struct Edge{
        int to, next, flow;
    }edge[M]; // 用链式前向星记录,flow为残量cf
    int n;
    int first[N], sign; // first为链式前向星的头指针, sign为指向edge的移动指针
    int depth[N], cur[N]; // depth为bfs序, cur为弧优化
    int start, end;// start为源点s end为汇点t
    void addEdgeOneWay(int u, int v, int flow){// 添加一条边，并且cf(u,v)=flow
        edge[sign].next = first[u];
        edge[sign].flow = flow;
        edge[sign].to = v;
        first[u] = sign ++;
    }
    bool bfs(){// 广搜搜索增广路
        memset(depth, 0, sizeof(int)*(n+1));
        queue<int> que;
        que.push(start); depth[start] = 1;
        while(!que.empty()){
            int now = que.front();
            que.pop();
            for(int i = first[now]; i != -1; i = edge[i].next){
                int to = edge[i].to, flow = edge[i].flow;
                if(!depth[to] && flow){ // 如果该边残量cf(u,v)=0也就没有增广价值了
                    depth[to] = depth[now] + 1;
                    que.push(to);
                    if(to == end) return true;
                }
            }
        }
        return false;
    }
    int dfs(int now, int pFlow){// 单路增广+弧优化, pFlow为到now这个点所经过的边的min(cf(u,v))
        if(now == end) return pFlow;
        for(int &i = cur[now]; i != -1; i = edge[i].next){// 弧优化，意思是在本次单路增广结束后，下一次增广无需将边从头开始遍历，接上上一次增广路之后搜索即可
            int to = edge[i].to;
            if(depth[to] == depth[now] + 1 && edge[i].flow){
                int flow = dfs(to, min(edge[i].flow, pFlow));
                if(flow){// flow为now到源点t(end)时的pFlow，也就是min(cf(u,v))
                    edge[i].flow -= flow;//将增广路所有cf(u,v)-=flow, cf(v,u)+=flow
                    edge[i^1].flow += flow;// 正向边与反向边是成对建的，所以(正向边^1=反向边)，(反向边^1=正向边)
                    return flow;
                }
            }
        }
        return 0;
    }
public:
    Graphics(int s, int e){clear(s, e);}
    Graphics(){clear(1, 1);}
    void setN(int n){// 缩小初始化范围
        this->n = n;
    }
    void clear(int s, int t){// 初始化s为源点,t为汇点
        sign = 0;
        n = N - 1;
        start = s;
        end = t;
        memset(first, 0xff, sizeof(int)*(n+1));
    }
    void addEdgeFlowWay(int u, int v, int flow){// 网络流边需增加残量为0的反向边
        addEdgeOneWay(u, v, flow);
        addEdgeOneWay(v, u, 0);
    }
    int dinic(){// 一样的松弛增广路直到无增广路后返回结果
        int maxFlow = 0;
        while(bfs()){
            memcpy(cur, first, sizeof(int)*(n+1));
            while(int flow = dfs(start, INF)){
                maxFlow += flow;
            }
        }
        return maxFlow;
    }
}g;

int a[N];

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    int n;
    scanf("%d", &n);
    for(int i = 1, x; i <= n; i ++){
        scanf("%d", &x);
        a[x] ++;
    }
    g.clear(0, 333333);
    g.setN(N-3);
    for(int i = 1; i <= 150000; i ++){
        g.addEdgeFlowWay(0, i, a[i]);
        g.addEdgeFlowWay(i, i + 160000, 1);
        g.addEdgeFlowWay(i, i + 160001, 1);
        if(i != 1) g.addEdgeFlowWay(i, i + 159999, 1);
        g.addEdgeFlowWay(i + 160000, 333333 , 1);
    }
    g.addEdgeFlowWay(150001 + 160000, 333333, 1);
    printf("%d\n", g.dinic());
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
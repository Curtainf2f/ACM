#include<stdio.h>
#include<vector>
#include<queue>
using namespace std;

const int MAXN = 505;
const int MAXM = 3e4+5;
const int INF = 0x3f3f3f3f;

template <typename T>
class Graphics {
private:
    struct Edge {
        int to, next;
        T w;
    } edge[MAXM];
    int first[MAXN], sign;
    int sumOfPoint;
    struct Node{
        int to;
        T w;
        Node(int a, int b):to(a), w(b){}
        Node(){}
        bool friend operator < (const Node &a, const Node &b){
            return a.w > b.w;
        }
    };
public:
    void clear(int n) {
        sumOfPoint = n;
        for(int i = 1; i <= n; i ++) {
            first[i] = -1;
        }
        sign = 0;
    }
    void addEdgeOneWay(int u, int v, int w) {
        edge[sign].to = v;
        edge[sign].w = w;
        edge[sign].next = first[u];
        first[u] = sign ++;
    }
    void addEdgeTwoWay(int u, int v, int w) {
        addEdgeOneWay(u, v, w);
        addEdgeOneWay(v, u, w);
    }
    vector<T> dijkstra(const vector<int> &start) {
        vector<T> dist(sumOfPoint+1, INF);
        vector<bool> visit(sumOfPoint+1);
        priority_queue<Node> bfs;
        for(unsigned i = 0; i < start.size(); i ++) {
            bfs.push(Node(start[i], 0));
        }
        while(!bfs.empty()) {
            Node now = bfs.top();
            bfs.pop();
            if(visit[now.to]) {
                continue;
            }
            visit[now.to] = true;
            dist[now.to] = now.w;
            for(int i = first[now.to]; i != -1; i = edge[i].next) {
                int to = edge[i].to, w = edge[i].w;
                if(!visit[to]) {
                    bfs.push(Node(to, now.w + w));
                }
            }
        }
        return dist;
    }
};

class Solution {
private:
    int n, m, u, v, w, k;
    int kk[MAXN];
    Graphics<int> graph;
public:
    void solve() {
        int t;
        scanf("%d", &t);
        while(t --) {
            scanf("%d%d", &n, &m);
            graph.clear(n);
            while(m --) {
                scanf("%d%d%d", &u, &v, &w);
                graph.addEdgeOneWay(u, v, w);
            }
            scanf("%d", &k);
            for(int i = 0; i < k; i ++) {
                scanf("%d", &kk[i]);
            }
            int ans = INF;
            for(int i = 0; i < 10; i ++) {
                vector<int> first, second;
                for(int j = 0; j < k; j ++) {
                    if(kk[j] >> i & 1) {
                        first.push_back(kk[j]);
                    } else {
                        second.push_back(kk[j]);
                    }
                }
                vector<int> cur = graph.dijkstra(first);
                for(unsigned j = 0; j < second.size(); j ++) {
                    ans = min(ans, cur[second[j]]);
                }
                cur = graph.dijkstra(second);
                for(unsigned j = 0; j < first.size(); j ++){
                    ans = min(ans, cur[first[j]]);
                }
            }
            printf("%d\n", ans);
        }
    }
} DarkScoCu;

int main() {
    DarkScoCu.solve();
    return 0;
}

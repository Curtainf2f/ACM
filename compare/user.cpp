#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define test(x) cerr << #x << "=" << x << endl
#else
    #define test(x)
#endif

const int N = 505;
const int M = N * N;
const int INF = 0x7f7f7f7f;

class Graphics
{
private:
	struct Edge
	{
		int to, cost, vol, next;
	} edge[M << 1];
	int first[N], sign, prePoint[N], preEdge[N], dist[N];
    int h[N];
	int sumOfPoint, start, end;
    void dijkstra() {
        fill(dist, dist + 1 + sumOfPoint, INF);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int> > > q;
        dist[start] = 0;
        q.push(make_pair(0, start));
        while(!q.empty()) {
            pair<int, int> now = q.top();
            q.pop();
            if(dist[now.second] < now.first) continue;
            for(int i = first[now.second]; i != -1; i = edge[i].next) {
                int to = edge[i].to, w = edge[i].cost, vol = edge[i].vol;
                if(!vol) continue;
                if(dist[to] == INF || dist[to] > now.first + w + h[now.second] - h[to]) {
                    dist[to] = now.first + w + h[now.second] - h[to];
                    prePoint[to] = now.second;
                    preEdge[to] = i;
                    q.push(make_pair(dist[to], to));
                }
            }
        }
    }
public:
	void clear(int n) {
		sumOfPoint = n;
        fill(h, h + n + 1, 0);
        fill(first, first + n + 1, -1);
		sign = 0;
	}
	inline void addEdgeOneWay(int u, int v, int vol, int cost) {
		edge[sign].to= v;
		edge[sign].vol = vol;
		edge[sign].cost = cost;
		edge[sign].next = first[u];
        first[u] = sign ++;
	}
	inline void addNetWorkEdge(int u, int v, int vol, int cost) {
		addEdgeOneWay(u, v, vol, cost);
		addEdgeOneWay(v, u, 0, -cost);
	}
	int minCostFlow(int u, int v) {
		start = u;
		end = v;
		int cost = 0;
		int flow = 0;
		while(1) {
            dijkstra();
            if(dist[end] == INF) break;
            for(register int i = 1; i <= sumOfPoint; i ++)
                h[i] += (dist[i] != INF) ? dist[i] : 0;
			int augmentMaxFlow = INF;
			for(int now = end; now != start; now = prePoint[now]) {
				if(edge[preEdge[now]].vol < augmentMaxFlow) {
					augmentMaxFlow = edge[preEdge[now]].vol;
				}
			}
			flow += augmentMaxFlow;
			cost += augmentMaxFlow * h[end];
			for(int now = end; now != start; now = prePoint[now]) {
				edge[preEdge[now]].vol -= augmentMaxFlow;
				edge[preEdge[now] ^ 1].vol += augmentMaxFlow;
			}
		}
		return cost;
	}
}graph;

int main()
{
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
	int n, m, k, p;
	while(~scanf("%d%d%d%d", &n, &m, &k, &p)) {
		graph.clear(n * 2 + m + 2);
		int Start = 0, End = n * 2 + m + 1;
		for(int i = 1; i <= n; i ++) {
			graph.addNetWorkEdge(i, i + n, 1, 0);
			graph.addNetWorkEdge(i + n, End, 1, 0);
		}
		int KaiCaiZhan = n * 2;
		for(int i = 0; i < n; i ++) {
			int x;
			scanf("%d", &x);
			graph.addNetWorkEdge(Start, KaiCaiZhan + x, 1, 0);
		}
		for(int i = 0; i < k; i ++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			graph.addNetWorkEdge(KaiCaiZhan + a, KaiCaiZhan + b, INF, c);
			graph.addNetWorkEdge(KaiCaiZhan + b, KaiCaiZhan + a, INF, c);
		}
		for(int i = 0; i < p; i ++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			graph.addNetWorkEdge(KaiCaiZhan + b, a, INF, c);
		}
		printf("%d\n", graph.minCostFlow(Start, End));
	}
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
	return 0;
}
#include<stdio.h>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;

const int MAXN = 505;
const int MAXM = MAXN * MAXN;
const int INF = 0x7f7f7f7f;

class Graphics
{
private:
	struct Edge
	{
		int to, cost, vol, next;
	} edge[MAXM << 1];
	int first[MAXN], sign, prePoint[MAXN], preEdge[MAXN], dist[MAXN];
	int sumOfPoint, start, end;
	bool spfa() {
	    vector<bool> visit(sumOfPoint+1, false);
		for (int i = 0; i <= sumOfPoint; ++i) {
			prePoint[i] = -1;
			dist[i] = INF;
		}
		dist[start] = 0;
		queue<int> bfs;
		bfs.push(start);
		visit[start] = true;
		while(!bfs.empty()) {
			int now = bfs.front();
			bfs.pop();
			visit[now] = 0;
			for(int i = first[now]; i != -1; i = edge[i].next) {
				int to = edge[i].to, cost = edge[i].cost, vol = edge[i].vol;
				if(vol > 0 && dist[now] + cost < dist[to]) {
					dist[to] = dist[now] + cost;
					prePoint[to] = now;
					preEdge[to] = i;
					if(!visit[to]){
                        bfs.push(to);
                        visit[to] = true;
					}
				}
			}
		}
		return prePoint[end] != -1;
	}
public:
	void clear(int n) {
		sumOfPoint = n;
		for (int i = 0; i <= n; ++i) {
			first[i] = -1;
		}
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
		while(spfa()) {
			int augmentMaxFlow = INF;
			for(int now = end; now != start; now = prePoint[now]) {
				if(edge[preEdge[now]].vol < augmentMaxFlow) {
					augmentMaxFlow = edge[preEdge[now]].vol;
				}
			}
			flow += augmentMaxFlow;
			cost += augmentMaxFlow * dist[end];
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
	return 0;
}

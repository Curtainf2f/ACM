#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define test(x) cerr << #x << "=" << x << endl
#else
    #define test(x)
#endif

typedef long long LL;

const int N = 1e5+5;

bool use[N];
pair<int, int> mp[N];

struct Node
{
    int now, left, right;
    Node(){}
    Node(int now, int left, int right):now(now), left(left), right(right){}
};


queue<Node> q;

struct Edge
{
    int to, next, l, r;
}edge[N<<1];

int first[N], sign = 1;

inline void addEdge(int u, int v, int l, int r){
    edge[sign].to = v;
    edge[sign].l = l;
    edge[sign].r = r;
    edge[sign].next = first[u];
    first[u] = sign ++;
}

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i ++){
        int u, v, l, r;
        scanf("%d%d%d%d", &u, &v, &l, &r);
        addEdge(u, v, l, r);
        addEdge(v, u, l, r);
    }
    q.push(Node(1, 1, n));
    while(!q.empty()){
        Node now = q.front();
        q.pop();
        if(use[now.now] && mp[now.now].first <= now.left && mp[now.now].second >= now.right) continue;
        if(!use[now.now]) mp[now.now].first = now.left, mp[now.now].second = now.right;
        else 
        use[now.now] = true;

    }
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
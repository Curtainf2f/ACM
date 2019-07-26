#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<vector>
using namespace std;

const int MAXN = 500005;

template <typename T>
class SegmentTree {
private:
    struct Node {
        int left, right;
        T sum, lazy;
    } node[MAXN << 2];
    T data[MAXN];
    void pushUp(int root) {
        node[root].sum = node[root << 1].sum + node[root << 1 | 1].sum;
    }
    void pushDown(int root) {
        if(node[root].left == node[root].right) return;
        int lson = root << 1;
        int rson = root << 1 | 1;
        node[lson].sum += node[root].lazy * (node[lson].right - node[lson].left + 1);
        node[rson].sum += node[root].lazy * (node[rson].right - node[rson].left + 1);
        node[lson].lazy += node[root].lazy;
        node[rson].lazy += node[root].lazy;
        node[root].lazy = 0;
    }
public:
    void build(int left, int right, int root = 1) {
        node[root].left = left;
        node[root].right = right;
        node[root].lazy = 0;
        if(left == right) {
            node[root].sum = data[left];
        } else {
            int mid = (left + right) >> 1;
            build(left, mid, root << 1);
            build(mid + 1, right, root << 1 | 1);
            pushUp(root);
        }
    }
    void update(int left, int right, T value, int root = 1) {
        int lson = root << 1;
        int rson = root << 1 | 1;
        node[root].sum += value * (right - left + 1);
        if(node[root].left == left && node[root].right == right) {
            node[root].lazy += value;
            return ;
        }
        if(left >= node[rson].left) {
            update(left, right, value, rson);
        } else if(right <= node[lson].right) {
            update(left, right, value, lson);
        } else {
            update(left, node[lson].right, value, lson);
            update(node[rson].left, right, value, rson);
        }
    }
    T query(int left, int right, int root = 1) {
        int lson = root << 1;
        int rson = root << 1 | 1;
        if(node[root].lazy) pushDown(root);
        if(node[root].left == left && node[root].right == right) {
            return node[root].sum;
        }
        if(left >= node[rson].left) {
            return query(left, right, rson);
        } else if(right <= node[lson].right) {
            return query(left, right, lson);
        } else {
            return query(left, node[lson].right, lson) + query(node[rson].left, right, rson);
        }
    }
    void clear(int n, const vector<int> &d) {
        for(int i = 1; i <= n; i ++) {
            this->data[i] = d[i];
        }
        build(1, n);
    }
};

template <typename T>
class TreeToLink {
private:
    struct Point {
        int size, son, depth, father, top, newId;
        T data;
    } point[MAXN];
    struct Edge {
        int to, next;
    } edge[MAXN << 1];
    int oldId[MAXN], first[MAXN], sign, sumOfPoint, cnt;
    SegmentTree<T> st;
    void dfs1(int u, int father = 0, int depth = 1) {
        point[u].depth = depth;
        point[u].father = father;
        point[u].size = 1;
        int maxson = -1;
        for(int i = first[u]; i != -1; i = edge[i].next) {
            int to = edge[i].to;
            if(to == father) continue;
            dfs1(to, u, depth + 1);
            point[u].size += point[to].size;
            if(point[to].size > maxson) {
                point[u].son = to;
                maxson = point[to].size;
            }
        }
    }
    void dfs2(int u, int top) {
        point[u].newId = ++cnt;
        oldId[cnt] = u;
        point[u].top = top;
        if(point[u].son == -1) {
            return ;
        }
        dfs2(point[u].son, top);
        for(int i = first[u]; i != -1; i = edge[i].next) {
            int to = edge[i].to;
            if(to == point[u].son || to == point[u].father) continue;
            dfs2(to, to);
        }
    }
public:
    void clear(int n) {
        sumOfPoint = n;
        sign = 0;
        cnt = 0;
        for(int i = 1; i <= n; i ++) {
            first[i] = -1;
            point[i].son = -1;
            scanf("%d", &point[i].data);
        }
    }
    void addEdgeOneWay(int u, int v) {
        edge[sign].to = v;
        edge[sign].next = first[u];
        first[u] = sign ++;
    }
    void addEdgeTwoWay(int u, int v) {
        addEdgeOneWay(u, v);
        addEdgeOneWay(v, u);
    }
    void preWork(int x = 1) {
        dfs1(x);
        dfs2(x, x);
        vector<int> data(sumOfPoint + 1);
        for(int i = 1; i <= sumOfPoint; i ++) {
            data[i] = point[oldId[i]].data;
        }
        st.clear(sumOfPoint, data);
    }
    void updatePath(int x, int y, T z){
        while(point[x].top != point[y].top){
            if(point[point[x].top].depth < point[point[y].top].depth)
                swap(x, y);
            st.update(point[point[x].top].newId, point[x].newId, z);
            x = point[point[x].top].father;
        }
        if(point[x].depth > point[y].depth)
            swap(x, y);
        st.update(point[x].newId, point[y].newId, z);
    }
    T queryPath(int x, int y){
        T ans = 0;
        while(point[x].top != point[y].top){
            if(point[point[x].top].depth < point[point[y].top].depth)
                swap(x, y);
            ans += st.query(point[point[x].top].newId, point[x].newId);
            x = point[point[x].top].father;
        }
        if(point[x].depth > point[y].depth)
            swap(x, y);
        ans += st.query(point[x].newId, point[y].newId);
        return ans;
    }
    void updateSon(int x, T z){
        st.update(point[x].newId, point[x].newId + point[x].size - 1, z);
    }
    T querySon(int x){
        return st.query(point[x].newId, point[x].newId + point[x].size - 1);
    }
    T queryPoint(int x) {
        return queryPath(x, x);
    }
    void updatePoint(int x, T z) {
        updatePath(x, x, z);
    }
};

class Solution {
private:
    int n, m, p;
    TreeToLink<int> ttl;
public:
    void solve() {
        while(~scanf("%d%d%d", &n, &m, &p)){
            ttl.clear(n);
            for(int i = 0, a, b; i < m; i ++) {
                scanf("%d%d", &a, &b);
                ttl.addEdgeTwoWay(a, b);
            }
            ttl.preWork();
            while(p --) {
                char opt;
                int a, b, c;
                scanf(" %c%d", &opt, &a);
                if(opt == 'I') {
                    scanf("%d%d", &b, &c);
                    ttl.updatePath(a, b, c);
                } else if(opt == 'D') {
                    scanf("%d%d", &b, &c);
                    ttl.updatePath(a, b, -c);
                } else if(opt == 'Q') {
                    printf("%d\n", ttl.queryPoint(a));
                }
            }
        }
    }
} DarkScoCu;

int main() {
    DarkScoCu.solve();
    return 0;
}
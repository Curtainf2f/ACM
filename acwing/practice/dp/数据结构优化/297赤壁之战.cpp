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

const int N = 1e6+5;
const LL INF = 0x3f3f3f3f3f3f3f3f;

template<typename T>
class SegmentTree{
private:
    struct Node
    {
        int left, right;
        T _min;
    }node[N<<2];
    void pushUp(int root){
        node[root]._min = min(node[lson(root)]._min, node[rson(root)]._min);
    }
public:
    T data[N];
    void build(int left, int right, int root = 1){
        node[root].left = left;
        node[root].right = right;
        if(left == right){
            node[root]._min = data[left];
            return ;
        }
        int mid = left + right >> 1;
        build(left, mid, lson(root));
        build(mid + 1, right, rson(root));
        pushUp(root);
    }
    void update(int pos, T value, int root = 1){
        if(node[root].left == node[root].right){
            node[root]._min = value;
            return ;
        }
        int mid = node[root].left + node[root].right >> 1;
        if(pos <= mid) update(pos, value, lson(root));
        else update(pos, value, rson(root));
        pushUp(root);
    }
    T findMin(int left, int right, int root = 1){
        if(left == node[root].left && right == node[root].right){
            return node[root]._min;
        }
        int mid = node[root].left + node[root].right >> 1;
        if(right <= mid) return findMin(left, right, lson(root));
        else if(left > mid) return findMin(left, right, rson(root));
        else return min(findMin(left, mid, lson(root)), findMin(mid + 1, right, rson(root)));
    }
};

SegmentTree<LL> tree;

struct Cost{
    int left, right, cost;
    bool operator < (const Cost &a){
        if(right == a.right) return left < a.left;
        return right < a.right;
    }
}cost[N];

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    int n, m, e;
    scanf("%d%d%d", &n, &m, &e);
    for(int i = 1; i <= n; i ++) scanf("%d%d%d", &cost[i].left, &cost[i].right, &cost[i].cost), cost[i].left ++, cost[i].right ++;
    e ++;
    for(int i = m; i <= e; i ++) tree.data[i] = INF;
    tree.data[m] = 0;
    tree.build(m, e);
    sort(cost + 1, cost + 1 + n);
    for(int i = 1; i <= n; i ++){
        LL change = tree.data[cost[i].right];
        test(cost[i].left);
        test(cost[i].right);
        tree.data[cost[i].right] = min(tree.data[cost[i].right], tree.findMin(cost[i].left - 1, cost[i].right - 1) + cost[i].cost);
        test(tree.data[cost[i].right]);
        if(tree.data[cost[i].right] != change) tree.update(cost[i].right, tree.data[cost[i].right]);
    }
    printf("%lld\n", tree.data[e] == INF ? -1 : tree.data[e]);
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
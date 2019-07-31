#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define test(x) cerr << #x << "=" << x << endl
#else
    #define test(x)
#endif

typedef long long LL;

const int N = 2e5+5;

int a[N];

struct SegmentTree {
    struct node {
        int l, r, num, lazy;
    } t[N << 2];

    void build(int rt, int l, int r) {
        t[rt].l = l;
        t[rt].r = r;
        t[rt].lazy = 0;
        if(l == r) {
            t[rt].num = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(rt << 1, l, mid);
        build(rt << 1 | 1, mid + 1, r);
    }

    void update(int rt, int l, int r, int value) {
        if(t[rt].l == l && t[rt].r == r) {
            t[rt].lazy = value;
            return;
        }
        if(t[rt].lazy)
            push_down(rt);
        int mid = (t[rt].l + t[rt].r) >> 1;
        if(r <= mid)
            update(rt << 1, l, r, value);
        else {
            if(l > mid)
                update(rt << 1 | 1, l, r, value);
            else {
                update(rt << 1, l, mid, value);
                update(rt << 1 | 1, mid + 1, r, value);
            }
        }
    }
    void del(int rt, int l, int r, int value) {
        if(t[rt].l == l && t[rt].r == r) {
            t[rt].num = value;
            return;
        }
        if(t[rt].lazy)
            push_down(rt);
        int mid = (t[rt].l + t[rt].r) >> 1;
        if(r <= mid)
            del(rt << 1, l, r, value);
        else {
            if(l > mid)
                del(rt << 1 | 1, l, r, value);
            else {
                del(rt << 1, l, mid, value);
                del(rt << 1 | 1, mid + 1, r, value);
            }
        }
    }
    int query(int rt, int l, int r) {
        if(t[rt].l == l && t[rt].r == r)
            return t[rt].num;
        if(t[rt].lazy)
            push_down(rt);
        int mid = (t[rt].l + t[rt].r) >> 1;
        if(r <= mid)
            return query(rt << 1, l, r);
        if(l > mid)
            return query(rt << 1 | 1, l, r);
        return query(rt << 1, l, mid) + query(rt << 1 | 1, mid + 1, r);
    }

    inline void push_down(int rt) {
        int lson = rt << 1, rson = rt << 1 | 1;
        if(t[lson].num < t[rt].lazy) t[lson].num = t[rt].lazy;
        if(t[rson].num < t[rt].lazy) t[rson].num = t[rt].lazy;
        t[lson].lazy = t[rt].lazy;
        t[rson].lazy = t[rt].lazy;
        t[rt].lazy = 0;
    }
}tree;

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
    tree.build(1, 1, n);
    int q;
    scanf("%d", &q);
    for(int i = 1; i <= q; i ++){
        int x, y, z;
        scanf("%d%d", &x, &y);
        if(x == 1){
            scanf("%d", &z);
            tree.del(1, y, y, z);
        }else if(x == 2){
            tree.update(1, 1, n, y);
        }
    }
    for(int i = 1; i <= n; i ++)
        printf("%d ", tree.query(1, i, i));
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
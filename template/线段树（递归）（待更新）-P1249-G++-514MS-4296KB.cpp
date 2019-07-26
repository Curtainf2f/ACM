#include<cstdio>

const int maxn = 1e5+5;

struct node{
    int left, right, v;
}tree[maxn << 2];

void build(int left, int right, int root){
    if(left == right){
        tree[root].v = 1;
        tree[root].left = tree[root].right = left;
        return ;
    }
    tree[root].left = left;
    tree[root].right = right;
    tree[root].v = 1;
    int mid = (left + right) / 2;
    build(left, mid, root << 1);
    build(mid + 1, right, root << 1 | 1);
}

void update(int l, int r, int v, int root){
    if(l <= tree[root].left && r >= tree[root].right){
        tree[root].v = v;
        return ;
    }
    if(tree[root].v != 0 && tree[root].v != v){
        tree[root << 1].v = tree[root].v;
        tree[root << 1 | 1].v = tree[root].v;
        tree[root].v = 0;
    }
    int mid = (tree[root].left + tree[root].right) / 2;
    if(r <= mid){
        update(l, r, v, root << 1);
    }else if(l > mid){
        update(l, r, v, root << 1 | 1);
    }else{
        update(l, r, v, root << 1);
        update(l, r, v, root << 1 | 1);
    }
}

int ans;

void subans(int root){
    if(tree[root].v != 0){
        ans += tree[root].v * (tree[root].right - tree[root].left + 1);
        return ;
    }
    subans(root << 1);
    subans(root << 1 | 1);
}

int main(){
    int t;
    scanf("%d", &t);
    for(int cas = 1; cas <= t; cas ++){
        ans = 0;
        int n;
        scanf("%d", &n);
        build(1, n, 1);
        int q;
        scanf("%d", &q);
        while(q--){
            int a, b, v;
            scanf("%d%d%d", &a, &b, &v);
            update(a, b, v, 1);
        }
        subans(1);
        printf("Case %d: The total value of the hook is %d.\n", cas, ans);
    }
    return 0;
}

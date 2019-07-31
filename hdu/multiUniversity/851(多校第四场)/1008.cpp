#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define test(x) cerr << #x << "=" << x << endl
#else
    #define test(x)
#endif

typedef long long LL;

const int N = 1e6+5;

class Segmentforest
{
public:
    int data[N];
    struct Node
    {
        int left, right, sum;
    }node[N * 40];
    int tree[N], sign, sumOfPoint;
    void clear(int sumOfPoint){
        sign = 0;
        this->sumOfPoint = sumOfPoint;
        tree[0] = build(0, N-1);
        for(int i = 1; i <= sumOfPoint; i ++){
            tree[i] = insert(0, N-1, tree[i-1], data[i-1], 1);
        }
    }
    int build(int left, int right){
        int get = sign ++;
        node[get].sum = 0;
        if(left == right) return get;
        int mid = (left + right) >> 1;
        node[get].left = build(left, mid);
        node[get].right = build(mid + 1, right);
        return get;
    }
    int insert(int left, int right, int root, int pos, int value){
        int get = sign ++;
        node[get] = node[root];
        if(left == right){
            node[get].sum += value;
            return get;
        }
        int mid = (left + right) >> 1;
        if(pos <= mid){
            node[get].left = insert(left, mid, node[root].left, pos, value);
        }else{
            node[get].right = insert(mid + 1, right, node[root].right, pos, value);
        }
        node[get].sum = node[node[get].left].sum + node[node[get].right].sum;
        return get;
    }
    int query(int treeLeft, int treeRight, int left, int right, int kth){
        if(left == right){
            return left;
        }
        int mid = (left + right) >> 1;
        int cnt = node[node[treeRight].left].sum - node[node[treeLeft].left].sum;
        if(kth <= cnt){
            return query(node[treeLeft].left, node[treeRight].left, left, mid, kth);
        }else{
            return query(node[treeLeft].right, node[treeRight].right, mid + 1, right, kth - cnt);
        }
    }
    int kthLoc(int treeLeft, int treeRight, int left, int right, int x){
        if(left == right){
            return 0;
        }
        int mid = (left + right) >> 1;
        int cnt = node[node[treeRight].left].sum - node[node[treeLeft].left].sum;
        if(x <= mid){
            return kthLoc(node[treeLeft].left, node[treeRight].left, left, mid, x);
        }else{
            return kthLoc(node[treeLeft].right, node[treeRight].right, mid + 1, right, x) + cnt;
        }
    }
    int getAns(int treeLeft, int treeRight, int left, int right, int x, int k, int _max){
        int loc = kthLoc(treeLeft, treeRight, left, right, x);
        int lleft = loc, rright = loc + 1;
        int lnum, rnum;
        test(loc);
        for(int time = 1; time < k; time ++){
            lnum = query(treeLeft, treeRight, left, right, lleft);
            rnum = query(treeLeft, treeRight, left, right, rright);
            if(rright > _max){
                lleft --;
                continue;
            }else if(lleft == 0){
                rright ++;
                continue;
            }
            if(x - lnum < rnum - x){
                lleft --;
            }else{
                rright ++;
            }
        }
        lnum = query(treeLeft, treeRight, left, right, lleft);
        rnum = query(treeLeft, treeRight, left, right, rright);
        if(lleft == 0) {
            return rnum - x;
        }else if(rright > _max){
            return x - lnum;
        }
        if(x - lnum < rnum - x){
            return x - lnum;
        }else{
            return rnum - x;
        }

    }
}SegForest;

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    int t;
    scanf("%d", &t);
    while (t --) {
        int n, q;
        scanf("%d%d", &n, &q);
        for(int i = 0; i < n; i ++) scanf("%d", &SegForest.data[i]);
        SegForest.clear(n);
        int ans = 0;
        for(int i = 1; i <= q; i ++){
            int l, r, p, k;
            scanf("%d%d%d%d", &l, &r, &p, &k);
            l ^= ans;
            r ^= ans;
            p ^= ans;
            k ^= ans;
            ans = SegForest.getAns(SegForest.tree[l-1], SegForest.tree[r], 0, N-1, p, k, r - l + 1);
            printf("%d\n", ans);
        }
    }
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
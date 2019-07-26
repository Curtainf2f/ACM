#include<stdio.h>
#include<math.h>
#include<algorithm>
using namespace std;

int blockSize;
inline int belong(int x){
    return x / blockSize;
}

class Solution{
    const static int MAXN = 100005;
    const static int MAXQ = 100005;
private:
    struct Ask{
        int left, right, id;
        bool operator < (const Ask &b){
            if(belong(this->left) == belong(b.left)){
                return this->right < b.right;
            }else{
                return this->left < b.left;
            }
        }
    }ask[MAXQ];
    int now, left, right, sumOfPoint, ans[MAXQ], a[MAXN], sumOfQ, kinds;
    int vis[MAXN];
    inline int add(int x){
        return vis[a[x]] ++ == 0;
    }
    inline int sub(int x){
        return -- vis[a[x]] == 0;
    }
public:
    void clear(int n){
        sumOfPoint = n;
        kinds = 0;
        for(int i = 1; i <= n; i ++){
            vis[i] = 0;
        }
        blockSize = sqrt(n);
    }
    void insertdata(int n){
        for(int i = 1; i <= n; i ++){
            scanf("%d", &a[i]);
        }
    }
    void insertAsk(int m){
        sumOfQ = m;
        for(int i = 1; i <= m; i ++){
            scanf("%d%d", &ask[i].left, &ask[i].right);
            ask[i].id = i;
        }
        sort(ask + 1, ask + m + 1);
    }
    void calAns(){
        int left = 1, right = 0;
        for(int i = 1; i <= sumOfQ; i ++){
            while(left < ask[i].left){
                kinds -= sub(left ++);
            }
            while(left > ask[i].left){
                kinds += add(-- left);
            }
            while(right > ask[i].right){
                kinds -= sub(right --);
            }
            while(right < ask[i].right){
                kinds += add(++ right);
            }
            ans[ask[i].id] = kinds;
        }
    }
    int getAns(int x){
        return ans[x];
    }
}solve;

int main(){
    int n, q;
    scanf("%d%d", &n, &q);
    solve.clear(n);
    solve.insertdata(n);
    solve.insertAsk(q);
    solve.calAns();
    for(int i = 1; i <= q; i ++){
        printf("%d\n", solve.getAns(i));
    }
    return 0;
}

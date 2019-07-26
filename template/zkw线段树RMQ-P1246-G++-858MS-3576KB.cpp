#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 200005;
const int inf = 0x7fffffff;

int tree[maxn << 2];
int M;

void print(int x)
{
    if(x<0)putchar('-'),x=-x;
    if(x>9)print(x/10);
    putchar(x%10+'0');
}

void read(int &x)
{
    int f=1;x=0;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
    x*=f;
}

void build(int n){
    for(M = 1; M <= n + 1; M <<= 1);
    for(int i = M + 1; i <= M + n; i ++)
        read(tree[i]);
    for(int i = M - 1; i; i --){
        tree[i] = max(tree[i << 1], tree[i << 1 | 1]);
    }
}

void change(int x, int v){
    tree[x = M + x] = v;
    while(x) tree[x >>= 1] = max(tree[x << 1], tree[x << 1 | 1]);
}

int RMQ(int s, int t){
    int L = -inf, R = -inf;
    for(s = s + M - 1, t = t + M + 1; s ^ t ^ 1; s >>= 1, t >>= 1){
        if(~ s & 1) L = max(L , tree[s ^ 1]);
        if(t & 1) R = max(R , tree[t ^ 1]);
    }
    return max(L, R);
}

int main(){
    int n, m;
    while(~scanf("%d%d", &n, &m)){
        build(n);
        while(m--){
            int a, b;
            char opt;
            scanf(" %c", &opt);
            read(a);
            read(b);
            if(opt == 'Q'){
                print(RMQ(a, b));
                putchar('\n');
            }
            else
                change(a, b);
        }
    }
    return 0;
}

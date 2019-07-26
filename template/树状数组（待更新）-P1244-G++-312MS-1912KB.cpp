#include<cstdio>

const int maxn = 50005;

int c[maxn], a[maxn], n;

inline int lowbit(int x){
    return x&(-x);
}

int sum(int i){
    int s = 0;
    while(i > 0){
        s += c[i];
        i -= lowbit(i);
    }
    return s;
}

void update(int i, int value){
    while(i <= n){
        c[i] += value;
        i += lowbit(i);
    }
}

inline void add(int i, int j){
    update(i, j);
}

inline void sub(int i, int j){
    update(i, -j);
}

inline int query(int i, int j){
    return sum(j) - sum(i-1);
}

void init(){
    for(int i = 0; i <= n; i ++){
        c[i] = 0;
        a[i] = 0;
    }
}

int main(){
    int t, cas = 0;
    char opt[6];
    scanf("%d", &t);
    while(t--){
        printf("Case %d:\n", ++cas);
        init();
        scanf("%d", &n);
        for(int i = 1; i <= n; i ++){
            scanf("%d", &a[i]);
            add(i, a[i]);
        }
        while(~scanf("%s", opt)){
            if(opt[0] == 'Q'){
                int i, j;
                scanf("%d%d", &i, &j);
                printf("%d\n", query(i, j));
            }
            else if(opt[0] == 'A'){
                int i, j;
                scanf("%d%d", &i, &j);
                add(i, j);
            }
            else if(opt[0] == 'S'){
                int i, j;
                scanf("%d%d", &i, &j);
                sub(i, j);
            }
            else
                break;
        }
    }
    return 0;
}

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
const int MOD = 1e9+7;
const LL INF = 0x3f3f3f3f3f3f3f3f;
 
int nxt[N], extend[N];
char s[N], T[N], tmp[N];
 
void getNext(char *s,int nxt[]){
    int nn = strlen(s);
    nxt[0] = nn;
    int p = 0;
    while (p+1 < nn && s[p] == s[p+1]) p++;
    nxt[1] = p;
    int k = 1, L;
    for (int i = 2; i < nn; i++){
        p =     k + nxt[k] - 1; L = nxt[i - k];
        if (i + L <= p) nxt[i] = L;
        else {
            int j = p - i + 1;
            if (j < 0) j = 0;
            while (i + j < nn && s[i + j] == s[j]) j++;
            nxt[i] = j; k = i;
        
        } 
    }
}
 
int getExtend(char *s,char *T,int extend[]){
    int nn = strlen(s) ,mm = strlen(T);
    getNext(s,nxt);
    int p = 0;
    while (p < nn && s[p] == T[p]) p++;    
    extend[0] = p;
    //extend[1] = p;
    int k = 0, L;
    for (int i = 1; i < nn; i++){
        p =     k + extend[k] - 1; L = nxt[i - k];
        if (i + L <= p) extend[i] = L;
        else {
            int j = p - i + 1;
            if (j < 0) j = 0;
            while (i + j < nn && s[i + j] == T[j]) j++;
            extend[i] = j; k = i;
        
        } 
    }
    int _max = 0;
    for (int i=0;i<nn;i++){
        _max = max(_max, extend[i]);
    }
    return _max;
}
 
 
int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    int n;
    scanf("%d", &n);
    scanf("%s", s);
    int nn = strlen(s);
    for(int i = 1; i < n; i ++){
        scanf("%s", T);
        int len = strlen(T), k = 0;
        int start = nn - len;
        if(start < 0) start = 0;
        for(int i = start; i < nn; i ++){
            tmp[k++] = s[i];
        }
        tmp[k] = 0;
        k = getExtend(tmp, T, extend);
        for(int i = k; T[i] != 0; i ++){
            s[nn++] = T[i];
        }
        s[nn] = '\0';
    }
    puts(s);
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
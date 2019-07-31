#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define test(x) cerr << #x << "=" << x << endl
#else
    #define test(x)
#endif

typedef long long LL;

const int N = 1e5+5;
const int INF = 0x7fffffff;
int stTable[N][25];
int _log[N], a[N];

void _logPreWork() {
    int k = 0;
    for(int i = 1; i < N; i <<= 1) {
        _log[i] = k ++;
    }
    for(int i = 1; i < N; i ++) {
        if(!_log[i])
            _log[i] = _log[i - 1];
    }
}

void stPreWork(int n) {
    int time = _log[n] + 1;
    for(int j = 1; j <= time; j ++) {
        for(int i = 1; i <= n - (1 << j) + 1; i ++) {
            stTable[i][j] = min(stTable[i][j - 1], stTable[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int rmq(int l, int r) {
    if(l > r) return INF;
    int k = _log[r - l + 1];
    return min(stTable[l][k], stTable[r - (1 << k) + 1][k]);
}

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    _logPreWork();
    int n, x, y;
    scanf("%d%d%d", &n, &x, &y);
    for(int i = 1; i <= n;i ++){
        scanf("%d", &stTable[i][0]);
    }
    stPreWork(n);
    for(int i = 1; i <= n; i ++){
        int left = i - x, right = i + y;
        if(left < 1) left = 1;
        if(right > n) right = n;
        if(rmq(left, i-1) > stTable[i][0] && rmq(i+1, right) > stTable[i][0]){
            printf("%d\n", i);
            break;
        }
    }
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
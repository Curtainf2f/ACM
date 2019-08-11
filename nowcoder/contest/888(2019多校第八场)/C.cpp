#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define test(x) cerr << #x << "=" << x << endl
#else
    #define test(x)
#endif

typedef long long LL;

const int N = 2e5+5;

int a[11][2000][2000];
int _log[2000];
int m;

void _logPreWork() {
    int k = 0;
    for(int i = 1; i < 2000; i <<= 1) {
        _log[i] = k ++;
    }
    for(int i = 1; i < 2000; i ++) {
        if(!_log[i])
            _log[i] = _log[i - 1];
    }
}

bool check(int ii, int jj){
    int cur = 0;
    for(int i = 1 ; i <= m; i ++){
        cur += a[_log[m]][ii][i] * a[_log[m]][jj][i];
    }
    return cur == 0;
}

void print(){
    for(int i = 1; i <= m; i ++){
        for(int j = 1; j <= m; j ++){
            if(j != 1) printf(" ");
            printf("%d", a[_log[m]][i][j]);
        }
        puts("");
    }
}

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    _logPreWork();
    a[1][1][1] = -1; a[1][1][2] = 1; a[1][2][1] = 1; a[1][2][2] = 1;
    for(int i = 2; i <= 10; i ++){
        for(int j = 1; j <= (1 << (i-1)); j ++){
            for(int k = 1; k <= 1 << (i-1); k ++){
                a[i][j][k] = a[i-1][j][k];
                a[i][j+(1<<(i-1))][k] = a[i-1][j][k];
            }
        }
        for(int j = 1; j <= (1 << (i-1)); j ++){
            for(int k = 1; k <= 1 << (i-1); k ++){
                if(j <= (1 << (i-2))) a[i][j][k+(1<<(i-1))] = a[i-1][j][k];
                else{
                    if(a[i-1][j][k] == 1) a[i][j][k+(1<<(i-1))] = -1;
                    else a[i][j][k+(1<<(i-1))] = 1;
                }
            }
        }
        for(int j = 1; j <= (1 << (i-1)); j ++){
            for(int k = 1; k <= 1 << (i-1); k ++){
                if(j <= (1 << (i-2))){
                    if(a[i-1][j][k] == 1) a[i][j+(1<<(i-1))][k+(1<<(i-1))] = -1;
                    else a[i][j+(1<<(i-1))][k+(1<<(i-1))] = 1;
                }
                else{
                    a[i][j+(1<<(i-1))][k+(1<<(i-1))] = a[i-1][j][k];
                }
            }
        }
    }
    scanf("%d", &m);
    print();
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
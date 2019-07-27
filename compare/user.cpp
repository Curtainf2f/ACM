#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define fuck(x) cerr << #x << "=" << x << endl
#else
    #define fuck(x)
#endif

typedef long long LL;
const int N = 3e6+5;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;

LL stTable1[N][22], stTable2[N][22];
int _log[N];

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

void stPreWork1(int n) {
    int time = _log[n] + 1;
    for(int j = 1; j <= time; j ++) {
        for(int i = 1; i <= n - (1 << j) + 1; i ++) {
            stTable1[i][j] = min(stTable1[i][j - 1], stTable1[i + (1 << (j - 1))][j - 1]);
        }
    }
}

LL rmqMin(int l, int r) {
    if(l > r) return -1;
    int k = _log[r - l + 1];
    return min(stTable1[l][k], stTable1[r - (1 << k) + 1][k]);
}

void stPreWork2(int n) {
    int time = _log[n] + 1;
    for(int j = 1; j <= time; j ++) {
        for(int i = 1; i <= n - (1 << j) + 1; i ++) {
            stTable2[i][j] = max(stTable2[i][j - 1], stTable2[i + (1 << (j - 1))][j - 1]);
        }
    }
}

LL rmqMax(int l, int r) {
    if(l > r) return -1;
    int k = _log[r - l + 1];
    return max(stTable2[l][k], stTable2[r - (1 << k) + 1][k]);
}

struct Node
{
    int l, index;
    LL num;
    Node(int l, LL num, int index):l(l), num(num), index(index){}
};

LL a[N], b[N];
stack<Node> stk;

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    _logPreWork();
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i ++) scanf("%lld", &a[i]);
    for(int i = 0; i < n; i ++) scanf("%lld", &b[i]);
    a[n] = -INF;
    b[n] = -INF;
    LL ans = -INF;
    for(int i = 0; i <= n; i ++){
        stTable1[i+1][0] = stTable1[i][0] + b[i];
        stTable2[i][0] = stTable1[i][0];
    }
    stPreWork1(n);
    stPreWork2(n);
    for(int i = 0; i <= n; i ++){
        Node tmp(i, a[i], i);
        while(!stk.empty() && a[i] <= stk.top().num){
            tmp.l = stk.top().l;
            LL cur1 = 1LL * (rmqMax(stk.top().index+1, i) - rmqMin(stk.top().l, stk.top().index)) * stk.top().num;
            LL cur2 = 1LL * (rmqMin(stk.top().index+1, i) - rmqMax(stk.top().l, stk.top().index)) * stk.top().num;
            LL cur = max(cur1, cur2);
            fuck(stk.top().index);
            fuck(cur);
            stk.pop();
            ans = max(cur, ans);
        }
        stk.push(tmp);
    }
    printf("%lld\n", ans);
    return 0;
}
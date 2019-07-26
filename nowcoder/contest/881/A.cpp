#include<stdio.h>
#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;

const int MAXN = 1e5+5;
const int INF = 0x7fffffff;
int stTable1[MAXN][25], stTable2[MAXN][25];
int _log[MAXN], a[MAXN];

void _logPreWork() {
    int k = 0;
    for(int i = 1; i < MAXN; i <<= 1) {
        _log[i] = k ++;
    }
    for(int i = 1; i < MAXN; i ++) {
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

int rmq1(int l, int r) {
    if(l > r) return -1;
    int k = _log[r - l + 1];
    return min(stTable1[l][k], stTable1[r - (1 << k) + 1][k]);
}

void stPreWork2(int n) {
    int time = _log[n] + 1;
    for(int j = 1; j <= time; j ++) {
        for(int i = 1; i <= n - (1 << j) + 1; i ++) {
            stTable2[i][j] = min(stTable2[i][j - 1], stTable2[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int rmq2(int l, int r) {
    if(l > r) return -1;
    int k = _log[r - l + 1];
    return min(stTable2[l][k], stTable2[r - (1 << k) + 1][k]);
}

int loc1[MAXN], loc2[MAXN];

queue<pair<int, int> > q;

bool check(int x){
    q.push(make_pair(1, x));
    bool ok = true;
    while(!q.empty()){
        int left = q.front().first;
        int right = q.front().second;
        q.pop();
        if(left >= right) continue;
        if(loc1[rmq1(left, right)] == loc2[rmq2(left, right)]){
            q.push(make_pair(left, loc1[rmq1(left, right)] - 1));
            q.push(make_pair(loc1[rmq1(left, right)] + 1, right));
        }else{
            ok = false;
            break;
        }
    }
    while(!q.empty()) q.pop();
    return ok;
}

int main() {
    _logPreWork();
    int n;
    while(~scanf("%d", &n)) {
        for(int i = 1; i <= n; i ++) {
            scanf("%d", &stTable1[i][0]);
            loc1[stTable1[i][0]] = i;
        }
        for(int i = 1; i <= n; i ++) {
            scanf("%d", &stTable2[i][0]);
            loc2[stTable2[i][0]] = i;
        }
        stPreWork1(n);
        stPreWork2(n);
        int left = 0, right = n + 1;
        while(left + 1 < right){
            int mid = left + right >> 1;
            if(check(mid)){
                left = mid;
            }else{
                right = mid;
            }
        }
        printf("%d\n", left);
    }
    return 0;
}

#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define test(x) cerr << #x << "=" << x << endl
#else
    #define test(x)
#endif

typedef long long LL;

const int N = 4e5+5;
const int INF = 0x7fffffff;

int _log[N], _clog[N];

void _logPreWork() {
    int k = 0;
    for(int i = 1; i < N; i <<= 1) {
        _log[i] = k;
        _clog[i] = k ++;
    }
    for(int i = 1; i < N; i ++) {
        if(!_log[i])
            _log[i] = _log[i - 1];
    }
}

vector<int> vec;
int a[N], bukkit[N], sum[N];

inline int get(int x){
    return lower_bound(vec.begin(), vec.end(), x) - vec.begin();
}

LL n, mem;

bool check(int k){
    bool c;
    if(_clog[k] && k != 1) c = true;
    else if(k == 1) c = true;
    else c = false;
    k = _log[k];
    if(c == false) k ++;
    return 1LL*n*k <= 1LL*mem*8;
}

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    _logPreWork();
    scanf("%I64d%I64d", &n, &mem);
    for(int i = 1; i <= n; i ++){
        scanf("%d", &a[i]);
        vec.push_back(a[i]);
    }
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    for(int i = 1; i <= n; i ++){
        bukkit[get(a[i])] ++;
    }
    int left = 0, right = vec.size() + 1;
    while (left + 1 < right) {
        int mid = left + right >> 1;
        if(check(mid)){
            left = mid;
        }else{
            right = mid;
        }
    }
    int ans = 0;
    for(int i = 1; i <= vec.size(); i ++){
        sum[i] = sum[i-1] + bukkit[i-1];
    }
    test(left);
    test(vec.size());
    for(int i = 0; i <= vec.size() - left; i ++){
        ans = max(sum[i+left] - sum[i], ans);
    }
    printf("%d\n", sum[vec.size()] - ans);
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
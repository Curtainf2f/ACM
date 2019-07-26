#include<bits/stdc++.h>
using namespace std;

#ifdef _LOCAL
    #define fuck(x) cerr << #x << "=" << x << endl
#else
    #define fuck(x)
#endif

typedef long long LL;

template<typename T>
class LinearBasis{
public:
    T data[64], gaussin[64];
    int cnt, n, gaussinCnt;
    LinearBasis(int bits){
        clear(bits);
    }
    void clear(int bits){
        for(int i = 0; i < n; i ++) data[i] = 0, gaussin[i] = 0;
        cnt = 0;
        gaussinCnt = 0;
        this->n = bits;
    }
    bool insert(T x){
        for(int i = n - 1; i >= 0; i --){
            if(x & (1LL << i)){
                if(!data[i]) {
                    data[i] = x;
                    cnt ++;
                    break;
                }
                x ^= data[i];
            }
        }
        return x > 0;
    }
    void calcGaussin(){
        for(int i = n - 1; i >= 0; i --){
            for(int j = i - 1; j >= 0; j --){
                if(data[i] & 1LL << j) data[i] ^= data[j];
            }
        }
        for(int i = 0; i < n; i ++){
            if(data[i]) gaussin[gaussinCnt++] = data[i]; 
        }
    }
    T kthMax(T k){
        T res = 0;
        for(int i = n - 1; i >= 0; i --){
            if(k & (1LL<<i)) res ^= gaussin[i];
        }
        return res;
    }
    T maxXor(T x){
        T res = x;
        for(int i = n - 1; i >= 0; i --){
            res = max(res, res ^ data[i]);
        }
        return res;
    }
    T minXor(T x){
        T res = x;
        for(int i = 0; i < n; i ++){
            res = min(res, res ^ data[i]);
        }
        return res;
    }
};

const int N = 1e5+5;
const int MOD = 1e9+7;

LL a[N];
LinearBasis<LL> aa(64), bb(64), cc(64);
LL fac[N];
vector<LL> v, r;

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    fac[0] = 1;
    for(int i = 1; i < N; i ++) fac[i] = fac[i-1] * 2 % MOD;
    int n;
    while (~scanf("%d", &n)) {
        aa.clear(64);
        bb.clear(64);
        cc.clear(64);
        r.clear();
        v.clear();
        for(int i = 1; i <= n; i ++) scanf("%lld", &a[i]);
        for(int i = 1; i <= n; i ++) {
            if(aa.insert(a[i])){
                v.push_back(a[i]);
            }else{
                r.push_back(a[i]);
            }
        }
        if(n == v.size()){
            puts("0");
            continue;
        }
        LL ans = r.size() * fac[r.size() - 1] % MOD;
        for(int i = 0; i < r.size(); i ++){
            bb.insert(r[i]);
        }
        for(int i = 0; i < v.size(); i ++){
            cc = bb;
            for(int j = 0; j < v.size(); j ++){
                if(i != j) cc.insert(v[j]);
            }
            if(!cc.insert(v[i])) ans = (ans + fac[r.size() - 1]) % MOD;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
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

const int N = 2e5+5;
const int MOD = 1e9+7;
const LL INF = 0x3f3f3f3f3f3f3f3f;

string s, t;

int l[N], r[N];

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    cin >> s >> t;
    for(int i = 0, now = 0; i < s.size(); i ++){
        if(now == t.size()) break;
        if(s[i] == t[now]){
            l[now] = i;
            now ++;
        }
    }
    for(int i = s.size() - 1, now = t.size() - 1; i >= 0; i --){
        if(now < 0) break;
        if(s[i] == t[now]){
            r[now] = i;
            now --;
        }
    }
    // for(int i = 0; i < t.size(); i ++){
    //     printf("%d ", l[i]);
    // }
    // puts("");
    // for(int i = 0; i < t.size(); i ++){
    //     printf("%d ", r[i]);
    // }
    // puts("");
    int ans = 0;
    for(int i = 0; i <= t.size(); i ++){
        if(i == 0){
            // test(r[i]);
            ans = max(r[i], ans);
        }else if(i == t.size()){
            // test((int)s.size()-l[i-1]-1);
            ans = max((int)s.size()-l[i-1]-1, ans);
        }else{
            // test(r[i] - l[i-1] - 1);
            ans = max(r[i] - l[i-1] - 1, ans);
        }
    }
    printf("%d\n", ans);
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
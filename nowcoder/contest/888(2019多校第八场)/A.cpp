#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define test(x) cerr << #x << "=" << x << endl
#else
    #define test(x)
#endif

typedef long long LL;

const int N = 3005;

int use[N];
LL sum[N][N];
LL sumC[N][N];
char s[N][N];
stack<pair<LL, LL> > stk;

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++){
        scanf("%s", s[i] + 1);
    }
    for(int j = 1; j <= m; j ++){
        for(int i = 1; i <= n; i ++){
            if(s[i][j] == '1') sum[i][j] = sum[i-1][j] + 1;
            else sum[i][j] = 0;
        }
    }
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m + 1; j ++){
            if(sum[i][j]) sumC[i][j] = sumC[i][j-1] + 1;
            else sumC[i][j] = sumC[i][j-1];
        }
    }
    LL ans = 0;
    pair<LL, LL> tmp;
    for(int i = n; i >= 1; i --){
        test(i);
        stk.push(make_pair(-1LL, 0LL));
        memset(use, 0, sizeof(use));
        for(int j = 1; j <= m + 1; j ++){
            if(j != m + 1){
                tmp.first = sum[i][j];
                tmp.second = j;
            }else{
                tmp.first = 0;
                tmp.second = m + 1;
            }
            while(!stk.empty() && tmp.first < stk.top().first){
                pair<LL, LL> temp = stk.top();
                stk.pop();
                use[temp.first] --;
                if(!use[temp.first] && sumC[i+1][j-1] - sumC[i+1][stk.top().second] < j - stk.top().second - 1) ans ++;
            }
            stk.push(tmp);
            use[tmp.first] ++;
        }
        test(ans);
        while(!stk.empty()) stk.pop();
    }
    printf("%lld\n", ans);
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
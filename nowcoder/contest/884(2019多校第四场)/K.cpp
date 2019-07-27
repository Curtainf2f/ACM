#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define fuck(x) cerr << #x << "=" << x << endl
#else
    #define fuck(x)
#endif
typedef long long LL;

const int N = 1e5+5;
const int MOD = 1e9+7;

char s[N];
int sum1[N], sum2[N];
map<int, int> mp;

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    scanf("%s", s + 1);
    int len = strlen(s+1);
    for(int i = 1; i <= len; i ++){
        if(s[i] == '0') sum1[i] = sum1[i-1] + 1;
        else sum1[i] = 0;
        sum2[i] = sum2[i-1] + s[i] - '0';
    }
    LL cur = 0;
    LL ans = 0;
    for(int i = 0; i <= len; i ++){
        fuck(sum2[i]);
        fuck(cur);
        if(sum1[i] == 1) ans ++;
        else if(sum1[i] >= 2){
            ans += mp[sum2[i]%3];
        }
        mp[sum2[i]%3] ++;
    }
    printf("%lld\n", ans);
    return 0;
}
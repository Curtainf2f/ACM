#include<stdio.h>
#include<iostream>
#include<string.h>
#include<queue>
#include<string>
#include<algorithm>
using namespace std;
 
typedef long long LL;
 
const int N = 2005;
const LL MOD = 1e9+7;
LL dp[N][N];
 
int main(){
    int n, m;
    while(~scanf("%d%d", &n, &m)){
        for(int i = 0; i <= n+m; i ++)
            for(int j = 0; j <= n+m; j ++)
                dp[i][j] = 0;
        dp[0][0] = 1;
        for(int i = 0; i <= n+m; i ++){
            for(int j = 0; j <= n+m; j ++){
                if(i < n+j) dp[i+1][j] = (dp[i+1][j] + dp[i][j]) % MOD;
                if(j < m+i) dp[i][j+1] = (dp[i][j+1] + dp[i][j]) % MOD;
            }
        }
        printf("%lld\n", dp[n+m][n+m]);
    }
    return 0;
}

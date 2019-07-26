#include<stdio.h>
#include<iostream>
#include<string.h>
#include<queue>
#include<string>
#include<algorithm>
using namespace std;
 
typedef long long LL;
 
const int N = 1005;
const LL MOD = 1e9+7;
 
LL a[N];
 
LL quickpow(LL a, LL n)
{
    LL ans = 1;
    while(n)
    {
        if(n&1)
        {
            ans = ans * a % MOD;
        }
        n >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
 
LL inv(LL b){
    return quickpow(b, MOD - 2);
}
 
 
int main(){
    int n;
    while(~scanf("%d", &n)){
        for(int i = 1; i <= n; i ++){
            scanf("%lld", &a[i]);
        }
        LL ans = 0;
        for(int i = 1; i <= n; i ++){
            LL sum = 1;
            for(int j = 1; j <= n; j ++){
                if(i != j) sum = sum * ((a[j]*a[j] % MOD + MOD - a[i]*a[i]%MOD) %MOD) % MOD;
            }
            sum = sum * (2*a[i]%MOD) % MOD;
            ans = (ans + inv(sum)) % MOD;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
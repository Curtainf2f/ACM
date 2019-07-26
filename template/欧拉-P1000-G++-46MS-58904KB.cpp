#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2e7+7, mod=998244353;
ll prime[N], fai[N]={0, 0};
bool check[N];
ll Euler(){
    register int i, j, tot=0;
    for(i=2; i<=N; ++i){
        if(!check[i]){
            prime[tot++]=i;
            fai[i]=i-1;
        }
        for(int j=0; j<tot; ++j){
            if(((ll)i)*prime[j]>N) break;
            check[i*prime[j]]=1;
            if(i%prime[j]==0){
                fai[i*prime[j]]=fai[i]*prime[j];
                break;
            }else{
                fai[i*prime[j]]=fai[i]*(prime[j]-1);
            }
        }
    }
}
int main(){
    Euler();
}

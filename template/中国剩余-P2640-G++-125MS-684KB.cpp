#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;

LL exgcd(LL a, LL b, LL &d, LL &x, LL &y){
    if(b == 0) d = a, x = 1, y = 0;
    else{
        exgcd(b, a%b, d, y, x);
        y -= a/b*x;
    }
}

LL solve(LL a, LL b, LL n){
    LL d, x, y;
    exgcd(a, n, d, x, y);
    if(b%d) return -1;
    x *= b/d;
    LL r = n/d;
    if(r < 0) r = -r;
    return (x%r + r) % r;
}


/**
        x = a1 (mod n1)
        x = a2 (mod n2)

        x = a1 + k1n1
        x = a2 + k2n2
        k1n1 - k2n2 = a2 - a1  //  gcd (n1, n2) | a2 - a1 则有解
        n1k1 + n2k2 = gcd(n1,n2) // exgcd 求 k1
        合并为
        x = a1 - n1*k1(a2 - a1) / gcd(n1,n2)(mod lcm(n1, n2))
**/

bool Merge(LL a[], LL n[], LL num, LL &A, LL &N){
    LL d, x, y;
    A = a[0], N = n[0];
    for(LL i = 1; i < num; i ++){
        exgcd(N, n[i], d, x, y);
        if((a[i] - A) % d){
            return false;
        }
        x = (a[i] - A) / d * x;
        y = n[i] / d;
        x = (x % y + y) % y;
        A = x*N + A;
        N = (N * n[i]) / d;
    }
    return true;
}

const int MAXN = 1005;
LL a[MAXN], n[MAXN];

int main(){
    int k;
    while(cin >> k){
        for(int i = 0; i < k; i ++){
            cin >> n[i] >> a[i];
        }
        LL ansA, ansN;
        if(Merge(a, n, k, ansA, ansN)){
            cout << ansA << endl;
        }
        else
            puts("-1");
    }
    return 0;
}

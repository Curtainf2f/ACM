#include<bits/stdc++.h>
#include <chrono>
#include <random>
using namespace std;

typedef long long LL;

int random(int a, int b) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(a, b)(rng);
}
 
LL random(LL a, LL b) {
    static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<LL>(a, b)(rng);
}

const int N = 1e5;

int main(){
    int n = N;
    int e = N-1;
    int s = 0;
    printf("%d %d %d\n", n, s, e);
    for(int i = 1; i <= n; i ++){
        printf("%d %d %d\n", i-1, i-1, random(N-5, N));
    }
    return 0;
}

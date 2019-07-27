#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<time.h>
#include<vector>
using namespace std;

typedef long long LL;
const int MAXN = 5;

int random(int n) {
    return (LL) rand() * rand() % n;
}

const int N = 1000;
vector<int> v;

int main() {
    srand(time(0));
    int n = random(N) + 1;
    int k = random(n) + 1;
    printf("%d %d\n", n, k);
    for(int i = 2; i <= n; i ++){
        int fa = random(i-1) + 1;
        printf("%d %d\n", fa, i);
    }
    for(int i = 1; i <= n; i ++){
        v.push_back(i);
    }
    for(int i = 1; i <= k; i ++){
        int loc = random(v.size());
        printf("%d ", v[loc]);
        v.erase(v.begin() + loc, v.begin() + loc + 1);
    }
}

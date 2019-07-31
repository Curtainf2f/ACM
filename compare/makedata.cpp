#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<algorithm>
#include<math.h>
#include<vector>
#include<assert.h>
using namespace std;

typedef long long LL;

const int N = 10;
const int M = 20;

int random(int n) {
    return (LL) rand() * rand() % n;
}

int main(){
    srand(time(0));
    int n = random(N) + 5;
    printf("%d\n", n);
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= 5; j ++){
            printf("%d ", random(M) + 1);
        }
        puts("");
    }
    return 0;
}

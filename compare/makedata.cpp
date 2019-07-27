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

int random(int n) {
    return (LL) rand() * rand() % n;
}

int main(){
    srand(time(0));
    int n = random(N) + 1;
    printf("%d\n", n);
    for(int i = 1; i <= n; i ++){
        printf("%d ", random(21) - 10);
    }
    puts("");
    for(int i = 1; i <= n; i ++){
        printf("%d ", random(21) - 10);
    }
    return 0;
}

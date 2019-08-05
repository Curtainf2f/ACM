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

const int N = 1000;
const int M = 2000000000;

int random(int n) {
    return (LL) rand() * rand() % n;
}


int main(){
    srand(time(0));
    int t = random(10) + 1;
    printf("%d\n", t);
    while (t --)
    {
        int n, m;
        n = random(1000) + 1;
        m = random(1000) + 1;
        printf("%d %d\n", n, m);
        for(int i = 1; i <= n; i ++){
            for(int j = 1; j <= m; j ++){
                printf("%d ", random(M) - M/2);
            }
            puts("");
        }
        for(int i = 1; i <= m; i ++) printf("%d ", random(M) - M/2);
        puts("");
    }
    return 0;
}

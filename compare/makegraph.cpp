#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<algorithm>
#include<math.h>
#include<vector>
#include<assert.h>
#include<map>
using namespace std;

typedef long long LL;

const int MAXN = 1e5;
const int MAXM = 5e5;

int random(int n) {
    return (long long) rand() * rand() % n;
}

pair<int, int> e[MAXM+1];
//map<pair<int, int>, bool> h;
string oldId[MAXN+1];
map<string, bool> have;

//void create(int n, int m) {
//    for(int i = 1; i < n; i ++) {
//        int fa = random(i) + 1;
//        e[i] = make_pair(fa, i + 1);
//        h[e[i]] = h[make_pair(i+1, fa)] = 1;
//    }
//    for(int i = n; i <= m; i ++) {
//        int x, y;
//        do{
//            x = random(n) + 1, y = random(n) + 1;
//        } while (x == y || h[make_pair(x, y)]);
//        e[i] = make_pair(x, y);
//        h[e[i]] = h[make_pair(y, x)] = 1;
//    }
//    random_shuffle(e + 1, e + m + 1);
//}

void create(int n, int m) {
    for(int i = 1; i < n; i ++) {
        int fa = random(i) + 1;
        e[i] = make_pair(fa, i + 1);
    }
    for(int i = n; i <= m; i ++) {
        int x, y;
        do{
            x = random(n) + 1, y = random(n) + 1;
        } while (x == y);
        e[i] = make_pair(x, y);
    }
    random_shuffle(e + 1, e + m + 1);
}

void create2(int n, int m){
    for(int i = 1; i < n; i ++) {
        e[i] = make_pair(i, i + 1);
    }
    random_shuffle(e + 1, e + m + 1);
}

void gao(int n){
    for(int i = 1; i <= n; i ++){
        int len = random(12) + 1;
        string a;
        for(int j = 1; j <= len; j ++){
            a.push_back(random(26) + 'a');
        }
        if(have.find(a) != have.end()){
            i --;
            continue;
        }
        have[a] = true;
        oldId[i] = a;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    srand(time(0));
    int n = random(MAXN) + 1;
    int m = random(MAXM - n) + n + 1;
//    n = MAXN;
//    m = MAXN - 1;
    gao(n);
    create(n, m);
    cout << n << " " << m << endl;
    for(int i = 1; i <= m; i ++){
        cout << oldId[e[i].first] << " " << oldId[e[i].second] << endl;
    }
    return 0;
}

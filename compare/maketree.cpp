#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<time.h>
#include<map>
using namespace std;

typedef long long LL;
const int MAXN = 5;

int random(int n) {
    return (LL) rand() * rand() % n;
}

string oldId[MAXN+1];
map<string, bool> have;

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
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    srand((unsigned)time(0));
    int n = random(MAXN) + 1, m = n - 1;
    cout << n << " " << m << endl;
    gao(n);
    for(int i = 2; i <= n; i ++) {
        int fa = random(i - 1) + 1;
        cout << oldId[fa] << " " << oldId[i] << endl;
    }
}

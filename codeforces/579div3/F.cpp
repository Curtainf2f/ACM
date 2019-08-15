#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define test(x) cerr << #x << "=" << x << endl
#else
    #define test(x)
#endif
#define lson(x) x << 1
#define rson(x) x << 1 | 1

typedef long long LL;

const int N = 1e6+5;

vector<pair<int, int> > pos, neg;
bool cmp(const pair<int, int> &a, const pair<int, int> &b){
    if(a.first == b.first) return a.second > b.second;
    else return a.first < b.first;
}

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    int n, r;
    scanf("%d%d", &n, &r);
    pair<int, int> x;
    for(int i = 1; i <= n; i ++){
        scanf("%d%d", &x.first, &x.second);
        if(x.second < 0) neg.push_back(x);
        else pos.push_back(x);
    }
    sort(pos.begin(), pos.end());
    for(int i = 0; i < pos.size(); i ++){
        
    }
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
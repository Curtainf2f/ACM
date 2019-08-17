#include <bits/stdc++.h>
  
using namespace std;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;
  
#ifdef _LOCAL
#define show(x) cerr << "[" << #x << ": " << x << "] (" << __LINE__ << ", in `" << __FUNCTION__ << "`)\n"
struct Tester {
    Tester() { freopen("data.in", "r", stdin); }
    ~Tester() { fprintf(stderr, "\nTime: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC)); }
} _shower;
#else
#define show(x)
#endif

const int N = 1e6+5;

int n;
LL k;
struct Node{
    int x, y;
}node[N];

map<string, int> quadInt;

struct Quadrant
{
    int x, y;
    bool friend operator < (const Quadrant &a, const Quadrant &b){
        string cur1, cur2;
        cur1.push_back(a.x);
        cur1.push_back(a.y);
        cur2.push_back(a.x);
        cur2.push_back(a.y);
        return quadInt[cur1] < quadInt[cur2];
    }
    bool friend operator == (const Quadrant &a, const Quadrant &b){
        string cur1, cur2;
        cur1.push_back(a.x);
        cur1.push_back(a.y);
        cur2.push_back(a.x);
        cur2.push_back(a.y);
        return quadInt[cur1] == quadInt[cur2];
    }
};


bool dfs(const Node &a, const Node &b, LL code){
    if(code == 1){
        
    }else{
        Quadrant aLoc, bLoc;
        aLoc.x = (a.x-1) / code;
        aLoc.y = (a.y-1) / code;
        bLoc.x = (b.x-1) / code;
        bLoc.y = (b.y-1) / code;
        if(aLoc == bLoc) dfs(a, b, code / 2);
        else return aLoc < bLoc;
    }
}

bool cmp(const Node &a, const Node &b){
    return dfs(a, b, 1<<(k-1));
}

int main(){
    quadInt["00"] = 0;
    quadInt["01"] = 1;
    quadInt["11"] = 2;
    quadInt["10"] = 3;

    return 0;
}
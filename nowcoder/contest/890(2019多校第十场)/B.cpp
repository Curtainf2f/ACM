#include <bits/stdc++.h>
 
using namespace std;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;
 
#ifdef _LOCAL
#define show(x) cerr << "[" << #x << ": " << x << "] (" << __LINE__ << ", in `" << __FUNCTION__ << "`)\n"
struct Tester {
    // Tester() { freopen("data.in", "r", stdin); }
    ~Tester() { fprintf(stderr, "\nTime: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC)); }
} _shower;
#else
#define show(x)
#endif
 
const int N = 1e4+5;
const int M = 1e4+5;
const LL MOD = 1e9+7;

string s[222];

int main(int argc, char const *argv[]) {
    s[1] = "COFFEE";
    s[2] = "CHICKEN";
    for(int i = 3; i < 22; i ++){
        s[i] = s[i-2] + s[i-1];
    }
    int n, k;
    while(cin >> n >> k){
        cout << s[n].substr(k - 1, 10) << endl;
    }
    return 0;
}
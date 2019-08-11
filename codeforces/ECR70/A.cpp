#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define test(x) cerr << #x << "=" << x << endl
#else
    #define test(x)
#endif

typedef long long LL;

const int N = 1e5+5;
const int INF = 0x7fffffff;
string s1, s2;

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    int t;
    cin >> t;
    while(t --){
        cin >> s1 >> s2;
        int lowbit = 0;
        for(int i = s2.size() - 1; i >= 0; i --){
            if(s2[i] == '1'){
                lowbit = s2.size() - i;
                break;
            }
        }
        int s2loc = lowbit;
        if(lowbit == 0) lowbit = 1;
        int lbs1 = 0;
        for(int i = s1.size() - lowbit; i >= 0; i --){
            if(s1[i] == '1'){
                lbs1 = s1.size() - i;
                break;
            }
        }
        test(lbs1);
        test(s2loc);
        cout << lbs1 - s2loc << endl;
    }
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define test(x) cerr << #x << "=" << x << endl
#else
    #define test(x)
#endif

typedef long long LL;

const int N = 1e5+5;
string s;

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    int t;
    cin >> t;
    while(t --){
        int maxUp = 0, maxDown = 0, maxLeft = 0, maxRight = 0;
        int x = 0, y = 0;
        cin >> s;
        for(int i = 0; i < s.size(); i ++){
            if(s[i] == 'W') y ++;
            else if(s[i] == 'S') y --;
            else if(s[i] == 'A') x --;
            else if(s[i] == 'D') x ++;
            maxUp = max(maxUp, y);
            maxDown = min(maxDown, y);
            maxLeft = min(maxLeft, x);
            maxRight = max(maxRight, x);
        }
        LL len = maxRight - maxLeft + 1;
        LL kuan = maxUp - maxDown + 1;
        LL ans = len * kuan;
        if(len > 2) ans = min(ans, (len - 1) * kuan);
        if(kuan > 2) ans = min(ans, len * (kuan-1));
        cout << ans << endl;
    }
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
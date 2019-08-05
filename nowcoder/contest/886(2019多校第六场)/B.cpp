#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define test(x) cerr << #x << "=" << x << endl
#else
    #define test(x)
#endif

typedef long long LL;

const int N = 2e5+5;

LL a[10];
char tmp[55];
string s, cmp;
string ans;

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    int t;
    scanf("%d", &t);
    for(int cas = 1; cas <= t; cas ++) {
        for(int i = 1; i <= 8; i ++) scanf("%16lld", &a[i]);
        for(int i = 1; i <= 8; i ++){
            LL x = 0;
            LL k = 1;
            while (a[i]) {
                x += (a[i] % 10) * k;
                a[i] /= 10;
                k *= 2;
            }
            a[i] = x;
        }
        for(int i = 1; i <= 8; i ++){
            sprintf(tmp, "%x", a[i]);
            s.push_back(':');
            s += tmp;
        }
        s.push_back(':');
        string curr = s;
        if(curr[curr.size() - 1] == ':' && curr[curr.size() - 2] != ':') curr.pop_back();
        if(curr[0] == ':' && curr[1] != ':') curr.erase(0, 1);
        ans = curr;
        cmp = ":0:0:";
        while (1)
        {
            string cur = cmp;
            cur += "0:";
            if(s.find(cur) == s.npos) break;
            cmp = cur;
        }
        int pos = 0;
        while ((pos = s.find(cmp, pos)) != string::npos) {
            string cur = s;
            cur.replace(pos, cmp.size(), "::");
            if(cur[cur.size() - 1] == ':' && cur[cur.size() - 2] != ':') cur.pop_back();
            if(cur[0] == ':' && cur[1] != ':') cur.erase(0, 1);
            if(cur.size() < ans.size()) ans = cur;
            else if(cur.size() == ans.size()){
                if(cur < ans) ans = cur;
            }
            pos ++;
        }
        
        printf("Case #%d: ", cas);
        cout << ans << endl;
        s.clear();
    }
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
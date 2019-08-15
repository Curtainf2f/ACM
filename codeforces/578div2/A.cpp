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

const int N = 1e5+5;
const int MOD = 1e9+7;
const LL INF = 0x3f3f3f3f3f3f3f3f;

string s;
int a[15];

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    int n;
    scanf("%d", &n);
    cin >> s;
    for(int i = 0; i < s.size(); i ++){
        if(s[i] == 'L'){
            for(int i = 0; i <= 9; i ++){
                if(a[i] == 0){
                    a[i] = 1;
                    break;
                }
            }
        }else if(s[i] == 'R'){
            for(int i = 9; i >= 0; i --){
                if(a[i] == 0){
                    a[i] = 1;
                    break;
                }
            }
        }else{
            a[s[i] - '0'] = 0;
        }
    }
    for(int i = 0; i <= 9; i ++) printf("%d", a[i]);
    puts("");
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
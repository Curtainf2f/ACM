#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define test(x) cerr << #x << "=" << x << endl
#else
    #define test(x)
#endif

typedef long long LL;

const int N = 2e5+5;

int ans[N];

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    string s;
    cin >> s;
    s.push_back('R');
    int left = 0, right = 0;
    int inpL, inpR;
    bool toLeft = false;
    for(int i = 0; i < s.size(); i ++){
        if(s[i] == 'R'){
            if(toLeft){
                int cur = left + right >> 1;
                int flo = (left + right) % 2;
                int times = max(left, right) - 1;
                int curLeft = cur, curRight = cur;
                if(left > right) curLeft += flo;
                else curRight += flo;
                if(times & 1) swap(curLeft, curRight);
                ans[inpL] = curRight;
                ans[inpR] = curLeft;
                right = 1;
                toLeft = false;
            }else{
                right ++;
            }
        }
        else{
            if(!toLeft){
                toLeft = true;
                inpL = i-1;
                inpR = i;
                left = 1;
            }else{
                left ++;
            }
        }
    }
    bool first = true;
    for(int i = 0; i < s.size() - 1; i ++){
        if(first) first = false;
        else printf(" ");
        printf("%d", ans[i]);
    }
    puts("");
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
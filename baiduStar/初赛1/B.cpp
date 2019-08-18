#include <bits/stdc++.h>
 
using namespace std;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;
 
#ifdef _LOCAL
#define test(x) cerr << "[" << #x << ": " << x << "] (" << __LINE__ << ", in `" << __FUNCTION__ << "`)\n"
struct Tester {
    Tester() { freopen("data.in", "r", stdin); }
    ~Tester() { fprintf(stderr, "\nTime: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC)); }
} _shower;
#else
#define test(x)
#endif
 
const int N = 10005;
const LL MOD = 1e9+7;

pair<int, int> a[N];

int main(int argc, char const *argv[]) {
    int t;
    scanf("%d", &t);
    while(t --){
        int n;
        scanf("%d", &n);
        for(int i = 1; i <= n; i ++){
            scanf("%d%d", &a[i].first, &a[i].second);
        }
        int left = a[1].first, right = a[1].second;
        int now = 1;
        for(int i = 2; i <= n; i ++){
            if(a[i].first >= left && a[i].first <= right && a[i].second >= left && a[i].second <= right){
                left = a[i].first;
                right = a[i].second;
            }else if(a[i].first >= left && a[i].first <= right){
                left = a[i].first;
            }else if(a[i].second >= left && a[i].second <= right){
                right = a[i].second;
            }else{
                now = i - 1;
                break;
            }
        }
        int pos;
        if(now + 1 <= n && a[now+1].second < left){
            pos = left;
        }else{
            pos = right;
        }
        LL ans = 0;
        while(now <= n){
            test(pos);
            test(ans);
            if(a[now].first <= pos && a[now].second >= pos){
                now ++;
                continue;
            }
            if(now == n){
                if(a[now].first > pos){
                    ans += ((a[now].first - pos) + 1) / 2;
                    pos = a[now].first;
                }else if(a[now].second < pos){
                    ans += ((pos - a[now].second) + 1) / 2;
                    pos = a[now].second;
                }
            }else{
                if(a[now].first > pos){
                    ans += ((a[now].first - pos) + 1) / 2;
                    if((a[now].first - pos) % 2 == 0){
                        pos = a[now].first;
                    }else{
                        int cur1 = 0, curNow = now;
                        while(a[curNow].first <= a[now].first && a[curNow].second >= a[now].first) cur1 ++, curNow ++;
                        int cur2 = 0; curNow = now;
                        while(a[curNow].first <= a[now].first + 1 && a[curNow].second >= a[now].first + 1) cur2 ++, curNow ++;
                        if(cur1 < cur2){
                            pos = a[now].first + 1;
                        }else if(cur1 > cur2){
                            pos = a[now].first;
                        }else{
                            if(curNow <= n && a[curNow].first > a[now].first) pos = a[now].first + 1;
                            else if(curNow <= n && a[curNow].second < a[now].first) pos = a[now].first;
                            else pos = a[now].first;
                        }
                    }
                }else if(a[now].second < pos){
                    ans += ((pos - a[now].second) + 1) / 2;
                    if((pos - a[now].second) % 2 == 0){
                        pos = a[now].first;
                    }else{
                        int cur1 = 0, curNow = now;
                        while(a[curNow].first <= a[now].second - 1 && a[curNow].second >= a[now].second - 1) cur1 ++, curNow ++;
                        int cur2 = 0; curNow = now;
                        while(a[curNow].first <= a[now].second && a[curNow].second >= a[now].second) cur2 ++, curNow ++;
                        if(cur1 < cur2){
                            pos = a[now].second;
                        }else if(cur1 > cur2){
                            pos = a[now].second - 1;
                        }else{
                            if(curNow <= n && a[curNow].first > a[now].second) pos = a[now].second;
                            else if(curNow <= n && a[curNow].second < a[now].second) pos = a[now].second - 1;
                            else pos = a[now].second;
                        }
                    }
                }
            }
        }
        printf("%I64d\n", ans);
    }
    return 0;
}
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
 
map<string, vector<pair<int, int> > > ns;
vector<string> ans;
string s, win;

int main(int argc, char const *argv[]) {
    int n, x;
    cin >> n;
    for(int i = 1; i <= n; i ++){
        cin >> s >> x;
        if(ns.find(s) != ns.end()){
            ns[s].push_back(make_pair(ns[s][ns[s].size()-1].first + x, i));
        }else{
            ns[s].push_back(make_pair(0, i));
            ns[s].push_back(make_pair(x, i));
        }
    }
    int _max = 0;
    for(auto it = ns.begin(); it != ns.end(); it ++){
        if((it->second)[(it->second).size()-1].first > _max){
            _max = (it->second)[(it->second).size()-1].first;
            ans.clear();
            ans.push_back(it->first);
        }else if((it->second)[(it->second).size()-1].first == _max){
            ans.push_back(it->first);
        }
    }
    int _min = 9999999;
    for(int i = 0; i < ans.size(); i ++){
        vector<pair<int, int> > &now = ns[ans[i]];
        int cur = 99999;
        for(int i = 0; i < now.size(); i ++){
            if(now[i].first >= _max){
                cur = now[i].second;
                break;
            }
        }
        test(cur);
        test(ans[i]);
        test(_min);
        if(cur < _min) _min = cur, win = ans[i];
    }
    cout << win << endl;
    return 0;
}
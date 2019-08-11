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
 
int to[10][10][10][10];
 
bool use[10];
// use x,y  a->b
void bfs(int x, int y, int s){
    memset(use, 0, sizeof(use));
    queue<pair<int, int> > q;
    q.push(make_pair(s, 0));
    bool first = true;
    while(!q.empty()){
        pair<int, int> now = q.front();
        q.pop();
        if(use[now.first]) continue;
        if(first) first = false;
        else{
            use[now.first] = true;
            to[x][y][s][now.first] = now.second;
        }
        q.push(make_pair((now.first+x)%10, now.second + 1));
        q.push(make_pair((now.first+y)%10, now.second + 1));
    }
}
 
int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    memset(to, 0xff, sizeof(to));
    for(int x = 0; x < 10; x ++){
        for(int y = 0; y < 10; y ++){
            for(int s = 0; s < 10; s ++){
                bfs(x, y, s);
            }
        }
    }
    string s;
    cin >> s;
    for(int x = 0; x < 10; x ++){
        for(int y = 0; y < 10; y ++){
            LL cur = 0;
            for(int ii = 1; ii < s.size(); ii ++){
                if(to[x][y][s[ii-1] - '0'][s[ii] - '0'] == -1){
                    cur = -1;
                    break;
                }
                cur += to[x][y][s[ii-1] - '0'][s[ii] - '0'] - 1;
            }
            if(cur == -1) cout << cur << " ";
            else cout << cur << " ";
        }
        cout << endl;
    }
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
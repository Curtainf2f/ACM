#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define test(x) cerr << #x << "=" << x << endl
#else
    #define test(x)
#endif

typedef long long LL;

const int N = 2e5+5;

string s;
vector<string> split;

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    int t;
    scanf("%d", &t);
    while(t --){
        cin >> s;
        bool zero;
        if(s[0] == '0') zero = true;
        else zero = false;
        string tmp;
        for(int i = 0; i < s.size(); i ++){
            if(s[i] == '0'){
                if(zero) tmp.push_back(s[i]);
                else{
                    split.push_back(tmp);
                    tmp = "0";
                    zero = true;
                }
            }else{
                zero = false;
                tmp.push_back(s[i]);
            }
        }
        if(tmp.size()) split.push_back(tmp);
        tmp.clear();
        for(int i = 1; i < split.size(); i ++){
            string cur1 = split[i-1] + split[i];
            string cur2 = split[i] + split[i-1];
            if(cur1 <= cur2){
                split.insert(split.begin() + i + 1, cur1);
                split.erase(split.begin() + i-1, split.begin() + i + 1);
                i = 0;
            }
        }
        for(int i = 0; i < split.size(); i ++){
            if(i != 0) putchar(' ');
            cout << split[i];
        }
        cout << endl;
        split.clear();
    }
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
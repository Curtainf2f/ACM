#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define test(x) cerr << #x << "=" << x << endl
#else
    #define test(x)
#endif

typedef long long LL;

struct p
{
    long long high, i;
} temp;

stack<p> s;
int main()
{
    long long li, ans, n;

    while(~scanf("%I64d", &n) && n)
    {
        p t;
        ans = 0;
        while(!s.empty())
            s.pop();
        temp.high=-1;
        temp.i=0;
        s.push(temp);
        LL anss = 0;
        for(int i = 1; i <= n+1; i++)
        {
            if(i != n+1)
            {
                scanf("%I64d", &t.high);
                t.i = i;
            }
            else
            {
                t.i = n+1;
                t.high = 0;
            }
            while(!s.empty() && t.high < s.top().high)
            {
                long long cur;
                anss ++;
                temp=s.top();
                s.pop();
                test(s.top().i);
              //  printf("[%I64d %d] %I64d\n",s.top().i,i,temp.high);
                cur = temp.high * (i - s.top().i-1 );
                if(cur > ans)
                    ans = cur;
            }
            s.push(t);
        }
        printf("%I64d\n", anss);
    }
    return 0;
}
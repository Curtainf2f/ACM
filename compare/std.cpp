#include<stdio.h>
#include<string.h>
#include<string>
#include<stdlib.h>
#include<math.h>
#include<algorithm>
#include<queue>
#include<stack>
#include<set>
#include<map>
#include<vector>
#include<iostream>
#include<bitset>
#include<unordered_map>
using namespace std;
#define sca(a) scanf("%d",&a)
#define out(a) printf("%d\n",a)
#define mes(x,a); memset(x,a,sizeof(x));
#define mk(a,b) make_pair(a,b)
#define lowbit(x)  x & (-x)
#define ll long long
#define fi first
#define se second
#define pii pair<int, int>
#define ull unsigned long long
const int maxn=1e7+5;
const int maxm=2e6+5;
const int inf =0x3f3f3f3f;
const int mod=998244353;
const double eps=1e-9;
const double pi=acos(-1);
const int siz=2;
int m,n,w;
ll gc[maxn];
ll sum[maxn];
void init()
{
    int n=1e7;
    sum[1]=1;
    for(int i=2; i<=n; i++)
    {
        sum[i]=i;
        gc[i]=i;
    }
    for(int i=2; i<=n; i++)
    {
        if(gc[i]==i)
        {
            for(int j=i; j<=n; j+=i)
                gc[j]=gc[j]/i*(i-1);
        }
    }
    for(int i=2; i<=n; i++)
    {
        int k=1;
        for(int j=i; j<=n; j+=i)
        {
            sum[j]=sum[j]+gc[i]*k;
            k++;
        }
        sum[i]%=mod;
    }
}
ll gcd(ll a,ll b)
{
    if(b==0)
        return a;
    return gcd(b,a%b);
}
template <class T>
ll getans(T a)
{
    ll ans=0;
    T j=1;
    T aa=2,b;
    if(a<7)
    {
        j=1;
        ans=1;
    }
    else
    {
        aa=j*j*j;
        b=(j+1)*(j+1)*(j+1);
        while(b<=a+1)
        {
            T bb=b-aa;
            int num1=bb%j;
            int num2=bb/j;
            ans=ans+num2*sum[j];
            if(num1)
            {
                int k=1;
                ans+=j;
                while(--num1)
                {
                    ans+=gcd(k,j);
                    k++;
                }
            }
            j++;
            aa=b;
            b=(j+1)*(j+1)*(j+1);
        }
    }
    int cnt1=(a+1)-aa;
    int num1=cnt1%j;
    int num2=cnt1/j;
    ans+=num2*sum[j];
    if(num1)
    {
        int k=1;
        ans+=j;
        while(--num1)
        {
            ans+=gcd(k,j);
            k++;
        }
    }
    return ans%mod;
}
template <class T>
void read(T &x)
{
    static char ch;
    static bool neg;
    for(ch=neg=0; ch<'0' || '9'<ch; neg|=ch=='-',ch=getchar());
    for(x=0; '0'<=ch && ch<='9'; (x*=10)+=ch-'0',ch=getchar());
    x=neg?-x:x;
}

int main()
{
    init();
    __int128 n;
    int t;
    read(t);
    while(t--)
    {
        read(n);
        printf("%I64d\n",getans(n));
    }
}

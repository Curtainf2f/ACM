#include<stdio.h>
#include<string.h>
#include<string>
#include<stdlib.h>
#include<math.h>
#include<algorithm>
#include<queue>
#include<stack>
#include<set>
#include<time.h>
#include<map>
#include<vector>
#include<iostream>
using namespace std;
#define sca(a) scanf("%d",&a)
#define out(a) printf("%d\n",a)
#define mes(x,a); memset(x,a,sizeof(x));
#define lowbit(x)  x & (-x)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define ll long long
#define fi first
#define se second
#define pii pair<int, int>
typedef unsigned long long ull;
const int maxn=5e5+5;
const int maxm=2e6+5;
const int inf =0x3f3f3f3f;
const ll mod=1e9+7;
const double eps=1e-9;
const double pi=acos(-1);
const double e=2.718281828;
int n,m,w,k;
ll ans;
struct ids
{
    int x,id;
} a[6][maxn];
bool cmp(const ids &a,const ids &b)
{
    if(a.x==b.x)
        return a.id<b.id;
    return a.x>b.x;
}
bool vis[maxn];
int main()
{
    int _;
    scanf("%d",&n);

    for(int j=0; j<n; j++)
    {
        for(int i=1; i<=5; i++)
            scanf("%d",&a[i][j].x),a[i][j].id=j;
    }
    sort(a[5],a[5]+n,cmp);
    sort(a[1],a[1]+n,cmp);
    sort(a[2],a[2]+n,cmp);
    sort(a[3],a[3]+n,cmp);
    sort(a[4],a[4]+n,cmp);
    int q=min(n,5);
    set<int>se;
    ans=-inf;
    for(int i=0; i<q; i++)
    {
        vis[a[1][i].id]=1;
        for(int j=0; j<q; j++)
        {
            if(vis[a[2][j].id]==0)
            {
                vis[a[2][j].id]=1;
                for(int k=0; k<q; k++)
                {
                    if(!vis[a[3][k].id])
                    {
                        vis[a[3][k].id]=1;
                        for(int l=0; l<q; l++)
                        {
                            if(!vis[a[4][l].id])
                            {
                                vis[a[4][l].id]=1;
                                for(int p=0; p<q; p++)
                                {
                                    if(vis[a[5][p].id]==0)
                                        ans=max(ans,1LL*a[1][i].x+a[2][j].x+a[3][k].x+a[4][l].x+a[5][p].x);
                                }
                                vis[a[4][l].id]=0;
                            }
                        }
                        vis[a[3][k].id]=0;
                    }
                }
                vis[a[2][j].id]=0;
            }
        }
        vis[a[1][i].id]=0;
    }
    cout<<ans<<endl;
    return 0;
}


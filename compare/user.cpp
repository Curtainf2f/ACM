#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<queue>
#include<map>
#include<set>
using namespace std;
long long dp[100005][10],z[100005][10];
int vis[100005][10][10];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=5; j++)
        {
            cin>>z[i][j];
        }
    }
    memset(vis,0,sizeof(vis));
    memset(dp,0,sizeof(dp));
    long long ans=-1;
    for(int i=1; i<=n; i++)
    {
        long long max2=-1,p2;
        for(int l=1; l<=5; l++)
        {
            if(dp[i-1][l]>max2)
            {
                max2=dp[i-1][l];
                p2=l;
            }
        }
        for(int j=1; j<=5; j++)
        {
            long long max1=-1,p;
            for(int l=1; l<=5; l++)
            {
                if(dp[i-1][l]-z[vis[i-1][l][j]][j]>max1)
                {
                    max1=dp[i-1][l]-z[vis[i-1][l][j]][j];
                    p=l;
                }
            }
            if(max1+z[i][j]>dp[i-1][p2])
            {
                dp[i][j]=max1+z[i][j];
                for(int k=1; k<=5; k++)
                {
                    vis[i][j][k]=vis[i-1][p][k];
                }
                vis[i][j][j]=i;
            }
            else
            {
                dp[i][j]=dp[i-1][p2];
                for(int k=1; k<=5; k++)
                {
                    vis[i][j][k]=vis[i-1][p2][k];
                }
            }
            ans=max(ans,dp[i][j]);
        }
    }
    cout<<ans<<endl;
}

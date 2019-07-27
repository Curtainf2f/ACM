#include <iostream>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <math.h>
#include <queue>
#define MAXN 3e6+10
#define inf 0x3f3f3f3f
using namespace std;
const int N=3e6+10;
typedef long long ll;
int a[N],L[N],R[N],s[N],top,b[N];
ll sum[N],ans=-0x7f7f7f7f,n,h[N];
ll l=1,r=1;
struct node
{
    int l,r;
    ll mx;
    ll mn;
} tree[N<<2];
void pushup(int index)
{
    tree[index].mx = max(tree[index<<1].mx,tree[index<<1|1].mx);
    tree[index].mn = min(tree[index<<1].mn,tree[index<<1|1].mn);
}
 
int cnt;
void build(int l,int r,int index)
{
    tree[index].l = l;
    tree[index].r = r;
    if(l == r)
    {
        tree[index].mn = tree[index].mx =sum[++cnt];
        return ;
    }
    int mid = (l+r)>>1;
    build(l,mid,index<<1);
    build(mid+1,r,index<<1|1);
    pushup(index);
}
 
ll queryMIN(int l,int r,int index)
{
    if(l <= tree[index].l && r >= tree[index].r)
    {
        return tree[index].mn;
    }
    int mid = (tree[index].l+tree[index].r)>>1;
    ll Min =0x7f7f7f7f;
    if(l <= mid)
    {
        Min = min(queryMIN(l,r,index<<1),Min);
    }
    if(r > mid)
    {
        Min = min(queryMIN(l,r,index<<1|1),Min);
    }
    return Min;
}
ll queryMAX(int l,int r,int index)
{
    if(l <= tree[index].l && r >= tree[index].r)
    {
        return tree[index].mx;
    }
    int mid = (tree[index].l+tree[index].r)>>1;
    ll Max = -0x7f7f7f7f;
    if(l <= mid)
    {
        Max = max(queryMAX(l,r,index<<1),Max);
    }
    if(r > mid)
    {
        Max = max(queryMAX(l,r,index<<1|1),Max);
    }
    return Max;
}
int main()
{
    ios::sync_with_stdio(false);
    cin>>n;
    memset(sum,0,sizeof(sum));
    for(int i=1; i<=n; i++)
    {
        cin>>a[i];
    }
    for(int i=1; i<=n; i++)
    {
        cin>>b[i];
        sum[i]=sum[i-1]+b[i];
    }
    build(1,n+1,1);
    top=0;
    for(int i=1; i<=n; i++)
    {
        while(top&&a[s[top]]>=a[i])
            --top;
        L[i]=(top==0?1:s[top]+1);
        s[++top]=i;
    }
    top=0;
    for(int i=n; i>=1; i--)
    {
        while(top&&a[s[top]]>=a[i])
            --top;
        R[i]=(top==0?n:s[top]-1);
        s[++top]=i;
    }
    for(int i=1; i<=n; i++)
    {
        ll temp;
        if(a[i]>0)
        {
            temp =(sum[R[i]] - sum[L[i]-1])*a[i];
        }
        else if(a[i]<0)
        {
            if(L[i]==1 && queryMAX(max(1,L[i]-1),max(1,i-1),1)<0)
                temp=(queryMIN(i,R[i],1))*a[i];
            else
                temp =(queryMIN(i,R[i],1)-queryMAX(max(1,L[i]-1),max(1,i-1),1))*a[i];
        }
        else if(a[i]==0)
            temp=0;
        if(temp>ans)
        {
            ans=temp;
        }
    }
    cout<<ans<<endl;
}
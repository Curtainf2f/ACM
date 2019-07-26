/**动态主席树(树状数组套权值线段树)**/
#include<cstdio>
#include<iostream>
#include<algorithm>
#define N 50001
#define M N*400
#define lowbit(x) x&(-x)
#define calmid int mid=((l+r)>>1);
#define preA  A[0]=0; while(r) A[++A[0]]=root[r],r-=lowbit(r);
#define preB  B[0]=0; while(l) B[++B[0]]=root[l],l-=lowbit(l);
#define goleftA for(int i=1;i<=A[0];i++) A[i]=lc[A[i]];
#define goleftB for(int i=1;i<=B[0];i++) B[i]=lc[B[i]];
#define gorightA for(int i=1;i<=A[0];i++) A[i]=rc[A[i]];
#define gorightB for(int i=1;i<=B[0];i++) B[i]=rc[B[i]];
#define gotmpA     for(int i=1;i<=A[0];i++) tmp+=sum[lc[A[i]]];
#define gotmpB     for(int i=1;i<=B[0];i++) tmp-=sum[lc[B[i]]];
int n,m,tot;
int root[N],a[N],hash[N<<1];
int A[20],B[20];
namespace CMT
{
    int cnt=0,lc[M],rc[M],sum[M];
    void insert(int &k,int l,int r,int pos,int w)
    {
        if(!k) k=++cnt;
        sum[k]+=w;
        if(l==r) return;
        int mid=((l+r)>>1);
        if(pos<=mid) insert(lc[k],l,mid,pos,w);
        else insert(rc[k],mid+1,r,pos,w);
    }
    int getrank(int l,int r,int w,bool ty)
    {
        int tmp=0;
        if(l==r)
        {
            if(!ty) return 0;
            else
            {
                for(int i=1;i<=A[0];i++) tmp+=sum[A[i]];
                for(int i=1;i<=B[0];i++) tmp-=sum[B[i]];
                return tmp;
            }
        }
        gotmpA; gotmpB; calmid;
        if(w<=mid)
        {
            goleftA; goleftB;
            return getrank(l,mid,w,ty);
        }
        else
        {
            gorightA; gorightB;
            return tmp+getrank(mid+1,r,w,ty);
        }
    }
    int getnum(int l,int r,int w)
    {
        if(l==r) return hash[l];
        int tmp=0;
        gotmpA; gotmpB; calmid;
        if(w<=tmp)
        {
            goleftA; goleftB;
            return getnum(l,mid,w);
        }
        else
        {
            gorightA; gorightB;
            return getnum(mid+1,r,w-tmp);
        }
    }
}
namespace BIT
{
    void add(int pos,int key,int val)
    {
        while(pos<=n)
        {
            CMT::insert(root[pos],1,tot,key,val);
            pos+=lowbit(pos);
        }
    }
    int Qrank(int l,int r,int k,bool ty)
    {
        preA;
        preB;
        return CMT::getrank(1,tot,k,ty);
    }
    int Qnum(int l,int r,int k)
    {
        preA;
        preB;
        return CMT::getnum(1,tot,k);
    }
    void modify(int pos,int w)
    {
        A[0]=0; int tmp=pos;
        while(pos<=n) A[++A[0]]=pos,pos+=lowbit(pos);
        for(int i=1;i<=A[0];i++) CMT::insert(root[A[i]],1,tot,a[tmp],-1);
        for(int i=1;i<=A[0];i++) CMT::insert(root[A[i]],1,tot,w,1);
        a[tmp]=w;
    }
}
namespace solution
{
    struct node
    {
        int op,opl,opr,opk;
    }e[N];
    void read(int &x)
    {
        x=0; char c=getchar();
        while(!isdigit(c)) c=getchar();
        while(isdigit(c)) { x=x*10+c-'0'; c=getchar(); }
    }
    void init()
    {
        read(n); read(m);
        for(int i=1;i<=n;i++) read(a[i]),hash[i]=a[i];
        int opt,l,r,k; int tmp=n;
        for(int i=1;i<=m;i++)
        {
            read(opt);
            if(opt==3) read(l),read(k);
            else read(l),read(r),read(k);
            e[i].op=opt; e[i].opl=l; e[i].opk=k;
            if(opt!=3) e[i].opr=r;
            if(opt!=2) hash[++tmp]=k;
        }
        std::sort(hash+1,hash+tmp+1);
        tot=std::unique(hash+1,hash+tmp+1)-(hash+1);
        for(int i=1;i<=n;i++)
        {
            a[i]=std::lower_bound(hash+1,hash+tot+1,a[i])-hash;
            BIT::add(i,a[i],1);
        }
        for(int i=1;i<=m;i++)
        if(e[i].op!=2) e[i].opk=std::lower_bound(hash+1,hash+tot+1,e[i].opk)-hash;
    }
    void solve()
    {
        for(int i=1;i<=m;i++)
        {
            if(e[i].op==1) printf("%d\n",BIT::Qrank(e[i].opl-1,e[i].opr,e[i].opk,0)+1);
            else if(e[i].op==2) printf("%d\n",BIT::Qnum(e[i].opl-1,e[i].opr,e[i].opk));
            else if(e[i].op==3) BIT::modify(e[i].opl,e[i].opk);
            else if(e[i].op==4)
            {
                int tmp=BIT::Qrank(e[i].opl-1,e[i].opr,e[i].opk,0);
                if(!tmp) printf("-2147483647\n");
                else printf("%d\n",BIT::Qnum(e[i].opl-1,e[i].opr,tmp));
            }
            else
            {
                int tmp=BIT::Qrank(e[i].opl-1,e[i].opr,e[i].opk,1);
                if(tmp==e[i].opr-e[i].opl+1) printf("2147483647\n");
                else printf("%d\n",BIT::Qnum(e[i].opl-1,e[i].opr,tmp+1));
            }
        }
    }
}
int main()
{
    using namespace solution;
    init();
    solve();
}

#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define test(x) cerr << #x << "=" << x << endl
#else
    #define test(x)
#endif

typedef long long LL;

const int N = 1e6+5;

char sa[1100000],sb[1100000];
int lena,lenb;
int p[1100000],ex[1100000];

void exkmp()
{
    p[1]=lenb;
    int x=1;
    while(sb[x]==sb[x+1]&&x+1<=lenb) x++;//因为我们p[1]是具有一定性，所以我们不能直接用，所以要先暴力求出p[2] 
    p[2]=x-1;
    int k=2;
    for(int i=3;i<=lenb;i++)
    {
        int pp=k+p[k]-1,L=p[i-k+1];//pp实际上是p 
        if(i+L<pp+1) p[i]=L;//i-k+L<pp-k+1化简后i+L<pp 
        else
        {
            int j=pp-i+1;
            if(j<0) j=0;
            while(sb[j+1]==sb[i+j]&&i+j<=lenb) j++;
            p[i]=j;
            k=i;
        }
    }
    x=1;
    while(sa[x]==sb[x]&&x<=lenb) x++;//ex[1]并不具有一定性，所以我们暴力求出ex[1] 
    ex[1]=x-1;
    k=1;
    for(int i=2;i<=lena;i++)
    {
        int pp=k+ex[k]-1,L=p[i-k+1];
        if(i+L<pp+1) ex[i]=L;
        else
        {
            int j=pp-i+1;
            if(j<0) j=0;
            while(sb[j+1]==sa[i+j]&&i+j<=lena&&j<=lenb) j++;
            ex[i]=j;
            k=i;
        }
    }
}

int main(){
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    int t;
    scanf("%d", &t);
    while (t --) {
        scanf("%s",sa+1);
        lenb=strlen(sa+1);
        lena=lenb-1;
        strcpy(sb+1, sa+1);
        for(int i = 1; i <= lena; i ++) sa[i] = sa[i+1];
        exkmp();
        int ans = 0;
        for(int i = 1; i <= lena; i ++){
            if(ex[lena] == lena - i + 1){
                ans += ex[lena];
            }else{
                ans += ex[lena] + 1;
            }
        }
        for(int i=1;i<lena;i++) printf("%d ",ex[i]);
        printf("%d\n",ex[lena]);
        printf("%d\n", ans);
    }
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
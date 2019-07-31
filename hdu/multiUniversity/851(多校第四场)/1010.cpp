#include<bits/stdc++.h>
using namespace std;
#ifdef _LOCAL
    #define test(x) cerr << #x << "=" << x << endl
#else
    #define test(x)
#endif

typedef long long LL;
const int N = 100000005;
LL Mult_Mod(LL a,LL b,LL m)//res=(a*b)%m
{
    a%=m;
    b%=m;
    LL res=0;
    while(b)
    {
        if(b&1)
            res=(res+a)%m;
        a=(a<<=1)%m;
        b>>=1;
    }
    return res%m;
}
LL Pow_Mod(LL a, LL b, LL m)//res=(a^b)%m
{
    LL res=1;
    LL k=a;
    while(b)
    {
        if((b&1))
            res=Mult_Mod(res,k,m)%m;

        k=Mult_Mod(k,k,m)%m;
        b>>=1;
    }
    return res%m;
}

bool Witness(LL a,LL n,LL x,LL sum)
{
    LL judge=Pow_Mod(a,x,n);
    if(judge==n-1||judge==1)
        return 1;

    while(sum--)
    {
        judge=Mult_Mod(judge,judge,n);
        if(judge==n-1)
            return 1;
    }
    return 0;
}

bool Miller_Rabin(LL n)
{
    if(n<2)
        return 0;
    if(n==2)
        return 1;
    if((n&1)==0)
        return 0;

    LL x=n-1;
    LL sum=0;
    while(x%2==0)
    {
        x>>=1;
        sum++;
    }


    int times=20;
    for(LL i=1; i<=times; i++)
    {
        LL a=rand()%(n-1)+1;//取与p互质的整数a
        if(!Witness(a,n,x,sum))//费马小定理的随机数检验
            return 0;
    }
    return 1;
}
LL GCD(LL a,LL b)
{
    return b==0?a:GCD(b,a%b);
}
LL Pollard_Rho(LL n,LL c)//寻找一个因子
{
    LL i=1,k=2;
    LL x=rand()%n;//产生随机数x0(并控制其范围在1 ~ x-1之间)
    LL y=x;
    while(1)
    {
        i++;
        x=(Mult_Mod(x,x,n)+c)%n;
        LL gcd=GCD(y-x,n);

        if(gcd<0)
            gcd=-gcd;

        if(gcd>1&&gcd<n)
            return gcd;

        if(y==x)
            return n;

        if(i==k)
        {
            y=x;
            k<<=1;
        }
    }
}

int total;//因子的个数
LL factor[N];//存储所有因子的数组，无序的
void Find_fac(LL n)//对n进行素因子分解，存入factor
{
    if(Miller_Rabin(n))//是素数就把这个素因子存起来
    {
        factor[++total]=n;
        return;
    }

    long long p=n;
    while(p>=n)//值变化，防止陷入死循环k
        p=Pollard_Rho(p,rand()%(n-1)+1);

    Find_fac(n/p);
    Find_fac(p);
}
int main()
{
    #ifdef _LOCAL
        freopen("data.in", "r", stdin);
    #endif
    srand(time(0));
    int T;
    scanf("%d", &T);
    while(T--)
    {
        LL n;
        int ans = 100000000;
        int temp = 1;
        scanf("%lld", &n);
        if(Miller_Rabin(n)){
            puts("1");
            continue;
        }
        total = 0;
        Find_fac(n);
        sort(factor+1, factor+total+1);

//        for(int i = 1; i <= total; i++)
//        {
//            printf("%lld ",factor[i]);
//        }
//        printf("\n");
        for(int i = 1; i <= total; i++)
        {
            if(factor[i+1] == factor[i])
            {
                temp++;
            }
            if(factor[i+1] != factor[i])
            {
                ans = min(ans, temp);
                temp = 1;
            }
        }
        printf("%d\n", ans);
    }
    #ifdef _LOCAL
        fprintf(stderr, "T: %d ms\n", int(1000.0 * clock() / CLOCKS_PER_SEC));
    #endif
    return 0;
}
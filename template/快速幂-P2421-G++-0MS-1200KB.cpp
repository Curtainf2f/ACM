#include <cstdio>
#include <cstring>

long long mod;

long long quickpow(long long a, long long n)
{
    long long ans = 1;
    while(n)
    {
        if(n&1)
        {
            ans = ans * a % mod;
        }
        n >>= 1;
        a = a * a % mod;
    }
    return ans;
}

int main(int argc, char const *argv[])
{
    long long c, x, m;
    int t;
    scanf("%d", &t);
    for(int i = 1; i <= t; i ++)
    {
        printf("Case #%d:\n", i);
        scanf("%I64d%I64d%I64d%I64d", &x, &m, &mod, &c);
        mod *= 9;
        long long cur = (quickpow(10, m) - 1 + mod) % mod / 9;
        if(cur * x % (mod / 9) == c)
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}

#include<cstdio>
#include<cstring>

const int maxn = 1000005;

int next[maxn];
char pattern[maxn], text[maxn];

void prefix_table(char *pattern, int n)
{
    next[0] = -1;
    int j = -1, i = 0;
    while(i < n - 1){
        if(j == -1 || pattern[j] == pattern[i]){
            i++;
            j++;
            next[i] = j;
        }
        else
            j = next[j];
    }
}

int kmp_search(char *text, char *pattern){
    int tlen = strlen(text);
    int plen = strlen(pattern);
    prefix_table(pattern, plen);
    int i = 0, j = 0;
    while(i < tlen && j < plen){
        if(j == -1 || text[i] == pattern[j]){
            i++;j++;
        }
        else
            j = next[j];
    }
    if(j == plen) return i - j;
    else return -1;
}

int main()
{
    while(~scanf("%s%s", text, pattern))
        printf("%d\n", kmp_search(text, pattern));
    return 0;
}

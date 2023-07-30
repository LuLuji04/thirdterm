#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxsize 100001

int main()
{
    long long int n,m;
    scanf("%lld %lld",&n,&m);
    long long int i;
    int g[maxsize];
    memset(g,0,sizeof(g));
    for(i=1;i<=m;i++)
    {
        long long int a,b,c;
        scanf("%lld %lld %lld",&a,&b,&c);
        g[a]+=c;
        g[b]+=c;
    }
    long int maxi=1;
    for(i=1;i<=m;i++)
    {
        if(g[i]>g[maxi])
        maxi=i;
    }
    printf("%lld",maxi);
    return 0;
}
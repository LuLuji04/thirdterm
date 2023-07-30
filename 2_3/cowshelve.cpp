#include<stdio.h>
#include<stdlib.h>

#define maxsize 50
#define INF 9223372036854775807 
long long cowh[maxsize];
long long ans;
int N;
long long B;
//int vis[maxsize]={0};
void dfsshel(long long sum,int dep)
{
    if(sum >= B)
    {
        if(sum < ans)
        ans=sum;

        return;
    } 
    if(dep >N-1)
    return;
    
    dfsshel(sum+cowh[dep],dep+1);
    dfsshel(sum,dep+1);
}



int main()
{
    scanf("%d %lld",&N,&B);
    
    for(int i=0;i<N;i++)
    {
        scanf("%lld",&cowh[i]);
    }
    ans=INF;
    dfsshel(0,0);
    
    printf("%lld",ans-B);
}
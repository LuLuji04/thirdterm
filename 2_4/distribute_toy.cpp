#include<stdio.h>
#define maxsize 1010
#define max(a,b) (((a)>(b))?(a):(b))
int a[maxsize][maxsize];
int n;

int vis[maxsize];
int ans = 0;
int h(int now ) {  // 估价函数
    int sum = 0;
    for (int i = now + 1; i <=n; i++)
    {
        int maxi=a[i][0];
        sum += a[i][maxi];
        
    }
    return sum;
}


void dfs(int id, int sb) 
{
    ans = max(ans, sb);
    if (id == n+1) 
    return;
    if (h(id - 1) + sb <= ans)
    return;
    
    dfs(id + 1, sb);
    for(int i=1;i<=n;i++)
    {
        if(vis[i]==0)
        {
            vis[i]=1;
            dfs(id + 1, sb + a[id][i]);
            vis[i]=0;
        }
    }
}


int main()
{
    
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int maxi=0;
        for(int j=1;j<=n;j++)
        {
            scanf("%d",&a[i][j]);
            if(a[i][j]>a[i][maxi])
            maxi=j;
        }
        a[i][0]=maxi;
    }
    dfs(1,0);
    printf("%d",ans);
    return 0;
}
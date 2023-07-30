#include<stdio.h>
#include<string.h>
#define maxsize 510

char maze[maxsize][maxsize];
int vis[maxsize][maxsize];
int n,m,ans,cnt;


int in(int x,int y)
{
    return x>=0 && x<n && y>=0 && y<m;
}
void dfs(int x,int y)
{

    vis[x][y]=1;
    for(int i=0;i<n;i++)
    {
        int tx=i;
        int ty=y;
        if(!vis[tx][ty]&&maze[tx][ty]=='1')
        dfs(tx,ty);
    }

    for(int j=0;j<m;j++)
    {
        int tx=x;
        int ty=j;
        if(!vis[tx][ty]&&maze[tx][ty]=='1')
        dfs(tx,ty);
    }
}

int main()
{
    int ans=0;
    memset(vis,0,sizeof(vis));

    scanf("%d %d",&n,&m);
    for(int i=0;i<n;i++)
    scanf("%s",maze[i]);

    for (int i=0;i<n;i++)
    {
        for (int j=0;j<m;j++)
        {
            if(maze[i][j]=='1'&&!vis[i][j])
            {
                ans++;
                dfs(i,j);
            }
        }
    }
    printf("%d",ans);
    return 0;
}
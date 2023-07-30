#include<stdio.h>
#include<string.h>
#define maxsize 10000

char maze[maxsize][maxsize];
int vis[maxsize][maxsize];
int n,m,ans,cnt;
int dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};

int in(int x,int y)
{
    return x>=0 && x<n && y>=0 && y<m;
}
void dfs(int x,int y)
{
    cnt++;
    vis[x][y]=1;
    for(int i=0;i<4;i++)
    {
        int tx=x+dir[i][0];
        int ty=y+dir[i][1];
        if(in(tx,ty)&&!vis[tx][ty]&&maze[tx][ty]=='#')
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
            if(maze[i][j]=='#'&&!vis[i][j])
            {
                //ans++;
                cnt=0;
                dfs(i,j);
                if(cnt > ans)
                ans=cnt;
            }
        }
    }
    printf("%d",ans);
    return 0;
}
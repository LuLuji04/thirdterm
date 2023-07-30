#include<stdio.h>
#define maxsize 9
#define INF 32767

int n;
int dir[4][2] = { { -1, 0}, {0, -1}, {1, 0}, {0, 1}};
int vis[maxsize][maxsize];
int qi[maxsize][maxsize];
int in(int x, int y) 
{
    return 1 <= x && x <= n && 1 <= y && y <= n;
}



int ans;
void dfs(int x,int y,int step)
{
    
    if(x==n&&y==1)
    {
        if(step==n*n)
        ans++;

        //vis[x][y]=0;
        return;
    }
    vis[x][y]=1;

    
    int flag=0;
    int chodir[4]={0};
    for (int i = 0; i < 4; i++)
    {
        int tx = x + dir[i][0];
        int ty = y + dir[i][1];
        qi[tx][ty]--;

        if(in(tx, ty)&&qi[tx][ty]==1&&!vis[tx][ty])
        {
            chodir[i]=1;
            flag=1;
        }
    }
    if (flag==1) 
    {
        for (int i = 0; i < 4; i++)
        { 
            int tx = x + dir[i][0];
            int ty = y + dir[i][1];
            if(chodir[i]==1&&in(tx, ty)&&!vis[tx][ty])
            {

                dfs(tx,ty,step+1);
            }
        }
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            
            int tx = x + dir[i][0];
            int ty = y + dir[i][1];
            if(in(tx, ty)&&!vis[tx][ty])
            {
                dfs(tx,ty,step+1); 
            }
        }
    }


    for (int i = 0; i < 4; i++)
    {
        int tx = x + dir[i][0];
        int ty = y + dir[i][1];
        qi[tx][ty]++;
    } 

    
    vis[x][y]=0;
}


int main()
{
    scanf("%d",&n);
    ans=0;
    for (int i = 0; i <= n+1; i++)
    {
        for (int j = 0; j <= n+1; j++)
        {
            if(i==0||i==n+1||j==0||j==n+1)
            qi[i][j]=INF;
            else if(i==1&&j==1 || i==n&&j==1 || i==1&&j==n || i==n&&j==n)
            qi[i][j]=2;
            else if(i==1||i==n||j==1||j==n)
            qi[i][j]=3;
            else
            qi[i][j]=4;
        }
    }
    qi[n][1]=3;
    dfs(1,1,1);
    printf("%d",ans);
    ans=0;
}
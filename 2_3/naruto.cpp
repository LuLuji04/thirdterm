#include<stdio.h>
#include<string.h>
#define maxsize 210
#define INF 32767
char map[maxsize][maxsize];


int  M,N,T;

int vis[maxsize][maxsize];
int dir[4][2] = { { -1, 0}, {0, -1}, {1, 0}, {0, 1}};
int ans = INF;

int in(int x, int y) {
    return 0 <= x && x < M && 0 <= y && y < N;
}
void dfs(int x, int y, int step,int ckl)
{
    if (step >= ans) 
        return;
    
    if(ckl<0)
        return;
    
    if (map[x][y] == '+')
     {
        ans = step;
        return;
    }

    vis[x][y] = 1;

    for (int i = 0; i < 4; i++)
    {
        int tx = x + dir[i][0];
        int ty = y + dir[i][1];
        if (in(tx, ty)  && !vis[tx][ty]) 
        {
            if(map[tx][ty] == '#')
            {
                dfs(tx, ty, step + 1,ckl-1);
            }
            else
                dfs(tx, ty, step + 1,ckl);
        }
    }
    vis[x][y] = 0;
}
int main() 
{

    scanf("%d %d %d",&M,&N,&T);
    for (int i = 0; i < M; i++) 
    {
        scanf("%s", map[i]);
    }
    int x, y;
    for (int i = 0; i < M; i++) 
    {
        for (int j = 0; j < N; j++)
         {
            if (map[i][j] == '@')
             {
                x = i;
                y = j;
            }
        }
    }
    dfs(x, y, 0,T);
    if(ans==INF)
    printf("%d",-1);
    else
    printf("%d", ans);
    return 0;
}

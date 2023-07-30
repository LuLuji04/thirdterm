#include <stdio.h>
#include<string.h>
#define maxsize 210
int M, N, T;
char map[maxsize][maxsize];
int vis[maxsize][maxsize][11];
int dir[4][2] = { { -1, 0}, {0, -1}, {1, 0}, {0, 1}};


int in(int x, int y)
 {
    return 0 <= x && x < M && 0 <= y && y < N;
}
struct node
{
    int x, y, d;
    int ckl;
} q[maxsize*maxsize];
int l,r;


int bfs(int sx, int sy,int T) {
    l = 0, r = 0;
    struct node t = {sx, sy, 0,T};
    q[r++] = t;
    vis[sx][sy][T] = 1;
    while (l < r)
    {
        struct node now = q[l++];

        if (map[now.x][now.y] == '+') 
        {
            return now.d;
        }
        for (int i = 0; i < 4; i++)
         {
            int tx = now.x + dir[i][0];
            int ty = now.y + dir[i][1];

            if(map[tx][ty] == '#')
            t.ckl=now.ckl-1;
            else
            t.ckl=now.ckl;
                
            if (t.ckl>=0 && in(tx, ty) && vis[tx][ty][t.ckl]==0) 
            {
                vis[tx][ty][t.ckl] = 1;
                t.x=tx;
                t.y=ty;
                t.d=now.d+1;
                q[r++] = t;
            }
        }
    }
    return -1;
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
    printf("%d",bfs(x,y,T));
}
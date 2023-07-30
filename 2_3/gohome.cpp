#include <stdio.h>
#include<string.h>
#define maxsize 2010
int n, m;
char map[maxsize][maxsize];
int vis[maxsize][maxsize][2];
int dir[4][2] = { { -1, 0}, {0, -1}, {1, 0}, {0, 1}};


int in(int x, int y)
 {
    return 0 <= x && x < n && 0 <= y && y < m;
}
struct node
{
    int x, y, d;
    int key;
} q[maxsize*maxsize];
int l,r;


int bfs(int sx, int sy) {
    l = 0, r = 0;
    struct node t = {sx, sy, 0};
    q[r++] = t;
    vis[sx][sy][0] = 1;
    while (l < r)
    {
        struct node now = q[l++];

        if (map[now.x][now.y] == 'T' && now.key==1) 
        {
            return now.d;
        }
        for (int i = 0; i < 4; i++)
         {
            int tx = now.x + dir[i][0];
            int ty = now.y + dir[i][1];

            if(map[tx][ty]=='P'||now.key==1)
            t.key=1;
            else
            t.key=0;
                
            if (in(tx, ty) && map[tx][ty]!='#' && vis[tx][ty][t.key]==0) 
            {
                vis[tx][ty][t.key] = 1;
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

    scanf("%d %d",&n,&m);
    for (int i = 0; i < n; i++) 
    {
        scanf("%s", map[i]);
    }
    int x, y;
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++)
         {
            if (map[i][j] == 'S')
             {
                x = i;
                y = j;
            }
        }
    }
    printf("%d",bfs(x,y));
}
#include <stdio.h>
int n, m;
char maze[110][110];

int dir[8][2] = { { 2, 1}, {2, -1}, {1, 2}, {1, -2}, {-2, 1}, {-2, -1}, {-1, 2}, {-1, -2}};
int vis[110][110];

int in(int x, int y) {
    return 0 <= x && x < 10 && 0 <= y && y < 9;
}
int dfs(int x, int y) {

    vis[x][y] = 1;
    if(maze[x][y] == 'T')
    {
        return 1;
    }
    
    
    for (int i = 0; i < 8; i++) {
        int tx = x + dir[i][0];
        int ty = y + dir[i][1];
        if(in(tx,ty)&&!vis[tx][ty]&&maze[tx][ty]!='#')
        {
            if(dfs(tx, ty))
            {
                return 1;
            }
            
        }
    }
    return 0;
}
int main() {

    int sx, sy;

    for(int i=0;i<10;i++)
    scanf("%s",maze[i]);

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 9; j++) {
            if(maze[i][j] == 'S')
            {
                sx=i;
                sy=j;
            }
            
        }
    }
    if(dfs(sx, sy))
    printf("Yes");
    else
    printf("No");

    return 0;
}
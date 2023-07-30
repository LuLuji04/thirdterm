#include <stdio.h>
#include<string.h>
int n, m, l, r;
char maze[1100][1100];
int vis[500][500][50];
int dir[4][2] = { { -1, 0}, {0, -1}, {1, 0}, {0, 1}};
int in(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < m;
}
struct node {
    int x, y, cha, d;
} q[100100];
int bfs(int sx, int sy, int cha) {
    l = 0, r = 0;
    struct node t = {sx, sy, cha, 0};
    q[r++] = t;
    vis[sx][sy][cha] = 1;
    while (l < r) {
        struct node now = q[l++];
        for(int i = 0; i < 4; i++) {
            int tx = now.x + dir[i][0];
            int ty = now.y + dir[i][1];
            if (maze[tx][ty] == '+') {
            	return now.d+1;
        	}
            if (in(tx, ty) && now.cha>=0 &&maze[tx][ty] != '#' && !vis[tx][ty][now.cha] ) {
		        vis[tx][ty][now.cha] = 1;
                struct node t = {tx, ty, now.cha, now.d + 1};
                q[r++] = t;
	        }
	        else if(in(tx, ty) && now.cha>0  && maze[tx][ty] == '#' ){
	        	if( !vis[tx][ty][now.cha-1]){
	        		vis[tx][ty][now.cha-1] = 1;
                	struct node t = {tx, ty, now.cha-1, now.d + 1};
                	q[r++] = t;
				}
			}
        }
    }
    return -1;
}
int main() {
    int cha;
    memset(vis,0,sizeof(vis));
    scanf("%d %d %d", &n, &m, &cha);
    for (int i = 0; i < n; i++) {
        scanf("%s", maze[i]);
    }
    int x, y;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (maze[i][j] == '@') {         
				x = i;
                y = j;
            }
        }
    }
    printf("%d\n", bfs(x, y, cha));
    return 0;
}
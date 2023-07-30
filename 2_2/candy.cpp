#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxsize 100010

struct edge {
    int v, next;
} e[maxsize];
int head[maxsize], eid;
void insert(int x, int y) {
    e[eid].v = y;
    e[eid].next = head[x];
    head[x] = eid++;
}
void insert2(int x, int y) {
    insert(x, y);
    insert(y, x);
}
int n, m, q[maxsize], l, r;
int dis[maxsize];
void bfs(int s) {
    memset(dis, -1, sizeof(dis));
    dis[s] = 1;
    l = r = 0;
    q[r++] = s;
    while (l < r) {
        int now = q[l++];
        for (int i = head[now]; ~i; i = e[i].next) {
            int v = e[i].v;
            if (dis[v] == -1) {
                dis[v] = dis[now] + 1;
                q[r++] = v;
            }
        }
    }
}


int main()
{
    int n,p,c;
    scanf("%d %d %d",&n,&p,&c);
    memset(head, -1, sizeof(head));
    int m;
    scanf("%d",&m);
    
    for (int i = 0; i < p; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        insert2(u, v);
    }
    bfs(c);
    int maxdis=0;
    for(int i=1;i<=n;i++)
    {
        if(dis[i]>maxdis)
        maxdis=dis[i];
    }
    printf("%d", maxdis+m);
    
    return 0;
}
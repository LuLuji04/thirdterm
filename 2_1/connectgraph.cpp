#include <stdio.h>
#include <string.h>
#define maxsize 40010
struct edge {
    int v, next;
} e[maxsize];
int p[maxsize], eid;
void insert(int x, int y) {
    e[eid].v = y;
    e[eid].next = p[x];
    p[x] = eid++;
}
void insert2(int x, int y) {
    insert(x, y);
    insert(y, x);
}
int vis[maxsize];
void dfs(int u) {
    vis[u] = 1;
    //printf("%d\n", u);
    for (int i = p[u]; ~i; i = e[i].next) {
        int v = e[i].v;
        if (!vis[v]) {
            dfs(v);
        }
    }
}
int main() {
    memset(p, -1, sizeof(p));
    memset(vis, 0, sizeof(vis));    
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        insert2(u, v);
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        if(vis[i]==0)
        {
            ans++;
            dfs(i);
        }
    }
    printf("%d",ans);
    return 0;
}
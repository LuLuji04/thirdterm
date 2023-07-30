#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxsize 1000010

struct edge 
{
    int v, next;
}e[maxsize];

struct hole
{
    long long x,y,z;
    int nex;
}head[maxsize];

int eid;

int is_touch(int u,int v,long long r)
{
    if(head[u].x==-1 && head[u].y==-1)
    {
        if(abs(head[u].z-head[v].z) <= r)
        return 1;
    }
    else
    {
        long long x=head[u].x-head[v].x;
        long long y=head[u].y-head[v].y;
        long long z=head[u].z-head[v].z;
        if(x*x+y*y+z*z <= (r+r)*(r+r))
        return 1;
    }
    return 0;
}
void insert(int u, int v) {
    e[eid].v = v;
    e[eid].next = head[u].nex;
    head[u].nex = eid++;
}

void insert2(int u,int n,long long r)
{
    for(int i=0;i<=n+1;i++)
    {
        if(head[i].z!=-1 &&i!=u && is_touch(i,u,r))
        {
            insert(i, u);
            insert(u, i);
        }
    }
}



int q[maxsize], l, r;
int dis[maxsize];

int bfs(int start,int end) {
    memset(dis, -1, sizeof(dis));
    dis[start] = 1;
    l = r = 0;
    q[r++] = start;
    while (l < r) {
        int now = q[l++];
        if(now==end)
        return dis[now];

        for (int i = head[now].nex; ~i; i = e[i].next) {
            int v = e[i].v;
            if (dis[v] == -1) {
                dis[v] = dis[now] + 1;
                q[r++] = v;
            }
        }
    }
    return -1;
}
void inhole()
{
    int n;
    long long h,r;
    scanf("%d %lld %lld",&n,&h,&r);
    memset(head, -1, sizeof(head));

    head[0].z=0;
    head[n+1].z=h;

    for(long long i=1;i<=n;i++)
    {
        long long x,y,z;
        scanf("%lld %lld %lld",&x,&y,&z);
        head[i].x=x;
        head[i].y=y;
        head[i].z=z;
        insert2(i,n,r);
    }
    int ans=bfs(0,n+1);
    if(ans==-1)
    printf("%d\n",-1);
    else
    printf("%d\n", ans-2);

}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        inhole();
    }
}
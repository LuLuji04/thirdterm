#include <stdio.h>
#include <string.h>
#include <math.h>
#define maxsize 10101
#define min(a,b) (((a)<(b))?(a):(b))
const double INF = 100000000;

struct edge {
    int v, next;
    double w;
    int f;//1有效,0无效
} e[maxsize * 2];

struct  pnode
{
    int x,y;
    int nex;
    int valid;
}head[maxsize];

int eid, n, m, s,  vis[maxsize];
double d[maxsize];

int shortestpre[maxsize];
int pre[maxsize];

void insert(int u, int v, double w)
 {
    struct edge t = {v,head[u].nex, w, 1};
    e[eid] = t;
    head[u].nex = eid++;
}
void insert2(int u, int v, double w) 
{
    insert(u, v, w);
    insert(v, u, w);
}

void shortest()
{
    for(int i=0;i<maxsize;i++)
    d[i]=INF;
    memset(pre, -1, sizeof(pre));
    memset(vis, 0, sizeof(vis));
    d[1] = 0;
    for (int i = 1; i <= n; i++) {
        double mind = INF;
        int u = 0;
        for (int j = 1; j <= n; j++) {
            if (!vis[j] && d[j] < mind) {
                mind = d[j];
                u = j;
            }
        }
        if (mind == INF) {
            break;
        }
        vis[u] = 1;//u是d中最短的点
        for (int j = head[u].nex; j != -1; j = e[j].next) {
            
            if(e[j].f==1)
            {
                int v = e[j].v;

                if(d[u]+e[j].w < d[v])
                {
                    d[v]=d[u]+e[j].w;
                    pre[v]=u;
                }
            }
            
        }
    }
}


int inpath(int u,int v)
{
    int keypath[maxsize]={0};
    int i=n,k=0;
    while(i>=1){
        keypath[k++]=i;
        i=shortestpre[i];
    }
    for(k=k-1;k>0;k--)
    {
        if(u==keypath[k]&&v==keypath[k-1])
        return 1;
    }
    return 0;
}

double secondshort()
{
    for(int i=0;i<maxsize;i++)
    shortestpre[i]=pre[i];
    double min=INF;

    for(int u=1;u<=n;u++)
    {
        for(int i=head[u].nex;~i;i=e[i].next)
        {
            if(inpath(u,e[i].v))
            {
                e[i].f=e[i^1].f=0;
                shortest();
                e[i].f=e[i^1].f=1;
                if(d[n]<min)
                min=d[n];
            }
        }
    }
    return min;
    
}

int main() {
    scanf("%d %d", &n, &m);  // s 是源点
    memset(head, -1, sizeof(head));

    for (int i = 1; i <= n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        head[i].valid=1;
        head[i].x=x;
        head[i].y=y;
    }
    for (int i = 1; i <= m; i++) 
    {
        int p, q ;
        scanf("%d %d", &p, &q);
        double w =pow((double)(head[p].x-head[q].x) , (double)2)
                 +pow((double)(head[p].y-head[q].y) , (double)2)  ;

        insert2(p, q, pow(w,(double)1/2));
    }

    shortest();

    printf("%.2lf",secondshort());
    
    return 0;
}
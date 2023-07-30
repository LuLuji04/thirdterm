#include "state.h"
#include<stdlib.h>
#include<string.h>
#define MAX 100000
#define  INF 0x3f3f3f3f

int n,cnt=0,eid=0;
int path[MAX];
int pre[MAX];
int visit[MAX];
int dis[MAX];
int head[MAX];

void init_State(struct State *s) {
    s->height = 0;
    s->width = 0;
    s->data = NULL;
}
void delete_State(struct State *s) {
    if (s->data != NULL) {
        for (int i = 0; i < s->height; i++) {
            free(s->data[i]);
        }
        free(s->data);
    }
    s->height = 0;
    s->width = 0;
    s->data = NULL;
}


struct edge
{
    int v,next,flag;
    int w;
}e[MAX];


void insert(int u, int v, int w)
{
    struct edge t = {v, head[u], 1, w};
    e[eid] = t;
    head[u] = eid++;
}


void insert2(int u, int v, int w)
{
    insert(u,v,w);
    insert(v,u,w);
}

int in(struct State *s,int x,int y)
{
    int width,height;
    if(x % 2 == 0)
    {
        width=s->width;
    }
    else
    {
        width=s->width-1;
    }
    height=s->height;
    return 0 <= x && x < height && 0 <= y && y < width;
}


int idx(struct State *s,int x,int y)
{
    return x * s->width + y+1;
}

int even[6][2] = {{-1,0},{1,0},{0,-1},{0,1},{-1,-1},{1,-1}};

int odd[6][2] = {{-1,0},{1,0},{0,-1},{0,1},{-1,1},{1,1}};
    //初始化



void parse(struct State *s, struct PNG *p) 
{
    s->width = p->width/8;
    s->height= p->height/8;

    s->data = (int **)malloc(s->height * sizeof(int *));
    for (int i = 0; i < s-> height; i++) 
    {
        s->data[i] = (int *)malloc(s->width * sizeof(int));
    }

    int x,y=6;
    int i=0,j=0;
    struct PXL *pxl;
    while(y < p->height)
    {   
        if(i%2==0)
        x=4;
        else
        x=8;
        j=0;
        while(x < p->width)
        {
            pxl=get_PXL(p,x,y);
            s->data[i][j]= 255*255*3 
                    - pxl->red* pxl->red 
                    - pxl->green* pxl->green 
                    - pxl->blue* pxl->blue; 

            x+=8;
            j++;
        }

        y+=8;
        i++;
    }



    if (s->height % 2 == 0)
    {
       n = (s->width * s->height - 1);
    }
    else
    {
        n = (s->width * s->height);
    }



    memset(head,-1,sizeof(head));
    for (int i = 0;i < s->height;i++)
    {
        
        if(i%2==0)
        {
            for (int j = 0;j < s->width;j++)
            {
                int u = idx(s,i,j);

                for (int k = 0; k < 6;k++)
                {
                    int tx = i + even[k][0];
                    int ty = j + even[k][1];
                    if (in(s,tx,ty))
                    {
                        int v = idx(s,tx,ty);
                        insert(u,v,s->data[tx][ty]);
                    }
                }
                
            }
        }

        else
        {
             for (int j = 0;j < s->width-1;j++)
            {
                int u = idx(s,i,j);
                for (int k = 0; k < 6;k++)
                {
                    
                    int tx = i + odd[k][0];
                    int ty = j + odd[k][1];
                    if (in(s,tx,ty))
                    {
                        int v = idx(s,tx,ty);
                        insert(u,v,s->data[tx][ty]);
                    }
                }
            }         
                
        }
    }
}


void Path(int x)
{
    if (x == 1)
    {
        path[cnt] = 1;
        return;
    }
    path[cnt++] = x;
    Path(pre[x]);
}





int solve1(struct State *s)
{
    
    for (int i = 1;i <= n;i++)
    {
        dis[i] = INF;
    }
    memset(visit,0,sizeof(visit));



    dis[1] = 0;
    for (int i = 1;i <= n;i++)
    {
        int mind = INF;
        int u = 0;
        for (int j = 1;j <= n;j++)
        {
            if (!visit[j] && dis[j] < mind)
            {
                mind = dis[j];
                u = j;
            }
        }

        if (mind == INF)
        {
            break;
        }

        visit[u] = 1;
        for (int j = head[u];~j;j = e[j].next)
        {
            if (e[j].flag)
            {
                int v = e[j].v;
                if (dis[v] > dis[u] + e[j].w)
                {
                    dis[v] = dis[u] + e[j].w;
                    pre[v] = u;
     
                }
            }
        }
    }

    
    return dis[n];
}


int secondmin,minest;
int solve2(struct State *s)
{
    Path(n);
    minest=dis[n];
    secondmin = INF;
    for (int i = 0;i <cnt;i++)
    {
        int u1 = path[i];
        int v1 = path[i + 1];

        int eidu,eidv;
        for (int j = head[u1];~j;j = e[j].next)
        {
            if (e[j].v == v1)
            {
                eidu=j;
            }
            
        }
        for (int j = head[v1];~j;j = e[j].next)
        {
            if (e[j].v == u1)
            {
                eidv=j;
            }
        }


        e[eidu].flag = 0;
        e[eidv].flag = 0;
        solve1(s);
        if (dis[n] > minest && dis[n] <secondmin ) 
        {
            secondmin = dis[n];
        }
        e[eidu].flag = 1;
        e[eidv].flag = 1;
    }
    
    return secondmin;
}

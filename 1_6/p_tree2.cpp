#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxsize 100

struct edge
{
    int v,next;
}e[maxsize*2];

int degree[maxsize];
int head[maxsize],eid,d[maxsize];

void init()
{
    eid=1;
    memset(head,-1,sizeof(head));
    memset(degree,0,sizeof(degree));
}
void insert(int x,int y)
{
    e[eid].v=y;
    e[eid].next=head[x];
    degree[x]++;
    //degree[y]++;
    head[x]=eid++;
}
void insertnocount(int x,int y)
{
    e[eid].v=y;
    e[eid].next=head[x];
    head[x]=eid++;
}
void insert2(int x,int y)
{
    insert(x,y);
    insertnocount(y,x);
}
int create()
{
    int n,m,i,j;

    init();
    scanf("%d",&n);
    for(i=1;i<=n-1;i++)
    {
        int x,y;
        scanf("%d %d",&x,&y);
        insert2(x,y);
    }
        
    
    int pnum=0;
    for (i=1;i<=n;i++)
    {
        int flag=1;
        for (j=head[i];~j;j=e[j].next)
        {
            if(degree[i]<degree[e[j].v])
            {
                flag=0;
                break;
            }   
        }
        if(flag==1)
            pnum++;
    }
    return pnum;
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        printf("%d\n", create());
    }
    return 0;
}
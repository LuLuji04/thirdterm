#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxsize 100

struct edge
{
    int v,next;
}e[maxsize*2];
int head[maxsize],eid,d[maxsize];

void init()
{
    eid=0;
    memset(head,-1,sizeof(head));
}
void insert(int x,int y)
{
    e[eid].v=y;
    e[eid].next=head[x];
    head[x]=eid++;
}
void insert2(int x,int y)
{
    insert(x,y);
    insert(y,x);
}

int main()
{
    int n,m,i,j;
    init();
    scanf("%d %d",&n,&m);
    for (i=0;i<m;i++)
    {
        int a,x,y;
        scanf("%d %d %d",&a,&x,&y);
        if(a==0)
        insert(x,y);
        else
        insert2(x,y);
    }
    for (i=0;i<n;i++)
    {
        printf("%d: ",i);
        for (j=head[i];~j;j=e[j].next)
        {
            printf("%d ",e[j].v);
        }
        printf("\n");
    }
    return 0;
}

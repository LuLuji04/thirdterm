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

int findname(char *namelist[],int *llen,char *name)
{
    int i=0;
    while(i<*llen && strcmp(name,namelist[i])!=0 )
        i++;

    if(i>=*llen)
    {
        namelist[i]=name;
        (*llen)++;
    }

    return i;
}
int main()
{
    int n,m,i,j;
    init();
    char *namelist[maxsize];
    int llen=0,x,y;;
    scanf("%d",&n);
    for (i=0;i<n;i++)
    {
        
        char *name=(char*)malloc(sizeof(char)*maxsize);
        scanf("%s",name);
        x=findname(namelist,&llen,name);

        name=(char*)malloc(sizeof(char)*maxsize);
        scanf("%s",name);
        y=findname(namelist,&llen,name);

        insert2(x,y);
    }

    scanf("%d",&n);

    for (i=0;i<n;i++)
    {
        char *name=(char*)malloc(sizeof(char)*maxsize);
        scanf("%s",name);
        x=findname(namelist,&llen,name);
        scanf("%s",name);
        y=findname(namelist,&llen,name);
        
        int flag=0;
        for (j=head[x];~j;j=e[j].next)
        {
            if(e[j].v==y)
            {
                 printf("Yes\n");
                 flag=1;
                 break;
            }
        }
        if(flag==0)
        printf("No\n");
    }
    return 0;
}

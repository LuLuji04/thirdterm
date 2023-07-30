#include<stdio.h>
#include<stdlib.h>
#define maxsize 10010

typedef struct node
{
    int x,d;
}Node;

int in(int x,int n)
{
    return x>=1&&x<=n;
}

int dir[maxsize];

int bfslift(int n,int sx,int ex)
{
    Node sq[maxsize];
    int l=0;
    int r=0;

    Node t={sx,0};
    sq[r++]=t;
    int vis[maxsize]={0};
    vis[sx]=1;

    while(l<r)
    {
        Node now=sq[l++];
        if(now.x==ex)
        return now.d;
        
        Node next;
        int tx;

        tx=now.x+dir[tx];
        if(in(tx,n) && vis[tx]==0)
        {
            next.x=tx;
            next.d=now.d+1;
            vis[next.x]=1;
            sq[r++]=next;
        }
        tx=now.x-dir[tx];
        if(in(tx,n) && vis[tx]==0)
        {
            next.x=tx;
            next.d=now.d+1;
            vis[next.x]=1;
            sq[r++]=next;
        }

    }
    return -1;
}


int main()
{
    int N,A,B;
    scanf("%d %d %d",&N,&A,&B);
    for(int i=1;i<=N;i++)
    {
        scanf("%d",&dir[i]);
    }
    printf("%d",bfslift(N,A,B));
    return 0;
}
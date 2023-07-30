#include<stdio.h>
#include<stdlib.h>
#define maxsize 10010

typedef struct node
{
    int x,d;
}Node;

int in(int x,int n)
{
    return x>=0&&x<=n;
}

int bfsjump(int n,int sx,int ex)
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

        tx=now.x+1;
        if(in(tx,n) && vis[tx]==0)
        {
            next.x=tx;
            next.d=now.d+1;
            vis[next.x]=1;
            sq[r++]=next;
        }
        tx=now.x-1;
        if(in(tx,n) && vis[tx]==0)
        {
            next.x=tx;
            next.d=now.d+1;
            vis[next.x]=1;
            sq[r++]=next;
        }
        tx=now.x*2;
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
    int n,A,B;
    scanf("%d %d %d",&n,&A,&B);
    printf("%d",bfsjump(n,A,B));
    return 0;
}
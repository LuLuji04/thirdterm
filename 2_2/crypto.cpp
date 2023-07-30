#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxsize 1000000

typedef struct node
{
    int n[4];
    int d;
}Node;


void copy(int dis[],int sou[])
{
    for(int i=0;i<4;i++)
    dis[i]=sou[i];
}

int equal(int n[],int e[])
{
    for(int i=0;i<4;i++)
    {
        if(n[i]!=e[i])
        return 0;
    }
    return 1;
}

int bfsdecry(int n[],int e[])
{
    Node sq[maxsize];
    int l=0;
    int r=0;

    Node t;
    copy(t.n,n);
    t.d=0;
    sq[r++]=t;

    int vis[10][10][10][10];
    memset(vis, 0, sizeof(vis));
    vis[n[0]][n[1]][n[2]][n[3]]=1;

    while(l<r)
    {
        Node now=sq[l++];
        if(equal(now.n , e))
        return now.d;
        
        Node next;
        int tx[4];

        for(int i=0;i<4;i++)
        {
            copy(tx,now.n);
            tx[i]=now.n[i]+1;

            if(tx[i]==10)
            tx[i]=1;

            if(vis[tx[0]] [tx[1]] [tx[2]] [tx[3]]==0)
            {
                
                copy(next.n,tx);
                next.d=now.d+1;
                vis[tx[0]] [tx[1]] [tx[2]] [tx[3]]=1;
                sq[r++]=next;
            }
        }
        for(int i=0;i<4;i++)
        {
            copy(tx,now.n);
            tx[i]=now.n[i]-1;
            
            if(tx[i]==0)
            tx[i]=9;

            if(vis[tx[0]] [tx[1]] [tx[2]] [tx[3]]==0)
            {
                
                copy(next.n,tx);
                next.d=now.d+1;
                vis[tx[0]] [tx[1]] [tx[2]] [tx[3]]=1;
                sq[r++]=next;
            }
        }
        for(int i=0;i<3;i++)
        {
            copy(tx,now.n);
            int tmp=tx[i];
            tx[i]=tx[i+1];
            tx[i+1]=tmp;

            if(vis[tx[0]] [tx[1]] [tx[2]] [tx[3]]==0)
            {
                
                copy(next.n,tx);
                next.d=now.d+1;
                vis[tx[0]] [tx[1]] [tx[2]] [tx[3]]=1;
                sq[r++]=next;
            }
        }
        
    }
    return -1;
}


int main()
{
    int n[4],num;
    scanf("%d",&num);
    for(int i=3;i>=0;i--)
    {
        n[i]=num%10;
        num/=10;
    }
    int e[4];
    scanf("%d",&num);
    for(int i=3;i>=0;i--)
    {
        e[i]=num%10;
        num/=10;
    }
    printf("%d",bfsdecry(n,e));
    return 0;
}
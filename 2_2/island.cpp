#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxsize 20

typedef struct node
{
    int x,y,d;
}Node;



int in(int x,int y,int M,int N)
{
    return x>=0 && x<M && y>=0 && y<N;
}

int dir[4][2]={{1,0},{0,1},{-1,0},{0,-1}};

int bfsfind(int M,int N,char maze[maxsize][maxsize])
{
    Node sq[maxsize*maxsize];
    int l=0;
    int r=0;
    Node start;   
    
    int ex,ey;
    int vis[maxsize][maxsize];
    memset(vis,0,sizeof(vis));
    for(int i=0;i<M;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(maze[i][j]=='@')
            {
                start.x=i;
                start.y=j;
                start.d=0;
                vis[i][j]=1;
            }
            if(maze[i][j]=='*')
            {
                ex=i;
                ey=j;
            }
        }
    }
    sq[r++]=start;

    while(l<r)
    {
        Node now=sq[l++];
        if(now.x==ex&&now.y==ey)
        return now.d;
        
        Node next;
        int tx,ty;

        for (int i=0;i<4;i++)
        {
            tx=now.x+dir[i][0];
            ty=now.y+dir[i][1];

            if(in(tx,ty,M,N) && vis[tx][ty]==0 &&maze[tx][ty]!='#')
            {
                next.x=tx;
                next.y=ty;
                next.d=now.d+1;
                vis[tx][ty]=1;
                sq[r++]=next;
            }
        }
        
  
    }
    return -1;
}


int main()
{
    int M,N;
    char maze[maxsize][maxsize];

    scanf("%d %d",&M,&N);
    for(int i=0;i<M;i++)
    scanf("%s",maze[i]);

    printf("%d",bfsfind(M,N,maze));
    return 0;
}
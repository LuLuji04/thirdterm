#include<stdio.h>
#define maxsize 1000
#define INF 32767

int n,m;
int dir[4][2] = { { -1, 0}, {0, -1}, {1, 0}, {0, 1}};
int vis[maxsize][maxsize];
char map[maxsize][maxsize];
int in(int x, int y)
{
    return 0 <= x && x < n && 0 <= y && y < m;
}


struct node
{
    int x[maxsize];
    int y[maxsize];
    int d;
}q[maxsize];
int l=0,r=0;



int bfs(int sx[],int sy[],int lenth)
{
    l=r=0;
    struct node t;
    for(int i=1;i<=lenth;i++)
    {
        t.x[i]=sx[i];
        t.y[i]=sy[i];
        vis[sx[i]][sy[i]]=1;
    }
    if(lenth!=2)
    vis[sx[lenth]][sy[lenth]]=0;

    t.d=0;
    q[r++]=t;

    while(l < r)
    {
        struct node now;
        now=q[l++];

        if (map[now.x[1]][now.y[1]] == '@') 
        {
            return now.d;
        }

        if(lenth!=2)
        vis[now.x[lenth]][now.y[lenth]]=0;

        for(int i = 0; i < 4; i++) 
        {
            int tx = now.x[1] + dir[i][0];
            int ty = now.y[1] + dir[i][1];
            if(in(tx,ty) && map[tx][ty]!='#'&&vis[tx][ty]==0)
            {
                vis[tx][ty]=1;

                for(int j=lenth;j>=2;j--)
                {
                    t.x[j] = now.x[j-1];
                    t.y[j] = now.y[j-1];
                }

                t.x[1]=tx;
                t.y[1]=ty;

                t.d=now.d+1;
                q[r++]=t;
            }

        }

    }
    return -1;
    
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=0;i<n;i++)
    scanf("%s",map[i]);

    int sx[maxsize],sy[maxsize],lenth=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(map[i][j]>='1'&&map[i][j]<='9')
            {
                sx[map[i][j]-'0']=i;
                sy[map[i][j]-'0']=j;
                if(map[i][j]-'0' > lenth)
                lenth=map[i][j]-'0';
            }
        }
    }

    printf("%d",bfs(sx,sy,lenth));
}
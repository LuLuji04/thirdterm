#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxsize 1000
#define INF 32767

char maze[maxsize][maxsize];

int n,m;
int loc[maxsize][2];
int boonum=0,step;

int check()
{
    int num0=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(maze[i][j]=='0')
            num0++;
        }
    }
    return num0;          
}
void mark(int x,int y)
{
    maze[x][y]='4';
    for(int i=0;i<n;i++)
    {
        switch (maze[i][y])
        {
        case '0':
            maze[i][y]='2';
            break;
        case '1':
            mark(i,y);
            maze[i][y]='3';
            break;
        default:
            break;
        }
    }
    for(int j=0;j<m;j++)
    {
        switch (maze[x][j])
        {
        case '0':
            maze[x][j]='2';
            break;
        case '1':
            mark(x,j);
            maze[x][j]='3';
            break;
        default:
            break;
        } 
    }
}
void delemark(int x,int y)
{
    maze[x][y]='1';
    for(int i=0;i<n;i++)
    {
        switch (maze[i][y])
        {
        case '2':
            maze[i][y]='0';
            break;
        case '3':
            delemark(i,y);
            maze[i][y]='1';
            break;
        default:
            break;
        }
    }
    for(int j=0;j<m;j++)
    {
        switch (maze[x][j])
        {
        case '2':
            maze[x][j]='0';
            break;
        case '3':
            delemark(x,j);
            maze[x][j]='1';
            break;
        default:
            break;
        } 
    }
    
}


void boom(int x,int y,int nowstep,int *minstep)
{
    mark(x,y);
    if(check()==0)
    {
        printf("%d",nowstep);
        exit(0);
        if(nowstep<*minstep)
        *minstep=nowstep;
        delemark(x,y);
        
        return;
    }

    for(int i=0;i<boonum;i++)
    {
        int xt = loc[i][0];
        int yt = loc[i][1];
        if(maze[xt][yt]=='1')
        boom(xt,yt,nowstep+1,minstep);
    }
    delemark(x,y);
}

int main()
{
    int minstep=INF;

    scanf("%d %d",&n,&m);
    for(int i=0;i<n;i++)
    scanf("%s",maze[i]);


    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(maze[i][j]=='1')
            {
                loc[boonum][0]=i;
                loc[boonum][1]=j;
                boonum++;
            }
        }
    }

    for(int i=0;i<boonum;i++)
    {
        boom(loc[i][0],loc[i][1],1,&minstep);
    }
    printf("%d",minstep);
}
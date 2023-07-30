#include<stdio.h>
#include<string.h>
#define INF 32767
char board[5][5];
char input[5][5];
char right[5][5]=   {{'1','1','1','1','1'},
                    {'0','1','1','1','1'},
                    {'0','0','*','1','1'},
                    {'0','0','0','0','1'},
                    {'0','0','0','0','0'}};
int dir[8][2]={{2,1},{2,-1},{1,2},{1,-2},{-2,1},{-2,-1},{-1, 2},{-1,-2}};

int vis[5][5];

int check()
{
    int dif=0;
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(board[i][j]!=right[i][j])
            dif++;
        }

    }
    return dif;
}

int in(int x,int y)
{
    return x>=0&&x<5&&y>=0&&y<5;
}

int correct(int x,int y)
{
    if(board[x][y]=='1')
    {
        if(y>=x+1||(y==0&&x==0)||(y==1&&x==1)||(y==2&&x==2))
        return 1;
    }
    else 
    {
        if(x>=y+1||(y==2&&x==2)||(y==3&&x==3)||(y==4&&x==4))
        return 1;
    }
    return 0;
}

int flag;
void knight(int x,int y,int step,int k)
{
    if(step==k)
    {
        if(check()==0)
        flag=1;

        return ;
    }
    if(check()-1+step>k)
    return;

    vis[x][y]==1;
    int tx,ty;
    for(int i=0;i<8;i++)
    {
        tx=x+dir[i][0];
        ty=y+dir[i][1];
        if(in(tx,ty)&&vis[tx][ty]==0)
        {

            board[x][y]=board[tx][ty];
            board[tx][ty]='*';
            knight(tx,ty,step+1,k);
            board[tx][ty]=board[x][y];
            board[x][y]='*';
        }
    }
    vis[x][y]=0;
}


int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        for(int i=0;i<5;i++)
        {
            scanf("%s",input[i]);
        }
        int x,y;
        for(int i=0;i<5;i++)
        {
            for(int j=0;j<5;j++)
            {
                if(input[i][j]=='*')
                {
                    x=i;
                    y=j;
                }
            }
        }
        flag=0;
        int i;
        for(i=1;i<=15;i++)
        {
            memset(vis,0,sizeof(vis));
            for(int i=0;i<5;i++)
            {
                for(int j=0;j<5;j++)
                {
                    board[i][j]=input[i][j];
                }
            }


            knight(x,y,0,i);
            if(flag==1)
            break;
        }
        if(flag==0)
        printf("%d\n",-1);
        else
        printf("%d\n",i);
    }
    return 0;
}
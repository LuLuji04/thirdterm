#include<stdio.h>
#include<string.h>
char sudoku[9][9];
int row[9][10];
int col[9][10];
int square[9][10];
int blank;

int vis[9][9];
int dir[4][2]={{1,0},{0,1},{-1,0},{0,-1}};

int check(int x,int y,int c)
{
    return !row[x][c] && !col[y][c]&& !square[(x/3)*3+y/3][c];
}

int in(int x,int y)
{
    return x!=-1&&y!=-1&&x!=9&&y!=9;
}

void putsudoku()
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            printf("%c ",sudoku[i][j]);
        }
        printf("\n");
    }
}

int ok=0;
void dfs(int x,int y,int dep)
{
    if(ok==1)
    return;
    if(dep==blank)
    {
        ok=1;
        putsudoku();
        return ;
    }

    vis[x][y]=1;
    if(sudoku[x][y]=='*')
    {
        for (int c=1;c<=9;c++)
        {
            if(check(x,y,c))
            {
                sudoku[x][y]=c+'0';
                row[x][c]=1;
                col[y][c]=1;
                square[(x/3)*3+y/3][c]=1;

                int tx,ty;
                for(int i=0;i<4;i++)
                {
                    tx=x+dir[i][0];
                    ty=y+dir[i][1];
                    if(in(tx,ty)&&vis[tx][ty]==0)
                    {
                        dfs(tx,ty,dep+1);
                    }
                }

                row[x][c]=0;
                col[y][c]=0;
                square[(x/3)*3+y/3][c]=0;
                sudoku[x][y]='*';
            }
        }
    }
    else
    {
        int tx,ty;
        for(int i=0;i<4;i++)
        {
            tx=x+dir[i][0];
            ty=y+dir[i][1];
            if(in(tx,ty)&&vis[tx][ty]==0)
            {
                dfs(tx,ty,dep);
            }
        }
        
    }
    vis[x][y]=0;
            
}


int main()
{
    blank=0;
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            scanf(" %c",&sudoku[i][j]);
        }
    }

    memset(row,0,sizeof(row));
    memset(col,0,sizeof(col));
    memset(square,0,sizeof(square));
    memset(vis,0,sizeof(vis));

    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(sudoku[i][j]!='*')
            {
                row[i][sudoku[i][j]-'0']=1;
                col[j][sudoku[i][j]-'0']=1;
                square[(i/3)*3+j/3][sudoku[i][j]-'0']=1;
            }
            else
            {
                blank++;
            }
        }
    }
    dfs(0,0,0);
    return 0;
}
#include<stdio.h>
#include<string.h>
char sudoku[9][9];
int row[9][10];
int col[9][10];
int square[9][10];
int blank;



int check(int x,int y,int c)
{
    return !row[x][c] && !col[y][c]&& !square[(x/3)*3+y/3][c];
}

void putsudoku()
{
    printf("one solotion:\n");
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            printf("%c ",sudoku[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


void dfs(int x,int y)
{

    if(x==9)
    {
        putsudoku();
        return ;
    }

    if(y==9)
    {
        dfs(x+1,0);
        return;
    }
    

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

                        
                dfs(x,y+1);


                row[x][c]=0;
                col[y][c]=0;
                square[(x/3)*3+y/3][c]=0;
                sudoku[x][y]='*';
            }
        }
    }
    else
    {
        dfs(x,y+1);
    }

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
    dfs(0,0);
    return 0;
}
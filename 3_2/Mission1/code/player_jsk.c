/**
 * @file player.h
 * @brief Black and White Game AI Player
 */
#include <string.h>
#include "../include/playerbase.h"
#include <stdio.h>
#include <stdlib.h>
#include <climits>

//#define INT_MAX 0x3f3f3f3f
//#define INT_MIN -0x3f3f3f3f


#define maxsize 15
#define max(x, y)  ((x) > (y) ? (x) : (y))
#define min(x, y)  ((x) < (y) ? (x) : (y))


int prior[maxsize][maxsize];




struct Player *copyPlayer(struct Player *player)
{
    struct Player *new_player = (struct Player *)malloc(sizeof(struct Player));
    new_player->row_cnt = player->row_cnt;
    new_player->col_cnt = player->col_cnt;

    new_player->mat = (char **)malloc(new_player->row_cnt * sizeof(char *));
    for (int i = 0; i < new_player->row_cnt; i++)
    {
        new_player->mat[i] = (char *)malloc(new_player->col_cnt * sizeof(char));
        for (int j = 0; j < new_player->col_cnt; j++)
        {
            new_player->mat[i][j] = player->mat[i][j];
        }
    }

    return new_player;
}

void freePlayer(struct Player *player)
{
    for (int i = 0; i < player->row_cnt; i++)
    {
        free(player->mat[i]);
    }
    free(player->mat);
    free(player);
}

void output(struct Player *player)
{
    for (int i=0; i < player->col_cnt; i++)
    {
	    printf("%s \n",player->mat[i]);
	}
}


int count_pieces(struct Player *player, char piece)
{
    int count = 0;
    for (int row = 0; row < player->row_cnt; row++)
    {
        for (int col = 0; col < player->col_cnt; col++)
        {
            if (player->mat[row][col] == piece)
            {
                count+=prior[row][col];
            }
        }
    }
    return count;
}

int count_corner_pieces(struct Player *player, char piece)
{
    int corners[4][2] = {{0, 0}, {0, player->col_cnt - 1}, {player->row_cnt - 1, 0}, {player->row_cnt - 1, player->col_cnt - 1}};
    int count = 0;
    for (int i = 0; i < 4; i++)
    {
        int x = corners[i][0];
        int y = corners[i][1];
        if (player->mat[x][y] == piece)
        {
            count++;
        }
    }
    return count;
}

int is_valid(struct Player *player, int posx, int posy,int maximizingPlayer)
{
    if (posx < 0 || posx >= player->row_cnt || posy < 0 || posy >= player->col_cnt)
    {
        return 0;
    }
    if (player->mat[posx][posy] == 'o' || player->mat[posx][posy] == 'O')
    {
        return 0;
    }
    int step[8][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
    for (int dir = 0; dir < 8; dir++)
    {
        int x = posx + step[dir][0];
        int y = posy + step[dir][1];
        if (x < 0 || x >= player->row_cnt || y < 0 || y >= player->col_cnt)
        {
            continue;
        }
        if ((maximizingPlayer==1&&player->mat[x][y] != 'o' )||(maximizingPlayer==0&&player->mat[x][y] != 'O' ))
        {
            continue;
        }
        while (1)
        {
            x += step[dir][0];
            y += step[dir][1];
            if (x < 0 || x >= player->row_cnt || y < 0 || y >= player->col_cnt || (player->mat[x][y] >= '1' && player->mat[x][y] <= '9'))
            {
                break;
            }
            if ((maximizingPlayer==1&&player->mat[x][y] == 'O')||(maximizingPlayer==0&&player->mat[x][y]=='o' ))
            {
                return 1;
            }
        }
    }
    return 0;
}

void eat(struct Player *player,int posx,int posy,int maximizingPlayer)
{
    int step[8][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
    for (int dir = 0; dir < 8; dir++)
    {
        int x = posx + step[dir][0];
        int y = posy + step[dir][1];
        if (x < 0 || x >= player->row_cnt || y < 0 || y >= player->col_cnt)
        {
            continue;
        }
        if ((maximizingPlayer==1&&player->mat[x][y] != 'o' )||(maximizingPlayer==0&&player->mat[x][y] != 'O' ))
        {
            continue;
        }
        while (1)
        {
            x += step[dir][0];
            y += step[dir][1];
            if (x < 0 || x >= player->row_cnt || y < 0 || y >= player->col_cnt || (player->mat[x][y] >= '1' && player->mat[x][y] <= '9'))
            {
                break;
            }
            if (maximizingPlayer==1&&player->mat[x][y] == 'O')
            {
                int tx=posx;
                int ty=posy;
                while (tx!=x || ty!=y)
                {
                    player->mat[tx][ty] = 'O';
                    tx+=step[dir][0];
                    ty += step[dir][1];
                }
                //output(player);
                break;
                
            }
            else if(maximizingPlayer==0&&player->mat[x][y]=='o' )
            {
                int tx=posx;
                int ty=posy;
                while (tx!=x || ty!=y)
                {
                    player->mat[tx][ty] = 'o';
                    tx+=step[dir][0];
                    ty += step[dir][1];
                }
                break;
            }
        }
    }
}

int get_stable(int board[maxsize][maxsize],int n,int current)
{
    int corner = 0;  // 角点
    int steady = 0;  // 稳定子

    int row = n - 1;
    int corner_map[4][4] = 
    {
        // 角点 i, j, 偏移方向 dy, dx
        {0, 0, 1, 1},
        {0, row, 1, -1},
        {row, 0, -1, 1},
        {row, row, -1, -1}
    };

    // 计算角点和稳定子
    for (int c = 0; c < 4; c++) 
    {
        int corner_i = corner_map[c][0];
        int corner_j = corner_map[c][1];
        int dy = corner_map[c][2];
        int dx = corner_map[c][3];

        if (board[corner_i][corner_j] == 0) 
        {
            // 角点为空时，计算临角点和对角点的权值
            corner += board[corner_i][corner_j + dx] * current * -3;
            corner += board[corner_i + dy][corner_j] * current * -3;
            corner += board[corner_i + dy][corner_j + dx] * current * -6;

            // 角点为空时，计算隔角点的权值
            corner += board[corner_i][corner_j + 2 * dx] * current * 4;
            corner += board[corner_i + 2 * dy][corner_j] * current * 4;
            corner += board[corner_i + dy][corner_j + 2 * dx] * current * 2;
            corner += board[corner_i + 2 * dy][corner_j + dx] * current * 2;
        }
        else 
        {
            // 角点不为空时，处理稳定子
            int i = corner_i;
            int j = corner_j;
            int current_color = board[corner_i][corner_j];

            corner += board[corner_i][corner_j] * current * 15;  // 角点的权值

            // 向偏移方向搜索稳定子
            while (i >= 0 && i <= row && board[i][corner_j] == current_color) 
            {
                steady += current * current_color;
                i += dy;
            }
            while (j >= 0 && j <= row && board[corner_i][j] == current_color) 
            {
                steady += current * current_color;
                j += dx;
            }
        }
    }
    if(n==8)
    return 6 * corner + 12 * steady;
    else if(n==10)
    return 10 * corner + 12 * steady;
    else if(n==12)
    return 8 * corner + 12 * steady;
    else
    return 8 * corner + 12 * steady;

}

int is_frontier(int board[maxsize][maxsize],int i,int j)
{
    // 遍历周围的8个方向
    for (int dy = -1; dy <= 1; dy++) 
    {
        for (int dx = -1; dx <= 1; dx++) 
        {
            // 排除中心位置
            if (!(dy == 0 && dx == 0) && board[i + dy][j + dx] != 0) 
            {
                return 1;  // 周围存在非空棋子，判断为前沿子
            }
        }
    }
    return 0;  // 周围没有非空棋子，不是前沿子
}


int get_frontier(int board[maxsize][maxsize],int n,int current)
{
    int frontier = 0;  // 前沿子

    // 遍历棋盘计算前沿子
    for (int i = 1; i <= n-2; i++) 
    {
        for (int j = 1; j <= n-2; j++) 
        {
            if (board[i][j] != 0 && is_frontier(board, i, j)) 
            {
                frontier -= board[i][j] * current;  // 容易被吃掉，所以要取反
            }
        }
    }
    return frontier;
}

int get_movable(struct Player *player,int current)
{
    int movable=0;
    int n=player->col_cnt;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (is_valid(player, i, j , 1))
            {
                movable += 1;
            }
            if(is_valid(player, i, j , 0))
            {
                movable-=1;
            }
        }
    }
    return movable;
}
int evaluate(struct Player *player,int ok_cnt)
{
    // TODO: 实现棋局评估函数，根据棋子位置的重要性、棋子的稳定性、棋子的数量等因素进行评估
    // 返回评估得分（正值表示优势，负值表示劣势）
    int board[maxsize][maxsize];
    for (int i = 0;i < player->row_cnt;i++)
    {
        for (int j = 0;j < player->col_cnt;j++)
        {
            
            if (player->mat[i][j] == 'O')
            {
                board[i][j] = 1;
            }
            else if (player->mat[i][j] == 'o')
            {
                board[i][j] = -1;
            }
            else
            {
                board[i][j] = 0;
            }
        }
    }
 
    int n=player->col_cnt;
    player_score = get_stable(board ,n,1)   + 4 * get_frontier(board,n,1);

    return player_score;
}



int alpha_beta(struct Player *player, int depth, int alpha, int beta, int maximizingPlayer)
{


    struct Point *ok_points = (struct Point *)malloc((player->row_cnt * player->col_cnt) * sizeof(struct Point));
    int ok_cnt = 0;

    for (int i = 0; i < player->row_cnt; i++)
    {
        for (int j = 0; j < player->col_cnt; j++)
        {
            if (is_valid(player, i, j,maximizingPlayer))
            {
                ok_points[ok_cnt++] = initPoint(i, j);
            }
        }
    }
    if (depth == 0)
    {
        return evaluate(player,ok_cnt);
    }   

    if (ok_cnt == 0)
    {
        return evaluate(player,0);
    }


    if (maximizingPlayer)
    {
        int max_score = INT_MIN;

        for (int i = 0; i < ok_cnt; i++)
        {
            struct Player *next_player = copyPlayer(player);
            next_player->mat[ok_points[i].X][ok_points[i].Y] = 'O';
            eat(next_player,ok_points[i].X,ok_points[i].Y,1);
            int score = alpha_beta(next_player, depth - 1, alpha, beta, 0);

            alpha = max(alpha, score);

            freePlayer(next_player);

            if (beta <= alpha)
            {
                free(ok_points);
                return beta;
            }
        }

        free(ok_points);
        return alpha;
    }
    else
    {
        int min_score = INT_MAX;

        for (int i = 0; i < ok_cnt; i++)
        {
            struct Player *next_player = copyPlayer(player);
            next_player->mat[ok_points[i].X][ok_points[i].Y] = 'o';
            eat(next_player,ok_points[i].X,ok_points[i].Y,0);

            int score = alpha_beta(next_player, depth - 1, alpha, beta, 1);

            //min_score = min(min_score, score);
            beta = min(beta, score);

            freePlayer(next_player);

            if (beta <= alpha)
            {
                free(ok_points);
                return alpha;
            }
        }
        free(ok_points);
        return beta;
    }
}

void init(struct Player *player)
{
    return;         
}



struct Point place(struct Player *player)
{
    struct Point *ok_points = (struct Point *)malloc((player->row_cnt * player->col_cnt) * sizeof(struct Point));
   // struct Point ok_points[player->row_cnt * player->col_cnt];
    int ok_cnt = 0;

    for (int i = 0; i < player->row_cnt; i++)
    {
        for (int j = 0; j < player->col_cnt; j++)
        {
            if (is_valid(player, i, j,1))
            {
                ok_points[ok_cnt++] = initPoint(i, j);
            }
        }
    }

    struct Point point = initPoint(-1, -1);
    if (ok_cnt > 0)
    {
        int max_score = INT_MIN;
        int score = 0;
        for (int i = 0; i < ok_cnt; i++)
        {
            struct Player *next_player = copyPlayer(player);
            next_player->mat[ok_points[i].X][ok_points[i].Y] = 'O';
            eat(next_player,ok_points[i].X,ok_points[i].Y,1);
             score = alpha_beta(next_player, 2, INT_MIN, INT_MAX, 0);

            if (score > max_score)
            {
                max_score = score;
                point = ok_points[i];
            }

            freePlayer(next_player);
        }
    }

    free(ok_points);
    return point;
}

/**
 * @file player.h
 * @brief Black and White Game AI Player
 */
#include <string.h>
#include "../include/playerbase.h"
#include <stdio.h>
#include <stdlib.h>
//#include <climits>

//#define INT_MAX 0x3f3f3f3f
//#define INT_MIN -0x3f3f3f3f


#define maxsize 15
#define max(x, y)  ((x) > (y) ? (x) : (y))
#define min(x, y)  ((x) < (y) ? (x) : (y))


int prior[maxsize][maxsize];

struct Point initPoint(int x, int y)
{
    struct Point t={x,y};
    return t;
}


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

//int count_corner_around_pieces(struct Player *player, char piece)

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
        if ((maximizingPlayer==0&&player->mat[x][y] != 'o' )||(maximizingPlayer==1&&player->mat[x][y] != 'O' ))
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
            if ((maximizingPlayer==0&&player->mat[x][y] == 'O')||(maximizingPlayer==1&&player->mat[x][y]=='o' ))
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
        if ((maximizingPlayer==0&&player->mat[x][y] != 'o' )||(maximizingPlayer==1&&player->mat[x][y] != 'O' ))
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
            if (maximizingPlayer==0&&player->mat[x][y] == 'O')
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
            else if(maximizingPlayer==1&&player->mat[x][y]=='o' )
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

int evaluate(struct Player *player, char **board)
{
    // TODO: 实现棋局评估函数，根据棋子位置的重要性、棋子的稳定性、棋子的数量等因素进行评估
    // 返回评估得分（正值表示优势，负值表示劣势）

    int player_score = 0;
    int opponent_score = 0;

    // 考虑棋子数量得分
    int num_pieces = count_pieces(player, 'O');
    int num_opponent_pieces = count_pieces(player, 'o');
    player_score += num_pieces - num_opponent_pieces;
    opponent_score += num_opponent_pieces - num_pieces ;

    // 考虑角落位置的额外权重
    int corner_weight = 5;
    player_score += corner_weight * count_corner_pieces(player, 'O');
    opponent_score += corner_weight * count_corner_pieces(player, 'o');

    //int corner_around_weight = -10;
    //player_score += corner_around_weight * count_corner_around_pieces(player, 'O');
    //opponent_score += corner_around_weight * count_corner_around_pieces(player, 'o');

    // 返回得分差（可根据实际需求进行调整）
    return player_score - opponent_score;
}


int alpha_beta(struct Player *player, int depth, int alpha, int beta, int maximizingPlayer)
{
    if (depth == 0)
    {
        return evaluate(player, player->mat);
    }

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
    if (ok_cnt == 0)
    {
        return evaluate(player, player->mat);
    }


    if (maximizingPlayer)
    {
        int max_score = INT_MIN;

        for (int i = 0; i < ok_cnt; i++)
        {
            struct Player *next_player = copyPlayer(player);
            next_player->mat[ok_points[i].X][ok_points[i].Y] = 'O';
            eat(next_player,ok_points[i].X,ok_points[i].Y,0);
            int score = alpha_beta(next_player, depth - 1, alpha, beta, 0);

            max_score = max(max_score, score);
            alpha = max(alpha, max_score);

            freePlayer(next_player);

            if (beta <= alpha)
            {
                break;
            }
        }

        free(ok_points);
        return max_score;
    }
    else
    {
        int min_score = INT_MAX;

        for (int i = 0; i < ok_cnt; i++)
        {
            struct Player *next_player = copyPlayer(player);
            next_player->mat[ok_points[i].X][ok_points[i].Y] = 'o';
            eat(next_player,ok_points[i].X,ok_points[i].Y,1);
            int score = alpha_beta(next_player, depth - 1, alpha, beta, 1);

            min_score = min(min_score, score);
            beta = min(beta, min_score);

            freePlayer(next_player);

            if (beta <= alpha)
            {
                break;
            }
        }

        free(ok_points);
        if(depth==5)
        printf("返回前：%d\n",min_score);
        return min_score;
    }
}

void init(struct Player *player)
{
    int row = player->row_cnt;
    int col = player->col_cnt;
    int temp_number = row / 2;

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            prior[i][j] = 2;
            if (i == 0 && j == 0 || j == col - 1 && i == 0 || i == row - 1 && j == 0 || i == row - 1 && j == col - 1)
            {
                prior[i][j] = 5;
            }
            else if ((i == 0 || i == row - 1) && (j >= 2 && j <= col - 3) || (j == 0 || j == col - 1) && (i >= 2 && i <= col - 3))
            {
                prior[i][j] = 3;
            }
            else if ((i == 1 && j == 0) || (i == 0 && j == 1) || (i == 1 && j == 1) || (i == 0 && j == col - 2) || (i == 1 && j == col - 1) || (i == 1 && j == col - 2) || (i == row - 1 && j == 1) || (i == row - 2 && j == 1) || (i == row - 2 && j == 0) || (i == row - 2 && j == row - 2) || (i == row - 2 && j == row - 1) || (i == row - 1 && j == col - 2))
            {
                prior[i][j] = 1;
            }
            else if ((i == temp_number - 2 && (j <= temp_number + 1 && j >= temp_number - 2)) || (i == temp_number + 1 && (j <= temp_number + 1 && j >= temp_number - 2)) || (i == temp_number && (j == temp_number + 1 || j == temp_number - 2)) || (i == temp_number - 1 && (j == temp_number + 1 || j == temp_number - 2)))
            {
                prior[i][j] = 3;
            }
        }
    }
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
            if (is_valid(player, i, j,0))
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
            //output(next_player);
            //printf("\n");
            eat(next_player,ok_points[i].X,ok_points[i].Y,0);
            //output(next_player);
             score = alpha_beta(next_player, 5, INT_MIN, INT_MAX, 0);
             printf("(%d %d):",ok_points[i].X,ok_points[i].Y);
            printf("*%d\n",score);
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


int main()
{
    /*char map[maxsize][maxsize]={
        "1111111111",
        "1111111111",
        "1111111111",
        "1111o11111",
        "1111oo1111",
        "1111oO1111",
        "1111OoOo11",
        "111111oO11",
        "1111111oOo",
        "111111111O",
    };*/
    char map[maxsize][maxsize]={
        "OoOOOOOOOO",
        "OooOOOOoOO",
        "OOooOOoOOO",
        "OOooOoOoOO",
        "1oOooOoOOO",
        "o1OooooOOO",
        "OooooooOOO",
        "Oooooooooo",
        "Oooooooooo",
        "Oooooooooo"
    };



    struct Player *new_player = (struct Player *)malloc(sizeof(struct Player));
    new_player->row_cnt = 10;
    new_player->col_cnt = 10;

    new_player->mat = (char **)malloc(new_player->row_cnt * sizeof(char *));
    for (int i = 0; i < new_player->row_cnt; i++)
    {
        new_player->mat[i] = (char *)malloc(new_player->col_cnt * sizeof(char));
        for (int j = 0; j < new_player->col_cnt; j++)
        {
            new_player->mat[i][j] = map[i][j];
        }
    }

    place(new_player);
    return 0;
}


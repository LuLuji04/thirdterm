/**
 * @file player.h
 * @author yangboyang@jisuanke.com
 * @copyright jisuanke.com
 * @date 2021-07-01
 */

#include <string.h>
#include "../include/playerbase.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX 15
int row,col;
int prior[MAX][MAX];
/*struct point_prior
{
    struct Point;
    int priority;
};*/

void init(struct Player *player) 
{
    row = player->row_cnt;
    col = player->col_cnt;
    int temp_number = row / 2;

        for (int i = 0;i < row;i++)
        {
            for (int j = 0;j < col;j++)
            {
            	prior[i][j] = 4;
                if (i == 0 && j == 0 || j == col - 1 && i == 0 || i == row - 1 && j == 0 || i == row - 1  && j == col - 1)
                {
                    prior[i][j] = 1;
                }
                else if((i == 0 || i == row -1) && (j >= 2 && j <= col - 3 ) || (j == 0 || j == col - 1 ) && (i >= 2 && i <= col - 3)){
					prior[i][j] = 3;
				}
				else if((i == 1 && j ==0) || (i == 0 && j ==1) || (i == 1 && j == 1) || (i == 0 && j == col -2) || (i == 1 && j == col -1) ||(i == 1 && j == col - 2) || (i == row -1 && j == 1) || (i == row - 2 && j == 1) || (i == row - 2 && j == 0) || (i == row -2 && j == row - 2) ||(i == row - 2 && j == row - 1) || (i == row - 1 && j == col - 2)){
					prior[i][j] = 5;
				}
				else if((i == temp_number - 2 && (j <= temp_number + 1 && j >= temp_number - 2 )) || (i == temp_number + 1 && (j <= temp_number + 1 && j >= temp_number - 2 )) || (i == temp_number  && ( j == temp_number + 1 || j == temp_number - 2)) || (i == temp_number - 1 && (j == temp_number + 1 || j == temp_number - 2))){
					prior[i][j] = 2;
				}
            }
        }
        /*for (int i = 0;i < 8;i++)
        {
            for (int j = 0;j < 8;j++)
            {
                printf("%d",prior[i][j]);
            }
            printf("\n");
        }*/
    

	// This function will be executed at the begin of each game, only once.
}

int is_valid(struct Player *player, int posx, int posy) 
{
    if (posx < 0 || posx >= player->row_cnt || posy < 0 || posy >= player->col_cnt) 
    {
        return false;
    }
    if (player->mat[posx][posy] == 'o' || player->mat[posx][posy] == 'O') 
    {
        return false;
    }
    int step[8][2] = {0, 1, 0, -1, 1, 0, -1, 0, 1, 1, -1, -1, 1, -1, -1, 1};
    for (int dir = 0;  dir < 8; dir++) 
    {
        int x = posx + step[dir][0];
        int y = posy + step[dir][1];
        if (x < 0 || x >= player->row_cnt || y < 0 || y >= player->col_cnt) 
        {
            continue;
        }
        if (player->mat[x][y] != 'o') 
        {
            continue;
        }
        while (true) 
        {
            x += step[dir][0];
            y += step[dir][1];
            if (x < 0 || x >= player->row_cnt || y < 0 || y >= player->col_cnt || (player->mat[x][y] >= '1' && player->mat[x][y] <= '9')) {
                break;
            }
            if (player->mat[x][y] == 'O') 
            {
                return true;
            }
        }
    }
    return false;
}




struct Point place(struct Player *player) 
{
    struct Point *ok_points = (struct Point *)malloc((player->row_cnt * player->col_cnt) * sizeof(struct Point));
    int ok_cnt = 0;
	for (int i = 0; i < player->row_cnt; i++) 
    {
        for (int j = 0; j < player->col_cnt; j++) 
        {
            if (is_valid(player, i, j)) 
            {
                ok_points[ok_cnt++] = initPoint(i, j);
            }
        }
    }
    struct Point point = initPoint(-1, -1); 
    if (ok_cnt > 0) 
    {
        int min = 9;
        int min_index = -1;
        int i = 0;
        int j = 0;
        for (i = 0;i < ok_cnt;i++)
        {
            if (prior[ok_points[i].X][ok_points[i].Y] < min)
            {
                min = prior[ok_points[i].X][ok_points[i].Y];
                min_index = i;
            }
        }

       //printf("%d\n",min);
        if (min_index != -1)
        {
            point = ok_points[min_index];
        }

        //printf("%d,%d",point.X,point.Y);

        free(ok_points);
	    return point;
    }
	return initPoint(-1, -1);   // give up
}


#include "../include/playerbase.h"
#include<math.h>
#include<stdlib.h>
#include <stdio.h>
#include <string.h>
#define maxsize 20
int food_cnt = 0, ghost_cnt = 2, super_food_cnt = 0;
int dir[4][2] = { 0 , 1 , 0 , -1 , 1 , 0 , -1 , 0 };
int n, m;
int vis[100][100];
int food_vis[100][100];
int super_food_vis[100][100];
struct node {
	int x, y, d;
};
void init(struct Player* player) {
	// This function will be executed at the begin of each game, only once.
	player->mat = NULL;
}
int in(int x, int y) {
	return x >= 0 && x < n&& y >= 0 && y < m;
}

struct Point* getNewFood(struct Player* player)
{
	//printf("hh\n");
	struct Point* t = (struct Point*)malloc(sizeof(struct Point));
	for (int i = 0; i < player->row_cnt; i++)
	{
		for (int j = 0; j < player->col_cnt; j++)
		{
			if (food_vis[i][j] == 0 && (player->mat[i][j] == 'o'))
			{
				t->X = i;
				t->Y = j;
				food_vis[i][j] = 1;
				return t;
			}
			food_vis[i][j] = 1;
		}
	}
}

struct Point* getNewSuperFood(struct Player* player)
{
	struct Point* t = (struct Point*)malloc(sizeof(struct Point));
	for (int i = 0; i < player->row_cnt; i++)
	{
		for (int j = 0; j < player->col_cnt; j++)
		{
			if (super_food_vis[i][j] == 0 && (player->mat[i][j] == 'O'))
			{
				t->X = i;
				t->Y = j;
				super_food_vis[i][j] = 1;
				return t;
			}
			super_food_vis[i][j] = 1;
		}
	}
}

void get_num(struct Player* player)
{
	for (int i = 0; i < player->row_cnt; i++)
	{
		for (int j = 0; j < player->col_cnt; j++)
		{
			if (player->mat[i][j] == 'o')
			{
				food_cnt++;
			}
			if (player->mat[i][j] == 'O')
			{
				super_food_cnt++;
			}
		}
	}
}


float chasing_bfs(struct Point* yourPos, struct Point* oppoPos, struct Player* player)
{
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			vis[i][j] = 0;
		}
	}
	int l = 0, r = 0;
	struct node q[3000];
	q[r].x = yourPos->X;
	q[r].y = yourPos->Y;
	q[r].d = 0;
	vis[q[r].x][q[r].y] = 1;
	r++;
	while (l < r)
	{
		struct node now = q[l++];
		if (now.x == oppoPos->X && now.y == oppoPos->Y)
			return now.d;
		for (int i = 0; i < 4; i++)
		{
			int tx = now.x + dir[i][0];
			int ty = now.y + dir[i][1];
			if (in(tx, ty) && player->mat[tx][ty] != '#' && !vis[tx][ty])
			{
				vis[tx][ty] = 1;
				struct node t = { tx,ty,now.d + 1 };
				q[r++] = t;
			}
		}
	}
	return 100000;
}

float evaluate(struct Point* pac, struct Player* player, int status)
{
	for (int i = 0; i < player->row_cnt; i++) {
		for (int j = 0; j < player->col_cnt; j++) {
			food_vis[i][j] = 0;
		}
	}
	for (int i = 0; i < player->row_cnt; i++) {
		for (int j = 0; j < player->col_cnt; j++) {
			super_food_vis[i][j] = 0;
		}
	}
	food_cnt = 0;
	super_food_cnt = 0;
	get_num(player);
	float WEIGHT_FOOD = 10;
	float WEIGHT_GHOST = -10;
	float WEIGHT_SCARED_GHOST = 200;
	float WEIGHT_SUPER_FOOD = 50;
	float score = 0;
	float distancesToFoodList[10000];
	float distancesToSuperFoodList[10];
	float WEIGHT_OPPONENT=0;
	struct Point *opponent=(struct Point *)malloc(sizeof(struct Point));
	opponent->X=player->opponent_posx;
	opponent->Y=player->opponent_posy;
	float distanceToOpponent=chasing_bfs(pac,opponent,player);
	struct Point* ghost[2];
	ghost[0] = (Point*)malloc(sizeof(Point));
	ghost[1] = (Point*)malloc(sizeof(Point));
	for (int i = 0; i < food_cnt; i++)
	{
		struct Point* foodPos = getNewFood(player);
		//printf("i=%d\n",i);
		//printf("P-x=%d P-y=%d\n",foodPos->X,foodPos->Y);
		distancesToFoodList[i] = chasing_bfs(pac, foodPos, player);
	}
	//printf("pac-x=%d pac-y=%d\n",pac->X,pac->Y);
	//printf("score1.0=%d\n",score);
	if (food_cnt > 0)
	{
		float minDistanse = distancesToFoodList[0];
		for (int i = 0; i < food_cnt; i++)
		{
			if (distancesToFoodList[i] < minDistanse)
			{
				minDistanse = distancesToFoodList[i];
			}
		}
		if (minDistanse == 0)
		{
			score += WEIGHT_FOOD * 2;
		}
		else {
			score += WEIGHT_FOOD / minDistanse;
		}
	}
	else
	{
		score += WEIGHT_FOOD;
	}
	//printf("score2.0=%d\n",score);
	for (int i = 0; i < super_food_cnt; i++)
	{
		struct Point* super_foodPos = getNewSuperFood(player);
		distancesToSuperFoodList[i] = chasing_bfs(pac, super_foodPos, player);
	}
	if (super_food_cnt > 0)
	{
		int minDistanse = distancesToSuperFoodList[0];
		for (int i = 0; i < super_food_cnt; i++)
		{
			if (distancesToSuperFoodList[i] < minDistanse)
			{
				minDistanse = distancesToSuperFoodList[i];
			}
		}
		if (minDistanse == 0)
		{
			score += WEIGHT_SUPER_FOOD * 2;
		}
		else
		{
			score += WEIGHT_SUPER_FOOD / minDistanse;
		}
	}
	else
	{
		score += WEIGHT_SUPER_FOOD;
	}
	if(player->your_status>2&&player->your_status<distanceToOpponent&&player->opponent_status==0)
	{
		WEIGHT_OPPONENT=100;
		if(distanceToOpponent>0)
		{
			score+=WEIGHT_OPPONENT/distanceToOpponent;
		}
		else
		{
			return -100000;
		}
	}
	if(player->opponent_status>0&&player->your_status==0&&(player->opponent_status*2)<distanceToOpponent)
	{
		WEIGHT_OPPONENT=-20;
		if(distanceToOpponent>0)
		{
			score+=WEIGHT_OPPONENT/distanceToOpponent;
		}
		else
		{
			return -100000;
		}
	}
	//printf("score3.0=%d\n",score);
	for (int i = 0; i < 2; i++)
	{
		//printf("i=%d\n",i);
		ghost[i]->X = player->ghost_posx[i];
		ghost[i]->Y = player->ghost_posy[i];
		int distance = chasing_bfs(pac, ghost[i], player);
		//printf("distance=%d\n",distance);
		if (distance > 0)
		{
			if(distance==1&&status==0)
			{
				return -100000;
			}
			else if (status > 2)
			{
				score += WEIGHT_SCARED_GHOST / distance;
			}
			else
			{
				score += WEIGHT_GHOST / distance;
			}
		}
		else
		{
			if (status > 0)
				score += WEIGHT_SCARED_GHOST;
			else
				return -100000;
		}
	}
	//printf("score4.0=%d\n",score);
	//printf("hh");
	return score;
}



struct Point walk(struct Player* player) {
	// This function will be executed in each round.
	n = player->row_cnt;
	m = player->col_cnt;
	if (player->mat[player->your_posx][player->your_posy] == 'o')
	{
		player->mat[player->your_posx][player->your_posy] = '.';
	}
	int food_cnt = 0, max = 0, ex = 0, ey = 0;
	for (int i = 0; i < player->row_cnt; i++)
	{
		for (int j = 0; j < player->col_cnt; j++)
		{
			if (player->mat[i][j] == 'o' || player->mat[i][j] == 'O')
			{
				food_cnt++;
			}
		}
	}
	struct Point* ghost[2];
	ghost[0] = (Point*)malloc(sizeof(Point));
	ghost[1] = (Point*)malloc(sizeof(Point));
	ghost[0]->X = player->ghost_posx[0];
	ghost[0]->Y = player->ghost_posy[0];
	ghost[1]->X = player->ghost_posx[1];
	ghost[1]->Y = player->ghost_posy[1];
	for (int i = 0; i < 4; i++)
	{
		int tx = player->your_posx + dir[i][0];
		int ty = player->your_posy + dir[i][1];
		if (!in(tx, ty) || player->mat[tx][ty] == '#')
		{
			continue;
		}
		struct Point* t;
		t = (Point*)malloc(sizeof(Point));
		t->X = tx;
		t->Y = ty;
		//printf("food_cnt=%d \n",food_cnt);
		char temp_char = player->mat[tx][ty];
		float temp = evaluate(t, player, player->your_status);
		player->mat[tx][ty] = temp_char;
		//printf("temp=%d\n",temp);
		if (temp > max)
		{
			max = temp;
			ex = tx;
			ey = ty;
		}
	}
	struct Point ret;
	ret.X = ex;
	ret.Y = ey;
	return ret;
}


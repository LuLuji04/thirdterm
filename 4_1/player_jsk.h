#include<stdio.h>
#include<stdlib.h>
#include<float.h>
#include<string.h>
#include "../include/playerbase.h"

#define max(x, y)  ((x) > (y) ? (x) : (y))
#define min(x, y)  ((x) < (y) ? (x) : (y))
#define maxsize 100

#define foot 3

int in(int x,int y,struct Player *p)
{
	return (x>=0 && x<p->row_cnt && y>=0 && y<p->col_cnt);
}

int dir[5][2] = {{0,1},{1,0},{-1,0},{0,-1},{0,0}};



struct node {
    int x, y, d;
} ;
int bfs_distance(struct Player *player, int start, int end)
{
    int vis[110][110];
    memset(vis,0,sizeof(vis));
    struct node q[10010];
    int l = 0, r = 0;
    int sx,sy;
    int ex,ey;
    switch (start)
    {
    case 0:
        sx = player->your_posx;
        sy = player->your_posy;
        break;

    case 1:
        sx = player->opponent_posx;
        sy = player->opponent_posy;
        break;
    default:
        return -1;
        break;
    }

    switch (end)
    {
    case 1:
        ex = player->ghost_posx[0];
        ey = player->ghost_posy[0];
        break;
    case 2:
        ex = player->ghost_posx[1];
        ey = player->ghost_posy[1];
        break;
    case 5:
        ex = player->opponent_posx;
        ey = player->opponent_posy;
    default:
        break;
    }


    struct node t = {sx, sy, 0};
    q[r++] = t;
    vis[sx][sy] = 1;
    while (l < r) {
        struct node now = q[l++];
        if (now.x == ex && now.y==ey)
        {
            return now.d;
        }
        if(player->mat[now.x][now.y] == 'o' && end==3)
        {
            return now.d;
        }
        if(player->mat[now.x][now.y] == 'O' && end==4)
        {
            return now.d;
        }
        for (int i = 0; i < 4; i++)
        {
            int tx = now.x + dir[i][0];
            int ty = now.y + dir[i][1];
            if (in(tx, ty,player) && player->mat[tx][ty] != '#' && !vis[tx][ty])
            {
                vis[tx][ty] = 1;
                struct node t = {tx, ty, now.d + 1};
                q[r++] = t;
            }
        }
    }
    return -1;
}

int ans = 1e9,vis[110][110];
int h(int x, int y,int ex,int ey) 
{
    return abs(ex - x) + abs(ey - y);
}

void dfs_distance(struct Player *player,int sx, int sy, int ex, int ey,int d)
{
    if (sx == ex && sy == ey)
    {
        ans = min(ans, d);
        return;
    }

    if (d + h(sx, sy, ex, ey) >= ans) 
    {
        return;
    }

    vis[sx][sy] = 1;
    for (int i = 0; i < 4; i++) 
    {
        int tx = sx + dir[i][0];
        int ty = sy + dir[i][1];
        if (in(tx, ty,player) && player->mat[tx][ty] != '#' && !vis[tx][ty]) 
        {
            dfs_distance(player,tx, ty,ex,ey ,d + 1);
        }
    }
    vis[sx][sy] = 0;

}

int init_dfs(struct Player *player,int start, int end)
{
    memset(vis,0,sizeof(vis));
    int sx,sy;
    int ex,ey;
    switch (start)
    {
    case 0:
        sx = player->your_posx;
        sy = player->your_posy;
        break;

    case 1:
        sx = player->opponent_posx;
        sy = player->opponent_posy;
        break;
    default:
        return -1;
        break;
    }

    switch (end)
    {
    case 1:
        ex = player->ghost_posx[0];
        ey = player->ghost_posy[0];
        break;
    case 2:
        ex = player->ghost_posx[1];
        ey = player->ghost_posy[1];
        break;
    case 5:
        ex = player->opponent_posx;
        ey = player->opponent_posy;
        break;
    default:

        break;
    }
    ans=1e9;
    dfs_distance(player,sx,sy,ex,ey,0);
    return ans == 1e9 ? -1 : ans;

}

int manhattan(struct Player *player,int start,int end)
{
    int sx,sy,ex,ey;
    switch (start)
    {
    case 0:
        sx = player->your_posx;
        sy = player->your_posy;
        break;

    case 1:
        sx = player->opponent_posx;
        sy = player->opponent_posy;
        break;
    default:
        return -1;
        break;
    }

    switch (end)
    {
    case 1:
        ex = player->ghost_posx[0];
        ey = player->ghost_posy[0];
        break;
    case 2:
        ex = player->ghost_posx[1];
        ey = player->ghost_posy[1];
        break;
    case 5:
        ex = player->opponent_posx;
        ey = player->opponent_posy;
        break;
    default:

        break;
    }

    return abs(ex - sx) + abs(ey - sy);
}

float evaluate(struct Player *player)
{
    int distance[6];//距离策略
    //0:己方  1：到鬼1  2：到鬼2  3：到普通星  4：到超级星  5：到对方AI 

    distance[1] =foot+ bfs_distance(player,0,1);
    distance[2] =foot+ bfs_distance(player,0,2);
    distance[3] =foot+ bfs_distance(player,0,3);
    distance[4] =foot+ bfs_distance(player,0,4);

    distance[5] =foot+ manhattan(player,0,5);
    //printf("%d",distance[i]);

    float ghost ,star=20 ,superstar=500 ,opponent;
    
        if (player->your_status == 0 && player->opponent_status == 0)
        {
            opponent = 0;
        }
        
        else if (player->your_status > 0 && player->opponent_status == 0)
        {
            opponent = player->opponent_score;
        }

        else if (player->your_status > 0 && player->opponent_status > 0)
        {
            opponent = 0;
        }

        else if (player->your_status >= 0 && player->opponent_status == -1)
        {
            opponent = 0;
        }

        if(player->your_status==0)
        ghost=-500;
        else
        ghost=500;

        if (distance[4] == foot-1)
        {
            superstar = 0;
        }

        if (distance[3] == foot-1)
        {
            star = 0;
        }

        return player->your_score +  star / (distance[3]) + superstar / (distance[4]) + opponent / (distance[5])+(1.0/2)*( 0/(distance[1])+ghost/(distance[2]));
}
    


struct Player *copy_move(struct Player *player,int tx,int ty,int maximizingPlayer)
{
    struct Player *new_player = (struct Player *)malloc(sizeof(struct Player));
    new_player->col_cnt = player->col_cnt;
    new_player->row_cnt = player->row_cnt;

    new_player->mat = (char **)malloc(new_player->row_cnt * sizeof(char *));
    for (int i = 0; i < new_player->row_cnt; i++)
    {
        new_player->mat[i] = (char *)malloc(new_player->col_cnt * sizeof(char));
        for (int j = 0; j < new_player->col_cnt; j++)
        {
            new_player->mat[i][j] = player->mat[i][j];
        }
    }
    new_player->your_posx = player->your_posx;
    new_player->your_posy = player->your_posy;
    new_player->opponent_posx = player->opponent_posx;
    new_player->opponent_posy = player->opponent_posy;
    new_player->ghost_posx[0] = player->ghost_posx[0];
    new_player->ghost_posy[0] = player->ghost_posy[0];
    new_player->ghost_posx[1] = player->ghost_posx[1];
    new_player->ghost_posy[1] = player->ghost_posy[1];

    

    new_player->your_status = player->your_status;
    new_player->opponent_status=player->opponent_status;

    new_player->your_score = player->your_score-1;
    new_player->opponent_score=player->opponent_score-1;

    if(maximizingPlayer==0)
    {
        new_player->your_posx = tx;
        new_player->your_posy = ty;

        if(new_player->your_status>0)
        new_player->your_status--;

        if(new_player->mat[tx][ty]=='o')
        {
            new_player->mat[tx][ty]='.';
        }
        else if(new_player->mat[tx][ty]=='O')
        {
            new_player->mat[tx][ty]='.';
            new_player->your_status=20;
        }

        if(player->your_status > 0&&(tx==player->ghost_posx[0]&&ty==player->ghost_posy[0]||tx==player->ghost_posx[1]&&ty==player->ghost_posy[1]))
        player->your_score = player->your_score+500;
        else if(player->your_status == 0&&(tx==player->ghost_posx[0]&&ty==player->ghost_posy[0]||tx==player->ghost_posx[1]&&ty==player->ghost_posy[1]))
        player->your_score = -1;

    }
    else if(maximizingPlayer==5)
    {
        new_player->opponent_posx = tx;
        new_player->opponent_posy = ty;

        if(new_player->opponent_status>0)
        new_player->opponent_status--;

        if(new_player->mat[tx][ty]=='o')
        {
            new_player->mat[tx][ty]='.';
        }
        else if(new_player->mat[tx][ty]=='O')
        {
            new_player->mat[tx][ty]='.';
            new_player->opponent_status=20;
        }
    }
    else
    {
        new_player->ghost_posx[maximizingPlayer-1] = tx;
        new_player->ghost_posy[maximizingPlayer-1] = ty;
    }
    
    return new_player;
}

void ghost_move(struct Player *player)
{
    for(int maximizingPlayer=1;maximizingPlayer<=2;maximizingPlayer++)
    {

        /*int a=bfs_distance(player,0,maximizingPlayer);
        int b=bfs_distance(player,1,maximizingPlayer);
        int p=a/(a+b);

        if (rand()%1000<=p)*/

        int nowd= bfs_distance(player,0,maximizingPlayer);
        int nowx=player->ghost_posx[maximizingPlayer-1];
        int nowy=player->ghost_posy[maximizingPlayer-1];
        int idx=4;
        
        int tx,ty;

        for (int i = 0; i < 4; i++)
        {                
            tx = nowx + dir[i][0];
            ty = nowy + dir[i][1];
            if (in(tx,ty,player)&&player->mat[tx][ty]!='#')
            {
                player->ghost_posx[maximizingPlayer-1] = tx;
                player->ghost_posy[maximizingPlayer-1] = ty;

                int td=manhattan(player,0,i);

                if(player->your_status==0)
                {
                    if(td<nowd)
                    {
                        nowd=td;
                        idx=i;
                    }
                }
                else
                {
                    if(td>nowd)
                    {
                        nowd=td;
                        idx=i;
                    }
                }
                
            }
        }
        player->ghost_posx[maximizingPlayer-1] = nowx + dir[idx][0];
        player->ghost_posy[maximizingPlayer-1] = nowy + dir[idx][1];
        
        //printf("(%d,%d)\n",player->ghost_posx[maximizingPlayer-1],player->ghost_posy[maximizingPlayer-1]);
    }
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



float alpha_beta(struct Player *player, int depth, float alpha, float beta, int maximizingPlayer)
{
    if(depth==2*foot+1)
    {
        float n=evaluate(player);
        return n;

    }
    
    if (maximizingPlayer==0)
    {
        for (int i = 0; i < 5; i++)
        {
            float score;
            int tx=player->your_posx+dir[i][0];
            int ty=player->your_posy+dir[i][1];
            if (in(tx,ty,player)&&player->mat[tx][ty]!='#')
            {
                /*if(player->mat[tx][ty]=='O')
                score =player->your_score+200/((depth+1)/2);
                else if(player->your_status > 0&&(tx==player->ghost_posx[0]&&ty==player->ghost_posy[0]||tx==player->ghost_posx[1]&&ty==player->ghost_posy[1]))
                score =player->your_score+500/((depth+1)/2);*/
                if(depth==1&&player->your_status == 0&&(tx==player->ghost_posx[0]&&ty==player->ghost_posy[0]||tx==player->ghost_posx[1]&&ty==player->ghost_posy[1]))
                return -FLT_MIN;
                else
                {
                    struct Player *next_player = copy_move(player,tx,ty,maximizingPlayer);
                    score= alpha_beta(next_player, depth + 1, alpha, beta, 0);
                    freePlayer(next_player);
                }
                
                //max_score = max(max_score, score);
                alpha = max(alpha, score);

                if (beta <= alpha)
                {
                    return beta;
                }
            } 
        }
        return alpha;
    }
    else if(maximizingPlayer==5)
    {
        int tx,ty;
        for (int i = 0; i < 5; i++)
        {

            tx=player->opponent_posx + dir[i][0];
            ty=player->opponent_posy + dir[i][1];

            if (in(tx,ty,player)&&player->mat[tx][ty]!='#')
            {
                struct Player *next_player = copy_move(player,tx,ty,maximizingPlayer);
                //ghost_move(next_player);


                float score = alpha_beta(next_player, depth + 1, alpha, beta, 0);
                beta = min(beta, score);

                freePlayer(next_player);

                if (beta <= alpha)
                {
                    return alpha;
                }
            }
        }
        return beta;
        
    }
    /*else
    {
        int tx,ty;
        for (int i = 0; i < 5; i++)
        {
            tx=player->ghost_posx[maximizingPlayer-1] + dir[i][0];
            ty=player->ghost_posy[maximizingPlayer-1] + dir[i][1];
                
            if (in(tx,ty,player)&&player->mat[tx][ty]!='#')
            {
                struct Player *next_player = copy_move(player,tx,ty,maximizingPlayer);
                
                int score;

                if(maximizingPlayer==1)
                score = alpha_beta(next_player, depth, alpha, beta, 2);
                else if(maximizingPlayer==2)
                score = alpha_beta(next_player, depth, alpha, beta, 5);
               
                //min_score = min(min_score, score);

                beta = min(beta, score);

                freePlayer(next_player);

                if (beta <= alpha)
                {
                    return alpha;
                }
            }
        }
        return beta;
    }*/
    
}


struct Point walk(struct Player *player)
{
    float max_score = -FLT_MAX;
    float score = 0;
    struct Point point=initPoint(-1, -1);

    for (int i = 0; i < 5; i++)
    {
        int tx=player->your_posx+dir[i][0];
        int ty=player->your_posy+dir[i][1];
        if (in(tx,ty,player)&&player->mat[tx][ty]!='#')
        {
            /*if(player->mat[tx][ty]=='O')
            score=player->your_score+ 200/1;
            else if(player->your_status > 0&&(tx==player->ghost_posx[0]&&ty==player->ghost_posy[0]||tx==player->ghost_posx[1]&&ty==player->ghost_posy[1]))
            score=player->your_score+ 500/1;*/
            if(player->your_status == 0&&(tx==player->ghost_posx[0]&&ty==player->ghost_posy[0]||tx==player->ghost_posx[1]&&ty==player->ghost_posy[1]))
            score=-FLT_MIN;
            
            else
            {
                struct Player *next_player = copy_move(player,tx,ty,0);
                //output(next_player);
                //printf("\n");
                //output(next_player);
                score = alpha_beta(next_player, 1, -FLT_MAX, FLT_MAX, 0);
                freePlayer(next_player);
            }
            
            //printf("(%d %d):",ok_points[i].X,ok_points[i].Y);
            //printf("*%d\n",score);
            if (score > max_score)
            {
                max_score = score;
                point = initPoint(tx,ty);
            }
            //output(next_player);
            //printf("\n");
            
        }
    }
    return point;
}

void init(struct Player *player) 
{
    return;
}